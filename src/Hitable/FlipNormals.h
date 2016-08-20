//
// Created by B. Scott Harper on 8/20/16.
//

#ifndef CEPRIT_FLIPNORMALS_H
#define CEPRIT_FLIPNORMALS_H

#include "Hitable.h"

class FlipNormals : public Hitable {
public:
	FlipNormals(Hitable* p) : ptr(p) {}

	virtual bool hit (const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
		if (ptr->hit(r, t_min, t_max, rec)) {
			rec.normal *= -1;
			return true;
		}

		return false;
	}
	bool bounding_box(double t0, double t1, AABB& box) const override {
		return ptr->bounding_box(t0, t1, box);
	}

	Hitable* ptr;
};

#endif //CEPRIT_FLIPNORMALS_H
