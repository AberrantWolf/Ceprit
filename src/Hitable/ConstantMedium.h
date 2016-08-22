//
// Created by B. Scott Harper on 8/20/16.
//

#ifndef CEPRIT_CONSTANTMEDIUM_H
#define CEPRIT_CONSTANTMEDIUM_H

#include <Defines.h>
#include <Material/Texture.h>
#include <Material/Isotropic.h>
#include "Hitable.h"

class ConstantMedium : public Hitable {
public:
	ConstantMedium(Hitable* b, real d, Texture* a) : boundary(b), density(d) {
		phase_function = new Isotropic(a);
	}

	virtual bool hit(const Ray &r, real t_min, real t_max, HitRecord &rec) const override;

	virtual bool bounding_box(real t0, real t1, AABB &box) const override;

	Hitable* boundary;
	real density;
	Material* phase_function;
};


#endif //CEPRIT_CONSTANTMEDIUM_H
