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

namespace lj { namespace centipede {

//------------------------------------------------------------------------------
//! Device types
//------------------------------------------------------------------------------
enum class DeviceType {
  CPU,            //!< Run on a CPU using regular code
#ifdef HAVE_CUDA
  CUDA            //!< Run on a GPU using CUDA
#endif
};

//------------------------------------------------------------------------------
// Algorithm types
//------------------------------------------------------------------------------
enum class AlgorithmType {
  Serial,         //!< Use a serial algorithm
  Parallel        //!< Use a parallel algorithm
};

//------------------------------------------------------------------------------
//! Unary function definition
//------------------------------------------------------------------------------
typedef void (*UnaryFunc)(void *, const void *);

} }
