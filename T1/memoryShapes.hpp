#ifndef MEMORYSHAPES_HPP
#define MEMORYSHAPES_HPP

#include <cmath>
#include <memory>
#include "shape.hpp"
#include "base-types.hpp"

namespace ivlicheva
{
  struct GoldenRatio
  {
    static size_t increased(size_t capacity)
    {
      const double goldenRatio = 1.6180339887;
      return std::ceil(capacity * goldenRatio) + 1;
    }
  };

  template< typename T, typename Strategy >
  std::unique_ptr< T[] > push(std::unique_ptr< T[] >&&, size_t&, size_t&, T&&);
}

template< typename T, typename Strategy = ivlicheva::GoldenRatio >
std::unique_ptr< T[] > ivlicheva::push(std::unique_ptr< T[] >&& array, size_t& size, size_t& capacity, T&& data)
{
  if (size < capacity)
  {
    std::unique_ptr< T[] > arrayNew = std::move(array);
    arrayNew[size++] = std::move(data);
    return arrayNew;
  }
  size_t capacityNew = Strategy::increased(capacity);
  std::unique_ptr< T[] > arrayNew = std::make_unique< T[] >(capacityNew);
  for (size_t i = 0; i < size; ++i)
  {
    arrayNew[i] = std::move(array[i]);
  }
  arrayNew[size++] = std::move(data);
  capacity = capacityNew;
  return arrayNew;
}

#endif
