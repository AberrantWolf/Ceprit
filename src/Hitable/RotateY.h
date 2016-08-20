//
// Created by B. Scott Harper on 8/20/16.
//

#ifndef CEPRIT_ROTATEY_H
#define CEPRIT_ROTATEY_H


#include "Hitable.h"

class RotateY : public Hitable {
public:
	RotateY(Hitable* p, real angle);

	virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
	virtual bool bounding_box(real t0, real t1, AABB &box) const override;

	Hitable* ptr;
	real sin_theta;
	real cos_theta;
	bool has_box;
	AABB bbox;

private:
	void rotate_vals(real& A, real& B) const;
	void reverse_rotate_vals(real& A, real& B) const;
};


#endif //CEPRIT_ROTATEY_H
