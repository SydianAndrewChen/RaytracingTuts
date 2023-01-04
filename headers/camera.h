#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

class Camera {
    public:
        Camera(
            Point3D lookfrom,
            Point3D lookat,
            vec3 vup,
            double vfov, 
            double aspect_ratio
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            auto w = unit_vector(lookfrom - lookat);
            auto u = unit_vector(cross(vup, w));
            auto v = cross(w, u);

            origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;
        }

        Ray get_ray(double s, double t) const {
            return Ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
        }

    private:
        Point3D origin;
        Point3D lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};
#endif