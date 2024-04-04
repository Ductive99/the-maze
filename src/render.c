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

Ray rays[RAYS];

/**
 * render - renders the frame.
 *
 * @instance: Pointer to the window and renderer.
 * @player: Pointer to the player struct.
*/
void render(SDL_Instance *instance, Player *player)
{
	SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
	SDL_RenderClear(instance->renderer);

	renderMap(instance);
	renderRays(instance, player);
	renderPlayer(instance, player);

	SDL_RenderPresent(instance->renderer);
}

/**
 * renderPlayer - renders a player.
 *
 * @instance: Pointer to the window and renderer.
 * @player: Pointer to the player struct.
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
 * @instance: Pointer to the window and renderer.
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


void renderRays(SDL_Instance *instance, Player *player)
{
    SDL_SetRenderDrawColor(instance->renderer, 255, 0, 0, 255);
    for (int i = 0; i < RAYS; i++) {
        SDL_RenderDrawLine(
            instance->renderer,
            scaler(player->x),
            scaler(player->y),
            scaler(rays[i].wallHitX),
            scaler(rays[i].wallHitY)
        );
    }
}

/**
 * castRays - Calls the castRay() function with the correct ray.
 *
 * @player: Pointer to the player struct.
*/
void castRays(Player *player)
{
	float rayAngle = player->rotAngle - (FOV / 2);

	for (int i = 0; i < RAYS; i++)
	{
		castRay(player, normalize(rayAngle), i);
		rayAngle += FOV / RAYS;
	}
}

/**
 * castRay - Casts a single ray until encountring a wall.
 *
 * @player: Pointer to the player struct.
 * @rayAngle: Angle relative to the player's orientation.
 * @Id: The id of the ray.
*/
void castRay(Player *player, float rayAngle, int Id)
{
	/* 1 for down  -  0 for up */
	int UPorDOWN = rayAngle > 0 && rayAngle < PI;
	/* 1 for right - 0 for left */
	int RIGHTorLEFT = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;

	float xintercept, yintercept;
	float xstep, ystep;

	/* HORIZONTAL RAY-GRID INTERSECTION */
	bool horzWallIsHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	float horzWallContent = 0;

	yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	yintercept += UPorDOWN ? TILE_SIZE : 0;

	xintercept = player->x + (yintercept - player->y) / tan(rayAngle);

	ystep = !UPorDOWN ? -TILE_SIZE : TILE_SIZE;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (!RIGHTorLEFT && xstep > 0) ? -1 : 1;
	xstep *= (RIGHTorLEFT && xstep < 0) ? -1 : 1;

	float nextHtouchX = xintercept;
	float nextHtouchY = yintercept;

	while ((nextHtouchX >= 0 && nextHtouchX <= WINDOW_WIDTH) && 
		(nextHtouchY >= 0 && nextHtouchY <= WINDOW_HEIGHT))
	{
		float xCheck = nextHtouchX;
		float yCheck = nextHtouchY + (UPorDOWN ? 0 : -1);

		if (isBlocked(xCheck, yCheck))
		{
			horzWallHitX = nextHtouchX;
			horzWallHitY = nextHtouchY;
            horzWallContent = map[(int)floor(yCheck / TILE_SIZE)][(int)floor(xCheck / TILE_SIZE)];
			horzWallIsHit = true;
			break;
		}
		else
		{
			nextHtouchX += xstep;
			nextHtouchY += ystep;
		}
	}

	/* VERTICAL RAY-GRID INTERSECTION */
	bool vertWallIsHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;

	xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
	xintercept += RIGHTorLEFT ? TILE_SIZE : 0;

	yintercept = player->y + (xintercept - player->x) * tan(rayAngle);

	xstep = RIGHTorLEFT ? TILE_SIZE : -TILE_SIZE;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (!UPorDOWN && ystep > 0) ? -1 : 1;
	ystep *= (UPorDOWN && ystep < 0) ? -1 : 1;

	float nextVtouchX = xintercept;
	float nextVtouchY = yintercept;

	while ((nextVtouchX >= 0 && nextVtouchX <= WINDOW_WIDTH) &&
		(nextVtouchY >= 0 && nextVtouchY <= WINDOW_HEIGHT))
	{
		float xCheck = nextVtouchX - (RIGHTorLEFT ? 0 : 1);
		float yCheck = nextVtouchY;

		if (isBlocked(xCheck, yCheck))
		{
			vertWallHitX = nextVtouchX;
			vertWallHitY = nextVtouchY;
			vertWallContent = map[(int)floor(yCheck / TILE_SIZE)][(int)floor(xCheck / TILE_SIZE)];
			vertWallIsHit = true;
			break;
		}
		else
		{
			nextVtouchX += xstep;
			nextVtouchY += ystep;
		}
	}

	float horzHitDistance = horzWallIsHit
		? distanceBtwn(player->x, player->y, horzWallHitX, horzWallHitY)
		: FLT_MAX;
	float vertHitDistance = vertWallIsHit
		? distanceBtwn(player->x, player->y, vertWallHitX, vertWallHitY)
		: FLT_MAX;

	if (vertHitDistance < horzHitDistance)
	{
        rays[Id].distance = vertHitDistance;
        rays[Id].wallHitX = vertWallHitX;
        rays[Id].wallHitY = vertWallHitY;
        rays[Id].wallHitContent = vertWallContent;
        rays[Id].wasHitVertical = 1;
	}
	else
	{
        rays[Id].distance = horzHitDistance;
        rays[Id].wallHitX = horzWallHitX;
        rays[Id].wallHitY = horzWallHitY;
        rays[Id].wallHitContent = horzWallContent;
        rays[Id].wasHitVertical = 0;
	}
    rays[Id].rayAngle = rayAngle;
    rays[Id].UorD = UPorDOWN;
    rays[Id].RorL = RIGHTorLEFT;
}
