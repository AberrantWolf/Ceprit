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

AABB surrounding_box(AABB box0, AABB box1) {
    Vec3 small(fmin(box0.min().x(), box1.min().x()),
               fmin(box0.min().y(), box1.min().y()),
               fmin(box0.min().z(), box1.min().z()));
    Vec3 big(fmax(box0.max().x(), box1.max().x()),
             fmax(box0.max().y(), box1.max().y()),
             fmax(box0.max().z(), box1.max().z()));
    
    return AABB(small, big);
}



class XYRect : public Hitable {
public:
	XYRect() {}
	XYRect(double _x0, double _x1, double _y0, double _y1, double _k, Material* m) :
	x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mat_p(m) {}
	
	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
	virtual bool bounding_box(double t0, double t1, AABB& box) const {
		box = AABB(Vec3(x0,y0, k-0.001), Vec3(x1, y1, k+0.001));
		return true;
	}
	
	Material* mat_p;
	double x0, x1, y0, y1, k;
};

bool XYRect::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
	double t = (k-r.origin().z()) / r.direction().z();
	
	if (t<0 || t > t_max) {
		return false;
	}
	
	double x = r.origin().x() + t*r.direction().x();
	double y = r.origin().y() + t*r.direction().y();
	if (x < x0 || x > x1 || y < y0 || y > y1) {
		return false;
	}
	
	// otherwise it hit
	rec.u = (x-x0)/(x1-x0);
	rec.v = (y-y0)/(y1-y0);
	rec.t = t;
	rec.mat_ptr = mat_p;
	rec.point = r.point_at_parameter(t);
	rec.normal = Vec3(0, 0, 1);
	
	return true;
}

#endif /* Hitable_h */
