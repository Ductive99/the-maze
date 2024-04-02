#include "maze.h"

const int map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

/**
 * scaler - multiplies a value by a scale factor
 *
 * @value: value to multiply
 *
 * Return: the product
*/
float scaler(float value)
{
	return (value * MAP_SCALE);
}

/**
 * render - renders the frame.
 *
 * @instance: pointer to the window and renderer.
 * @player: pointer to the player struct.
 * @map: the map's 2D array.
*/
void render(SDL_Instance *instance, Player *player)
{
	SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
	SDL_RenderClear(instance->renderer);

	renderMap(instance);
	renderPlayer(instance, player);

	SDL_RenderPresent(instance->renderer);
}

/**
 * renderPlayer - renders a player.
 *
 * @instance: pointer to the window and renderer.
 * @player: pointer to the player struct.
*/
void renderPlayer(SDL_Instance *instance, Player *player)
{
	SDL_SetRenderDrawColor(instance->renderer, 255, 255, 255, 255);
	SDL_Rect playerRect = {
		scaler(player->x),
		scaler(player->y),
		scaler(player->w),
		scaler(player->h)
	};
	SDL_RenderFillRect(instance->renderer, &playerRect);

	SDL_RenderDrawLine(
		instance->renderer,
		scaler(player->x),
		scaler(player->y),
		scaler(player->x + cos(player->rotAngle) * 40),
		scaler(player->y + sin(player->rotAngle) * 40)
	);
}

/**
 * renderMap - renders the 2D map.
 *
 * @instance: pointer to the window and renderer.
 * @map: the map's 2D array.
*/
void renderMap(SDL_Instance *instance)
{
	int tileX, tileY, color;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			tileX = j * TILE_SIZE;
			tileY = i * TILE_SIZE;
			color = map[i][j] != 0 ? 255 : 0;

			SDL_SetRenderDrawColor(
				instance->renderer, color, color, color, 255
			);
			SDL_Rect tileRect = {
				scaler(tileX),
				scaler(tileY),
				scaler(TILE_SIZE),
				scaler(TILE_SIZE),
			};
			SDL_RenderFillRect(instance->renderer, &tileRect);
		}
	}
}

bool isBlocked(float x, float y)
{
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return true;

	int indexX = floor(x / TILE_SIZE);
	int indexY = floor(y / TILE_SIZE);

	return map[indexY][indexX] != 0;
}
