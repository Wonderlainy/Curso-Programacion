#include <iostream>
#include <SDL.h>

int main(int argc, char* args[]) {
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    
    
    SDL_Delay(3000); // Keep the window open for 3 seconds
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
