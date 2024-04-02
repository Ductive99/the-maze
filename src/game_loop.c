#include "maze.h"

/**
 * setup - initializes a player's position and speed.
 *
 * @player: pointer to the player struct.
*/
void setup(Player *player)
{
	player->x = WINDOW_WIDTH / 2;
	player->y = WINDOW_HEIGHT / 2;
	player->w = 5;
	player->h = 5;
	player->turnDirection = 0;
	player->walkDirection = 0;
	player->rotAngle = PI / 2;
	player->walkSpeed = 200;
	player->rotSpeed = 75 * PI / 180;
}

/**
 * process - processes user's input.
 *
 * @game_state: variable to end the loop.
 * @player: player instance.
*/
void process(Player *player, int *game_state)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		SDL_KeyCode KEY = event.key.keysym.sym;

		switch (event.type)
		{
			case SDL_QUIT:
				*game_state = false;
				break;
			case SDL_KEYDOWN:
			{
				switch (KEY)
				{
					case SDLK_ESCAPE:
						*game_state = false;
						break;
					case SDLK_UP:
					case SDLK_DOWN:
						player->walkDirection = (KEY == SDLK_UP) ? 1 : -1;
						break;
					case SDLK_RIGHT:
					case SDLK_LEFT:
						player->turnDirection = (KEY == SDLK_RIGHT) ? 1 : -1;
						break;
					default:
						break;
				}
				break;
			}
			case SDL_KEYUP:
			{
				if (KEY == SDLK_UP || KEY == SDLK_DOWN)
					player->walkDirection = 0;
				else if (KEY == SDLK_RIGHT || KEY == SDLK_LEFT)
					player->turnDirection = 0;
				break;
			}
		}
	}
}

/**
 * update - handles updating the frames and wall collisions.
 *
 * @player: pointer to the player struct.
 * @last_frame_time: time since the last frame.
*/
void update(Player *player, int *last_frame_time)
{
	int wait_time = FRAME_TIME - (SDL_GetTicks() - *last_frame_time);

	if (wait_time > 0  && wait_time <= FRAME_TIME)
		SDL_Delay(wait_time);

	float delta_time = (SDL_GetTicks() - *last_frame_time) / 1000.0f;

	*last_frame_time = SDL_GetTicks();

	movePlayer(player, delta_time);
}

/**
 * movePlayer - controls the player's movement.
 *
 * @player: pointer to the player struct.
 * @Dt: delta time: time since last render.
*/
void movePlayer(Player *player, float Dt)
{
	float step = player->walkDirection * player->walkSpeed * Dt;

	player->rotAngle += player->turnDirection * player->rotSpeed * Dt;

	player->x += cos(player->rotAngle) * step;
	player->y += sin(player->rotAngle) * step;
}
