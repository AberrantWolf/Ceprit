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
};

#endif /* Hitable_h */
