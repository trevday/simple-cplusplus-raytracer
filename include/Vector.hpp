#ifndef Vector_hpp
#define Vector_hpp

#include <math.h>

template <unsigned int S, class Type>
class Vector {
 public:
  Vector() {
    for (int i = 0; i < S; ++i) {
      arr[i] = 0;
    }
  }
  Vector(Type* data) {
    for (int i = 0; i < S; ++i) {
      arr[i] = data[i];
    }
  }

  inline Type& operator[](const unsigned int idx) { return arr[idx]; }
  inline const Type& operator[](const unsigned int idx) const {
    return arr[idx];
  }

  inline const Vector<S, Type>& operator+() const { return *this; }
  const Vector<S, Type> operator-() const {
    Type newData[S];
    for (int i = 0; i < S; ++i) {
      newData[i] = -arr[i];
    }
    return Vector<S, Type>(newData);
  }

  Vector<S, Type>& operator+=(const Vector<S, Type>& v2) {
    for (int i = 0; i < S; ++i) {
      arr[i] += v2.arr[i];
    }
    return *this;
  }
  Vector<S, Type>& operator-=(const Vector<S, Type>& v2) {
    for (int i = 0; i < S; ++i) {
      arr[i] -= v2.arr[i];
    }
    return *this;
  }
  Vector<S, Type>& operator*=(const Vector<S, Type>& v2) {
    for (int i = 0; i < S; ++i) {
      arr[i] *= v2.arr[i];
    }
    return *this;
  }
  Vector<S, Type>& operator/=(const Vector<S, Type>& v2) {
    for (int i = 0; i < S; ++i) {
      arr[i] /= v2.arr[i];
    }
    return *this;
  }
  Vector<S, Type>& operator*=(const Type f) {
    for (int i = 0; i < S; ++i) {
      arr[i] *= f;
    }
    return *this;
  }
  Vector<S, Type>& operator/=(const Type f) {
    for (int i = 0; i < S; ++i) {
      arr[i] /= f;
    }
    return *this;
  }

  Vector<S, Type> operator+(const Vector<S, Type>& v2) const {
    Type newData[S];
    for (int i = 0; i < S; ++i) {
      newData[i] = arr[i] + v2.arr[i];
    }
    return Vector<S, Type>(newData);
  }
  Vector<S, Type> operator-(const Vector<S, Type>& v2) const {
    Type newData[S];
    for (int i = 0; i < S; ++i) {
      newData[i] = arr[i] - v2.arr[i];
    }
    return Vector<S, Type>(newData);
  }
  Vector<S, Type> operator*(const Vector<S, Type>& v2) const {
    Type newData[S];
    for (int i = 0; i < S; ++i) {
      newData[i] = arr[i] * v2.arr[i];
    }
    return Vector<S, Type>(newData);
  }
  Vector<S, Type> operator/(const Vector<S, Type>& v2) const {
    Type newData[S];
    for (int i = 0; i < S; ++i) {
      newData[i] = arr[i] / v2.arr[i];
    }
    return Vector<S, Type>(newData);
  }
  Vector<S, Type> operator*(Type f) const {
    Type newData[S];
    for (int i = 0; i < S; ++i) {
      newData[i] = arr[i] * f;
    }
    return Vector<S, Type>(newData);
  }
  Vector<S, Type> operator/(Type f) const {
    Type newData[S];
    for (int i = 0; i < S; ++i) {
      newData[i] = arr[i] / f;
    }
    return Vector<S, Type>(newData);
  }

  inline Type Length() const { return sqrt(SquaredLength()); }
  Type SquaredLength() const {
    Type total = 0;
    for (int i = 0; i < S; ++i) {
      total += (arr[i] * arr[i]);
    }
    return total;
  }

  inline Vector<S, Type> Normalize() const { return (*this) / Length(); }
  void NormalizeInPlace() {
    Type k = 1.0 / Length();
    for (int i = 0; i < S; ++i) {
      arr[i] *= k;
    }
  }

  Type Dot(const Vector<S, Type>& v2) const {
    Type total = 0;
    for (int i = 0; i < S; ++i) {
      total += (arr[i] * v2.arr[i]);
    }
    return total;
  }

 protected:
  Type arr[S];
};

template <unsigned int S, class Type>
inline Vector<S, Type> operator*(Type f, const Vector<S, Type>& v2) {
  return v2 * f;
}

#endif /* Vector_h */
