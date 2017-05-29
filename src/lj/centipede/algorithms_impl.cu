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

namespace {

//------------------------------------------------------------------------------
// Transformation kernel
//------------------------------------------------------------------------------
__global__ void transform(void *output, const void *input,
                          uint32_t out_elem_size, uint32_t in_elem_size,
                          uint32_t size, lj::centipede::UnaryFunc op) {
  uint32_t idx = threadIdx.x + blockDim.x * blockIdx.x;
  const char *inputI  = (const char *)input;
  char       *outputI = (char *)output;
  if(idx >= size)
    return;

  inputI  += idx*in_elem_size;
  outputI += idx*out_elem_size;
  (*op)(outputI, inputI);
}
}

namespace lj { namespace centipede {

//------------------------------------------------------------------------------
// Transformation
//------------------------------------------------------------------------------
template<>
void TransformImpl<DeviceType::CUDA, AlgorithmType::Parallel>(
  void *output, uint32_t out_elem_size,
  const void *input, uint32_t in_elem_size,
  uint32_t size, UnaryFunc op) {

  void *d_input;
  void *d_output;

  uint32_t input_size  = size*in_elem_size;
  uint32_t output_size = size*out_elem_size;

  auto status = cudaMalloc((void**) &d_input,  input_size);
  if(status != cudaSuccess)
    throw std::runtime_error("Unable to allocate GPU memory for input data");

  status = cudaMalloc((void**) &d_output, output_size);
  if(status != cudaSuccess) {
    cudaFree(d_input);
    throw std::runtime_error("Unable to allocate GPU memory for output data");
  }

  cudaMemcpy(d_input, input, input_size, cudaMemcpyHostToDevice);

  uint32_t blocks = size/1024 + 1;
  transform<<<blocks, 1024>>>(d_output, d_input, out_elem_size, in_elem_size,
                              size, op);

  cudaMemcpy(output, d_output, output_size, cudaMemcpyDeviceToHost);

  cudaFree(d_input);
  cudaFree(d_output);
}

} }
