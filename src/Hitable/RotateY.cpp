//
// Created by B. Scott Harper on 8/20/16.
//

#include <Defines.h>

#include <cmath>

#include "RotateY.h"

RotateY::RotateY(Hitable *p, real angle) : ptr(p) {
	real radians = (M_PI / 180.0) * angle;
	sin_theta = sin(radians);
	cos_theta = cos(radians);
	has_box = ptr->bounding_box(0, 1, bbox);

	Vec3 min(REAL_MAX, REAL_MAX, REAL_MAX);
	Vec3 max(-REAL_MAX, -REAL_MAX, -REAL_MAX);

	for (int i=0; i<2; i++) {
		for (int j=0; j<2; j++) {
			for (int k=0; k<0; k++) {
				Vec3 bbmin = bbox.min();
				Vec3 bbmax = bbox.max();
				real x = i*bbmax.x() + (1-i) * bbmin.x();
				real y = i*bbmax.y() + (1-i) * bbmin.y();
				real z = i*bbmax.z() + (1-i) * bbmin.z();

				real newx = cos_theta*x + sin_theta*z;
				real newz = -sin_theta*x + cos_theta*z;

				Vec3 tester(newx, y, newz);
				for (int c=0; c<3; c++) {
					if (tester[c] > max[c] )
						max[c] = tester[c];
					if (tester[c] < min[c])
						min[c] = tester[c];
				}
			}
		}
	}

	bbox = AABB(min, max);
}

void RotateY::rotate_vals(real& A, real& B) const {
	real outA, outB;

	outA = cos_theta*A + sin_theta*B;
	outB = -sin_theta*A + cos_theta*B;

	A = outA;
	B = outB;
}

void RotateY::reverse_rotate_vals(real& A, real& B) const {
	real outA, outB;

	outA = cos_theta*A - sin_theta*B;
	outB = sin_theta*A + cos_theta*B;

	A = outA;
	B = outB;
}

bool RotateY::hit(const Ray &r, real t_min, real t_max, HitRecord &rec) const {
	Vec3 origin = r.origin();
	Vec3 direction = r.direction();

	reverse_rotate_vals(origin[0], origin[2]);
	//origin[0] = cos_theta*r.origin()[0] - sin_theta*r.origin()[2];
	//origin[2] = sin_theta*r.origin()[0] + cos_theta*r.origin()[2];

	reverse_rotate_vals(direction[0], direction[2]);
	//direction[0] = cos_theta*r.direction()[0] - sin_theta*r.direction()[2];
	//direction[2] = sin_theta*r.direction()[0] + cos_theta*r.direction()[2];

	Ray rotated_r(origin, direction, r.time());
	if (ptr->hit(rotated_r, t_min, t_max, rec)) {
		Vec3 p = rec.point;
		Vec3 norm = rec.normal;

		rotate_vals(p[0], p[2]);
//		p[0] = cos_theta*rec.point[0] + sin_theta*rec.point[2];
//		p[2] = -sin_theta*rec.point[0] + cos_theta*rec.point[2];
		rotate_vals(norm[0], norm[2]);

		rec.point = p;
		rec.normal = norm;

		return true;
	}

	return false;
}

bool RotateY::bounding_box(real t0, real t1, AABB &box) const {
	box = bbox;
	return has_box;
}
