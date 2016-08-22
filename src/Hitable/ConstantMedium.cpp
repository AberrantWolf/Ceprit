//
// Created by B. Scott Harper on 8/20/16.
//

#include "ConstantMedium.h"

bool ConstantMedium::hit(const Ray &r, real t_min, real t_max, HitRecord &rec) const {
	bool db = (drand48() < 0.0001);
	db = false;
	HitRecord rec1, rec2;

	if (boundary->hit(r, -REAL_MAX, REAL_MAX, rec1)) {
		if (boundary->hit(r, rec1.t+0.0001, REAL_MAX, rec2)) {
			if (db) {
				std::cerr << "\nt0 t1 " << rec1.t << " " << rec2.t << "\n";
			}

			if (rec1.t < t_min)
				rec1.t = t_min;
			if (rec2.t > t_max)
				rec2.t = t_max;

			if (rec1.t >= rec2.t) {
				return false;
			}

			if (rec1.t < 0) {
				rec1.t = 0; // collision is behind where the ray originated
			}

			real dir_length = r.direction().length();
			real dist_inside_boundary = (rec2.t - rec1.t) * dir_length;
			real hit_dist = (real) (-(1/density) * log(drand48()));
			if (hit_dist < dist_inside_boundary) {
				rec.t = rec1.t + hit_dist / dir_length;
				rec.point = r.point_at_parameter(rec.t);
				rec.normal = Vec3(1, 0, 0); // arbitrary
				rec.mat_ptr = phase_function;

				if (db) {
					std::cerr << "hit_dist = " << hit_dist << std::endl;
					std::cerr << "rec.t = " << rec.t << std::endl;
					std::cerr << "rec.point = " << rec.point << std::endl;
				}

				return true;
			}
		}
	}

	return false;
}

bool ConstantMedium::bounding_box(real t0, real t1, AABB& box) const {
	return boundary->bounding_box(t0, t1, box);
}
