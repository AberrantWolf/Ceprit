//
//  Sphere.h
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef Sphere_h
#define Sphere_h

#include "Hitable.h"
#include "Ray.h"
#include "Material.h"

class Sphere : public Hitable {
public:
    Sphere() {}
    Sphere(Vec3 cen, double r, Material* m) : center(cen), radius(r), mat(m) {}
    
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    
private:
    Vec3 center;
    double radius;
    Material* mat;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    Vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = dot(oc, r.direction());
    double c = dot(oc, oc) - radius*radius;
    
    float discriminant = b*b - a*c;
    
    if (discriminant > 0) {
        double temp = (-b - sqrt(discriminant))/a;
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.point = r.point_at_parameter(rec.t);
            rec.normal = (rec.point - center) / radius;
            rec.mat_ptr = mat;
            
            return true;
        }
        temp = (-b + sqrt(discriminant))/a;
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.point = r.point_at_parameter(rec.t);
            rec.normal = (rec.point - center) / radius;
            rec.mat_ptr = mat;
            
            return true;
        }
        
    }
    
    return false;
}

#endif /* Sphere_h */
