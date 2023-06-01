#include "maze.h"

player_t player;
controller_btn keys;

/**
 * poll_events - function to handle events
 * @ins: the instance of SDL
 *
 * This function handles SDL events such as key presses and window close events.
 * It converts the original while loop to a for loop and uses switch statements
 * to handle different event types.
 *
 * Return: 1 if the program should quit, 0 otherwise
 **/
int poll_events(SDL_Structure ins)
{
    SDL_Event ev;

    // Process all pending events
    for (; SDL_PollEvent(&ev);)
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            // Quit button is pressed, return 1 to indicate program should quit
            return 1;
        case SDL_KEYDOWN:
            // A key is pressed down
            key_down(ev);
            if (keys.x == 1)
                // 'x' key is pressed, return 1 to indicate program should quit
                return 1;
            break;
        case SDL_KEYUP:
            // A key is released
            key_up(ev);
            break;
        }
        // Handle key down events
        handle_key_down(ins);
    }

    return 0;
}

/**
 * handle_key_down - handle when a key is pressed down
 * @ins: the given instance
 *
 * This function handles the logic when a key is pressed down.
 * It converts the original if statements to switch statements.
 *
 * Return: nothing
 **/
void handle_key_down(SDL_Structure ins)
{
    int mx, my, px = player.x / map_s, py = player.y / map_s, xo = 0, yo = 0;

    xo = (player.dx < 0) ? -20 : 20;
    yo = (player.dy < 0) ? -20 : 20;

    switch (keys.a)
    {
    case 1:
        // 'a' key is pressed, decrease player angle and reset if needed
        player.a -= 0.1;
        player.a = AngleReset(player.a);
        // Calculate new player direction
        player.dx = cos(player.a) * 5;
        player.dy = sin(player.a) * 5;
        break;
    }

    switch (keys.d)
    {
    case 1:
        // 'd' key is pressed, increase player angle and reset if needed
        player.a += 0.1;
        player.a = AngleReset(player.a);
        // Calculate new player direction
        player.dx = cos(player.a) * 5;
        player.dy = sin(player.a) * 5;
        break;
    }

    switch (keys.w)
    {
    case 1:
        // 'w' key is pressed
        mx = ((player.dx * 5) + player.x + xo) / map_s;
        my = ((player.dy * 5) + player.y + yo) / map_s;
        if (get_map_value(mx, py, 0) == 0)
            player.x += player.dx * 2;
        if (get_map_value(px, my, 0) == 0)
            player.y += player.dy * 2;
        break;
    }

    switch (keys.s)
    {
    case 1:
        // 's' key is pressed
        mx = ((player.x - (player.dx * 5)) - xo) / map_s;
        my = ((player.y - (player.dy * 5)) - yo) / map_s;
        if (get_map_value(mx, py, 0) == 0)
            player.x -= player.dx * 2;
        if (get_map_value(px, my, 0) == 0)
            player.y -= player.dy * 2;
        break;
    }

    switch (keys.e)
    {
    case 1:
        // 'e' key is pressed, handle door activity
        handle_door();
        break;
    }

    // Set the drawing color, draw required items, and update the screen
    SDL_SetRenderDrawColor(ins.renderer, 76, 76, 76, 0);
    SDL_RenderClear(ins.renderer);
    display(ins);
    SDL_RenderPresent(ins.renderer);
}

/**
 * handle_door - function to handle the door open activity
 *
 * This function handles the logic when the 'e' key is pressed,
 * specifically when the player is near a door.
 *
 * Return: nothing
 **/
void handle_door(void)
{
    int px_add_off, py_add_off, mx, my, xo, yo;

    xo = (player.dx < 0) ? -30 : 30;
    yo = (player.dy < 0) ? -50 : 50;
    px_add_off = (player.x + xo) / map_s;
    py_add_off = (player.y + yo) / map_s;
    mx = px_add_off;
    my = py_add_off;

    if (get_map_value(mx, my, 0) == 4)
        setmap_value(mx, my, 0);
}

/**
 * key_down - function to handle key down event
 * @ev: the given event
 *
 * This function handles the logic when a key is pressed down.
 * It converts the original if statements to switch statements.
 *
 * Return: nothing
 **/
void key_down(SDL_Event ev)
{
    switch (ev.key.keysym.sym)
    {
    case SDLK_LEFT:
    case SDLK_a:
        keys.a = 1;
        break;
    case SDLK_RIGHT:
    case SDLK_d:
        keys.d = 1;
        break;
    case SDLK_UP:
    case SDLK_w:
        keys.w = 1;
        break;
    case SDLK_DOWN:
    case SDLK_s:
        keys.s = 1;
        break;
    case SDLK_e:
        keys.e = 1;
        break;
    case SDLK_ESCAPE:
        keys.x = 1;
        break;
    }
}

/**
 * key_up - function to handle key up event
 * @ev: the given event
 *
 * This function handles the logic when a key is released.
 * It converts the original if statements to switch statements.
 *
 * Return: nothing
 **/
void key_up(SDL_Event ev)
{
    switch (ev.key.keysym.sym)
    {
    case SDLK_LEFT:
    case SDLK_a:
        keys.a = 0;
        break;
    case SDLK_RIGHT:
    case SDLK_d:
        keys.d = 0;
        break;
    case SDLK_UP:
    case SDLK_w:
        keys.w = 0;
        break;
    case SDLK_DOWN:
    case SDLK_s:
        keys.s = 0;
        break;
    case SDLK_e:
        keys.e = 0;
        break;
    case SDLK_ESCAPE:
        keys.x = 0;
        break;
    }
}
