//
// Created by B. Scott Harper on 8/20/16.
//

#ifndef CEPRIT_AARECTS_H
#define CEPRIT_AARECTS_H

#include "Defines.h"
#include "Hitable.h"

class XYRect : public Hitable {
public:
	XYRect() {}
	XYRect(real _x0, real _x1, real _y0, real _y1, real _k, Material* m) :
			x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mat_p(m) {}

	virtual bool hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const override;
	virtual bool bounding_box(real t0, real t1, AABB& box) const override {
		box = AABB(Vec3(x0,y0, k-0.001), Vec3(x1, y1, k+0.001));
		return true;
	}

	Material* mat_p;
	real x0, x1, y0, y1, k;
};


class XZRect : public Hitable {
public:
	XZRect() {}
	XZRect(real _x0, real _x1, real _z0, real _z1, real _k, Material* m) :
			x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mat_p(m) {}

	virtual bool hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const override;
	virtual bool bounding_box(real t0, real t1, AABB& box) const override {
		box = AABB(Vec3(x0, k-0.001, z0), Vec3(x1, k+0.001, z1));
		return true;
	}

	Material* mat_p;
	real x0, x1, z0, z1, k;
};


class YZRect : public Hitable {
public:
	YZRect() {}
	YZRect(real _y0, real _y1, real _z0, real _z1, real _k, Material* m) :
			y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mat_p(m) {}

	virtual bool hit(const Ray& r, real t_min, real t_max, HitRecord& rec) const override;
	virtual bool bounding_box(real t0, real t1, AABB& box) const override {
		box = AABB(Vec3(k-0.001, y0, z0), Vec3(k+0.001, y1, z1));
		return true;
	}

	Material* mat_p;
	real y0, y1, z0, z1, k;
};


#endif //CEPRIT_AARECTS_H
