#include "main.h"
#include <string>

int main(int argc, char* argv[])
{
	// Initialize SDL by calling Setup class?

	//Run "game loop" and wait for event to close window.

	//I should probably do it the c++ way instead of the c# way...

	mousePosition = Point(300, 300);
	rayCaster = RayCaster();
	lightingSystem = LightingSystem();
	SDL_Window* window = display.InitializeWindow(800, 600); // probably use smart pointer for this?
	pointLight = PointLight(150, 25, 0xFF0000FF, mousePosition);
	rays = pointLight.getRays();
	initializeWalls();

	const int targetFPS = 32;
	const int frameDelay = 1000 / targetFPS;

	while (!quit) // listen to esc key event
	{
		Uint32 frameStart = SDL_GetTicks();
		getInputs();
		update();

		Uint32 frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void initializeWalls()
{
	walls.resize(NR_OF_WALLS);
	// Window borders
	walls[0] = Line(Point(0, 0), Point(799, 0)); // Top
	walls[1] = Line(Point(799, 0), Point(799, 599)); // Right
	walls[2] = Line(Point(799, 599), Point(0, 599)); // Bottom
	walls[3] = Line(Point(0, 599), Point(0, 0)); // Left

	// Rectangle
	walls[4] = Line(Point(50, 50), Point(50, 100));
	walls[5] = Line(Point(50, 100), Point(150, 100));
	walls[6] = Line(Point(150, 100), Point(150, 50));
	walls[7] = Line(Point(150, 50), Point(50, 50));

	// Triangle
	walls[8] = Line(Point(200, 200), Point(300, 200));
	walls[9] = Line(Point(300, 200), Point(250, 100));
	walls[10] = Line(Point(250, 100), Point(200, 200));

	// Hexagon
	walls[11] = Line(Point(400, 300), Point(450, 300));
	walls[12] = Line(Point(450, 300), Point(475, 350));
	walls[13] = Line(Point(475, 350), Point(450, 400));
	walls[14] = Line(Point(450, 400), Point(400, 400));
	walls[15] = Line(Point(400, 400), Point(375, 350));
	walls[16] = Line(Point(375, 350), Point(400, 300));

	// Zigzag wall
	walls[17] = Line(Point(500, 100), Point(550, 150));
	walls[18] = Line(Point(550, 150), Point(500, 200));
	walls[19] = Line(Point(500, 200), Point(550, 250));
	walls[20] = Line(Point(550, 250), Point(500, 300));

	// Star/cross
	walls[21] = Line(Point(600, 400), Point(700, 500));
	walls[22] = Line(Point(700, 400), Point(600, 500));
	walls[23] = Line(Point(650, 350), Point(650, 550));
	walls[24] = Line(Point(550, 450), Point(750, 450));
}

void getInputs()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			quit = true;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
		{
			pointLight.decreaseIntensity();
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT )
		{
			pointLight.increaseIntensity();
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_0)
		{
			showRays = !showRays;
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_1)
		{
			showLightBoundary = !showLightBoundary;
		}


		else if (event.type == SDL_MOUSEMOTION)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			mousePosition.x = static_cast<float>(x);
			mousePosition.y = static_cast<float>(y);
		}
	}
}

void update()
{

	pointLight.setPosition(mousePosition);
	pointLight.updateBoundary();
	lightingSystem.updatePointLight(pointLight, walls);
	//calculateRayHits();
	render();
}

void displayRays()
{
	// Update ray color based on hit status

	rays = pointLight.getRays();

	for (int i = 0; i< pointLight.getCurrentResolution(); i++)
	{
		float closestDistance = 0.0f;
		if (rays[i].hitResult.hasHit)
		{
			rays[i].color = 0xFF0000FF;
			display.drawCircle(rays[i].hitResult.hitPoint.x, rays[i].hitResult.hitPoint.y, 5, 0xFF0000FF, false);
			closestDistance = rays[i].hitResult.distance;
		}
		else
		{
			rays[i].color = 0xFFFFFFFF;
			closestDistance = rays[i].length;
		}

		// Draw the ray
		Line line = {
			rays[i].start,
			Point(
				rays[i].start.x + (rays[i].direction.x * closestDistance),
				rays[i].start.y + (rays[i].direction.y * closestDistance))
		};

		display.drawLine(line, rays[i].color);

		// Draw the ray start point
		//display.drawCircle(ray.start.x, ray.start.y, 3, 0xFF00FF00, false);
	}

}

void render()
{
	display.clearFrameBuffer(0x00000000);

	if (showLightBoundary)
		display.drawLightBoundary(pointLight);

	display.drawLight(pointLight);

	if (showRays)
		displayRays();

	for (const auto& wall : walls)
	{
		display.drawLine(wall, 0xFFFFFFFF);
	}

	display.render();
}

