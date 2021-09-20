#pragma once
#include <array>
#include <filesystem/serialisation/trivially_copyable.hpp>
#include <fstream>

namespace fs {

    template <size_t size, trivially_copyable T>
    inline std::ifstream& operator>>(std::ifstream& is, std::array<T,size>& obj) {
        is.read(reinterpret_cast<char*>(obj.data()),
                size * sizeof(T));
        return is;
    };

    template <size_t size, trivially_copyable T>
    inline std::ofstream& operator<<(std::ofstream& os, std::array<T,size>& obj) {
        os.write(reinterpret_cast<char*>(obj.data()),
                 size * sizeof(T));
        return os;
    };

}  // namespace fs