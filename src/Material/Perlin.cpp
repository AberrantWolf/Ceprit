//
// Created by B. Scott Harper on 8/20/16.
//

#include <stdlib.h>
#include <Vec3.h>

#include "Perlin.h"

Vec3* Perlin::ranvec = perlin_generate();
int* Perlin::perm_x = perlin_generate_perm();
int* Perlin::perm_y = perlin_generate_perm();
int* Perlin::perm_z = perlin_generate_perm();

Vec3* perlin_generate() {
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

int* perlin_generate_perm() {
	int* p = new int[256];
	for(int i=0; i<256; i++) {
		p[i] = i;
	}
	permute(p, 256);
	return p;
}