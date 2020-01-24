#include "SDL.h"
#include "ray.h"
#include <iostream>
vec3 color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    /*std::cout << r.direction() << "\n";
    std::cout << unit_direction << "\n";*/
    float t = 0.5 * (unit_direction.y() + 1.0);

    //std::cout << t << ": " << (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0) <<"\n";
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        vec3 horizontal(4.0, 0.0, 0.0);
        vec3 vertical(0.0, 2.0, 0.0);
        vec3 origin(0.0, 0.0, 0.0);
        vec3 lower_left_corner(-2.0, -1.0, -1.0);
        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;
            int my = 0; 
            int mx = 0;
            SDL_GetRendererOutputSize(renderer, &mx, &my);
            while (!done) {
                SDL_Event event;

                SDL_RenderClear(renderer);
                
                for (int y = my-1; y > 0; y--)
                {
                    for (int x = 0; x < mx; x++ )
                    {
                        ray r(origin, lower_left_corner + (float(x) / float(mx)) * horizontal + (float(y) / float(my)) * vertical);
                        vec3 col = color(r);
                    SDL_SetRenderDrawColor(renderer, int(col[0] * 255.99), int(col[1] * 255.99), int(col[2]* 255.99), SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, x,my-y,x,my-y);
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