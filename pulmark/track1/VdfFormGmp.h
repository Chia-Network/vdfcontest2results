/**
Copyright (C) 2019 Markku Pulkkinen

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**/

#ifndef VDFFORMGMP_H
#define VDFFORMGMP_H

#include <cassert>
#include <iostream>
#include <x86intrin.h>

#include "ClassGroup.h"
#include "Composer.h"
#include "Reducer.h"

/**
 * @brief The VdfFormGmp class that use GNU MP library for VDF competition.
 */
class alignas(64) VdfFormGmp {

public:
  /**
   * @brief VdfFormGmp - default constructor.
   */
  VdfFormGmp() {
    numBits = 4096;
    init();
  }

  ~VdfFormGmp() { clear(); }

  /**
   * @brief VdfFormGmp - copy constructor.
   */
  VdfFormGmp(const VdfFormGmp &rhs) {
    numBits = rhs.numBits;
    init();
    assign(rhs);
  }

  /**
   * @brief VdfFormGmp - generates classgroup values using given input params.
   * Sets also initial mem alloc size for mpz_t type variables
   */
  VdfFormGmp(uint64_t a_, uint64_t b_, const char *discriminator,
             uint16_t numBits_ = 4096) {
    numBits = numBits_;
    init();
    generate(a_, b_, discriminator);
  }

  /**
   * @brief operator = overload.
   */
  VdfFormGmp &operator=(const VdfFormGmp &rhs) {
    if (&rhs == this)
      return *this;

    numBits = rhs.numBits;
    clear();
    init();
    assign(rhs);
    return *this;
  }

  /**
   * @brief printForm - prints a,b into console output.
   */
  inline void printForm() {
      gmp_printf("%Zd\n%Zd", cg.a, cg.b);
  }

  /**
   * @brief square - does repeated squaring iterations cnt times.
   * @param cnt - iteration counter
   */
  inline void square(const uint64_t &cnt) {

    // prefetch to ensure that data including functors is cached
    _mm_prefetch(this, _MM_HINT_T0);

    // create and init local static structs for fast access,
    // this should play well with cache, all variables needed
    // by algorithm are close to each other.
    static ClassGroupContext t;
    static Reducer reducer(t);
    mpz_set(t.a, cg.a);
    mpz_set(t.b, cg.b);
    mpz_set(t.c, cg.c);
    static Composer composer(t);
    composer.init(cg.d);

    unsigned long long i(cnt);
    while (i--) {
      composer.run();
      reducer.run();
    }

    // copy new values into class group
    mpz_set(cg.a, t.a);
    mpz_set(cg.b, t.b);
    mpz_set(cg.c, t.c);
  }

private:
  ClassGroup cg;
  uint16_t numBits{4096};
  uint8_t fill[62];

  inline void clear() { mpz_clears(cg.a, cg.b, cg.c, cg.d, NULL); }

  inline void assign(const VdfFormGmp &rhs) {
    mpz_set(cg.a, rhs.cg.a);
    mpz_set(cg.b, rhs.cg.b);
    mpz_set(cg.c, rhs.cg.c);
    mpz_set(cg.d, rhs.cg.d);
  }

  inline void init() {
    mpz_init2(cg.a, numBits);
    mpz_init2(cg.b, numBits);
    mpz_init2(cg.c, numBits);
    mpz_init2(cg.d, numBits);
  }

  inline void generate(uint64_t a_, uint64_t b_, const char *discriminator) {
    static ClassGroupContext t(numBits);
    static Reducer reducer(t);
    mpz_set_str(cg.d, discriminator, 0);
    mpz_set_ui(t.a, a_);
    mpz_set_ui(t.b, b_);

    // c = (b * b - d)/4a
    mpz_pow_ui(t.m, t.b, 2);
    mpz_sub(t.m, t.m, cg.d);
    mpz_mul_2exp(t.r, t.a, 2);
    mpz_mdiv(t.c, t.m, t.r);

    // do initial reduction
    reducer.run();

    mpz_set(cg.a, t.a);
    mpz_set(cg.b, t.b);
    mpz_set(cg.c, t.c);
  }
};

#endif // VDFFORMGMP_H
