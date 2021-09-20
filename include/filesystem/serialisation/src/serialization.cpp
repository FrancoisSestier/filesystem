#pragma once

#include <filesystem/serialisation/array_serialization.hpp>
#include <filesystem/serialisation/trivially_copyable.hpp>
#include <filesystem/serialisation/tuple_serialization.hpp>
#include <filesystem/serialisation/vector_serialization.hpp>
#include <filesystem/serialisation/trivially_copyable.hpp>
#include <filesystem/serializable.hpp>
#include <fstream>
#include <type_traits>
#include <vector>

namespace fs {

    //////////////////////////////////////////////////////////////
    ///     vector

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
    std::istream& operator>>(std::istream& is, std::vector<T, A>& obj) {
        details::read_size(is, obj);
        if (obj.size() != 0) {
            is.read(reinterpret_cast<char*>(obj.data()),
                    details::size_of_vector(obj));
        }

        return is;
    };

    template <serializable T, typename A,
              typename = std::enable_if_t<!std::is_trivially_copyable_v<T>>>
    std::istream& operator>>(std::istream& is, std::vector<T, A>& obj) {
        details::read_size(is, obj);
        if (obj.size() != 0) {
            for (size_t i = 0; i < obj.size(); i++) {
                is >> obj[i];
            }
        }

        return is;
    };

    template <trivially_copyable T, typename A>
    std::ostream& operator<<(std::ostream& os, std::vector<T, A>& obj) {
        details::write_size(os, obj);
        os.write(reinterpret_cast<char*>(obj.data()),
                 details::size_of_vector(obj));
        return os;
    };

    template <serializable T, typename A,
              typename = std::enable_if_t<!std::is_trivially_copyable_v<T>>>
    std::ostream& operator<<(std::ostream& os, std::vector<T, A>& obj) {
        details::write_size(os, obj);
        for (size_t i = 0; i < obj.size(); i++) {
            os << obj[i];
        }
        return os;
    };

    //////////////////////////////////////////////////////////////
    ///     array

    template <size_t size, trivially_copyable T>
    std::ifstream& operator>>(std::ifstream& is, std::array<T, size>& obj) {
        is.read(reinterpret_cast<char*>(obj.data()), size * sizeof(T));
        return is;
    };

    template <size_t size, trivially_copyable T>
    std::ofstream& operator<<(std::ofstream& os, std::array<T, size>& obj) {
        os.write(reinterpret_cast<char*>(obj.data()), size * sizeof(T));
        return os;
    };

    //////////////////////////////////////////////////////////////
    ///     trivially_copyable

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

    //////////////////////////////////////////////////////////////
    ///     tuple

    template <typename... Ts>
    std::ostream& operator<<(std::ostream& os, std::tuple<Ts...>& tuple) {
        std::apply([&](Ts&... tupleArgs) { ((os << tupleArgs), ...); }, tuple);

        return os;
    };

    template <typename... Ts>
    std::istream& operator>>(std::istream& is, std::tuple<Ts...>& tuple) {
        std::apply([&](Ts&... tupleArgs) { ((is >> tupleArgs), ...); }, tuple);
        return is;
    };

}  // namespace fs
