#include <iostream>
#include <string>

#include "Camera.hpp"
#include "Dielectric.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "ShapeList.hpp"
#include "Sphere.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Shape* RandomScene() {
  std::vector<Shape*> list;
  list.push_back(new Sphere(Vec3f(0, -1000, 0), 1000,
                            new Lambertian(Vec3f(0.5, 0.5, 0.5))));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      float choose = drand48();
      Vec3f center(a + 0.9f * drand48(), 0.2f, b + 0.9f * drand48());
      if ((center - Vec3f(4, 0.2, 0)).Length() > 0.9f) {
        if (choose < 0.8) {
          list.push_back(new Sphere(
              center, 0.2f,
              new Lambertian(Vec3f(drand48() * drand48(), drand48() * drand48(),
                                   drand48() * drand48()))));
        } else if (choose < 0.95) {
          list.push_back(new Sphere(
              center, 0.2f,
              new Metal(Vec3f(0.5f * (1 + drand48()), 0.5f * (1 + drand48()),
                              0.5f * (1 + drand48())),
                        0.5f * drand48())));
        } else {
          list.push_back(new Sphere(center, 0.2f, new Dielectric(1.5)));
        }
      }
    }
  }

  list.push_back(new Sphere(Vec3f(0, 1, 0), 1.0, new Dielectric(1.5)));
  list.push_back(
      new Sphere(Vec3f(-4, 1, 0), 1.0, new Lambertian(Vec3f(0.4, 0.2, 0.1))));
  list.push_back(
      new Sphere(Vec3f(4, 1, 0), 1.0, new Metal(Vec3f(0.7, 0.6, 0.5), 0.0)));

  return new ShapeList(list);
}

Shape* PresetScene() {
  std::vector<Shape*> list;
  list.push_back(new Sphere(Vec3f(0, 0, -1), 0.5f,
                            new Lambertian(Vec3f(0.1f, 0.2f, 0.5f))));
  list.push_back(new Sphere(Vec3f(0, -100.5, -1), 100,
                            new Lambertian(Vec3f(0.8f, 0.8f, 0.0f))));
  list.push_back(new Sphere(Vec3f(1, 0, -1), 0.5f,
                            new Metal(Vec3f(0.8f, 0.6f, 0.2f), 0.0f)));
  list.push_back(new Sphere(Vec3f(-1, 0, -1), 0.5f, new Dielectric(1.5)));
  list.push_back(new Sphere(Vec3f(-1, 0, -1), -0.45f, new Dielectric(1.5)));

  return new ShapeList(list);
}

Vec3f Color(const Ray& r, Shape* world, int depth) {
  HitRecord record;
  if (world->Hit(r, 0.001, MAXFLOAT, record)) {
    Ray scattered;
    Vec3f attenuation;
    if (depth < 50 &&
        record.material->Scatter(r, record, attenuation, scattered)) {
      return attenuation * Color(scattered, world, depth + 1);
    }
    return Vec3f(0, 0, 0);
  }
  // Sky blend
  Vec3f dir = r.Direction().Normalize();
  float t = 0.5f * (dir.y() + 1.0f);
  return Vec3f(1.0f, 1.0f, 1.0f) * (1.0f - t) + Vec3f(0.5f, 0.7f, 1.0f) * t;
}

int main(int argc, char* argv[]) {
  if (argc < 2 ||
      (strcmp(argv[1], "preset") != 0 && strcmp(argv[1], "random") != 0)) {
    std::cout << "Please enter 'preset' or 'random' for scene selection."
              << std::endl;
    return 1;
  }

  Shape* world;
  Vec3f pos;
  float aperture;
  float focus;
  if (strcmp(argv[1], "preset") == 0) {
    world = PresetScene();
    pos = Vec3f(0, 0, 1);
    aperture = 0.3f;
    focus = 2.0f;
  } else {
    world = RandomScene();
    pos = Vec3f(13, 2, 3);
    aperture = 0.1f;
    focus = 10.0f;
  }

  // Default parameters
  int sizeX = 800;
  int sizeY = 600;
  int ns = 100;
  const char* fileOut = "test.png";
  // Command line args
  if (argc > 2) {
    sizeX = std::stoi(argv[2]);
  }
  if (argc > 3) {
    sizeY = std::stoi(argv[3]);
  }
  if (argc > 4) {
    ns = std::stoi(argv[4]);
  }
  if (argc > 5) {
    fileOut = argv[5];
  }

  Camera camera(pos, Vec3f(0, 0, 0), Vec3f(0, 1, 0), 90,
                float(sizeX) / float(sizeY), aperture, focus);

  unsigned char* data = new unsigned char[(sizeX * sizeY) * 3];
  for (int y = 0; y < sizeY; ++y) {
    for (int x = 0; x < sizeX; ++x) {
      Vec3f color(0, 0, 0);
      for (int s = 0; s < ns; ++s) {
        float u = float(x + drand48()) / float(sizeX);
        float v = float((sizeY - y) + drand48()) / float(sizeY);

        Ray r = camera.GetRay(u, v);
        color +=
            Color(r, world, 0);  // 0 for starting ray depth, Color is recursive
      }
      color /= float(ns);
      color = Vec3f(sqrt(color.x()), sqrt(color.y()), sqrt(color.z()));

      int i = (sizeX * y + x) * 3;
      data[i] = (unsigned char)(255.99 * color.x());
      data[i + 1] = (unsigned char)(255.99 * color.y());
      data[i + 2] = (unsigned char)(255.99 * color.z());
    }
  }

  if (stbi_write_png(fileOut, sizeX, sizeY, 3, data,
                     sizeX * sizeof(unsigned char) * 3) == 0) {
    std::cout << "There was an error writing the file " << fileOut << std::endl;
    return 1;
  }

  delete world;
  delete[] data;
  std::cout << "Success!" << std::endl;
}
