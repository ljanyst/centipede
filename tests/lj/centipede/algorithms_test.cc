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

#include <cppunit/extensions/HelperMacros.h>
#include <lj/centipede/algorithms.hh>

#include <random>
#include <vector>
#include <algorithm>
#include <functional>

using namespace lj::centipede;

//------------------------------------------------------------------------------
// Declaration
//------------------------------------------------------------------------------
template<typename Impl>
class AlgorithmsTest: public CppUnit::TestCase
{
  private:
    CPPUNIT_TEST_SUITE(AlgorithmsTest);
      CPPUNIT_TEST(TransformTest);
    CPPUNIT_TEST_SUITE_END();

  public:
    void TransformTest();
};

struct ACS: public Algorithms<DeviceType::CPU, AlgorithmType::Serial> {};
CPPUNIT_TEST_SUITE_REGISTRATION(AlgorithmsTest<ACS>);

#ifdef HAVE_CUDA
  struct ACuP: public Algorithms<DeviceType::CUDA, AlgorithmType::Parallel> {};
  CPPUNIT_TEST_SUITE_REGISTRATION(AlgorithmsTest<ACuP>);
#endif

//------------------------------------------------------------------------------
// Transform
//------------------------------------------------------------------------------
template<typename Impl>
void AlgorithmsTest<Impl>::TransformTest() {
  std::vector<int> rnd_data;
  std::vector<int> rnd_ref;
  std::vector<int> data  = {1, 2, 3, 4, 5};
  std::vector<int> ref   = {13, 14, 15, 16, 17};

  std::random_device                 device;
  std::mt19937                       engine(device());
  std::uniform_int_distribution<int> dist;
  auto gen = std::bind(dist, engine);

  rnd_data.resize(100000);
  std::generate(rnd_data.begin(), rnd_data.end(), gen);

  rnd_ref = rnd_data;
  for(auto &i: rnd_ref)
    i += 12;

  std::vector<int> output(data.size());
  Impl::template Transform<Plus12Int>(output, data);
  CPPUNIT_ASSERT(output == ref);

  output.resize(rnd_data.size());
  Impl::template Transform<Plus12Int>(output, rnd_data);
  CPPUNIT_ASSERT(output == rnd_ref);
}
