//---------------------------------------------------------------------------//
// Copyright (c) 2018-2019 Nil Foundation AG
// Copyright (c) 2018-2019 Mikhail Komarov <nemo@nilfoundation.org>
// Copyright (c) 2018 Chia Network Inc
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//---------------------------------------------------------------------------//

#include <iostream>

#include <nil/crypto3/vdf/chia.hpp>
#include <nil/crypto3/vdf/algorithm/compute.hpp>

using namespace nil::crypto3;

int main(int argc, char *argv[]) {

    typedef typename vdf::chia::state_type<mpz_t> state_type;
    typedef typename state_type::number_type number_type;

    number_type discriminant;
    mpz_init(discriminant);
    mpz_set_str(discriminant, argv[1], 0);

    state_type state;

    vdf::compute<vdf::chia>(discriminant, std::stoi(argv[2]), state);

#ifdef CRYPTO3_VDF_MPIR
    mpz_out_str(stdout, 10, state.form.a);
    fputc('\n',stdout);
    mpz_out_str(stdout, 10, state.form.b);
    fflush(stdout);
#else
    std::cout << state.form.a << std::endl << state.form.b;
    std::cout << std::flush;
#endif
}