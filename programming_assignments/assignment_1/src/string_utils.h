#pragma once

#include <string>

// Return a lowercase copy of the text.
std::string normalize(std::string text);

// Remove whitespace from the start and end, preserving spaces inside.
std::string trim(std::string text);
