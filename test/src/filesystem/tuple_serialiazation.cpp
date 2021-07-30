#include <gtest/gtest.h>

#include <filesystem/serialisation/tuple_serialization.hpp>

TEST(SERIALIZATION, SIMPLE_TUPLE_SERIALIZATION) {
    using namespace fs;

    // SERRILAZATION
    const auto filepath = "test.bin";

    std::ofstream ofstream(filepath,
                           std::ios_base::binary | std::ios_base::out);

    std::tuple tuple = {8, 'c', 9.5};

    ASSERT_EQ(std::get<0>(tuple), 8);
    ASSERT_EQ(std::get<1>(tuple), 'c');
    ASSERT_EQ(std::get<2>(tuple), 9.5);
    ofstream << tuple;
    ofstream.close();

    std::get<0>(tuple) = 1;
    std::get<1>(tuple) = 'd';
    std::get<2>(tuple) = 1.2;

    ASSERT_EQ(std::get<0>(tuple), 1);
    ASSERT_EQ(std::get<1>(tuple), 'd');
    ASSERT_EQ(std::get<2>(tuple), 1.2);

    // DESERRILAZATION

    std::ifstream ifstream(filepath, std::ios_base::binary | std::ios_base::out
                                         | std::ios_base::in);

    ifstream >> tuple;

    ASSERT_EQ(std::get<0>(tuple), 8);
    ASSERT_EQ(std::get<1>(tuple), 'c');
    ASSERT_EQ(std::get<2>(tuple), 9.5);

    ifstream.close();
}

TEST(SERIALIZATION, VECTOR_TUPLE_SERIALIZATION) {
    using namespace fs;

    // SERRILAZATION
    const auto filepath = "test.bin";

    std::ofstream ofstream(filepath,
                           std::ios_base::binary | std::ios_base::out);

    std::tuple tuple
        = {std::vector<int>{0, 1, 2}, std::vector<char>{'a', 'b', 'c'},
           std::vector<float>{.1f, .2f, .3f}};

    ASSERT_EQ(std::get<0>(tuple).at(0), 0);
    ASSERT_EQ(std::get<1>(tuple).at(0), 'a');
    ASSERT_EQ(std::get<2>(tuple).at(0), .1f);

    ASSERT_EQ(std::get<0>(tuple).size(), 3);
    ASSERT_EQ(std::get<1>(tuple).size(), 3);
    ASSERT_EQ(std::get<2>(tuple).size(), 3);

    ofstream << tuple;

    ofstream.close();

    std::get<0>(tuple).clear();
    std::get<1>(tuple).clear();
    std::get<2>(tuple).clear();

    ASSERT_EQ(std::get<0>(tuple).size(), 0);
    ASSERT_EQ(std::get<1>(tuple).size(), 0);
    ASSERT_EQ(std::get<2>(tuple).size(), 0);

    // DESERRILAZATION

    std::ifstream ifstream(filepath, std::ios_base::binary | std::ios_base::out
                                         | std::ios_base::in);

    ifstream >> tuple;

    ASSERT_EQ(std::get<0>(tuple).at(0), 0);
    ASSERT_EQ(std::get<1>(tuple).at(0), 'a');
    ASSERT_EQ(std::get<2>(tuple).at(0), .1f);

    ASSERT_EQ(std::get<0>(tuple).size(), 3);
    ASSERT_EQ(std::get<1>(tuple).size(), 3);
    ASSERT_EQ(std::get<2>(tuple).size(), 3);

    ifstream.close();
}