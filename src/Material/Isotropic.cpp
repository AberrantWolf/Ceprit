//
// Created by B. Scott Harper on 8/20/16.
//

#include <Hitable/Hitable.h>
#include <Util.h>
#include "Isotropic.h"
#include "Material.h"

bool Isotropic::scatter(const Ray &in_r, const HitRecord &rec, Vec3 &attenuation, Ray &scattered) const {
	scattered = Ray(rec.point, random_point_in_unit_sphere());
	attenuation = albedo->value(rec.u, rec.v, rec.point);
	return true;
}
