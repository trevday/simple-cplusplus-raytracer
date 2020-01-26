#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Ray.hpp"

class Material;

struct HitRecord {
  float t;
  Vec3f p;
  Vec3f normal;
  Material* material;
};

class Material {
 public:
  Material() {}
  virtual ~Material() {}

  virtual bool Scatter(const Ray& in, const HitRecord& hit, Vec3f& attenuation,
                       Ray& scattered) const = 0;
};

#endif
