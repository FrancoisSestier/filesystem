#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <filesystem/serialisation/array_serialization.hpp>
#include <fstream>

TEST(SERIALIZATION, ARRAY_SERIALIZATION) {
    using namespace fs;

    // SERRILAZATION
    const auto filepath = "test.bin";

    std::ofstream ofstream(filepath,
                           std::ios_base::binary | std::ios_base::out);

    std::array<int, 10> arr;

    std::fill(arr.begin(), arr.end(), 50);

    std::for_each(arr.begin(), arr.end(),
                  [](const int& i) { ASSERT_EQ(i, 50); });

    ofstream << arr;
    ofstream.close();

    // DESERRILAZATION

    std::ifstream ifstream(filepath, std::ios_base::binary | std::ios_base::out
                                         | std::ios_base::in);

    std::fill(arr.begin(), arr.end(), 0);

    std::for_each(arr.begin(), arr.end(),
                  [](const int& i) { ASSERT_EQ(i, 0); });
    ifstream >> arr;

    std::for_each(arr.begin(), arr.end(),
                  [](const int& i) { ASSERT_EQ(i, 50); });

    ifstream.close();
}