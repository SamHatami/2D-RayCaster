#include <SDL.h>
#include <iostream>
#include "Display.h"
#include "main.h"

#include "RayCaster.h"

bool quit = false;
Display display;
RayCaster rayCaster;
point mousePosition;
line walls[4];
ray* rays;

int main(int argc, char* argv[]) {

	// Initialize SDL by calling Setup class?
	
	//Run "game loop" and wait for event to close window.

	//I should probably do it the c++ way instead of the c# way...

	mousePosition = point(0, 0);
	rayCaster = RayCaster();

	SDL_Window* window = display.InitializeWindow(800,600); 
	
	Initialize();

	while (!quit)
	{
		Update();
	}
    //SDL_Delay(5000); // Wait for 3 seconds
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void Initialize() {

	walls[0] = line(point(50, 50), point(50, 100));
	walls[1] = line(point(100, 100), point(200, 100));
	walls[2] = line(point(200, 100), point(200, 200));
	walls[3] = line(point(200, 200), point(100, 200));
	
}

void GetInputs() {

	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type) {

	case SDL_MOUSEMOTION:
		mousePosition.x = event.motion.x;
		mousePosition.y = event.motion.y;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			quit = true;
		}
	}

}

void Update() {

	rayCaster.CastRays(mousePosition);
	GetInputs();
	Render();

}

void Render() {
	display.ClearFrameBuffer(0x00000000);
	//draw rectangle at mouse, with offset of 5 pixels to center it over the tip
	display.DrawRectangle(mousePosition.x-5, mousePosition.y-5, 10, 10, 0xFFFFFF00);

	for (int i = 0; i < 4; i++) {
		display.DrawLine(walls[i], 0xFFFFFF00);
	}
	rays = rayCaster.GetRays();
	for (int i = 0; i < 10; i++) {
		line line = { rays[i].start, point(rays[i].start.x + rays[i].direction.x * 100, rays[i].start.y + rays[i].direction.y * 100) };
		display.DrawLine(line, rays[i].color);
	}
	display.DrawCircle(400, 300, 5, 0xFFFFFF00, false);

	//display.DrawRectangle(200, 200, 100, 100, 0xFFFFFF00);
	display.Render();
}