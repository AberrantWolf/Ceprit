//
//  main.cpp
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#include <iostream>
#include <random>

#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"
#include "BVHNode.h"

Vec3 color(const Ray& r, Hitable* world, int depth) {
    HitRecord rec;
    
    if (world->hit(r, 0.0001, MAXFLOAT, rec)) {
        Ray scattered;
        Vec3 attenuation;
        
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth+1);
        }
        
        return Vec3(0, 0, 0);
    } else {
        // Sky background
        Vec3 unit_direction = unit_vector(r.direction());
        double t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
    }
}

HitableList* random_scene() {
    int n = 500;
    Hitable** list = new Hitable*[n+1];
    
    ConstantTexture* gray = new ConstantTexture(Vec3(0.5, 0.5, 0.5));
	ConstantTexture* gold = new ConstantTexture(Vec3(1.0, 0.7, 0));
	CheckerTexture* check = new CheckerTexture(gray, gold);
    list[0] = new Sphere(Vec3(0, -1000, 0), Vec3(0, -1000, 0), 0, 1, 1000,
						 new Labertian(check));
    
    int i = 1;
    for (int a = -11; a<11; a++) {
        for (int b=-11; b<11; b++) {
            float choose_mat = drand48();
            Vec3 center(a + 0.9*drand48(), 0.2, b + 0.9*drand48());
            if ((center-Vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.7) {
                    //diffuse
                    ConstantTexture* col_tex = new ConstantTexture(Vec3(drand48(), drand48(), drand48()));
                    Material *mat = new Labertian(col_tex);
                    list[i++] = new Sphere(center, center + Vec3(0, 0.5*drand48(), 0),  0, 1, 0.2, mat);
                } else if (choose_mat < 0.9) {
                    // metal
                    Material *mat = new Metal(Vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48())), 0.5*drand48());
                    list[i++] = new Sphere(center, center,  0, 1, 0.2, mat);
                } else {
                    // Glass
                    list[i++] = new Sphere(center, center, 0, 1, 0.2, new Dielectric(1.5));
                }
            }
        }
    }
    
    ConstantTexture* red = new ConstantTexture(Vec3(0.9, 0.2, 0.1));
    
    list[i++] = new Sphere(Vec3(0, 1, 0), Vec3(0, 1, 0), 0, 1, 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(Vec3(-4, 1, 0), Vec3(-4, 1, 0), 0, 1, 1.0, new Labertian(red));
    list[i++] = new Sphere(Vec3(4, 1, 0), Vec3(4, 1, 0), 0, 1, 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.0));
    
    return new HitableList(list, i);
}

int main(int argc, const char * argv[]) {
    int nx = 100;
    int ny = 100;
    int ns = 100;   // number of samples
    
    HitableList* world = random_scene();
    
    BVHNode* tree = new BVHNode(world->list, world->list_size, 0, 1);
    
    Vec3 lookfrom(13, 2, 3);
    Vec3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    
    double focal_dist = 10; //(lookfrom - lookat).length();
    double aperture = 0.05;
    
    Camera cam(lookfrom, lookat, vup, 20, double(nx)/double(ny), aperture, focal_dist, 0.0, 1.0);
    
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >=0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 col(0, 0, 0);
            
            for (int s=0; s<ns; s++) {
                double u = double(i + dis(gen)) / double(nx);
                double v = double(j + dis(gen)) / double(ny);
                
                Ray r = cam.get_ray(u, v);
                
                col += color(r, tree, 0);
            }
            col /= double(ns);
            col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            
            int ir = int(255.99f * col[0]);
            int ig = int(255.99f * col[1]);
            int ib = int(255.99f * col[2]);
            std::cout << ir << "    " << ig << "    " << ib << "\n";
        }
    }
    
    return 0;
}
