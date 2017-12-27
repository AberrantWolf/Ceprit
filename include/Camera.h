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
    Camera(const Vec3& lookfrom, const Vec3& lookat, const Vec3& vup,
           real fovy, real aspect,
           real aperture, real focus_dist,
           real t0, real t1)
    {
        lens_radius = aperture / 2;
        
        real theta = fovy * M_PI / 180;
        real half_height = tan(theta/2);
        real half_width = aspect * half_height;
        
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        
        lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
        
        time0 = t0;
        time1 = t1;
    }
    
    Ray get_ray(real s, real t) {
        Vec3 rd = lens_radius * random_point_in_unit_disk();
        Vec3 offset =u * rd.x() + v*rd.y();
        
        real time = time0 + RAND() * (time1 - time0);
        return Ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset, time);
    }
    
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    
    Vec3 u, v, w;
    real lens_radius;
    
    // Shutter open/shut times
    real time0, time1;
};

#endif /* Camera_h */
