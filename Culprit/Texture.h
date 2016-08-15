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
		return Vec3(1, 1, 1) * 0.5 * (1 + noise.noise(scale * p));
	}
	
	Perlin noise;
	double scale;
};

#endif /* Texture_h */
