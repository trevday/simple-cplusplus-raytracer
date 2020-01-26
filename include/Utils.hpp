#ifndef UTILS_HPP
#define UTILS_HPP

#include "Vector3.hpp"

Vec3f RandomUnitDisk();

Vec3f UnitSphereRandom();

inline Vec3f Reflect(const Vec3f& v, const Vec3f& n) {
  return v - 2 * v.Dot(n) * n;
}

bool Refract(const Vec3f& v, const Vec3f& n, float refractedIndex,
             Vec3f& refracted);

float Schlick(float cosine, float index);

#endif
