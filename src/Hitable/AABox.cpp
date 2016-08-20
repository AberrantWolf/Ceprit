//
// Created by B. Scott Harper on 8/20/16.
//

#include "AABox.h"
#include "FlipNormals.h"
#include "AARects.h"
#include "HitableList.h"

AABox::AABox(const Vec3 &p0, const Vec3 &p1, Material *mp) {
	pmin = p0;
	pmax = p1;

	Hitable** list = new Hitable*[6];

	real x0 = p0.x();
	real x1 = p1.x();

	real y0 = p0.y();
	real y1 = p1.y();

	real z0 = p0.z();
	real z1 = p1.z();

	// Front/back
	list[0] =                 new XYRect(x0, x1, y0, y1, z1, mp);
	list[1] = new FlipNormals(new XYRect(x0, x1, y0, y1, z0, mp));
	// Top/bottom
	list[2] =                 new XZRect(x0, x1, z0, z1, y1, mp);
	list[3] = new FlipNormals(new XZRect(x0, x1, z0, z1, y0, mp));
	// Left/right
	list[4] =                 new YZRect(y0, y1, z0, z1, x1, mp);
	list[5] = new FlipNormals(new YZRect(y0, y1, z0, z1, x0, mp));

	list_ptr = new HitableList(list, 6);
}

bool AABox::hit(const Ray &r, real t_min, real t_max, HitRecord &rec) const {
	return list_ptr->hit(r, t_min, t_max, rec);
}
