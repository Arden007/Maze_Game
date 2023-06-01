#ifndef Game_h
#define Game_h

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "unistd.h"
#include "math.h"
#include "time.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 600
#define gun_scale 0.35
#define map_x 8
#define map_y 8
#define map_s 64
#define PI 3.14159265
#define PI2 (0.5 * PI)
#define PI3 (1.5 * PI)
#define DR 0.0174533
#define MAP_SCALE 0.25
#define num_enemy 5
#define FOV (PI / 3)
#define num_rays 60

/**
 * struct SDL_Structure - SDL2 instance structure (Window & Renderer)
 *
 * @window: SDL2 window for the game
 * @renderer: SDL2 renderer draws the surface to display
 *
 * Description: SDL2 structure that creates the window to render/draw the surface of the game
 */
typedef struct SDL_Structure
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Structure;

/**
 * struct controller_btn - event keys structure to create controller
 * @w: up key
 * @s: down key
 * @a: left key
 * @d: right key
 * @e: key for open door
 * @x: key for exit
 *
 * Description: structure for handling movement & rotation
 **/
typedef struct controller_btn
{
	int w, a, d, s, e, x;
} controller_btn;

/**
 * struct player - structure for the player
 * @x: the x coordinate postion
 * @y: the y coordinate position
 * @w: the width of the player
 * @h: the height of the player
 * @a: angle of the player
 * @dx: delta x of the player
 * @dy: delta y of the player
 **/
typedef struct player
{
	float x, y, w, h, a, dx, dy;
} player_t;

extern player_t player;

/**
 * struct enemy - structure for the enemy
 * @x: the x coordinate postion
 * @y: the y coordinate position
 * @z: the z coordinate
 * @path: the given path of the image
 **/
typedef struct enemy
{
	float x, y, z;
	char *path;
} enemy_t;

extern enemy_t enemy;
extern float rayDistances[num_rays];

/** main.c **/
void init_game(void);
void display(SDL_Structure instance);

/** window.c **/
int init_instance(SDL_Structure *in);
float AngleReset(float a);

/** drawGame.c **/
void display_player(SDL_Structure instance);
void draw_map(SDL_Structure ins);
void draw_scene(SDL_Structure ins, int n, float h, float rayAngle, float shade,
				float rx, float ry, int m_txr);
void draw_floor(SDL_Structure ins, float ln_off, int n, float line, float ra);
void draw_roof(SDL_Structure ins, float ln_off, int n, float line, float ra);

/** game_renderer.c **/
void add_weapon(SDL_Structure ins);
void draw_enemy(SDL_Structure ins);
float find_viewdistance(void);
void draw_sprite_map(SDL_Structure ins);
void sort_sprite(int *sprite, double *spr_dis, int n);

/** player_movement_and_input.c **/
int poll_events(SDL_Structure instance);
void handle_key_down(SDL_Structure instance);
void key_up(SDL_Event ev);
void key_down(SDL_Event ev);
void handle_door(void);

/** texture.c **/
float get_texture(int index);

/** memory.c **/
void free_grid(SDL_Point ***grid);
void free_tokens(char **tokens);
void free_cols(char ***cols);
void free_numbers(int **numbers);

/** maze_renderer.c **/
void rayCasting(SDL_Structure ins);
float find_distance(float ax, float ay, float bx, float by);
void castRay(float rayAngle, float *ray_x, float *ray_y);
void drawWall(SDL_Structure ins, int rayIndex, float distance);

/** helper.c **/
int _atoi(char *s);
char *_strdup(char *str);
int _length(char *str);
int **get_altitude(char **argv);
char **str_split(char *str, char *del);

/** map_operations.c **/
void setmap_value(int mx, int my, int val);
int get_map_value(int x, int y, int mp);
void free_numbers(int **numbers);
void make_map(char **argv);

#endif /*Game_h*/
