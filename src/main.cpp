//
//  main.cpp
//  Culprit
//
//  Created by B. Scott Harper on 8/14/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#include <iostream>
#include <random>

#include <Hitable/AARects.h>

#include "Sphere.h"
#include "Hitable/HitableList.h"
#include "Camera.h"
#include <memory>
//#include "BVHNode.h"

#ifdef DEBUG
#define WIDTH 100
#define HEIGHT 100
#define NSAMPLES 30
#else
#define WIDTH 400
#define HEIGHT 400
#define NSAMPLES 500
#define MAX_BOUNCES 10
#endif

Vec3 color(const Ray& r, Hitable* world, int depth) {
    HitRecord rec;
    
    if (world->hit(r, 0.001, REAL_MAX, rec)) {
        Ray scattered;
        Vec3 attenuation;
		Vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.point);
        
        if (depth < MAX_BOUNCES && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return emitted + attenuation * color(scattered, world, depth+1);
		} else {
			return emitted;
		}
			
        return Vec3(0, 0, 0);
    } else {
		return Vec3(0, 0, 0);
        // Sky background
//        Vec3 unit_direction = unit_vector(r.direction());
//        real t = 0.5 * (unit_direction.y() + 1.0);
//        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
    }
}

HitableList* random_scene() {
    int n = 500;
    Hitable** list = new Hitable*[n+1];
    
    ConstantTexture* gray = new ConstantTexture(Vec3(0.5, 0.5, 0.5));
	ConstantTexture* gold = new ConstantTexture(Vec3(1.0, 0.7, 0));
	CheckerTexture* check = new CheckerTexture(gray, gold);
    list[0] = new Sphere(Vec3(0, -1000, 0), Vec3(0, -1000, 0), 0, 1, 1000,
						 new Lambertian(check));
    
    int i = 1;
    for (int a = -11; a<11; a++) {
        for (int b=-11; b<11; b++) {
            real choose_mat = RAND();
            Vec3 center(a + 0.9*RAND(), 0.2, b + 0.9*RAND());
            if ((center-Vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.7) {
                    //diffuse
                    ConstantTexture* col_tex = new ConstantTexture(Vec3(RAND(), RAND(), RAND()));
                    Material *mat = new Lambertian(col_tex);
                    list[i++] = new Sphere(center, center + Vec3(0, 0.5*RAND(), 0),  0, 1, 0.2, mat);
                } else if (choose_mat < 0.9) {
                    // metal
                    Material *mat = new Metal(Vec3(0.5*(1+RAND()), 0.5*(1+RAND()), 0.5*(1+RAND())), 0.5*RAND());
                    list[i++] = new Sphere(center, center,  0, 1, 0.2, mat);
                } else {
                    // Glass
                    list[i++] = new Sphere(center, center, 0, 1, 0.2, new Dielectric(1.5));
                }
            }
        }
    }
    
    ConstantTexture* red = new ConstantTexture(Vec3(1.0, 0.05, 0.05));
    
    list[i++] = new Sphere(Vec3(0, 1, 0), Vec3(0, 1, 0), 0, 1, 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(Vec3(-4, 1, 0), Vec3(-4, 1, 0), 0, 1, 1.0, new Lambertian(red));
    list[i++] = new Sphere(Vec3(4, 1, 0), Vec3(4, 1, 0), 0, 1, 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.0));
    
    return new HitableList(list, i);
}

HitableList* SimpleLight() {
	Texture* pertex = new NoiseTexture(4);
	Hitable** list = new Hitable*[4];
	
	Vec3 pos = Vec3(0, -1000, 0);
	list[0] = new Sphere(pos, pos, 0, 1, 1000, new Lambertian(pertex));
	pos = Vec3(0, 2, 0);
	list[1] = new Sphere(pos, pos, 0, 1, 2, new Lambertian(pertex));
	pos = Vec3(2, 4, 2);
	list[2] = new Sphere(pos, pos, 0, 1, 0.5, new DiffuseLight(new ConstantTexture(Vec3(4, 4, 4))));
	list[3] = new XYRect(3, 5, 1, 3, -2, new DiffuseLight(new ConstantTexture(Vec3(8, 8, 8))));
	
	return new HitableList(list, 4);
}

int main(int argc, const char * argv[]) {
    int nx = WIDTH;
    int ny = HEIGHT;
    int ns = NSAMPLES;   // number of samples
    
	//HitableList* world = random_scene();
//	Hitable* list[2];
//	
//	int tx, ty, tn;
//	unsigned char* tex_data = stbi_load("./planet.jpg", &tx, &ty, &tn, 0);
//	if (tx == 0 || ty == 0) {
//		return -1;
//	}
//	
//	Vec3 center = Vec3(0, 1.5, 0);
//	real radius = 1.5;
//	Texture* tex = new ImageTexture(tex_data, tx, ty);
//	list[0] = new Sphere(center, center, 0, 1, radius, new Lambertian(tex));
//	
//	center = Vec3(0, -1000, 0);
//	radius = 1000;
//	tex = new NoiseTexture(4);
//	list[1] = new Sphere(center, center, 0, 1, radius, new Lambertian(tex));
//	
//	HitableList* world = new HitableList(list, 2);
	//HitableList* world = SimpleLight();

	std::unique_ptr<Hitable> world = CornellBox();
	
    //BVHNode* tree = new BVHNode(world->list, world->list_size, 0, 1);
    
    Vec3 lookfrom(278, 278, -800);
    Vec3 lookat(278, 278, 0);
    Vec3 vup(0, 1, 0);
    
    real focal_dist = 10.0; (lookfrom - lookat).length();
    real aperture = 0.0;
	real fovy = 40.0;
    
    Camera cam(lookfrom, lookat, vup, fovy, real(nx)/real(ny), aperture, focal_dist, 0.0, 1.0);
    
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >=0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 col(0, 0, 0);
            
            for (int s=0; s<ns; s++) {
                real u = real(i + dis(gen)) / real(nx);
                real v = real(j + dis(gen)) / real(ny);
                
                Ray r = cam.get_ray(u, v);
				
				Vec3 tcol = color(r, world.get(), 0);
//				real cmax = fmax(tcol.x(), fmax(tcol.y(), tcol.z()));
//				if (cmax > 1) {
//					tcol /= cmax;
//				}
				
				col += tcol;
            }
            col /= real(ns);
            col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            
            int ir = int(255.99f * col[0]);
            int ig = int(255.99f * col[1]);
            int ib = int(255.99f * col[2]);
            std::cout << ir << "    " << ig << "    " << ib << "\n";
        }
    }
    
    return 0;
}
