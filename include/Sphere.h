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

#include <cmath>

#include "Defines.h"
#include <Util.h>
#include "Ray.h"
#include "Material/Material.h"

void get_sphere_uv(const Vec3& p, real& u, real& v) {
	real phi = atan2(p.z(), p.x());
	real theta = asin(p.y());
	u = 1-(phi + M_PI) / (2*M_PI);
	v = (theta + M_PI/2) / M_PI;
}

class Sphere : public Hitable {
public:
    Sphere() {}
    Sphere(Vec3 cen0, Vec3 cen1, real t0, real t1, real r, Material* m)
    : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat(m) {}
    
    Vec3 center(real time) const;
    
    virtual bool hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const override;
    virtual bool bounding_box(real t0, real t1, AABB& box) const override;
    
private:
    real radius;
    Material* mat;
    
    Vec3 center0, center1;
    real time0, time1;
};

Vec3 Sphere::center(real time) const {
    return center0 + ((time - time0)/(time1 - time0)) * (center1 - center0);
}

bool Sphere::hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const {
    Vec3 oc = r.origin() - center(r.time());
    real a = dot(r.direction(), r.direction());
    real b = dot(oc, r.direction());
    real c = dot(oc, oc) - radius*radius;
    
    float discriminant = b*b - a*c;
    
    if (discriminant > 0) {
        real temp = (-b - sqrt(discriminant))/a;
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.point = r.point_at_parameter(rec.t);
            rec.normal = (rec.point - center(r.time())) / radius;
            rec.mat_ptr = mat;
			get_sphere_uv((rec.point-center(r.time()))/radius, rec.u, rec.v);
            
            return true;
        }
        temp = (-b + sqrt(discriminant))/a;
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.point = r.point_at_parameter(rec.t);
            rec.normal = (rec.point - center(r.time())) / radius;
            rec.mat_ptr = mat;
			get_sphere_uv((rec.point-center(r.time()))/radius, rec.u, rec.v);
            
            return true;
        }
        
    }
    
    return false;
}

bool Sphere::bounding_box(real t0, real t1, AABB &box) const {
    Vec3 r_corner = Vec3(radius, radius, radius);
    AABB bb0 = AABB(center0 - r_corner, center0 + r_corner);
    AABB bb1 = AABB(center1 - r_corner, center1 + r_corner);
    box = surrounding_box(bb0, bb1);
    return true;
}

#endif /* Sphere_h */
