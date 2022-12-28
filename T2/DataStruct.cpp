#include "DataStruct.hpp"
#include <iostream>
#include "StreamGuard.hpp"
#include "iokeys.hpp"
#include "iostructs.hpp"

std::ostream& ivlicheva::operator<<(std::ostream& stream, const DataStruct& data)
{
  {
    StreamGuard guard(stream);
    stream << "(:key1 0" << std::oct << data.key1;
  }
  {
    StreamGuard guard(stream);
    stream << ":key2 (:N " <<  data.key2.first << ":D " << data.key2.second << ":)";
  }
  stream << ":key3 \"" << data.key3 << "\":)";
  return stream;
}

std::istream& ivlicheva::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  in >> DelimeterIO{'('} >> DelimeterIO{':'};
  for (int i = 0; i < 3; ++i)
  {
    std::string name = "";
    in >> name;
    if (name == "key1")
    {
      in >> UllOctIO{input.key1};
    }
    else if (name == "key2")
    {
      in >> RatLspIO{input.key2};
    }
    else if (name == "key3")
    {
      in >> StringIO{input.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> DelimeterIO{':'};
  }
  in >> DelimeterIO{')'};
  if (in)
  {
    data = input;
  }
  return in;
}

bool ivlicheva::operator<(const DataStruct& struct1, const DataStruct& struct2)
{
  if (struct1.key1 != struct2.key1)
  {
    return struct1.key1 < struct2.key1;
  }
  if (struct1.key2 != struct2.key2)
  {
    return 1.f * struct1.key2.first / struct1.key2.second < 1.f * struct2.key2.first / struct2.key2.second;
  }
  return struct1.key3.length() < struct2.key3.length();
}
