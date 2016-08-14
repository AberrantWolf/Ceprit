//
//  Hitable.h
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef Hitable_h
#define Hitable_h

#include "Vec3.h"
#include "Ray.h"
#include "AABB.h"

class Material;

struct HitRecord {
    double t;   //distance along ray
    Vec3 point;
    Vec3 normal;
    Material* mat_ptr;
};

class Hitable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual bool bounding_box(double t0, double t1, AABB& box) const = 0;
};

AABB surrounding_box(AABB box0, AABB box1) {
    Vec3 small(fmin(box0.min().x(), box1.min().x()),
               fmin(box0.min().y(), box1.min().y()),
               fmin(box0.min().z(), box1.min().z()));
    Vec3 big(fmax(box0.max().x(), box1.max().x()),
             fmax(box0.max().y(), box1.max().y()),
             fmax(box0.max().z(), box1.max().z()));
    
    return AABB(small, big);
}

#endif /* Hitable_h */
