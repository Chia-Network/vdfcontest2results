//---------------------------------------------------------------------------//
// Copyright (c) 2018-2019 Nil Foundation AG
// Copyright (c) 2018-2019 Mikhail Komarov <nemo@nilfoundation.org>
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

#ifndef CRYPTO3_VDF_CHIA_HPP
#define CRYPTO3_VDF_CHIA_HPP

#include <nil/crypto3/vdf/detail/chia_functions.hpp>

namespace nil {
    namespace crypto3 {
        namespace vdf {
            class chia {
                typedef detail::chia_functions policy_type;

            public:
#if defined(CRYPTO3_VDF_GMP) || defined(CRYPTO3_VDF_MPIR)

                template<typename T = mpz_t> using state_type = typename policy_type::state_type<T>;

                template<typename T, typename I>
                inline static void compute(state_type<T> &state, const T &d, I itr) {
                    policy_type::discriminant_generator(state, d);

                    mpz_abs(state.L, d);
                    mpz_root(state.L, state.L, 4);

                    for (int i = 0; i < itr; i++) {
                        policy_type::nudupl(state);
                        policy_type::fast_reduce(state);
                    }
                }

#elif defined(CRYPTO3_VDF_FLINT)

                template<typename T = fmpz_t> using state_type = typename policy_type::state_type<T>;

                template<typename T, typename I>
                inline static void compute(state_type<T> &state, const T &d, I itr) {
                    policy_type::discriminant_generator(state, d);

                    fmpz_abs(state.L, d);
                    fmpz_root(state.L, state.L, 4);

                    for (int i = 0; i < itr; i++) {
                        policy_type::nudupl(state);
                        policy_type::fast_reduce(state);
                    }
                }

#elif defined(CRYPTO3_VDF_BOOST)

                template<typename T, typename F> using state_type = typename policy_type::state_type<T, F>;

                template<typename Backend, expression_template_option ExpressionTemplates>
                static binary_quadratic_form<number<Backend, ExpressionTemplates>> compute(
                        const number<Backend, ExpressionTemplates> &discriminant) {

                }

#endif
            };
        }
    }
}

#endif //CRYPTO3_CHIA_HPP
