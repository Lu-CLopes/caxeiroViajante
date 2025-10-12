#include "../lib/visual.h"


int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    int initval = SDL_initialize(&window, &renderer);
    if(initval)
        return 1; // if any error ocurred during initialization

    bool quit = false;
    SDL_Event e;


    // points initialiation logic
    Point points[AMOUNT_POINTS];
    init_benchmark(points);

    int position = 0;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_DOWN:
                        break;

                    case SDLK_UP:
                        break;

                    case SDLK_RIGHT:
                        if(position < AMOUNT_POINTS)
                            position++;
                        break;
                        
                    case SDLK_LEFT:
                        if(position >= 0)
                            position--;
                        break;
                }
            }
        }

        
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
        SDL_RenderClear(renderer);

        // print the x and y axis
        showAxis(renderer, true);




        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
        drawPoints(renderer, points, position);


        // Update the screen
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}