//
//  Material.h
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include "Vec3.h"

class Material {
public:
    virtual bool scatter(const Ray& in_r,
                         const HitRecord& rec,
                         Vec3& attenuation,
                         Ray& scattered) const = 0;
};

class Labertian : public Material {
public:
    Labertian(const Vec3& a) : albedo(a) {}
    
    virtual bool scatter(const Ray& in_r,
                         const HitRecord& rec,
                         Vec3& attenuation,
                         Ray& scattered) const override {
        Vec3 target = rec.point + rec.normal + random_point_in_unit_sphere();
        scattered = Ray(rec.point, target - rec.point);
        attenuation = albedo;
        
        return true;
    }
    
    Vec3 albedo;
};

class Metal : public Material {
public:
    Metal(const Vec3& a, double f) : albedo(a), fuzz(f) {}
    
    virtual bool scatter(const Ray& in_r,
                         const HitRecord& rec,
                         Vec3& attenuation,
                         Ray& scattered) const override {
        Vec3 reflected = reflect(unit_vector(in_r.direction()), rec.normal);
        scattered = Ray(rec.point, reflected + fuzz * random_point_in_unit_sphere());
        attenuation = albedo;
        
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    
    Vec3 albedo;
    double fuzz;
};

double schlick(double cosine, double ref_idx) {
    double r0 = (1-ref_idx)/(1+ref_idx);
    r0 = r0*r0;
    
    return r0 + (1-r0)*pow((1-cosine), 5);
}

class Dielectric : public Material {
public:
    Dielectric(double ri) : ref_idx(ri) {}
    
    virtual bool scatter(const Ray& in_r,
                         const HitRecord& rec,
                         Vec3& attenuation,
                         Ray& scattered) const override {
        Vec3 outward_normal;
        Vec3 reflected = reflect(in_r.direction(), rec.normal);
        
        float ni_over_nt;
        attenuation = Vec3(1.0, 1.0, 1.0);
        Vec3 refracted;
        
        double reflect_prob;
        double cosine;
        
        if (dot(in_r.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(in_r.direction(), rec.normal) / in_r.direction().length();
        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -dot(in_r.direction(), rec.normal) / in_r.direction().length();
        }
        
        // find probability of reflection
        if (refract(in_r.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            reflect_prob = 1.0;
        }
        
        // set scattered ray to reflected or refracted
        if (drand48() < reflect_prob) {
            scattered = Ray(rec.point, reflected);
        } else {
            scattered = Ray(rec.point, refracted);
        }
        
        return true;
    }
    
    double ref_idx;
};

#endif /* Material_h */
