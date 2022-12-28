#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <utility>
#include <string>
#include <iosfwd>

namespace ivlicheva
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };
  std::ostream& operator<<(std::ostream&, const DataStruct&);
  std::istream& operator>>(std::istream&, DataStruct&);
  bool operator<(const DataStruct&, const DataStruct&);
}

#endif
