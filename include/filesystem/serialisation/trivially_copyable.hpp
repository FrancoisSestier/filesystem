#pragma once
#include "fstream"

namespace fs {

    template <typename T>
    concept trivially_copyable = std::is_trivially_copyable_v<T>;

    template <trivially_copyable T>
    std::ifstream& operator>>(std::ifstream& is, T& obj) {
        is.read(reinterpret_cast<char*>(obj.data()), sizeof(T));
        return is;
    };

    template <trivially_copyable T>
    std::ofstream& operator<<(std::ofstream& os, T& obj) {
        os.write(reinterpret_cast<char*>(obj.data()), sizeof(T));
        return os;
    };

}  // namespace fs
