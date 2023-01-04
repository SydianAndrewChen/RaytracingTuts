#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "common.h"

#include "hittable.h"
class MovingSphere: public Hittable{
public:
    MovingSphere() {};
    MovingSphere(Point3D c0, Point3D c1, double _t0, double _t1, double r, shared_ptr<Material> m):
        center0(c0), center1(c1), time0(_t0), time1(_t1), radius(r), mat_ptr(m){};
    
    virtual bool hit(
        const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool bounding_box(double time0, double time1, AABB & output_box) const override;

    Point3D center(double time) const;

public:
    Point3D center0, center1;
    double radius;
    double time0, time1;
    shared_ptr<Material> mat_ptr;
};

Point3D MovingSphere::center(double time) const {
    return center0 + ((time - time0) / (time1 - time0))*(center1 - center0);
}

bool MovingSphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
    vec3 oc = r.origin() - center(r.time());
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    auto outward_normal = (rec.p - center(r.time())) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool MovingSphere::bounding_box(double _time0, double _time1, AABB& output_box) const {
    AABB box0(
        center(_time0) - vec3(radius, radius, radius),
        center(_time0) + vec3(radius, radius, radius));
    AABB box1(
        center(_time1) - vec3(radius, radius, radius),
        center(_time1) + vec3(radius, radius, radius));
    output_box = surrounding_box(box0, box1);
    return true;
}

#endif