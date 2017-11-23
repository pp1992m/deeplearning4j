//
// Created by raver119 on 10.11.2017.
//

#include "testlayers.h"
#include <ops/declarable/CustomOperations.h>
#include <NDArray.h>
#include <NDArrayFactory.h>
#include <NativeOps.h>
#include <helpers/BitwiseUtils.h>

using namespace nd4j;
using namespace nd4j::graph;

class BitwiseUtilsTests : public testing::Test {
public:

};

// oviously, this test will fail on big-endian machines, but who cares
TEST_F(BitwiseUtilsTests, Test_Runtime_Endianess_1) {
    bool isBE = BitwiseUtils::isBE();

    ASSERT_FALSE(isBE);
}

TEST_F(BitwiseUtilsTests, Test_ValueBit_1) {
    int idx = BitwiseUtils::valueBit(1);

    ASSERT_EQ(0, idx);
}

TEST_F(BitwiseUtilsTests, Test_ValueBit_2) {
    int idx = BitwiseUtils::valueBit(2);

    ASSERT_EQ(1, idx);
}

TEST_F(BitwiseUtilsTests, Test_ValueBits_1) {
    std::vector<int> expected({1, 1});
    while (expected.size() < 32)
        expected.push_back(0);

    std::vector<int> result = BitwiseUtils::valueBits(3);

    ASSERT_EQ(32, result.size());
    ASSERT_EQ(expected, result);
}

TEST_F(BitwiseUtilsTests, Test_ValueBits_2) {
    int value = 48;
    int flipped = BitwiseUtils::flip_bits(value);

    ASSERT_NE(value, flipped);

    auto o = BitwiseUtils::valueBits(value);
    auto f = BitwiseUtils::valueBits(flipped);

    for (int e = 0; e < o.size(); e++)
        ASSERT_NE(o.at(e), f.at(e));
}