#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    public:
        Ray() {}
        Ray(const Point3D& origin, const vec3& direction)
            : orig(origin), dir(direction)
        {}

        Point3D origin() const  { return orig; }
        vec3 direction() const { return dir; }

        Point3D at(double t) const {
            return orig + t*dir;
        }

    public:
        Point3D orig;
        vec3 dir;
};

#endif