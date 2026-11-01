#pragma once

#include <cstddef>
#include <string>

// Remove leading and trailing spaces, tabs, and carriage returns.
inline std::string trim(const std::string& text) {
    const std::string whitespace = " \t\r";
    const std::size_t first = text.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return "";
    }
    const std::size_t last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}
