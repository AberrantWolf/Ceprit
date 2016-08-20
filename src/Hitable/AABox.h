//
// Created by B. Scott Harper on 8/20/16.
//

#ifndef CEPRIT_AABOX_H
#define CEPRIT_AABOX_H


#include "Hitable.h"

class AABox : public Hitable {
public:
	AABox(const Vec3& p0, const Vec3& p1, Material* mp);

	bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

	bool bounding_box(double t0, double t1, AABB &box) const override {
		box = AABB(pmin, pmax);
		return true;
	}

	Vec3 pmin, pmax;
	Hitable* list_ptr;
};

#endif //CEPRIT_AABOX_H
