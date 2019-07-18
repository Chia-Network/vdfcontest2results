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

#ifndef COMPOSER_H
#define COMPOSER_H

#include <algorithm>
#include <array>
#include <cmath>
#include "gmp.h"

#include "ClassGroup.h"

/**
 * @brief The Composer class does compose operation for VDF 
 * repeated squaring algorithm. The implementation is based on NUDUPL
 * algorithm.
 */
class alignas(64) Composer {

public:
  /**
   * @brief Composer - constructs by using reference into cg context.
   */  
  Composer(ClassGroupContext &ctx_) : ctx(ctx_) {
    mpz_init2(D, 4096);
    mpz_init2(L, 4096);
    mpz_init2(G, 4096);
    mpz_init2(Q1, 4096);
    mpz_init2(y, 4096);
    mpz_init2(By, 4096);
    mpz_init2(Dy, 4096);
    mpz_init2(ax, 4096);
    mpz_init2(ay, 4096);
    mpz_init2(bx, 4096);
    mpz_init2(by, 4096);
    mpz_init2(dx, 4096);
    mpz_init2(dy, 4096);
    mpz_init2(t, 4096);
    mpz_init2(x, 4096);
    mpz_init2(q, 4096);
    mpz_init2(r, 4096);
  }

  ~Composer() {
    mpz_clears(D, L, G, Q1, y, By, Dy, ax, ay, bx, by, dx, dy, t, x, q, r, NULL);
  }

  /**
   * @brief init - initializes D and L using given discriminant.
   */  
  inline void init(const mpz_t &discriminant) {
    mpz_set(D, discriminant); // D = dinscriminant
    mpz_abs(L, D);            // L = -D
    mpz_root(L, L, 4);        // L = 4th_root(L) = 4th_root(|D|)
  }

  /**
   * @brief run - does the composition using NUDUPL algorithm.
   */  
  inline void run() {
    mpz_gcdext(G, y, nullptr, ctx.b, ctx.a);

    mpz_divexact(By, ctx.a, G);
    mpz_divexact(Dy, ctx.b, G);

    mpz_mul(bx, y, ctx.c);
    mpz_mod(bx, bx, By);

    mpz_set(by, By);

    if (mpz_cmpabs(by, L) <= 0) {
      mpz_mul(dx, bx, Dy);
      mpz_sub(dx, dx, ctx.c);
      mpz_divexact(dx, dx, By);
      mpz_mul(ctx.a, by, by);
      mpz_mul(ctx.c, bx, bx);
      mpz_add(t, bx, by);
      mpz_mul(t, t, t);
      mpz_sub(ctx.b, ctx.b, t);
      mpz_add(ctx.b, ctx.b, ctx.a);
      mpz_add(ctx.b, ctx.b, ctx.c);
      mpz_mul(t, G, dx);
      mpz_sub(ctx.c, ctx.c, t);
      return;
    }

    mpz_gcdext_partial(y, x, by, bx, q, r, L);

    mpz_neg(x, x);
    if (mpz_sgn(x) > 0) {
      mpz_neg(y, y);
    } else {
      mpz_neg(by, by);
    }

    mpz_mul(ax, G, x);
    mpz_mul(ay, G, y);

    mpz_mul(t, Dy, bx);
    mpz_submul(t, ctx.c, x);
    mpz_divexact(dx, t, By);
    mpz_mul(Q1, y, dx);
    mpz_add(dy, Q1, Dy);
    mpz_add(ctx.b, dy, Q1);
    mpz_mul(ctx.b, ctx.b, G);
    mpz_divexact(dy, dy, x);
    mpz_mul(ctx.a, by, by);
    mpz_mul(ctx.c, bx, bx);
    mpz_add(t, bx, by);
    mpz_submul(ctx.b, t, t);
    mpz_add(ctx.b, ctx.b, ctx.a);
    mpz_add(ctx.b, ctx.b, ctx.c);
    mpz_submul(ctx.a, ay, dy);
    mpz_submul(ctx.c, ax, dx);
  }

private:
  ClassGroupContext &ctx;

  mpz_t D, L;
  mpz_t G, y, By, Dy;
  mpz_t ax, ay;
  mpz_t bx, by;
  mpz_t dx, dy;
  mpz_t t, x, Q1;
  mpz_t q, r;

  inline void mpz_gcdext_partial(mpz_t &co2, mpz_t &co1, mpz_t &r2, mpz_t &r1,
                                 mpz_t &r, mpz_t &q, const mpz_t &L) {
    mpz_set_ui(co2, 0);
    mpz_set_si(co1, -1);

    while (mpz_cmp_ui(r1, 0) && mpz_cmp(r1, L) > 0) {
      unsigned long bits2 = mpz_sizeinbase(r2, 2);
      unsigned long bits1 = mpz_sizeinbase(r1, 2);
      long i = (bits2 > bits1 ? bits2 : bits1) - 64 + 1;
      if (i < 0)
        i = 0;

      mpz_tdiv_q_2exp(r, r2, i);
      long rr2 = mpz_get_si(r);
      mpz_tdiv_q_2exp(r, r1, i);
      long rr1 = mpz_get_si(r);
      mpz_tdiv_q_2exp(r, L, i);
      long bb = mpz_get_si(r);

      long aa2 = 0;
      long aa1 = 1;
      long bb2 = 1;
      long bb1 = 0;

      for (i = 0; rr1 != 0 && rr1 > bb; i++) {
        long qq = rr2 / rr1;

        long t1 = rr2 - qq * rr1;
        long t2 = aa2 - qq * aa1;
        long t3 = bb2 - qq * bb1;

        if (i & 1) {
          if (t1 < -t3 || rr1 - t1 < t2 - aa1)
            break;
        } else {
          if (t1 < -t2 || rr1 - t1 < t3 - bb1)
            break;
        }

        rr2 = rr1;
        rr1 = t1;
        aa2 = aa1;
        aa1 = t2;
        bb2 = bb1;
        bb1 = t3;
      }

      if (i == 0) {
        mpz_fdiv_qr(q, r2, r2, r1);
        mpz_swap(r2, r1);

        mpz_submul(co2, co1, q);
        mpz_swap(co2, co1);
      } else {
        mpz_mul_si(r, r2, bb2);
        if (aa2 >= 0)
          mpz_addmul_ui(r, r1, aa2);
        else
          mpz_submul_ui(r, r1, -aa2);
        mpz_mul_si(r1, r1, aa1);
        if (bb1 >= 0)
          mpz_addmul_ui(r1, r2, bb1);
        else
          mpz_submul_ui(r1, r2, -bb1);
        mpz_set(r2, r);

        mpz_mul_si(r, co2, bb2);
        if (aa2 >= 0)
          mpz_addmul_ui(r, co1, aa2);
        else
          mpz_submul_ui(r, co1, -aa2);
        mpz_mul_si(co1, co1, aa1);
        if (bb1 >= 0)
          mpz_addmul_ui(co1, co2, bb1);
        else
          mpz_submul_ui(co1, co2, -bb1);
        mpz_set(co2, r);

        if (mpz_sgn(r1) < 0) {
          mpz_neg(co1, co1);
          mpz_neg(r1, r1);
        }
        if (mpz_sgn(r2) < 0) {
          mpz_neg(co2, co2);
          mpz_neg(r2, r2);
        }
      }
    }

    if (mpz_sgn(r2) < 0) {
      mpz_neg(co2, co2);
      mpz_neg(co1, co1);
      mpz_neg(r2, r2);
    }
  }
};

#endif // COMPOSER_H
