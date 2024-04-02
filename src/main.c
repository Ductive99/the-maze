#include "maze.h"

/* Global Variables */
SDL_Instance instance = {NULL, NULL};
Player player;
int last_frame_time = 0;
int game_state = false;

/**
 * main - Entry Point
 *
 * Return: 0 always
*/
int main(void)
{
	game_state = init_instance(&instance);

	setup(&player);

	while (game_state)
	{
		process(&player, &game_state);
		update(&player, &last_frame_time);
		render(&instance, &player);
	}

	destroy(&instance);

	return (0);
}
