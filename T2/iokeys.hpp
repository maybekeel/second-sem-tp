#ifndef IOKEYS_HPP
#define IOKEYS_HPP

#include <utility>
#include <iosfwd>

namespace ivlicheva
{
  struct UllOctIO
  {
    unsigned long long& ref;
  };

  struct RatLspIO
  {
    std::pair< long long, unsigned long long >& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream&, UllOctIO&&);
  std::istream& operator>>(std::istream&, RatLspIO&&);
  std::istream& operator>>(std::istream&, StringIO&&);
}

#endif
