#ifndef FORMULA_H
#define FORMULA_H

// Dependencies
#include <cmath>

// Formula
class Formula {
	public:
		static float u(float G, float M);
		static float relativeOrbitalSpeed(float G, float m1, float m2, float r);
};

#endif
