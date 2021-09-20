#pragma once
#include <filesystem/serialisation/array_serialization.hpp>
#include <filesystem/serialisation/trivially_copyable.hpp>
#include <filesystem/serialisation/vector_serialization.hpp>
#include <fstream>
#include <iostream>
#include <tuple>

namespace fs {

    template <typename... Ts>
    inline std::ostream& operator<<(std::ostream& os, std::tuple<Ts...>& tuple) {
        std::apply([&](Ts&... tupleArgs) { ((os << tupleArgs), ...); }, tuple);

        return os;
    };

    template <typename... Ts>
    inline std::istream& operator>>(std::istream& is, std::tuple<Ts...>& tuple) {
        std::apply([&](Ts&... tupleArgs) { ((is >> tupleArgs), ...); }, tuple);
        return is;
    };

}  // namespace fs