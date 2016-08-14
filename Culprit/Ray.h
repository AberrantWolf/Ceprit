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
    Ray(const Vec3 in_origin, const Vec3 in_direction) {
        A = in_origin;
        B = in_direction;
    }
    Vec3 origin() const { return A; }
    Vec3 direction() const { return B; }
    Vec3 point_at_parameter(double t) const { return A + t*B; }
    
private:
    Vec3 A; //origin
    Vec3 B; //direction
};

#endif /* Ray_h */
