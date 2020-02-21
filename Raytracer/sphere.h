#pragma once
#include "hittable.h"

class sphere : hitable {
public:
	sphere() {}
	sphere(vec3 cen, float r) : center(cen), radius(r) {};
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {};
	vec3 center;
	float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {

}