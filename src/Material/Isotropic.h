//
// Created by B. Scott Harper on 8/20/16.
//

#ifndef CEPRIT_ISOTROPIC_H
#define CEPRIT_ISOTROPIC_H


#include <Ray.h>
#include <Hitable/Hitable.h>
#include "Material.h"

class Isotropic : public Material {
public:
	Isotropic(Texture* a) : albedo(a) {}

	virtual bool scatter(const Ray &in_r, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const override;

	Texture* albedo;
};


#endif //CEPRIT_ISOTROPIC_H
