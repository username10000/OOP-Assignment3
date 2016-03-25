#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H
#define PI 3.14159265359

// Dependencies
#include <cmath>

class Functions {
	public:
		static double dist(double x1, double y1, double x2, double y2);
		static double map(double v, double lmin, double lmax, double rmin, double rmax);
		static int randomInt(int start, int stop);
		static float randomFloat(float start, float stop);
};

#endif