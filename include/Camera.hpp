#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Ray.hpp"
#include "Utils.hpp"

class Camera {
 public:
  Camera(Vec3f pos, Vec3f lookAt, Vec3f up, float verticalFOV, float aspect,
         float aperture, float focusDist) {  // verticalFOV is in degrees
    float theta = verticalFOV * M_PI / 180.0;
    float halfHeight = tan(theta / 2.0);
    float halfWidth = aspect * halfHeight;

    origin = pos;
    w = (pos - lookAt).Normalize();
    u = up.Cross(w).Normalize();
    v = w.Cross(u);

    lowerLeftCorner = pos - (halfWidth * focusDist * u) -
                      (halfHeight * focusDist * v) - (w * focusDist);
    horizontal = 2.0f * halfWidth * focusDist * u;
    vertical = 2.0f * halfHeight * focusDist * v;

    lensRadius = aperture / 2.0;
  }

  Ray GetRay(float s, float t) const {
    Vec3f rayDisk = lensRadius * RandomUnitDisk();
    Vec3f offset = u * rayDisk.x() + v * rayDisk.y();
    return Ray(origin + offset, lowerLeftCorner + (horizontal * s) +
                                    (vertical * t) - origin - offset);
  }

 private:
  Vec3f origin;
  Vec3f lowerLeftCorner;
  Vec3f horizontal;
  Vec3f vertical;
  Vec3f u;
  Vec3f v;
  Vec3f w;
  float lensRadius;
};

#endif
