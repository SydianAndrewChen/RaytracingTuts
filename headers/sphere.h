#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"


class Sphere: public Hittable{
public:
    Sphere(){}
    Sphere(Point3D && _center, double r):center(_center), radius(r){}; 
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    
    Point3D center;
    double radius;    

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
    rec.normal = (rec.p - center) / radius;
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}

#endif