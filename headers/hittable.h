#ifndef HITTABLE_H
#define HITTABLE_H

#include "common.h"
#include "aabb.h"

class Material;

struct HitRecord {
    Point3D p;
    vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t;

    bool front_face;

    inline void set_face_normal(const Ray & r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual bool bounding_box(double time0, double time1, AABB & output_box) const = 0;
};

#endif