#include "include.h"

#include "parameters.h"

#include "bit_manipulation.h"
#include "double_utility.h"
#include "integer.h"

#include "asm_main.h"

#include "vdf_original.h"

#include "vdf_new.h"

#include "gpu_integer.h"
#include "gpu_integer_divide.h"

#include "gcd_base_continued_fractions.h"
//#include "gcd_base_divide_table.h"
#include "gcd_128.h"
#include "gcd_unsigned.h"

#include "gpu_integer_gcd.h"

#include "asm_types.h"

#include "threading.h"

#include "vdf_fast.h"

#include "vdf_test.h"

bool warn_on_corruption_in_production=false;

//always works
void repeated_square_original(form& f, const integer& D, const integer& L, uint64 iterations) {
    vdf_original::form f_in;
    f_in.a[0]=f.a.impl[0];
    f_in.b[0]=f.b.impl[0];
    f_in.c[0]=f.c.impl[0];

    vdf_original::form f_res=vdf_original::repeated_square(&f_in, iterations);

    mpz_set(f.a.impl, f_res.a);
    mpz_set(f.b.impl, f_res.b);
    mpz_set(f.c.impl, f_res.c);
}

//this is not thread safe; it is only called from the main thread
void repeated_square(form& f, const integer& D, const integer& L, uint64 total_iterations) {
    uint64 num_iterations=0;

    #ifdef VDF_TEST
        uint64 num_calls_fast=0;
        uint64 num_iterations_fast=0;
        uint64 num_iterations_slow=0;
    #endif

    while (num_iterations<total_iterations) {
        uint64 c_checkpoint_interval=checkpoint_interval;

        #ifdef VDF_TEST
            form f_copy;
            form f_copy_3;
            bool f_copy_3_valid=false;
            if (vdf_test_correctness) {
                f_copy=f;
                c_checkpoint_interval=1;

                f_copy_3=f;
                f_copy_3_valid=square_fast_impl(f_copy_3, D, L, num_iterations);
            }
        #endif

        uint64 batch_size=total_iterations-num_iterations;
        if (batch_size>c_checkpoint_interval) {
            batch_size=c_checkpoint_interval;
        }

        #ifdef ENABLE_TRACK_CYCLES
            print( "track cycles enabled; results will be wrong" );
            repeated_square_original(f, D, L, 100); //randomize the a and b values
        #endif

        uint64 actual_iterations=repeated_square_fast(f, D, L, batch_size);

        #ifdef VDF_TEST
            ++num_calls_fast;
            if (actual_iterations!=~uint64(0)) num_iterations_fast+=actual_iterations;
        #endif

        #ifdef ENABLE_TRACK_CYCLES
            print( "track cycles actual iterations", actual_iterations );
            return; //exit the program
        #endif

        if (actual_iterations==~uint64(0)) {
            //corruption; f is unchanged. do the entire batch with the slow algorithm
            repeated_square_original(f, D, L, batch_size);
            actual_iterations=batch_size;

            #ifdef VDF_TEST
                num_iterations_slow+=batch_size;
            #endif

            if (warn_on_corruption_in_production) {
                print( "!!!! corruption detected and corrected !!!!" );
            }
        }

        if (actual_iterations<batch_size) {
            //the fast algorithm terminated prematurely for whatever reason. f is still valid
            //it might terminate prematurely again (e.g. gcd quotient too large), so will do one iteration of the slow algorithm
            //this will also reduce f if the fast algorithm terminated because it was too big
            repeated_square_original(f, D, L, 1);

            #ifdef VDF_TEST
                ++num_iterations_slow;
                if (vdf_test_correctness) {
                    assert(actual_iterations==0);
                    print( "fast vdf terminated prematurely", num_iterations );
                }
            #endif

            ++actual_iterations;
        }

        num_iterations+=actual_iterations;

        #ifdef VDF_TEST
            if (vdf_test_correctness) {
                form f_copy_2=f;
                f_copy_2.reduce();

                repeated_square_original(f_copy, D, L, actual_iterations);
                assert(f_copy==f_copy_2);
            }
        #endif
    }

    #ifdef VDF_TEST
        print( "fast average batch size", double(num_iterations_fast)/double(num_calls_fast) );
        print( "fast iterations per slow iteration", double(num_iterations_fast)/double(num_iterations_slow) );
    #endif

    assert(num_iterations==total_iterations);
}

int main(int argc, char* argv[]) {
    if (getenv( "warn_on_corruption_in_production" )!=nullptr) {
        warn_on_corruption_in_production=true;
    }

    if (is_vdf_test) {
        print( "=== Test mode ===" );
    }

    if (warn_on_corruption_in_production) {
        print( "=== Warn on corruption enabled ===" );
    }

    assert(is_vdf_test); //assertions should be disabled in VDF_MODE==0

    init_gmp();
    allow_integer_constructor=true; //make sure the old gmp allocator isn't used

    set_rounding_mode();
    vdf_original::init();

    integer D(argv[1]);
    int64 num_iterations=from_string<int64>(argv[2]);
    form f=form::generator(D);

    integer L=root(-D, 4);

    repeated_square(f, D, L, uint64(num_iterations));

    f.reduce(); //f is not reduced/normalized all the way for the fast vdf

    cout << f.a.impl << "\n";
    cout << f.b.impl;
    cout.flush();

    #ifdef GENERATE_ASM_TRACKING_DATA
    {
        using namespace asm_code;

        print( "" );

        map<string, double> tracking_data;

        for (int x=0;x<num_asm_tracking_data;++x) {
            if (!asm_tracking_data_comments[x]) {
                continue;
            }

            tracking_data[asm_tracking_data_comments[x]]=asm_tracking_data[x];
        }

        for (auto c : tracking_data) {
            string base_name;
            for (int x=0;x<c.first.size();++x) {
                if (c.first[x] == ' ') {
                    break;
                }
                base_name+=c.first[x];
            }

            auto base_i=tracking_data.find(base_name);
            double base=1;
            if (base_i!=tracking_data.end() && base_i->second!=0) {
                base=base_i->second;
            }

            print(c.first, c.second/base, "                                              ", base);
        }
    }
    #endif
}