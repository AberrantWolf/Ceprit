//
//  Ray.h
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef Ray_h
#define Ray_h

#include "Vec3.h"

class Ray {
public:
    Ray() {}
    Ray(const Vec3 in_origin, const Vec3 in_direction, real ti = 0.0) {
        A = in_origin;
        B = in_direction;
        _time = ti;
    }
    Vec3 origin() const { return A; }
    Vec3 direction() const { return B; }
    Vec3 point_at_parameter(real t) const { return A + t*B; }
    real time() const { return _time; }
    
private:
    Vec3 A; //origin
    Vec3 B; //direction
    real _time;
};

#endif /* Ray_h */
