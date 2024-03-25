#include "maze.h"

int main(void)
{
	SDL_Instance instance;
	instance.window = NULL;
	SDL_Surface *windowSurface = NULL;
	SDL_Surface *imageSurface = NULL;

	if (init(&instance) != 0)
		return (1);

	windowSurface = SDL_GetWindowSurface(instance.window);
	imageSurface = SDL_LoadBMP("ductive.bmp");

	if (imageSurface == NULL)
	{
		fprintf(stderr, "Unable to Load Image: %s\n", SDL_GetError());
		return (1);
	}
	
	SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
	SDL_UpdateWindowSurface(instance.window);
	SDL_Delay(3000);


	SDL_FreeSurface(imageSurface);
	SDL_DestroyWindow(instance.window);
	imageSurface = NULL;
	windowSurface = NULL;
	instance.window = NULL;
	SDL_Quit();

	return (0);
}
