#ifndef STREAMGUARD_HPP
#define STREAMGUARD_HPP

#include <ios>

namespace ivlicheva
{
  class StreamGuard
  {
    public:
      StreamGuard(std::ios&);
      ~StreamGuard();

    private:
      std::ios& stream_;
      std::streamsize precision_;
      std::ios::fmtflags flags_;
  };
}

#endif
