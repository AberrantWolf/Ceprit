//
// Created by B. Scott Harper on 8/20/16.
//

#include <Util.h>
#include <Material/Material.h>
#include <Hitable/AARects.h>
#include <Hitable/HitableList.h>
#include <Hitable/FlipNormals.h>

Vec3 random_point_in_unit_disk() {
	Vec3 p;
	do {
		p = 2.0 * Vec3(drand48(), drand48(), 0.0) - Vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);

	return p;
}

bool refract(const Vec3& v, const Vec3& n, double ni_over_nt, Vec3& refracted) {
	Vec3 uv = unit_vector(v);
	double dt = dot(uv, n);
	double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);

	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}

	return false;
}

// Utility function for calculating reflectivity vs refractivity
double schlick(double cosine, double ref_idx) {
	double r0 = (1-ref_idx)/(1+ref_idx);
	r0 = r0*r0;

	return r0 + (1-r0)*pow((1-cosine), 5);
}

AABB surrounding_box(AABB box0, AABB box1) {
	Vec3 small(fmin(box0.min().x(), box1.min().x()),
	           fmin(box0.min().y(), box1.min().y()),
	           fmin(box0.min().z(), box1.min().z()));
	Vec3 big(fmax(box0.max().x(), box1.max().x()),
	         fmax(box0.max().y(), box1.max().y()),
	         fmax(box0.max().z(), box1.max().z()));

	return AABB(small, big);
}

Hitable* CornellBox() {
	Hitable** list = new Hitable*[6];

	Material* red = new Lambertian( new ConstantTexture( Vec3(0.65, 0.05, 0.05)) );
	Material* white = new Lambertian( new ConstantTexture( Vec3(0.73, 0.73, 0.73)) );
	Material* green = new Lambertian( new ConstantTexture( Vec3(0.12, 0.45, 0.15)) );
	Material* light = new DiffuseLight( new ConstantTexture( Vec3(15, 15, 15)) );

	list[0] = new FlipNormals(new YZRect(0, 555, 0, 555, 555, green)); // left
	list[1] = new YZRect(0, 555, 0, 555, 0, red); // right
	list[2] = new XZRect(213, 343, 227, 332, 554, light); // light panel near top
	list[3] = new FlipNormals(new XZRect(0, 555, 0, 555, 0, white)); // bottom
	list[4] = new XZRect(0, 555, 0, 555, 555, white); // top
	list[5] = new FlipNormals(new XYRect(0, 555, 0, 555, 555, white));

	return new HitableList(list, 5);
}