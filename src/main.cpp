#include "../lib/visual.h"


int main(int argc, char* argv[])
{
    std::cout << "\nFormat: bspgm (benchmark, seed, population, generations and mutation)\nEx1.: 10010 runs benchmark and changes the number of generations\n" << std::endl;
    bool showBenchmark = false;
    int pop = POPULATION;
    int gnrt = GENERATIONS_MAX;
    uint8_t mut = CHANCE_OF_MUTATION;
    int currMod = 2;

    if(argc > 1)
    {
        // benchmark
        if(argv[1][0] == '1')
        {
            showBenchmark = true;
        }

        // seed
        if(argv[1][1] == '1' && argc >= currMod+1)
        {
            srand(atoi(argv[currMod++]));
        }
        else {
            srand(time(NULL));
        }

        // Population
        if(argv[1][2] == '1' && argc >= currMod+1)
        {
            pop = atoi(argv[currMod++]);
            if(pop % 6 != 0)
            {
                std::cout << "ERROR POPULATION MUST BE DIVISIBLE BY 6" << std::endl;
                return 1;
            }
        }

        // generations
        if(argv[1][3] == '1' && argc >= currMod+1)
        {
            gnrt = atoi(argv[currMod++]);
        }

        // mutation chance
        if(argv[1][4] == '1' && argc >= currMod+1)
        {
            mut = (uint8_t) atoi(argv[currMod++]);

            if(mut > 100)
            {
                std::cout << "ERROR MUTATION MORE THAN 100%% CHANCE" << std::endl;
                return 1;
            }
        }
    }
    else    // no mods, no benchmark, 
        srand(time(NULL));


    SDL_Window* window;
    SDL_Renderer* renderer;

    int initval = SDL_initialize(&window, &renderer);
    if(initval)
        return 1; // if any error ocurred during initialization

    bool quit = false;
    SDL_Event e;


    // points initialiation logic
    Point points[AMOUNT_POINTS];
    ai_agent agents[pop];
    Point saved[500][AMOUNT_POINTS];
    int gens = 0;

    if(showBenchmark)
        init_benchmark(points);
    else
        init_random(points);

    // TRAINING
    train(agents, points, saved, &gens, pop, gnrt, mut);

    const int lastSavedID = (gens-1)/(gnrt/500);

    // perceiving the improvement
    std::cout << "Generations: " << gens << std::endl;
    if(showBenchmark)
    {
        std::cout << "Solution: " << evaluation(points) << std::endl;
    }
    std::cout << "Initial: " << evaluation(saved[0]) << std::endl;
    std::cout << "After training: " << evaluation(saved[lastSavedID]) << std::endl;

    int currGen = lastSavedID;
    int position = 0;
    bool initial = false;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_DOWN:
                        initial = false;
                        if(currGen < lastSavedID)
                            currGen++;
                        break;

                    case SDLK_UP:
                        initial = false;
                        if(currGen > 0)
                            currGen--;
                        break;

                    case SDLK_RIGHT:
                        if(position < AMOUNT_POINTS)
                            position++;
                        break;
                        
                    case SDLK_LEFT:
                        if(position > 0)
                            position--;
                        break;
                        
                    case SDLK_TAB:
                        initial = !initial;
                        break;
                        
                    case SDLK_SPACE:
                        initial= false;
                        currGen = lastSavedID;
                        break;

                    case SDLK_BACKSPACE:
                        initial= false;
                        currGen = 0;
                        break;

                    case SDLK_LSHIFT:
                        position = 0;
                        break;
                    case SDLK_RSHIFT:
                        position = 0;
                        break;

                    case SDLK_LCTRL:
                        position = AMOUNT_POINTS;
                        break;
                    case SDLK_RCTRL:
                        position = AMOUNT_POINTS;
                        break;
                }
            }
        }

        
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
        SDL_RenderClear(renderer);

        // print the x and y axis
        showAxis(renderer, true);




        if(initial)
        {
            SDL_SetRenderDrawColor(renderer, 136, 231, 136, 255); // Light Green for initial
            drawPoints(renderer, points, position);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
            drawPoints(renderer, saved[currGen], position);
        }




        // Update the screen
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}