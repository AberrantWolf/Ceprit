//
// Created by B. Scott Harper on 8/20/16.
//

#ifndef CEPRIT_TRANSLATION_H
#define CEPRIT_TRANSLATION_H


#include "Hitable.h"

class Translation : public Hitable {
public:
	Translation(Hitable* p, const Vec3& displacement) : ptr(p), offset(displacement) {}

	virtual bool hit(const Ray &r, real t_min, real t_max, HitRecord &rec) const override {
		Ray moved(r.origin() - offset, r.direction(), r.time());
		if (ptr->hit(moved, t_min, t_max, rec)) {
			rec.point += offset;
			return true;
		}
		return false;
	}

	virtual bool bounding_box(real t0, real t1, AABB &box) const override {
		if (ptr->bounding_box(t0, t1, box)) {
			box = AABB(box.min() + offset, box.max() + offset);
			return true;
		}

		return false;
	}

	Hitable* ptr;
	Vec3 offset;
};


#endif //CEPRIT_TRANSLATION_H
