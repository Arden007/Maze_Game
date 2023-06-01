#include "maze.h"

player_t player;
float rayDistances[num_rays];

/**
 * rayCasting - Function that performs raycasting to render the 3D scene.
 * @ins: The SDL2 structure used for rendering.
 *
 * This function casts rays from the player's position and renders the 3D scene based on the ray intersections with walls.
 **/
void rayCasting(SDL_Structure ins)
{
    float rayAngle, ray_x, ray_y;
    // float px, py;
    int i;

    SDL_Rect top, map;
    top.x = 0, top.y = 0, top.w = SCREEN_WIDTH, top.h = 400;
    map.x = 0, map.y = 0, map.w = (map_x * (map_s * MAP_SCALE));
    map.h = (map_y * (map_s * MAP_SCALE));

    // Render the sky
    SDL_SetRenderDrawColor(ins.renderer, 30, 144, 255, 0);
    SDL_RenderFillRect(ins.renderer, &top);

    // Render the ground
    SDL_SetRenderDrawColor(ins.renderer, 76, 76, 76, 0);
    SDL_RenderFillRect(ins.renderer, &map);

    // Cast rays and render the scene
    rayAngle = player.a - DR * 30;
    rayAngle = AngleReset(rayAngle);

    for (i = 0; i < num_rays; i++)
    {
        // Cast the ray and find the intersection point with the wall
        castRay(rayAngle, &ray_x, &ray_y);

        // Store the ray distance for later use
        rayDistances[i] = find_distance(player.x, player.y, ray_x, ray_y);

        // Draw the 3D projection of the wall
        drawWall(ins, i, rayDistances[i]);

        rayAngle += DR;
        rayAngle = AngleReset(rayAngle);
    }
}

/**
 * castRay - Function that casts a ray and finds the intersection point with the wall.
 * @rayAngle: The angle of the ray to cast.
 * @ray_x: Pointer to store the x-coordinate of the intersection point.
 * @ray_y: Pointer to store the y-coordinate of the intersection point.
 *
 * This function casts a ray from the player's position in the specified direction and finds the intersection point with the wall.
 **/
void castRay(float rayAngle, float *ray_x, float *ray_y)
{
    // Calculate the ray direction vector
    float ray_dx = cos(rayAngle);
    float ray_dy = sin(rayAngle);

    // Find the step size for ray increments based on the ray direction
    int step_x = (ray_dx > 0) ? 1 : -1;
    int step_y = (ray_dy > 0) ? 1 : -1;

    // Calculate the distance to the next x and y grid lines
    float deltaDist_x = fabs(1 / ray_dx);
    float deltaDist_y = fabs(1 / ray_dy);

    // Calculate the initial ray position in the grid
    int mapX = (int)player.x;
    int mapY = (int)player.y;

    // Calculate the initial ray distance to the x and y grid lines
    float sideDist_x;
    float sideDist_y;

    // Calculate the initial step direction for the sideDist values
    // int stepSide_x;
    // int stepSide_y;

    // Calculate the sideDist values and the step direction
    if (ray_dx < 0)
    {
        sideDist_x = (player.x - map_x) * deltaDist_x;
        step_x = -1;
    }
    else
    {
        sideDist_x = (map_x + 1.0 - player.x) * deltaDist_x;
        step_x = 1;
    }
    if (ray_dy < 0)
    {
        sideDist_y = (player.y - map_y) * deltaDist_y;
        step_y = -1;
    }
    else
    {
        sideDist_y = (map_y + 1.0 - player.y) * deltaDist_y;
        step_y = 1;
    }

    // Perform the DDA algorithm to find the intersection point with the wall
    int hit = 0;
    while (hit == 0)
    {
        // Jump to the next map cell in the ray direction
        if (sideDist_x < sideDist_y)
        {
            sideDist_x += deltaDist_x;
            mapX += step_x;
            hit = 0; // Vertical wall hit
        }
        else
        {
            sideDist_y += deltaDist_y;
            mapY += step_y;
            hit = 1; // Horizontal wall hit
        }

        // Check if the ray hit a wall
        int map_value = get_map_value(map_x, map_y, 0);
        if (map_value > 0)
        {
            hit = 1; // Wall hit
            *ray_x = map_x;
            *ray_y = map_y;
        }
    }
}

/**
 * drawWall - Function that renders the 3D projection of a wall.
 * @ins: The SDL2 structure used for rendering.
 * @rayIndex: The index of the ray in the rayDistances array.
 * @distance: The distance from the player to the wall.
 *
 * This function renders the 3D projection of a wall based on the distance from the player to the wall and the ray angle.
 **/
void drawWall(SDL_Structure ins, int rayIndex, float distance)
{
    // Calculate the wall height based on the distance
    float wallHeight = (map_s * MAP_SCALE) / distance;

    // Calculate the top and bottom screen coordinates of the wall slice
    int wallTop = (SCREEN_HEIGHT / 2) - (wallHeight / 2);
    int wallBottom = (SCREEN_HEIGHT / 2) + (wallHeight / 2);

    // Set the wall color
    SDL_SetRenderDrawColor(ins.renderer, 255, 255, 255, 0);

    // Render the wall slice
    SDL_RenderDrawLine(ins.renderer, rayIndex, wallTop, rayIndex, wallBottom);
}

/**
 * find_distance - Function that calculates the distance between two points.
 * @ax: The x-coordinate of the first point.
 * @ay: The y-coordinate of the first point.
 * @bx: The x-coordinate of the second point.
 * @by: The y-coordinate of the second point.
 *
 * This function calculates the Euclidean distance between two points in a 2D space.
 **/
float find_distance(float ax, float ay, float bx, float by)
{
    return sqrtf((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}
