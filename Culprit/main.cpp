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

int main(int argc, const char * argv[]) {
    int nx = 200;
    int ny = 100;
    int ns = 100;   // number of samples
    
    Hitable* list[2];
    
    double R = cos(M_PI/4);
    list[0] = new Sphere(Vec3(-R, 0, -1), R, new Labertian(Vec3(0, 0, 1)));
    list[1] = new Sphere(Vec3( R, 0, -1), R, new Labertian(Vec3(1, 0, 0)));
    //list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.3));
    //list[3] = new Sphere(Vec3(-1, 0, -1), 0.5, new Dielectric(1.5));
    //list[4] = new Sphere(Vec3(-1, 0, -1), -0.45, new Dielectric(1.5));
    
    Hitable* world = new HitableList(list, 2);
    Camera cam(90, double(nx)/double(ny));
    
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
                
                col += color(r, world, 0);
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
