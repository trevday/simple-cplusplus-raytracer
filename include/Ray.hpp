#ifndef RAY_HPP
#define RAY_HPP

#include "Vector3.hpp"

class Ray {
 public:
  Ray() {}
  Ray(const Vec3f& a, const Vec3f& b) : A(a), B(b) {}
  Vec3f Origin() const { return A; }
  Vec3f Direction() const { return B; }
  Vec3f PointAt(float t) const { return A + (B * t); }

  Vec3f A;
  Vec3f B;
};

#endif
