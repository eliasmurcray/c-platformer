#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Surface *gBmapSurface = NULL;

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	gWindow = SDL_CreateWindow("My First Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (gWindow == NULL) {
		return false;
	}

	gSurface = SDL_GetWindowSurface(gWindow);

	return true;
}

bool load_assets() {
	gBmapSurface = SDL_LoadBMP("assets/test-asset.bmp");
	return gBmapSurface != NULL;
}

void exit_SDL() {
	SDL_FreeSurface(gBmapSurface);
	gBmapSurface = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

int main(int argc, char *args[]) {
	if (!init()) {
		printf("Failed to initialize! SDL_Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	if (!load_assets()) {
		printf("Failed to load assets! SDL_Error: %s\n", SDL_GetError());
		return EXIT_SUCCESS;
	}

	SDL_BlitSurface(gBmapSurface, NULL, gSurface, NULL);

	//SDL_FillRect(gSurface, NULL,
		     //SDL_MapRGB(gSurface->format, 0xff, 0xff, 0xff));

	SDL_UpdateWindowSurface(gWindow);

	SDL_Event e;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
		}
	}

	exit_SDL();

	return EXIT_SUCCESS;
}
