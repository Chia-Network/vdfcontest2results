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

#ifndef VDFFORMGMPNUDUPL_H
#define VDFFORMGMPNUDUPL_H

#include <cassert>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <array>
#include <cmath>

#include "gmp.h"

// constants utilized in akasnil reducer
namespace {
const int_fast64_t THRESH{1ul << 31};
const int_fast64_t EXP_THRESH{31};
} // namespace

/**
 * @brief The VdfFormGmpNudupl class that use GNU MP library for big integers.
 * and NUDUPL algorithm for repeated squaring.
 */
class alignas(64) VdfFormGmpNudupl {
public:
  /**
   * @brief VdfFormGmpNudupl - default constructor
   */
  VdfFormGmpNudupl(uint16_t numBits = 4096) {
    mpz_init2(a, numBits);
    mpz_init2(b, numBits);
    mpz_init2(c, numBits);
    mpz_init2(g, numBits);

    mpz_init2(x, numBits);
    mpz_init2(y, numBits);
    mpz_init2(s, numBits);
    mpz_init2(t, numBits);

    mpz_init2(By, numBits);
    mpz_init2(Dy, numBits);
    mpz_init2(bx, numBits);
    mpz_init2(dx, numBits);

    mpz_init2(by, numBits);
    mpz_init2(dy, numBits);
    mpz_init2(L, numBits);
    mpz_init2(D, numBits);
    
    mpz_init2(faa, numBits);
    mpz_init2(fab, numBits);
    mpz_init2(fac, numBits);

    mpz_init2(fba, numBits);
    mpz_init2(fbb, numBits);
    mpz_init2(fbc, numBits);

    mpz_init2(fca, numBits);
    mpz_init2(fcb, numBits);
    mpz_init2(fcc, numBits);
  }

  /**
   * @brief VdfFormGmpNudupl - constructs form using given params
   */
  VdfFormGmpNudupl(uint64_t a, uint64_t b, const char *d,
                   uint16_t numBits = 4096)
      : VdfFormGmpNudupl(numBits) {
    generate(a, b, d);
  }

  /**
   * @brief ~VdfFormGmpNudupl - destructor
   */
  ~VdfFormGmpNudupl() {
    mpz_clears(a, b, c, D, L, s, t, g, y, By, Dy, bx, by, dx, dy, x, 
               faa, fab, fac, fba, fbb, fbc, fca, fcb, fcc, nullptr);
  }

  /**
   * @brief square - does repeated squaring
   * @param cnt - iteration count
   */
  inline void square(const uint64_t cnt) {
    uint64_t i(cnt);
    while (i--) {
      nudupl();
      reduce_akasnil();
      // reduce();
      // reduce_antic();
    }
  }

  /**
   * @brief printForm - prints into console output classgroup a,b values.
   */
  inline void printForm() {
    gmp_printf("%Zd\n%Zd", a, b);
  }

private:
  mpz_t a, b, c, g;
  mpz_t By, Dy, bx, dx;
  mpz_t by, dy, L, D;
  mpz_t x, y, s, t;
  mpz_t faa, fab, fac;
  mpz_t fba, fbb, fbc;
  mpz_t fca, fcb, fcc;

  inline void generate(uint64_t a_, uint64_t b_, const char *discriminator) {
    // D = discriminator
    mpz_set_str(D, discriminator, 0);

    // init initial form 'f'
    mpz_set_ui(a, a_);
    mpz_set_ui(b, b_);
    // c = (b * b - d)/4a
    mpz_pow_ui(c, b, 2);
    mpz_sub(c, c, D);
    mpz_mul_2exp(L, a, 2);
    mpz_fdiv_q(c, c, L);

    // L = 4th_root(|D|)
    mpz_abs(L, D);
    mpz_root(L, L, 4);
  }

  inline void nudupl() {
    mpz_gcdext(g, y, nullptr, b, a);
    // mpz_gcdinv(g, y, b, a);
    if (mpz_cmp_ui(g, 1)) {
      mpz_divexact(By, a, g);
      mpz_divexact(Dy, b, g);
    } else {
      mpz_set(By, a);
      mpz_set(Dy, b);
    }
    mpz_mul(bx, y, c);
    mpz_mod(bx, bx, By);
    mpz_set(by, By);

    if (mpz_cmpabs(by, L) <= 0) {

      // ((bx * Dy) - c)/By -> x
      mpz_mul(dx, bx, Dy);
      mpz_sub(dx, dx, c);
      mpz_divexact(x, dx, By);
      // bx^2 -> y
      mpz_pow_ui(y, bx, 2);
      // (bx + by)^2 -> s
      mpz_add(bx, bx, by);
      mpz_pow_ui(s, bx, 2);

      // new a = by^2
      mpz_pow_ui(a, by, 2);

      // new b = b - s + a + y
      mpz_sub(b, b, s);
      mpz_add(b, b, a);
      mpz_add(b, b, y);

      // new c = y - (g * x)
      mpz_mul(s, g, x);
      mpz_sub(c, y, s);
      return;
    }

    mpz_gcdext_partial(y, x, by, bx, s, t, L);
    mpz_neg(x, x);
    if (mpz_sgn(x) > 0) {
      mpz_neg(y, y);
    } else {
      mpz_neg(by, by);
    }

    // ((Dy * bx) - (c * x))/By -> dx
    mpz_mul(t, Dy, bx);
    mpz_submul(t, c, x);
    mpz_divexact(dx, t, By);
    // (y * dx) -> s
    mpz_mul(s, y, dx);
    // (y * dx) + Dy -> dy
    mpz_add(dy, s, Dy);

    // by * by -> a
    mpz_pow_ui(a, by, 2);
    // bx * bx -> c
    mpz_pow_ui(c, bx, 2);

    // new b = g * (dy + s)
    mpz_add(t, dy, s);
    mpz_mul(b, t, g);
    // new b = b - (bx + by)^2
    mpz_add(t, bx, by);
    mpz_submul(b, t, t);
    // new b = b + a + c
    mpz_add(b, b, a);
    mpz_add(b, b, c);

    // new c = c - (g * x * dx)
    mpz_mul(t, g, x);
    mpz_submul(c, t, dx);

    // new a = a - ((g * y) * (dy/x))
    mpz_divexact(t, dy, x);
    mpz_mul(s, g, y);
    mpz_submul(a, s, t);
  }

  inline bool isReduced() {
    if (mpz_cmpabs(a, b) < 0)
      return false;
    if (mpz_cmpabs(c, b) < 0)
      return false;

    int a_c(mpz_cmp(a, c));
    if (a_c > 0) {
      mpz_swap(a, c);
      mpz_neg(b, b);
    } else if (a_c == 0 && mpz_sgn(b) < 0) {
      mpz_neg(b, b);
    }
    return true;
  }

  inline void reduce() {
    while (!isReduced()) {
      // (c + b)/2c == (1 + (b/c))/2 -> s
      mpz_fdiv_q(t, b, c);
      mpz_add_ui(t, t, 1);
      mpz_fdiv_q_2exp(s, t, 1);
      // cs -> t
      mpz_mul(t, c, s);
      // 2cs -> y
      mpz_mul_2exp(y, t, 1);
      // (cs - b) -> t
      mpz_sub(t, t, b);

      // new b = -b + 2cs
      mpz_sub(b, y, b);

      // new a = c, c = a
      mpz_swap(a, c);

      // new c = c + cs^2 - bs ( == c + (s * ( cs - b)))
      mpz_addmul(c, s, t);
    }
  }

  inline void reduce_antic() {
    int done;
    do {
      done = 1;

      if (mpz_cmp(c, a) < 0) {
        mpz_swap(a, c);
        mpz_neg(b, b);

        done = 0;
      }

      if (mpz_cmpabs(b, a) > 0) {
        mpz_add(t, a, a);
        mpz_fdiv_r(b, b, t);
        if (mpz_cmp(b, a) > 0)
          mpz_sub(b, b, t);

        mpz_add(t, t, t);
        mpz_mul(c, b, b);
        mpz_sub(c, c, D);
        mpz_divexact(c, c, t);

        done = 0;
      }
    } while (!done);

    if (mpz_cmpabs(a, b) == 0 || mpz_cmp(a, c) == 0)
      if (mpz_sgn(b) < 0)
        mpz_neg(b, b);
  }

  inline void reduce_akasnil() {
    while (!isReduced()) {
      int_fast64_t aa, bb, cc;
      {
        int_fast64_t a_exp, b_exp, c_exp;
        mpz_get_si_2exp(aa, a_exp, a);
        mpz_get_si_2exp(bb, b_exp, b);
        mpz_get_si_2exp(cc, c_exp, c);
        auto mm = std::minmax({a_exp, b_exp, c_exp});
        if (mm.second - mm.first > EXP_THRESH) {
          reduce();
          continue;
        }
        // Ensure a, b, c are shifted so that a : b : c ratios are same as
        // f.a : f.b : f.c. a, b, c will be used as approximations to f.a,
        // f.b, f.c
        int_fast64_t max_exp(mm.second++); // for safety vs overflow
        aa >>= (max_exp - a_exp);
        bb >>= (max_exp - b_exp);
        cc >>= (max_exp - c_exp);
      }
      {
        int_fast64_t u, v, w, x;
        calc_uvwx(u, v, w, x, aa, bb, cc);
        
        mpz_mul_si(faa, a, u * u);
        mpz_mul_si(fab, b, u * w);
        mpz_mul_si(fac, c, w * w);

        mpz_mul_si(fba, a, u * v << 1);
        mpz_mul_si(fbb, b, u * x + v * w);
        mpz_mul_si(fbc, c, w * x << 1);

        mpz_mul_si(fca, a, v * v);
        mpz_mul_si(fcb, b, v * x);
        mpz_mul_si(fcc, c, x * x);

        mpz_add(a, faa, fab);
        mpz_add(a, a, fac);

        mpz_add(b, fba, fbb);
        mpz_add(b, b, fbc);

        mpz_add(c, fca, fcb);
        mpz_add(c, c, fcc);
      }
    }
  }

  inline void signed_shift(uint64_t op, int64_t shift, int_fast64_t &r) {
    if (shift > 0)
      r = static_cast<int64_t>(op << shift);
    else if (shift <= -64)
      r = 0;
    else
      r = static_cast<int64_t>(op >> (-shift));
  }

  inline void mpz_get_si_2exp(int_fast64_t &r, int_fast64_t &exp,
                              const mpz_t op) {
    // Return an approximation x of the large mpz_t op by an int64_t and the
    // exponent e adjustment. We must have (x * 2^e) / op = constant
    // approximately.
    int_fast64_t size(static_cast<long>(mpz_size(op)));
    uint_fast64_t last(mpz_getlimbn(op, (size - 1)));
    int_fast64_t lg2 = exp = ((63 - __builtin_clzll(last)) + 1);
    signed_shift(last, (63 - exp), r);
    if (size > 1) {
      exp += (size - 1) * 64;
      uint_fast64_t prev(mpz_getlimbn(op, (size - 2)));
      int_fast64_t t;
      signed_shift(prev, -1 - lg2, t);
      r += t;
    }
    if (mpz_sgn(op) < 0)
      r = -r;
  }

  inline void calc_uvwx(int_fast64_t &u, int_fast64_t &v, int_fast64_t &w,
                        int_fast64_t &x, int_fast64_t &a, int_fast64_t &b,
                        int_fast64_t &c) {
    // We must be very careful about overflow in the following steps
    int below_threshold;
    int_fast64_t u_{1}, v_{0}, w_{0}, x_{1};
    int_fast64_t a_, b_, s;
    do {
      u = u_;
      v = v_;
      w = w_;
      x = x_;

      s = static_cast<int_fast64_t>(
              (floorf(b / (static_cast<float>(c))) + 1)) >>
          1;

      a_ = a;
      b_ = b;
      // cs = c * s;

      // a = c
      a = c;
      // b = -b + 2cs
      b = -b + (c * s << 1);
      // c = a + cs^2 - bs
      c = a_ - s * (b_ - c * s);

      u_ = v;
      v_ = -u + s * v;
      w_ = x;
      x_ = -w + s * x;

      // The condition (abs(v_) | abs(x_)) <= THRESH protects against
      // overflow
      below_threshold = (abs(v_) | abs(x_)) <= THRESH ? 1 : 0;
    } while (below_threshold && a > c && c > 0);

    if (below_threshold) {
      u = u_;
      v = v_;
      w = w_;
      x = x_;
    }
  }
  
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

  inline void mpz_gcdinv(mpz_t &d, mpz_t &a, const mpz_t &f, const mpz_t &g) {
    if (mpz_cmp_ui(f, 0) == 0) {
      mpz_set(d, g);
      return;
    }
    if (mpz_fits_ulong_p(f)) {
      unsigned long s;
      unsigned long r;
      r = n_gcdinv(&s, mpz_get_ui(f), mpz_get_ui(g));
      mpz_set_ui(d, r);
      mpz_set_ui(a, s);
      return;
    }
    mpz_gcdext(d, a, nullptr, f, g);
  }

  inline unsigned long n_gcdinv(unsigned long *s, unsigned long x,
                                unsigned long y) {
    long v1, v2, t2;
    unsigned long d, r, quot, rem;

    v1 = 0;
    v2 = 1;
    r = x;
    x = y;

    /* y and x both have top bit set */
    if ((long)(x & r) < 0) {
      d = x - r;
      t2 = v2;
      x = r;
      v2 = v1 - v2;
      v1 = t2;
      r = d;
    }

    /* second value has second msb set */
    while ((long)(r << 1) < 0) {
      d = x - r;
      if (d < r) /* quot = 1 */
      {
        t2 = v2;
        x = r;
        v2 = v1 - v2;
        v1 = t2;
        r = d;
      } else if (d < (r << 1)) /* quot = 2 */
      {
        x = r;
        t2 = v2;
        v2 = v1 - (v2 << 1);
        v1 = t2;
        r = d - x;
      } else /* quot = 3 */
      {
        x = r;
        t2 = v2;
        v2 = v1 - 3 * v2;
        v1 = t2;
        r = d - (x << 1);
      }
    }

    while (r) {
      /* overflow not possible due to top 2 bits of r not being set */
      if (x < (r << 2)) /* if quot < 4 */
      {
        d = x - r;
        if (d < r) /* quot = 1 */
        {
          t2 = v2;
          x = r;
          v2 = v1 - v2;
          v1 = t2;
          r = d;
        } else if (d < (r << 1)) /* quot = 2 */
        {
          x = r;
          t2 = v2;
          v2 = v1 - (v2 << 1);
          v1 = t2;
          r = d - x;
        } else /* quot = 3 */
        {
          x = r;
          t2 = v2;
          v2 = v1 - 3 * v2;
          v1 = t2;
          r = d - (x << 1);
        }
      } else {
        quot = x / r;
        rem = x - r * quot;
        x = r;
        t2 = v2;
        v2 = v1 - quot * v2;
        v1 = t2;
        r = rem;
      }
    }

    if (v1 < 0)
      v1 += y;

    (*s) = v1;

    return x;
  }
};

#endif // VDFFORMGMPNUDUPL_H
