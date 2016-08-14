//
//  Sphere.h
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

// TODO: Move the center function to a transform/animatable position class on Hitable rather than hardcoded in Sphere

#ifndef Sphere_h
#define Sphere_h

#include "Hitable.h"
#include "Ray.h"
#include "Material.h"

class Sphere : public Hitable {
public:
    Sphere() {}
    Sphere(Vec3 cen0, Vec3 cen1, double t0, double t1, double r, Material* m)
    : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat(m) {}
    
    Vec3 center(double time) const;
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    
private:
    double radius;
    Material* mat;
    
    Vec3 center0, center1;
    double time0, time1;
};

Vec3 Sphere::center(double time) const {
    return center0 + ((time - time1)/(time1 - time0)) * (center1 - center0);
}

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    Vec3 oc = r.origin() - center(r.time());
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius*radius;
    
    float discriminant = b*b - a*c;
    
    if (discriminant > 0) {
        double temp = (-b - sqrt(discriminant))/a;
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.point = r.point_at_parameter(rec.t);
            rec.normal = (rec.point - center(r.time())) / radius;
            rec.mat_ptr = mat;
            
            return true;
        }
        temp = (-b + sqrt(discriminant))/a;
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.point = r.point_at_parameter(rec.t);
            rec.normal = (rec.point - center(r.time())) / radius;
            rec.mat_ptr = mat;
            
            return true;
        }
        
    }
    
    return false;
}

#endif /* Sphere_h */
