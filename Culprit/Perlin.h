//
//  Perlin.h
//  Culprit
//
//  Created by B. Scott Harper on 8/15/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef Perlin_h
#define Perlin_h

#include "Vec3.h"

inline double perlin_interp(Vec3 c[2][2][2], double u, double v, double w) {
	double uu = u*u*(3-2*u);
	double vv = v*v*(3-2*v);
	double ww = w*w*(3-2*w);
	
	double accum = 0;
	
	for (int i=0; i<2; i++) {
		for (int j=0; j<2; j++) {
			for (int k=0; k<2; k++) {
				Vec3 weight_v(u-i, v-j, w-k);
				accum += (i*uu + (1-i)*(1-uu)) *
						 (j*vv + (1-j)*(1-vv)) *
						 (k*ww + (1-k)*(1-ww)) *
						 dot(c[i][j][k], weight_v);
			}
		}
	}
	
	return accum;
}

class Perlin {
public:
	double noise(const Vec3& p) const {
		double u = p.x() - floor(p.x());
		double v = p.y() - floor(p.y());
		double w = p.z() - floor(p.z());
		
		int i = floor(p.x()); //int(4 * p.x()) & 255;
		int j = floor(p.y()); //int(4 * p.y()) & 255;
		int k = floor(p.z()); //int(4 * p.z()) & 255;
		
		Vec3 c[2][2][2];
		for (int di=0; di<2; di++) {
			for (int dj=0; dj<2; dj++) {
				for (int dk=0; dk<2; dk++) {
					c[di][dj][dk] = ranvec[perm_x[(i+di) & 255] ^ perm_y[(j+dj) & 255] ^ perm_z[(k+dk) & 255]];
				}
			}
		}
		
		
		return perlin_interp(c, u, v, w);
		//return randouble[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
	}
	
	static Vec3* ranvec;
	static int* perm_x;
	static int* perm_y;
	static int* perm_z;
};

static Vec3* perlin_generate() {
	Vec3* p = new Vec3[256];
	for (int i=0; i<256; i++) {
		p[i] = unit_vector(Vec3(-1 + 2 * drand48(), -1 + 2 * drand48(), -1 + 2 * drand48()));
	}
	return p;
}

void permute(int* p, int n) {
	for (int i=n-1; i>0; i--) {
		int target = int(drand48()*(i+1));
		int tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
}

static int* perlin_generate_perm() {
	int* p = new int[256];
	for(int i=0; i<256; i++) {
		p[i] = i;
	}
	permute(p, 256);
	return p;
}

Vec3* Perlin::ranvec = perlin_generate();
int* Perlin::perm_x = perlin_generate_perm();
int* Perlin::perm_y = perlin_generate_perm();
int* Perlin::perm_z = perlin_generate_perm();

#endif /* Perlin_h */
