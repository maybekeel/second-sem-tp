#include "ioparse.hpp"
#include <string>
#include <stdexcept>
#include "base-types.hpp"

ivlicheva::point_t ivlicheva::convertStringToPoint(std::string& str)
{
  std::string x = getSubstring(str);
  std::string y = getSubstring(str);
  if (x.empty() || y.empty())
  {
    throw std::logic_error("Incorrect string");
  }
  return point_t{std::stod(x), std::stod(y)};
}

std::string ivlicheva::getSubstring(std::string& str)
{
  size_t n = str.find_first_of(' ', 0);
  std::string word = str.substr(0, n);
  n = (n == str.npos) ? n : n + 1;
  str.erase(0, n);
  return word;
}
