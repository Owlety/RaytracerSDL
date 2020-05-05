#pragma once
#ifndef HITABLEH
#define HITABLEH
#include "Ray.h"

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}
vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}
struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
	material* mat_ptr;
};

class hitable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif // !HITABLEH