#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP

#include "Material.hpp"

class Dielectric : public Material {
 public:
  Dielectric(float r);
  virtual ~Dielectric() {}
  virtual bool Scatter(const Ray& in, const HitRecord& hit, Vec3f& attenuation,
                       Ray& scattered) const override;

 private:
  float refractiveIndex;
};

#endif
