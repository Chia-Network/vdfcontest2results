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

#ifndef CRYPTO3_VDF_COMPUTE_HPP
#define CRYPTO3_VDF_COMPUTE_HPP

namespace nil {
    namespace crypto3 {
        namespace vdf {
            template<typename Vdf, typename InputIterator, typename Integer, typename OutputIterator>
            OutputIterator compute(InputIterator first, InputIterator last, Integer difficulty, OutputIterator out) {

            }

            template<typename Vdf, typename SinglePassRange, typename Integer, typename OutputIterator>
            OutputIterator compute(const SinglePassRange &r, Integer difficulty, OutputIterator out) {

            }

#ifndef CRYPTO3_VDF_FLINT

            template<typename Vdf, typename SinglePassRange, typename Integer, typename OutputRange>
            OutputRange &compute(const SinglePassRange &r, Integer difficulty, OutputRange &out) {

            }

#endif

#ifndef CRYPTO3_VDF_BOOST

            template<typename Vdf, typename NumberType, typename Integer>
            void compute(const NumberType &challenge, Integer difficulty, typename Vdf::template state_type<> &out) {
                Vdf::compute(out, challenge, difficulty);
            }

#else

            template<typename Vdf,
                     typename Backend1, expression_template_option ExpressionTemplates1,
                     typename Backend2, expression_template_option ExpressionTemplates2,
                     typename Integer>
            void compute(const number <Backend1, ExpressionTemplates1> &challenge, Integer difficulty,
                         number <Backend2, ExpressionTemplates2> &out) {
                Vdf::compute(challenge, difficulty, out);
            }

#endif
        }
    }
}

#endif //CRYPTO3_VDF_COMPUTE_HPP
