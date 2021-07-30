#pragma once
#include <filesystem/serialisation/trivially_copyable.hpp>
#include <filesystem/serializable.hpp>
#include <fstream>
#include <vector>
#include <type_traits>      

namespace fs {

    namespace details {
        template <typename T, typename A>
        void write_size(std::ostream& os, std::vector<T, A>& obj) {
            size_t size = obj.size();
            os.write(reinterpret_cast<char*>(&size), sizeof(size_t));
        }

        template <typename T, typename A>
        void read_size(std::istream& is, std::vector<T, A>& obj) {
            size_t size = 0;
            is.read(reinterpret_cast<char*>(&size), sizeof(size_t));
            obj.resize(size);
        }

        template <typename T, typename A>
        size_t size_of_vector(const std::vector<T, A>& obj) {
            return obj.size() * sizeof(T);
        }


    }  // namespace details

    template <trivially_copyable T, typename A>
    std::ostream& operator<<(std::ostream& os, std::vector<T, A>& obj) {
        details::write_size(os, obj);
        os.write(reinterpret_cast<char*>(obj.data()), details::size_of_vector(obj));
        return os;
    };

    template <serializable T, typename A, typename = std::enable_if_t<!std::trivially_copyable_v<T>>>
    std::ostream& operator<<(std::ostream& os, std::vector<T, A>& obj) {
        details::write_size(os, obj);
        for (size_t i = 0; i < obj.size(); i++) {
            os << obj[i];
        }
        return os;
    };

    template <trivially_copyable T, typename A>
    std::istream& operator>>(std::istream& is, std::vector<T, A>& obj) {
        details::read_size(is, obj);
        if (obj.size() != 0) {
            is.read(reinterpret_cast<char*>(obj.data()), details::size_of_vector(obj));
        }

        return is;
    };

    template <serializable T, typename A, typename = std::enable_if_t<!std::trivially_copyable_v<T>>>
    std::istream& operator>>(std::istream& is, std::vector<T, A>& obj) {
        details::read_size(is, obj);
        if (obj.size() != 0) {
            for (size_t i = 0; i < obj.size(); i++) {
                is >> obj[i];
            }
        }

        return is;
    };

}  // namespace fs
