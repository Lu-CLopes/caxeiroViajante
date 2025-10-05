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
    Point a(-100,150, true);
    Point b(200, -250);

    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
        SDL_RenderClear(renderer);

        // print the x and y axis
        showAxis(renderer, true);




        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
        drawCircle(renderer, a);
        drawCircle(renderer, b);
        line(renderer, a, b, true);


        // Update the screen
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}