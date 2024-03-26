#include "maze.h"

/* Global Variables */
SDL_Instance instance = {NULL, NULL};
game_object ball;
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

	setup(&ball);

	while (game_state)
	{
		process(&game_state);
		update(&ball, &last_frame_time);
		render(&instance, &ball);
	}

	destroy(&instance);

	return (0);
}
