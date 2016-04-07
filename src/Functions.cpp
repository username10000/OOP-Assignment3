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

// Return String with the Comma added for the Thousands place
std::string Functions::toStringWithComma(int num) {
	if (num == 0) {
		return "0";
	}

	std::stringstream ss;
	bool negative = num < 0 ? true : false;
	int digits = 1;

	while (num) {
		int d = abs(num % 10);

		if (digits != 0) {
			ss << d;
			digits = (digits + 1) % 4;
		} else {
			ss << "," << d;
			digits = 2;
		}
		num /= 10;
	}

	if (negative)
		ss << "-";

	std::string string(ss.str());
	std::string reverse(string.rbegin(), string.rend());

	return reverse;
}