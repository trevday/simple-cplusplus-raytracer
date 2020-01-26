#include "ShapeList.hpp"

ShapeList::ShapeList() {}
ShapeList::ShapeList(std::vector<Shape*> shapes) : shapes(shapes) {}
ShapeList::~ShapeList() {
  for (auto s : shapes) {
    delete s;
  }
  shapes.clear();
}

bool ShapeList::Hit(const Ray& r, float tMin, float tMax,
                    HitRecord& record) const {
  HitRecord tempRec;
  float closest = tMax;
  bool hitAnything = false;
  for (auto s : shapes) {
    if (s->Hit(r, tMin, closest, tempRec)) {
      hitAnything = true;
      closest = tempRec.t;
      record = tempRec;
    }
  }
  return hitAnything;
}
