#include "SDL.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include <iostream>
#include <stdlib.h>

float hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return -1;
    }
    else return (-b - sqrt(discriminant)) / (2.0 * a);
}
//work
vec3 color(const ray& r, hitable *world) {
    hit_record rec;
    if (world->hit(r, 0.0, FLT_MAX, rec)){
        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        
        vec3 origin(0.0, 0.0, 0.0);
        if (SDL_CreateWindowAndRenderer(256, 256, 0, &window, &renderer) == 0) {
            
            SDL_bool done = SDL_FALSE;
            int my = 0; 
            int mx = 0;
            int ns = 10;
            SDL_GetRendererOutputSize(renderer, &mx, &my);
            vec3 horizontal(((float)mx/(float)my)*((float)mx/ (float)my), 0.0, 0.0);
            vec3 vertical(0.0, ((float)mx/ (float)my), 0.0);
            vec3 lower_left_corner(-((float)mx / (float)my) * ((float)mx / (float)my) /2, -((float)mx / (float)my)/2, -1.0);
            hitable *list[2];
            //
            list[0] = new sphere(vec3(0, 0, -1), 0.3);
            list[1] = new sphere(vec3(0, -3.29, -1), 3);
            hitable* world = new hitable_list(list, 2);
            camera cam(mx, my);
            while (!done) {
                SDL_Event event;

                SDL_RenderClear(renderer);
                
                for (int y = 0; y < my; y++)
                {
                    for (int x = 0; x < mx; x++ )
                    {
                        vec3 col(0, 0, 0);
                        for (int s=0; s < ns; s++)
                        {
                            float u = float(x + static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / float(mx);
                            float v = float(y + static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / float(my);
                            ray r = cam.get_ray(u, v);
                            vec3 p = r.point_at_parameter(2.0);
                            col += color(r, world);
                        }
                        col /= ns;
                    SDL_SetRenderDrawColor(renderer, int(col[0] * 255.99), int(col[1] * 255.99), int(col[2]* 255.99), SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawPoint(renderer, x, my - y);
                    }
                } 
                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}