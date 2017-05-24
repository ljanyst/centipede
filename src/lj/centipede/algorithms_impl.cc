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

#include "algorithms_impl.hh"
#include "defs.hh"

namespace lj { namespace centipede {

template<>
void TransformImpl<DeviceType::CPU, AlgorithmType::Serial>(
  void *output, uint32_t out_elem_size,
  const void *input, uint32_t in_elem_size,
  uint32_t size, UnaryFunc op) {

  const char *inputI  = (const char *)input;
  char       *outputI = (char *)output;
  for(uint32_t i = 0; i < size; ++i) {
    op(outputI, inputI);
    outputI += out_elem_size;
    inputI  += in_elem_size;
  }
}
} }
