#include "maze.h"

/**
 * free_grid - free allocated memory of grid
 * @grid: the given grid
 *
 * Return: nothing
 **/
void free_grid(SDL_Point ***grid)
{
	if (grid != NULL)
	{
		int i = 0;
		while (i < map_x)
		{
			int j = 0;
			while (j < map_y)
			{
				free(grid[i][j]);
				j++;
			}
			free(grid[i]);
			i++;
		}
		free(grid);
	}
	else
	{
		return;
	}
}

/**
 * free_tokens - free the memory assigned for tokens
 * @tokens: the given tokens
 *
 * Return: Nothing
 **/
void free_tokens(char **tokens)
{
	if (tokens != NULL)
	{
		int i = 0;
		while (tokens[i] != NULL)
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
	else
	{
		return;
	}
}

/**
 * free_numbers - free the memory assigned for numbers
 * @numbers: the given numbers
 *
 * Return: Nothing
 **/
void free_numbers(int **numbers)
{
	if (numbers != NULL)
	{
		int i = 0;
		while (i < map_x)
		{
			free(numbers[i]);
			i++;
		}
		free(numbers);
	}
	else
	{
		return;
	}
}

/**
 * free_altitude - free the allocated memory for altitude map
 * @altitude: the altitude map
 * @rows: the number of rows
 **/
void free_altitude(int **altitude, int rows)
{
	if (altitude != NULL)
	{
		int i = 0;
		while (i < rows)
		{
			free(altitude[i]);
			i++;
		}
		free(altitude);
	}
	else
	{
		return;
	}
}

/**
 * free_cols - free allocated memory of columns
 * @cols: the given columns
 *
 * Return: nothing
 **/
void free_cols(char ***cols)
{
	if (cols != NULL)
	{
		int i = 0;
		while (i < map_x)
		{
			int j = 0;
			while (j < map_y)
			{
				free(cols[i][j]);
				j++;
			}
			free(cols[i]);
			i++;
		}
		free(cols);
	}
	else
	{
		return;
	}
}
