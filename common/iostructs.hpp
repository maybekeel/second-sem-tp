#ifndef IOSTRUCTS_HPP
#define IOSTRUCTS_HPP

#include <string>
#include <iosfwd>

namespace ivlicheva
{
  struct DelimeterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream&, DelimeterIO&&);
}

#endif
