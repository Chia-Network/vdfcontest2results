/**
Copyright (C) 2018 Markku Pulkkinen

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

#ifndef VDFFORMANTIC_H
#define VDFFORMANTIC_H

#include <cstdint>
#include <iostream>

#include "ClassGroup.h"
#include "Reducer.h"
#include "antic/qfb.h"
#include "flint2/flint.h"
#include "gmp/gmp.h"

class alignas(64) VdfFormAntic {
public:
  VdfFormAntic(uint16_t numBits = 4096) {
    qfb_init(f);
    fmpz_init(D);
    fmpz_init(L);

    fmpz_init(a1);
    fmpz_init(b1);
    fmpz_init(c1);
    fmpz_init(ca);
    fmpz_init(cb);
    fmpz_init(cc);
    fmpz_init(k);
    fmpz_init(s);
    fmpz_init(t);
    fmpz_init(u2);
    fmpz_init(v1);
    fmpz_init(v2);
    fmpz_init(m2);
    fmpz_init(r1);
    fmpz_init(r2);
    fmpz_init(co1);
    fmpz_init(co2);
    fmpz_init(temp);
    fmpz_init(q);
    fmpz_init(r);
  }

  VdfFormAntic(uint64_t a, uint64_t b, const char *d, uint16_t numBits = 4096)
      : VdfFormAntic(numBits) {
    generate(a, b, d);
  }

  ~VdfFormAntic() {
    qfb_clear(f);
    fmpz_clear(D);
    fmpz_clear(L);

    fmpz_clear(m2);
    fmpz_clear(r1);
    fmpz_clear(r2);
    fmpz_clear(co1);
    fmpz_clear(co2);
    fmpz_clear(temp);
    fmpz_clear(ca);
    fmpz_clear(cb);
    fmpz_clear(cc);
    fmpz_clear(k);
    fmpz_clear(s);
    fmpz_clear(t);
    fmpz_clear(u2);
    fmpz_clear(v2);
    fmpz_clear(a1);
    fmpz_clear(b1);
    fmpz_clear(c1);
    fmpz_clear(q);
    fmpz_clear(r);
  }

  inline void square(const uint64_t cnt) {
    uint64_t i(cnt);
    while (i--) {
      nudupl();
    }
    reduce();
  }

  inline void printForm() {
    fmpz_print(f->a);
    printf("\n");
    fmpz_print(f->b);
    fflush(stdout);
  }

private:
  qfb_t f;
  fmpz_t D, L;
  fmpz_t a1, b1, c1, ca, cb, cc, k, s, t, u2, v1, v2;
  fmpz_t m2, r1, r2, co1, co2, temp;
  fmpz_t q, r;

  /**
   * @brief generate
   * @param a
   * @param b
   * @param discriminator
   */
  inline void generate(uint64_t a, uint64_t b, const char *discriminator) {
    // D = discriminator
    fmpz_set_str(D, discriminator, 0);

    // init initial form 'f'
    fmpz_set_ui(f->a, a);
    fmpz_set_ui(f->b, b);
    // c = (b * b - d)/4a
    fmpz_pow_ui(f->c, f->b, 2);
    fmpz_sub(f->c, f->c, D);
    fmpz_mul_2exp(L, f->a, 2);
    fmpz_fdiv_q(f->c, f->c, L);

    // L = 4th_root(|D|)
    fmpz_abs(L, D);
    fmpz_root(L, L, 4);
  }

  /**
   * @brief nudupl
   */
  inline void nudupl() {
    /* nucomp calculation */

    fmpz_set(a1, f->a);
    fmpz_set(c1, f->c);

    // fmpz_zero(k);

    if (fmpz_cmpabs(b1, a1) == 0) {
      fmpz_set(s, a1);
      fmpz_zero(v2);
    } else if (fmpz_sgn(f->b) < 0) {
      fmpz_neg(b1, f->b);
      // fmpz_gcdinv(s, v2, b1, a1);
      gcdinv(s, v2, b1, a1);
      fmpz_neg(v2, v2);
    } else
      // fmpz_gcdinv(s, v2, f->b, a1);
      gcdinv(s, v2, f->b, a1);

    fmpz_mul(t, v2, c1);
    fmpz_neg(k, t);

    if (!fmpz_is_one(s)) {
      fmpz_fdiv_q(a1, a1, s);
      fmpz_mul(c1, c1, s);
    }

    fmpz_fdiv_r(k, k, a1);

    if (fmpz_cmp(a1, L) < 0) {
      fmpz_mul(t, a1, k);

      fmpz_mul(ca, a1, a1);

      fmpz_mul_2exp(cb, t, 1);
      fmpz_add(cb, cb, f->b);

      fmpz_add(cc, f->b, t);
      fmpz_mul(cc, cc, k);
      fmpz_add(cc, cc, c1);

      fmpz_fdiv_q(cc, cc, a1);
    } else {
      fmpz_set(r2, a1);
      fmpz_set(r1, k);

      // fmpz_xgcd_partial(co2, co1, r2, r1, L);
      xgcd_partial(co2, co1, r2, r1, L);

      fmpz_mul(t, a1, r1);

      fmpz_mul(m2, f->b, r1);
      fmpz_mul(temp, c1, co1);
      fmpz_sub(m2, m2, temp);
      fmpz_tdiv_q(m2, m2, a1);

      fmpz_mul(ca, r1, r1);
      fmpz_mul(temp, co1, m2);
      if (fmpz_sgn(co1) < 0)
        fmpz_sub(ca, ca, temp);
      else
        fmpz_sub(ca, temp, ca);

      fmpz_mul(cb, ca, co2);
      fmpz_sub(cb, t, cb);
      fmpz_mul_2exp(cb, cb, 1);
      fmpz_fdiv_q(cb, cb, co1);
      fmpz_sub(cb, cb, f->b);
      fmpz_mul_2exp(temp, ca, 1);
      fmpz_fdiv_r(cb, cb, temp);

      fmpz_mul(cc, cb, cb);
      fmpz_sub(cc, cc, D);
      fmpz_fdiv_q(cc, cc, ca);
      fmpz_fdiv_q_2exp(cc, cc, 2);

      if (fmpz_sgn(ca) < 0) {
        fmpz_neg(ca, ca);
        fmpz_neg(cc, cc);
      }
    }

    fmpz_set(f->a, ca);
    fmpz_set(f->b, cb);
    fmpz_set(f->c, cc);
  }

  /**
   * @brief reduce
   */
  inline void reduce() {
    int done = 0;

    while (!done) {
      done = 1;

      if (fmpz_cmp(f->c, f->a) < 0) {
        fmpz_swap(f->a, f->c);
        fmpz_neg(f->b, f->b);

        done = 0;
      }

      if (fmpz_cmpabs(f->b, f->a) > 0) {
        fmpz_add(t, f->a, f->a);
        fmpz_fdiv_r(f->b, f->b, t);
        if (fmpz_cmp(f->b, f->a) > 0)
          fmpz_sub(f->b, f->b, t);

        fmpz_add(t, t, t);
        fmpz_mul(f->c, f->b, f->b);
        fmpz_sub(f->c, f->c, D);
        fmpz_divexact(f->c, f->c, t);

        done = 0;
      }
    }

    if (fmpz_cmpabs(f->a, f->b) == 0 || fmpz_cmp(f->a, f->c) == 0)
      if (fmpz_sgn(f->b) < 0)
        fmpz_neg(f->b, f->b);
  }

  /**
   * @brief gcdinv
   * @param d
   * @param a
   * @param f
   * @param g
   */
  inline void gcdinv(fmpz_t d, fmpz_t a, const fmpz_t f, const fmpz_t g) {
    FLINT_ASSERT(fmpz_cmp(f, g) < 0);

    if (fmpz_is_zero(f)) {
      fmpz_set(d, g);
      return;
    }

    if (!COEFF_IS_MPZ(*g)) /* g is small, hence f is small */
    {
      fmpz ff, gg;
      ff = *f;
      gg = *g;

      _fmpz_demote(d);
      _fmpz_demote(a);

      *d = n_gcdinv((mp_limb_t *)a, ff, gg);
    } else /* g is large */
    {
      _fmpz_promote_val(d);
      _fmpz_promote_val(a);

      if (!COEFF_IS_MPZ(*f)) /* u is small */
      {
        mpz_t fptr;

        fptr->_mp_alloc = 1;
        fptr->_mp_size = 1;
        fptr->_mp_d = (mp_limb_t *)f;

        mpz_gcdext(COEFF_TO_PTR(*d), COEFF_TO_PTR(*a), nullptr, fptr,
                   COEFF_TO_PTR(*g));
      } else /* f is large */
      {
        mpz_gcdext(COEFF_TO_PTR(*d), COEFF_TO_PTR(*a), nullptr, COEFF_TO_PTR(*f),
                   COEFF_TO_PTR(*g));
      }

      _fmpz_demote_val(d);
      _fmpz_demote_val(a);
    }
  }

  /**
   * @brief xgcd_partial
   * @param co2
   * @param co1
   * @param r2
   * @param r1
   * @param L
   */
  inline void xgcd_partial(fmpz_t co2, fmpz_t co1, fmpz_t r2, fmpz_t r1,
                           const fmpz_t L) {
    slong aa2, aa1, bb2, bb1, rr1, rr2, qq, bb, t1, t2, t3, i;
    slong bits, bits1, bits2;

    fmpz_zero(co2);
    fmpz_set_si(co1, -1);

    while (!fmpz_is_zero(r1) && fmpz_cmp(r1, L) > 0) {
      bits2 = fmpz_bits(r2);
      bits1 = fmpz_bits(r1);
      bits = FLINT_MAX(bits2, bits1) - FLINT_BITS + 1;
      if (bits < 0)
        bits = 0;

      fmpz_tdiv_q_2exp(r, r2, bits);
      rr2 = fmpz_get_ui(r);
      fmpz_tdiv_q_2exp(r, r1, bits);
      rr1 = fmpz_get_ui(r);
      fmpz_tdiv_q_2exp(r, L, bits);
      bb = fmpz_get_ui(r);

      aa2 = 0;
      aa1 = 1;
      bb2 = 1;
      bb1 = 0;

      for (i = 0; rr1 != 0 && rr1 > bb; i++) {
        qq = rr2 / rr1;

        t1 = rr2 - qq * rr1;
        t2 = aa2 - qq * aa1;
        t3 = bb2 - qq * bb1;

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
        fmpz_fdiv_qr(q, r2, r2, r1);
        fmpz_swap(r2, r1);

        fmpz_submul(co2, co1, q);
        fmpz_swap(co2, co1);
      } else {
        fmpz_mul_si(r, r2, bb2);
        if (aa2 >= 0)
          fmpz_addmul_ui(r, r1, aa2);
        else
          fmpz_submul_ui(r, r1, -aa2);
        fmpz_mul_si(r1, r1, aa1);
        if (bb1 >= 0)
          fmpz_addmul_ui(r1, r2, bb1);
        else
          fmpz_submul_ui(r1, r2, -bb1);
        fmpz_set(r2, r);

        fmpz_mul_si(r, co2, bb2);
        if (aa2 >= 0)
          fmpz_addmul_ui(r, co1, aa2);
        else
          fmpz_submul_ui(r, co1, -aa2);
        fmpz_mul_si(co1, co1, aa1);
        if (bb1 >= 0)
          fmpz_addmul_ui(co1, co2, bb1);
        else
          fmpz_submul_ui(co1, co2, -bb1);
        fmpz_set(co2, r);

        if (fmpz_sgn(r1) < 0) {
          fmpz_neg(co1, co1);
          fmpz_neg(r1, r1);
        }
        if (fmpz_sgn(r2) < 0) {
          fmpz_neg(co2, co2);
          fmpz_neg(r2, r2);
        }
      }
    }

    if (fmpz_sgn(r2) < 0) {
      fmpz_neg(co2, co2);
      fmpz_neg(co1, co1);
      fmpz_neg(r2, r2);
    }
  }
};
#endif // VDFFORMANTIC_H
