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

#pragma once

#include "defs.hh"
#include "algorithms_impl.hh"

#include <stdexcept>

namespace lj { namespace centipede {

//------------------------------------------------------------------------------
//! A collection of algorithms
//------------------------------------------------------------------------------
template<DeviceType device, AlgorithmType algorithm>
struct Algorithms {
  //----------------------------------------------------------------------------
  //! Transform the input vector using the operation and put the result in the
  //! output vector
  //----------------------------------------------------------------------------
  template<template<DeviceType dev> class Operation,
           typename ItemIn, typename ItemOut>
  static void Transform(std::vector<ItemOut>      &output,
                        const std::vector<ItemIn> &input) {
    TransformImpl<device, algorithm>(&output.front(), sizeof(ItemOut),
                                   &input.front(), sizeof(ItemIn),
                                   input.size(), Operation<device>::GetPointer());
  }
};
} }
