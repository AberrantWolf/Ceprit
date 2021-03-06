//
// Created by B. Scott Harper on 8/20/16.
//

#include "AARects.h"


bool XYRect::hit(const Ray &r, real t_min, real t_max, HitRecord &rec) const {
	real t = (k-r.origin().z()) / r.direction().z();

	if (t<t_min || t > t_max) {
		return false;
	}

	real x = r.origin().x() + t*r.direction().x();
	real y = r.origin().y() + t*r.direction().y();
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

bool XZRect::hit(const Ray &r, real t_min, real t_max, HitRecord &rec) const {
	real t = (k-r.origin().y()) / r.direction().y();

	if (t<t_min || t > t_max) {
		return false;
	}

	real x = r.origin().x() + t*r.direction().x();
	real z = r.origin().z() + t*r.direction().z();
	if (x < x0 || x > x1 || z < z0 || z > z1) {
		return false;
	}

	// otherwise it hit
	rec.u = (x-x0)/(x1-x0);
	rec.v = (z-z0)/(z1-z0);
	rec.t = t;
	rec.mat_ptr = mat_p;
	rec.point = r.point_at_parameter(t);
	rec.normal = Vec3(0, 1, 0);

	return true;
}

bool YZRect::hit(const Ray &r, real t_min, real t_max, HitRecord &rec) const {
	real t = (k-r.origin().x()) / r.direction().x();

	if (t<t_min || t > t_max) {
		return false;
	}

	real y = r.origin().y() + t*r.direction().y();
	real z = r.origin().z() + t*r.direction().z();
	if (y < y0 || y > y1 || z < z0 || z > z1) {
		return false;
	}

	// otherwise it hit
	rec.u = (y-y0)/(y1-y0);
	rec.v = (z-z0)/(z1-z0);
	rec.t = t;
	rec.mat_ptr = mat_p;
	rec.point = r.point_at_parameter(t);
	rec.normal = Vec3(1, 0, 0);

	return true;
}