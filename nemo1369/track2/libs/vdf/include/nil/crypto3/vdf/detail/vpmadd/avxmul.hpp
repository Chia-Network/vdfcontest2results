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

#ifndef CRYPTO3_VDF_BIG_MUL_HPP
#define CRYPTO3_VDF_BIG_MUL_HPP

#include <cstdint>

void mul1024_avx512(uint64_t res[32], uint64_t a[16], uint64_t b[16]);

void mul2048_avx512(uint64_t res[64], uint64_t a[32], uint64_t b[32]);

void mul3072_avx512(uint64_t res[96], uint64_t a[48], uint64_t b[48]);

void mul4096_avx512(uint64_t res[128], uint64_t a[64], uint64_t b[64]);

void mul1024_vpmadd(uint64_t res[32], uint64_t a[16], uint64_t b[16]);

void mul2048_vpmadd(uint64_t res[64], uint64_t a[32], uint64_t b[32]);

void mul3072_vpmadd(uint64_t res[96], uint64_t a[48], uint64_t b[48]);

void mul4096_vpmadd(uint64_t res[128], uint64_t a[64], uint64_t b[64]);

#endif
