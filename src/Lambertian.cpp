#include "Lambertian.hpp"

#include "Utils.hpp"

Lambertian::Lambertian(const Vec3f& albedo) : albedo(albedo) {}

bool Lambertian::Scatter(const Ray& in, const HitRecord& hit,
                         Vec3f& attenuation, Ray& scattered) const {
  Vec3f target = hit.p + hit.normal + UnitSphereRandom();
  scattered = Ray(hit.p, target - hit.p);
  attenuation = albedo;
  return true;
}
