#pragma once
#include <fstream>
#include <concepts>

namespace fs {
    
    template<typename T>
    concept serializable = 
    requires(std::ostream& out, T& t) { out << t; } && 
    requires(std::ifstream& in, T& t) { in >> t; };

}