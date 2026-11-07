#pragma once

#include <SDL.h> // Include SDL header

Display display;
	SDL_Event event;
	bool quit = false;

	void get_inputs();
	void update();
	void render();

