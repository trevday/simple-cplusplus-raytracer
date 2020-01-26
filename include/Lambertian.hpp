#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "Material.hpp"

class Lambertian : public Material {
 public:
  Lambertian(const Vec3f& albedo);
  virtual ~Lambertian() {}

  virtual bool Scatter(const Ray& in, const HitRecord& hit, Vec3f& attenuation,
                       Ray& scattered) const override;

 private:
  Vec3f albedo;
};

#endif
