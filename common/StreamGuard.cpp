#include "StreamGuard.hpp"

ivlicheva::StreamGuard::StreamGuard(std::ios& stream):
  stream_(stream),
  precision_(stream.precision()),
  flags_(stream.flags())
{}

ivlicheva::StreamGuard::~StreamGuard()
{
  stream_.precision(precision_);
  stream_.flags(flags_);
}
