//------------------------------------------------------------------------------
// Copyright (c) 2017 by Lukasz Janyst <lukasz@jany.st>
//------------------------------------------------------------------------------
// This file is part of the Centipede software suite.
//
// Centipede is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Centipede is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Centipede.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include "operators.hh"

using namespace lj::centipede;

template<>
__device__ void Plus12Int<DeviceType::CUDA>
  ::Op(void *result, const void *input) {
  *(int *)result = *(int *)input + 12;
}

namespace {
__device__ UnaryFunc ptr = Plus12Int<DeviceType::CUDA>::Op;
}

template<>
UnaryFunc Plus12Int<DeviceType::CUDA>::GetPointer() {
  UnaryFunc h_ptr;
  cudaMemcpyFromSymbol(&h_ptr, ptr, sizeof(UnaryFunc));
  return h_ptr;
};
