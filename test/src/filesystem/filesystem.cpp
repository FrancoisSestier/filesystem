#pragma once
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
    fs::filesystem filesystem;

    {
        std::vector<trivial_struct> vec
            = {{1, 'a', .1f}, {2, 'b', .2f}, {3, 'c', .3f}};

        filesystem.write("test2.bin", vec);
    }

    auto vec = filesystem.read<std::vector<trivial_struct>>("test2.bin");

    check_data_integrity(vec);
}

TEST(FILESYSTEM, WRITE_READ2) {
    fs::filesystem filesystem;

    std::vector<trivial_struct> vec
        = {{1, 'a', .1f}, {2, 'b', .2f}, {3, 'c', .3f}};

    filesystem.write("test2.bin", vec);

    vec.clear();
    ASSERT_EQ(vec.size(), 0);

    filesystem.read("test2.bin", vec);

    check_data_integrity(vec);
}

TEST(FILESYSTEM, WRITE_READ_WITH_OFFSET) {
    fs::filesystem filesystem;

    std::vector<trivial_struct> vec
        = {{1, 'a', .1f}, {2, 'b', .2f}, {3, 'c', .3f}};

    size_t vec_size = sizeof(trivial_struct) * vec.size() + sizeof(size_t);

    filesystem.write("test3.bin", vec, vec_size);
    filesystem.write("test3.bin", vec, 0);

    auto vec1
        = filesystem.read<std::vector<trivial_struct>>("test3.bin", vec_size);
    auto vec2
        = filesystem.read<std::vector<trivial_struct>>("test2.bin", vec_size);

    check_data_integrity(vec1);
    check_data_integrity(vec2);
}

TEST(FILESYSTEM, ASYNC) {
    fs::filesystem filesystem;

    std::vector<trivial_struct> vec
        = {{1, 'a', .1f}, {2, 'b', .2f}, {3, 'c', .3f}};

    size_t vec_size = sizeof(trivial_struct) * vec.size() + sizeof(size_t);

    auto f0 = filesystem.write_async<std::vector<trivial_struct>>("test_async.bin",std::move(vec));
    f0.wait();
    auto f1 = filesystem.read_async<std::vector<trivial_struct>>("test_async.bin");
    auto vec1 = f1.get();
    check_data_integrity(vec1);
    //check_data_integrity(vec2);
}