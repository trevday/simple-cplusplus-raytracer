#include "Metal.hpp"

#include "Utils.hpp"

Metal::Metal(const Vec3f& albedo, float fuzziness)
    : albedo(albedo), fuzziness(fuzziness) {}

bool Metal::Scatter(const Ray& in, const HitRecord& hit, Vec3f& attenuation,
                    Ray& scattered) const {
  Vec3f reflected = Reflect(in.Direction().Normalize(), hit.normal);
  scattered = Ray(hit.p, reflected + fuzziness * UnitSphereRandom());
  attenuation = albedo;
  return scattered.Direction().Dot(hit.normal) > 0.0f;
}
