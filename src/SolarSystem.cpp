#include <SolarSystem.h>

SolarSystem::SolarSystem(long long _radius) {
	radius = _radius;
}

SolarSystem::SolarSystem() : SolarSystem(1000000) {
}

long long SolarSystem::getRadius() {
	return radius;
}