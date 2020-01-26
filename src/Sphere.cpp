#include "Sphere.hpp"

Sphere::Sphere() {}
Sphere::Sphere(Vec3f center, float r, Material* material)
    : center(center), radius(r), material(material) {}
Sphere::~Sphere() {
  // Sphere owns its material
  delete material;
}

bool Sphere::Hit(const Ray& r, float tMin, float tMax,
                 HitRecord& record) const {
  Vec3f oc = r.Origin() - center;
  float a = r.Direction().Dot(r.Direction());
  float b = 2.0f * oc.Dot(r.Direction());
  float c = oc.Dot(oc) - radius * radius;
  float discriminant = b * b - 4.0f * a * c;

  if (discriminant > 0.0f) {
    float tHit = (-b - sqrt(discriminant)) / (2.0f * a);
    if (tHit >= tMax || tHit <= tMin) {
      tHit = (-b + sqrt(discriminant)) / (2.0f * a);
    }

    if (tHit < tMax && tHit > tMin) {
      record.t = tHit;
      record.p = r.PointAt(tHit);
      record.normal = ((record.p - center) / radius).Normalize();
      record.material = material;
      return true;
    }
  }
  return false;
}
