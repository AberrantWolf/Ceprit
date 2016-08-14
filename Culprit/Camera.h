//
//  Camera.h
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Ray.h"

class Camera {
public:
    Camera(double fovy, double aspect) {
        double theta = fovy * M_PI / 180;
        double half_height = tan(theta/2);
        double half_width = aspect * half_height;
        
        lower_left_corner = Vec3(-half_width, -half_height, -1.0);
        horizontal = Vec3(2 * half_width, 0.0, 0.0);
        vertical = Vec3(0.0, 2 * half_height, 0.0);
        origin = Vec3(0.0, 0.0, 0.0);
    }
    
    Ray get_ray(double u, double v) {
        return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }
    
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
};

#endif /* Camera_h */
