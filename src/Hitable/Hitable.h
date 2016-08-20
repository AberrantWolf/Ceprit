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
	double u, v;
};

class Hitable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual bool bounding_box(double t0, double t1, AABB& box) const = 0;
};

#endif /* Hitable_h */
