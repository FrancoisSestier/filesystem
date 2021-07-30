#include <gtest/gtest.h>

#include <filesystem/serialisation/vector_serialization.hpp>

TEST(SERIALIZATION, VECTOR_SERIALIZATION) {
    using namespace fs;

    // SERRILAZATION
    const auto filepath = "test.bin";

    std::ofstream ofstream(filepath,
                           std::ios_base::binary | std::ios_base::out);

    std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ofstream << vec;
    ofstream.close();

    vec.clear();

    ASSERT_EQ(vec.size(), 0);
    
    // DESERRILAZATION

    std::ifstream ifstream(filepath, std::ios_base::binary | std::ios_base::out
                                         | std::ios_base::in);

    std::fill(vec.begin(), vec.end(), 0);

    ifstream >> vec;

    ASSERT_EQ(vec.size(), 10);

    ASSERT_EQ(vec.at(0), 0);
    ASSERT_EQ(vec.at(9), 9);

    ASSERT_EQ(vec.at(2), 2);

    ifstream.close();
}