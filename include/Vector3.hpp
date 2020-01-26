#ifndef Vector3_hpp
#define Vector3_hpp

#include "Vector.hpp"

template <class Type>
class Vector3 : public Vector<3, Type> {
 public:
  Vector3() {}
  Vector3(Type x, Type y, Type z) {
    this->arr[0] = x;
    this->arr[1] = y;
    this->arr[2] = z;
  }
  Vector3(const Vector<3, Type>& other) {
    this->arr[0] = other[0];
    this->arr[1] = other[1];
    this->arr[2] = other[2];
  }

  inline Type x() const { return this->arr[0]; }
  inline Type y() const { return this->arr[1]; }
  inline Type z() const { return this->arr[2]; }

  inline Vector3 Cross(const Vector3& v2) const {
    return Vector3((y() * v2.z()) - (z() * v2.y()),
                   (z() * v2.x()) - (x() * v2.z()),
                   (x() * v2.y()) - (y() * v2.x()));
  }
};

typedef Vector3<float> Vec3f;

#endif
