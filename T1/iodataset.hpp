#ifndef IODATASET_HPP
#define IODATASET_HPP

#include <memory>
#include <string>
#include <iosfwd>
#include "shape.hpp"
#include "base-types.hpp"

namespace ivlicheva
{
   using shapesArray_t = std::unique_ptr< std::unique_ptr< ivlicheva::Shape >[] >;
   using pointsArray_t = std::unique_ptr< point_t[] >;
   void outShapes(shapesArray_t&, size_t, std::ostream&);
   double calculateShapesArea(const shapesArray_t&, size_t);
}

#endif
