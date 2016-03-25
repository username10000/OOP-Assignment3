#include <Functions.h>

// Distance between two sets of coordinates
double Functions::dist(double x1, double y1, double x2, double y2) {
	double X = pow(x2 - x1, 2);
	double Y = pow(y2 - y1, 2);

	return sqrt(X + Y);
}

// Map a value between two other values
double Functions::map(double v, double lmin, double lmax, double rmin, double rmax) {
	if (v < lmin)
		v = lmin;

	if (v > lmax)
		v = lmax;

	double leftRange = lmax - lmin;
	double rightRange = rmax - rmin;

	double leftPercentage = (v - lmin) / leftRange;

	return rmin + (leftPercentage * rightRange);
}

// Get a Random Integer value between two Integer values
int Functions::randomInt(int start, int stop) {
	return rand() % (stop - start + 1) + start;
}

// Get a Random Float value between two Float float
float Functions::randomFloat(float start, float stop) {
	return start + (float)(rand() / (float)(RAND_MAX / (stop - start)));
}