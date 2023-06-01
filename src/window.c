#include "maze.h"

/**
 * init_instance - intialize all instance
 * @init: the given instance
 *
 * Return: 0 on success 1 otherwise
 **/

int init_instance(SDL_Structure *init)
{
    /** You can't call any SDL functions without initializing SDL first. Since all we care about is using SDL's video subsystem, we will only be passing it the SDL_INIT_VIDEO flag.**/
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        /* When there's an error, SDL_Init returns -1. When there's an error we want to print to the console what happened, other wise the application will just flash for a second and then go away.
           SDL_GetError is a very useful function.Whenever something goes wrong you need to know whorizontalY.SDL_GetError will let you know if any errors happened inside of any SDL function.return (1);
        */
    }
    /** Create window with width & height recieved
     *  If SDL initialized successfully, we'll want to create a window using SDL_CreateWindow.
     **/
    init->window = SDL_CreateWindow("The Maze Game", 0, 0, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    /** Checks if window initialized correctly **/
    if (init->window == NULL)
    {
        // If there is an error, SDL_CreateWindow returns NULL. If there's no window, we want to print out the error to the console.
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        // Quit SDL subsystems
        SDL_Quit();
        return (1);
    }
    /** Create a 2D rendering context for a window.
     *  If SDL initialized successfully, we'll want to create a renderer using SDL_CreateRenderer.
     * **/
    init->renderer = SDL_CreateRenderer(init->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    /** Checks if renderer initialized correctly **/
    if (init->renderer == NULL)
    {
        // If there is an error, SDL_CreateRenderer returns NULL. If there's no renderer, we want to print out the error to the console.
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        // Quit SDL subsystems
        SDL_Quit();
        return (1);
    }
    /** Checks if image is initialized correctly **/
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        fprintf(stderr, "Error: Failed to initialized image correctly.\n");
        return (1);
    }
    return (0);
}

/**
 * AngleReset - if the angle is out of range ,we Readjusted the angle accoedingly
 * @a: postion of the angle recieved
 *
 * Return: the Readjusted angle to it's correct position
 **/
float AngleReset(float a)
{
    /** if the angle is above 360 degeree **/
    if (a > 2 * PI)
        a -= 2 * PI;
    /** if the angle is negative **/
    if (a < 0)
        a += 2 * PI;
    return (a);
}
