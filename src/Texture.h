//
//  Texture.h
//  Culprit
//
//  Created by B. Scott Harper on 8/15/16.
//  Copyright © 2016 Harpers. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include "Vec3.h"
#include "Perlin.h"
#include "stb_image.h"

//
// ABSTRACT Texture class interface
//
class Texture {
public:
	virtual Vec3 value(double u, double v, const Vec3& p) const = 0;
};


//
// Constant color texture
//
class ConstantTexture : public Texture {
public:
	ConstantTexture() {}
	ConstantTexture(Vec3 c) : color(c) {}
	
	virtual Vec3 value(double u, double v, const Vec3& p) const override {
		return color;
	}
	
	Vec3 color;
};


class CheckerTexture : public Texture {
public:
	CheckerTexture() {}
	CheckerTexture(Texture* t0, Texture* t1): odd(t0), even(t1) {}
	
	virtual Vec3 value(double u, double v, const Vec3& p) const override  {
		double sines = sin(10*p.x()) * sin(10*p.y()) * sin(10*p.z());
		
		if (sines < 0) {
			return odd->value(u, v, p);
		} else {
			return even->value(u, v, p);
		}
	}
	
	Texture* odd;
	Texture* even;
};

class NoiseTexture : public Texture {
public:
	NoiseTexture() {}
	NoiseTexture(double sc) : scale(sc) {}
	virtual Vec3 value(double u, double v, const Vec3& p) const override  {
		//return Vec3(1, 1, 1) * 0.5 * (1 + noise.noise(scale * p));
		//return Vec3(1, 1, 1) * noise.turb(scale * p);
		return Vec3(1, 1, 1) * 0.5 * (1 + sin(scale*p.z() + 10 * noise.turb(p)));
	}
	
	Perlin noise;
	double scale;
};


class ImageTexture : public Texture {
public:
	ImageTexture() {}
	ImageTexture(unsigned char* pixels, int A, int B) : data(pixels), nx(A), ny(B) {}
	
	virtual Vec3 value(double u, double v, const Vec3& p) const;
	
	unsigned char* data;
	int nx, ny;
};

Vec3 ImageTexture::value(double u, double v, const Vec3 &p) const {
	int i = (  u)*nx;
	int j = (1-v)*ny-0.001;
	
	if (i<0) i = 0;
	if (j<0) j = 0;
	if (i>nx-1) i = nx-1;
	if (j>ny-1) j = ny-1;
	
	double r = int(data[3*i + 3*nx*j]) / 255.0;
	double g = int(data[3*i + 3*nx*j+1]) / 255.0;
	double b = int(data[3*i + 3*nx*j+2]) / 255.0;
	
	return Vec3(r, g, b);
}

#endif /* Texture_h */
