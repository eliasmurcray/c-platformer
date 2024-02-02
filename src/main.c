#include "Camera.h"
#include "Collision.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

typedef struct {
	double x;
	double y;
	double x_vel;
	double y_vel;
} Player;

int main(int argc, char *args[]) {
	SDL_Window *window = SDL_CreateWindow(
	    "My First Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(
	    window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n",
			SDL_GetError());
		return EXIT_FAILURE;
	}

	Player player = {0., 0., 0., 0.};
	Camera camera = {.0f, .0f, .1f};
	SDL_Rect *rects[2] = {
	    &(SDL_Rect){50, 50, 75, 75},
	    &(SDL_Rect){200, 200, 50, 50},
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, rects[0]);
	SDL_RenderPresent(renderer);
	
	bool run = true;
	while (run) {
		uint32_t frame_start = SDL_GetTicks();

		SDL_Event e;
		while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) run = false;

		const uint8_t *keys = SDL_GetKeyboardState(NULL);
		player.x_vel = (float) (keys[SDL_SCANCODE_RIGHT] - keys[SDL_SCANCODE_LEFT]) * 2.f;
		if (keys[SDL_SCANCODE_UP]) {
			player.y_vel = -8.f;
		}
		player.x += player.x_vel;
                player.y += player.y_vel;
                player.y_vel += .33f;
                if (player.y > 400.) {
                        player.y = 400.;
                }
                Camera_update(&camera, (float) (SCREEN_WIDTH / 2 - 20 - (int) player.x), (float) (SCREEN_HEIGHT / 2 - 20 - (int) player.y));

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                const size_t l = sizeof(rects) / sizeof(SDL_Rect *);
                size_t i;
                for (i = 0; i < l; i++) {
                        SDL_Rect *r = rects[i];
                        SDL_Rect r0 =
                            {r->x + (int)camera.x,
                                        r->y + (int)camera.y, r->w, r->h};
                        SDL_RenderFillRect(renderer, &r0);
                }
		
		SDL_Rect p = {camera.x + player.x, camera.y + player.y, 20, 20};
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &p);

                SDL_RenderPresent(renderer);

		uint32_t frame_time = SDL_GetTicks() - frame_start;
		if (frame_time < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - frame_time);
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
