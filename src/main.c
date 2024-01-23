#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {
	SDL_Window *window = NULL;
	SDL_Surface *surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n",
		       SDL_GetError());
		return EXIT_FAILURE;
	}

	window = SDL_CreateWindow("My First Game", SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
				  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Failed to create SDL window! SDL_Error: %s\n",
		       SDL_GetError());
		return EXIT_FAILURE;
	}

	surface = SDL_GetWindowSurface(window);

	SDL_FillRect(surface, NULL,
		     SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));

	SDL_UpdateWindowSurface(window);

	SDL_Event e;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return EXIT_SUCCESS;
}
