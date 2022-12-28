#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.hpp"

int main()
{
  using istreamIter_t = std::istream_iterator< ivlicheva::DataStruct >;
  using ostreamIter_t = std::ostream_iterator< ivlicheva::DataStruct >;
  std::vector< ivlicheva::DataStruct > vector;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::copy(istreamIter_t(std::cin), istreamIter_t(), std::back_inserter(vector));
  }
  std::sort(vector.begin(), vector.end());
  std::copy(vector.begin(), vector.end(), ostreamIter_t(std::cout, "\n"));
  return 0;
}
