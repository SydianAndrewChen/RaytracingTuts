#include "headers/color.h"
#include "headers/vec3.h"
#include "headers/ray.h"
#include "headers/hittable.h"
#include "headers/hittable_list.h"
#include "headers/sphere.h"
#include "headers/camera.h"
#include "headers/common.h"

#include <iostream>

Color ray_color(const Ray & r, const Hittable & world, int depth){
    HitRecord rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)){
        // Point3D target = rec.p + rec.normal + random_in_unit_sphere();
        // Point3D target = rec.p + rec.normal + random_unit_vector();
        Point3D target = rec.p + rec.normal + random_in_hemisphere(rec.normal);
        return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth-1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const float aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    HittableList world;
    world.add(make_shared<Sphere>(Point3D(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(Point3D(0,-100.5,-1), 100));

    // Camera
    Camera camera;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = camera.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}