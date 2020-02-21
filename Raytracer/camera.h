#ifndef CAMERAH
#define CAMERAH
#include <stdlib.h>
#include "Ray.h"

class camera {
public:
	camera(float mx, float my){
		lower_left_corner = vec3(-((float)mx / (float)my) * ((float)mx / (float)my) / 2, -((float)mx / (float)my) / 2, -1.0);
		horizontal = vec3(((float)mx / (float)my) * ((float)mx / (float)my), 0.0, 0.0);
		vertical = vec3(0.0, ((float)mx / (float)my), 0.0);
		origin = vec3(0.0, 0.0, 0.0);
	}
	ray get_ray(float u, float v) {
		return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};






#endif // !CAMERAH