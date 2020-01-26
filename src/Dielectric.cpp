#include "Dielectric.hpp"

#include <iostream>
#include "Utils.hpp"

Dielectric::Dielectric(float r) : refractiveIndex(r) {}

bool Dielectric::Scatter(const Ray& in, const HitRecord& hit,
                         Vec3f& attenuation, Ray& scattered) const {
  attenuation = Vec3f(1.0, 1.0, 1.0);

  float normalDot = in.Direction().Dot(hit.normal);

  float index;
  Vec3f outwardNormal;
  float reflectionProb;
  float cosine;

  if (normalDot > 0.0f) {
    outwardNormal = -hit.normal;
    index = refractiveIndex;
    cosine = normalDot / in.Direction().Length();
    cosine =
        sqrt(1 - refractiveIndex * refractiveIndex * (1 - cosine * cosine));
  } else {
    outwardNormal = hit.normal;
    index = 1.0f / refractiveIndex;
    cosine = -normalDot / in.Direction().Length();
  }

  Vec3f refracted;
  if (Refract(in.Direction(), outwardNormal, index, refracted)) {
    reflectionProb = Schlick(cosine, refractiveIndex);
  } else {
    reflectionProb = 1.0f;
  }

  if (drand48() < reflectionProb) {
    scattered = Ray(hit.p, Reflect(in.Direction(), hit.normal));
  } else {
    scattered = Ray(hit.p, refracted);
  }
  return true;
}
