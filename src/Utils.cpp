#include "Utils.hpp"

#include <stdlib.h>

Vec3f RandomUnitDisk() {
  float x = 2.0f * drand48() - 1.0f;
  float y = sqrt(1.0f - x * x);
  return Vec3f(x, y, 0);
}

Vec3f UnitSphereRandom() {
  float azimuth = drand48() * M_PI * 2.0f;
  float y = drand48();
  float sinElevation = sqrt(1.0f - y * y);
  float x = sinElevation * cos(azimuth);
  float z = sinElevation * sin(azimuth);
  return Vec3f(x, y, z);
}

bool Refract(const Vec3f& v, const Vec3f& n, float refractedIndex,
             Vec3f& refracted) {
  Vec3f normalized = v.Normalize();
  float dt = normalized.Dot(n);
  float discriminant = 1.0f - refractedIndex * refractedIndex * (1 - dt * dt);
  if (discriminant > 0) {
    refracted = refractedIndex * (normalized - n * dt) - n * sqrt(discriminant);
    return true;
  }
  return false;
}

float Schlick(float cosine, float index) {
  float r0 = (1 - index) / (1 + index);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}
