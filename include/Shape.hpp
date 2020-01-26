#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Material.hpp"

class Shape {
 public:
  Shape() {}
  virtual ~Shape() {}

  virtual bool Hit(const Ray& r, float tMin, float tMax,
                   HitRecord& record) const = 0;
};

#endif
