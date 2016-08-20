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

Vec3* perlin_generate();
void permute(int* p, int n);
int* perlin_generate_perm();

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
		
		int i = (int)floor(p.x()); //int(4 * p.x()) & 255;
		int j = (int)floor(p.y()); //int(4 * p.y()) & 255;
		int k = (int)floor(p.z()); //int(4 * p.z()) & 255;
		
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
	
	double turb(const Vec3& p, int depth=7) const {
		double accum = 0;
		Vec3 temp_p = p;
		double weight = 1.0;
		for (int i=0; i<depth; i++) {
			accum += weight*noise(temp_p);
			weight *= 0.5;
			temp_p *= 2;
		}
		
		return fabs(accum);
	}
	
	static Vec3* ranvec;
	static int* perm_x;
	static int* perm_y;
	static int* perm_z;
};

#endif /* Perlin_h */
