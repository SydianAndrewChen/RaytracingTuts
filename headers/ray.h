#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    public:
        Ray() {}
        Ray(const Point3D& origin, const vec3& direction, double time = 0.0)
            : orig(origin), dir(direction), tm(time)
        {}

        Point3D origin() const  { return orig; }
        vec3 direction() const { return dir; }
        double time() const { return tm; }
        Point3D at(double t) const {
            return orig + t*dir;
        }

    private:
        Point3D orig;
        vec3 dir;
        double tm;
};

#endif