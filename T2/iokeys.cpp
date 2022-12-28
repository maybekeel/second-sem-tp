#include "iokeys.hpp"
#include <iostream>
#include <string>
#include "iostructs.hpp"
#include "StreamGuard.hpp"

std::istream& ivlicheva::operator>>(std::istream& in, UllOctIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  StreamGuard guard(in);
  in >> std::oct >> dest.ref;
  return in;
}

std::istream& ivlicheva::operator>>(std::istream& in, RatLspIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimeterIO{'('} >> DelimeterIO{':'} >> DelimeterIO{'N'} >> dest.ref.first;
  in >> DelimeterIO{':'} >> DelimeterIO{'D'} >> dest.ref.second >> DelimeterIO{':'} >> DelimeterIO{')'};
  return in;
}

std::istream& ivlicheva::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimeterIO{'"'}, dest.ref, '"');
}
