//
//  AABB.h
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef AABB_h
#define AABB_h

#include "Vec3.h"
#include "Ray.h"

class AABB {
public:
    AABB() {}
    AABB(const Vec3& a, const Vec3& b) { _min = a; _max = b; }
    
    Vec3 min() const { return _min; }
    Vec3 max() const { return _max; }
    
    bool hit(const Ray& r, double tmin, double tmax) const {
        for (int a=0; a<3; a++) {
            double invD = 1.0f / r.direction()[a];
            
            double t0 = (_min[a] - r.origin()[a]) * invD;
            double t1 = (_max[a] - r.origin()[a]) * invD;
            
            if (invD < 0.0) {
                std::swap(t0, t1);
            }
            
            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;
            if (tmax <= tmin)
                return false;
        }
        
        return true;
    }
    
    Vec3 _min;
    Vec3 _max;
};

#endif /* AABB_h */
