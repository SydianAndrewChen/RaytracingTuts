#ifndef SPHERE_H
#define SPHERE_H

#include "common.h"
#include "hittable.h"

class Sphere: public Hittable{
public:
    Sphere(){}
    Sphere(Point3D c, double r, shared_ptr<Material> mp):
        center(c), radius(r), mat_ptr(mp){}; 
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    virtual bool bounding_box(double time0, double time1, AABB & output_box) const override;

    Point3D center;
    double radius;    
    shared_ptr<Material> mat_ptr;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const{
    vec3 oc = r.origin() - center;
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
    auto outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool Sphere::bounding_box(double time0, double time1, AABB& output_box) const {
    output_box = AABB(
        center - vec3(radius, radius, radius),
        center + vec3(radius, radius, radius));
    return true;
}

#endif