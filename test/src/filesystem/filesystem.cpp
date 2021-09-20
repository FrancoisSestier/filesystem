#include <gtest/gtest.h>

#include <filesystem/filesystem.hpp>

struct trivial_struct {
    int a;
    char b;
    float c;
};

using namespace fs;

void check_data_integrity(std::vector<trivial_struct> &vec) {
    ASSERT_EQ(vec.size(), 3);

    ASSERT_EQ(vec.at(0).a, 1);
    ASSERT_EQ(vec.at(0).b, 'a');
    ASSERT_EQ(vec.at(0).c, .1f);

    ASSERT_EQ(vec.at(1).a, 2);
    ASSERT_EQ(vec.at(1).b, 'b');
    ASSERT_EQ(vec.at(1).c, .2f);

    ASSERT_EQ(vec.at(2).a, 3);
    ASSERT_EQ(vec.at(2).b, 'c');
    ASSERT_EQ(vec.at(2).c, .3f);
}

TEST(FILESYSTEM, WRITE_READ1) {

    {
        std::vector<trivial_struct> vec
            = {{1, 'a', .1f}, {2, 'b', .2f}, {3, 'c', .3f}};

        fs::write("test2.bin", vec);
    }

    auto vec = fs::read<std::vector<trivial_struct>>("test2.bin");

    check_data_integrity(vec);
}

TEST(FILESYSTEM, WRITE_READ_WITH_OFFSET) {

    std::vector<trivial_struct> vec
        = {{1, 'a', .1f}, {2, 'b', .2f}, {3, 'c', .3f}};

    size_t vec_size = sizeof(trivial_struct) * vec.size() + sizeof(size_t);

    fs::write("test3.bin", vec, vec_size);
    fs::write("test3.bin", vec, 0);

    auto vec1
        = fs::read<std::vector<trivial_struct>>("test3.bin", 0);
    auto vec2
        = fs::read<std::vector<trivial_struct>>("test3.bin", vec_size);

    check_data_integrity(vec1);
    check_data_integrity(vec2);
}

TEST(FILESYSTEM, ASYNC) {

    std::vector<trivial_struct> vec
        = {{1, 'a', .1f}, {2, 'b', .2f}, {3, 'c', .3f}};

    size_t vec_size = sizeof(trivial_struct) * vec.size() + sizeof(size_t);

    auto f0 = fs::write_async<std::vector<trivial_struct>>("test_async.bin",std::move(vec));
    f0.wait();
    auto f1 = fs::read_async<std::vector<trivial_struct>>("test_async.bin");
    auto vec1 = f1.get();
    check_data_integrity(vec1);
    //check_data_integrity(vec2);
}

TEST(FILESYSTEM, STRING) {

    std::string str{"i'm a string yes very much"};

    fs::write("atestfile.bin",str);
    std::string str_2 = fs::read<std::string>("atestfile.bin");
    
    ASSERT_EQ(str,str_2);
}