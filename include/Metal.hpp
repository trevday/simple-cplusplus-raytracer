#ifndef METAL_HPP
#define METAL_HPP

#include "Material.hpp"

class Metal : public Material {
 public:
  Metal(const Vec3f& albedo, float fuzziness);
  virtual ~Metal() {}

  virtual bool Scatter(const Ray& in, const HitRecord& hit, Vec3f& attenuation,
                       Ray& scattered) const override;

 private:
  Vec3f albedo;
  float fuzziness;
};

#endif
