//
// Created by B. Scott Harper on 8/20/16.
//

#include <Vec3.h>
#include "Texture.h"

Vec3 ImageTexture::value(real u, real v, const Vec3 &p) const {
	int i = (int)  (  u)*nx;
	int j = (int) ((1-v)*ny-0.001);

	if (i<0) i = 0;
	if (j<0) j = 0;
	if (i>nx-1) i = nx-1;
	if (j>ny-1) j = ny-1;

	real r = int(data[3*i + 3*nx*j]) / 255.0;
	real g = int(data[3*i + 3*nx*j+1]) / 255.0;
	real b = int(data[3*i + 3*nx*j+2]) / 255.0;

	return Vec3(r, g, b);
}