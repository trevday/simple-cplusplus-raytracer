#ifndef SHAPELIST_HPP
#define SHAPELIST_HPP

#include <vector>

#include "Shape.hpp"

class ShapeList : public Shape {
 public:
  ShapeList();
  ShapeList(std::vector<Shape*> shapes);
  virtual ~ShapeList();

  virtual bool Hit(const Ray& r, float tMin, float tMax,
                   HitRecord& record) const override;

 private:
  std::vector<Shape*> shapes;
};

#endif
