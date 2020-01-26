#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"

class Sphere : public Shape {
 public:
  Sphere();
  Sphere(Vec3f center, float r, Material* material);
  virtual ~Sphere();

  virtual bool Hit(const Ray& r, float tMin, float tMax,
                   HitRecord& record) const override;

 private:
  Vec3f center;
  float radius;
  Material* material;
};

#endif
