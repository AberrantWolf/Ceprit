//
// Created by B. Scott Harper on 8/20/16.
//



#include <Ray.h>
#include <Util.h>
#include "Hitable.h"
#include "HitableList.h"

bool HitableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
	HitRecord temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;

	for (int i=0; i<list_size; i++) {
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

bool HitableList::bounding_box(double t0, double t1, AABB &box) const {
	if (list_size < 1) return false;

	AABB temp_box;
	bool first_true = list[0]->bounding_box(t0, t1, temp_box);
	if (!first_true) {
		return false;
	} else {
		box = temp_box;
	}

	for (int i=0; i<list_size; i++) {
		if (list[i]->bounding_box(t0, t1, temp_box)) {
			box = surrounding_box(box, temp_box);
		} else return false;
	}

	return true;
}