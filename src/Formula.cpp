#include <Formula.h>

// Standard Gravitational Parameter
float Formula::u(float G, float M) {
	return G * M;
}

float Formula::relativeOrbitalSpeed(float G, float m1, float m2, float r) {
	return sqrt(G * (m1 + m2) / r);
}