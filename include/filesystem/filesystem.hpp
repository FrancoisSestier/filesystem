#pragma once
#include <filesystem/serialisation/array_serialization.hpp>
#include <filesystem/serialisation/trivially_copyable.hpp>
#include <filesystem/serialisation/tuple_serialization.hpp>
#include <filesystem/serialisation/vector_serialization.hpp>
#include <filesystem/serializable.hpp>
#include <filesystem>
#include <fstream>
#include <future>
#include <mutex>
namespace fs {

    namespace internal {

        inline static std::mutex mutex;

        template <typename T>
        inline void write_(const std::string& filepath, T&& data,
                           size_t offset = 0) {
            const std::lock_guard<std::mutex> lock(internal::mutex);
            write<T>(filepath, data, offset);
        }

        template <typename T>
        inline T read_(const std::string& filepath, size_t offset = 0) {
            const std::lock_guard<std::mutex> lock(internal::mutex);
            return read<T>(filepath, offset);
        }

    }  // namespace internal

    template <typename T>
    inline void read(const std::string& filepath, T& data, size_t offset = 0) {
        std::ifstream ifs(filepath, std::ios_base::binary | std::ios_base::out
                                        | std::ios_base::in);
        if (ifs.is_open()) {
            ifs.seekg(offset, std::ios_base::beg);
            ifs >> data;
            ifs.close();
        }
    }

    template <typename T>
    T read(const std::string& filepath, size_t offset = 0) {
        std::ifstream ifs(filepath, std::ios_base::binary | std::ios_base::out
                                        | std::ios_base::in);
        T data;
        if (ifs.is_open()) {
            ifs.seekg(offset, std::ios_base::beg);
            ifs >> data;
            ifs.close();
        }
        return data;
    }

    template <typename T>
    void write(const std::string& filepath, T& data, size_t offset = 0) {
        if (!std::filesystem::exists(filepath)) {
            std::ofstream ofs(filepath, std::ios_base::out);
            ofs.close();
        }

        std::ofstream ofs(filepath, std::ios_base::binary | std::ios_base::in
                                        | std::ios_base::out);
        if (ofs.is_open()) {
            ofs.seekp(offset, std::ios_base::beg);
            ofs << data;
            ofs.close();
        }
    }

    template <>
    std::string read<std::string>(const std::string& filepath, size_t offset) {
        std::filesystem::path f_path{filepath};
        std::string str;

        if (std::filesystem::exists(f_path)) {
            std::ifstream ifs(filepath, std::ios_base::binary
                            
                                            | std::ios_base::in);
            size_t size = std::filesystem::file_size(f_path);
            str.resize(size, '\0');
            ifs.read(&str[0], size);
            ifs.close();
        }
        return str;
    }

    template <>
    void write<std::string>(const std::string& filepath, std::string& data,
                            size_t offset) {
        std::filesystem::path f_path{filepath};

        std::ofstream ofs(filepath.c_str(),
                          std::fstream::out | std::fstream::binary);

        ofs.write(&data[0], data.length());
        ofs.close();
    }

    template <typename T>
    auto read_async(const std::string& filepath, size_t offset = 0) {
        return std::async(std::launch::async, &internal::read_<T>, filepath,
                          offset);
    }

    template <typename T>
    auto write_async(const std::string& filepath, T&& data, size_t offset = 0) {
        return std::async(std::launch::async, &internal::write_<T>, filepath,
                          std::move(data), offset);
    }

}  // namespace fs