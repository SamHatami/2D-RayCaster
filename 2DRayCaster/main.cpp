
#include "main.h"
#include <string>



int main(int argc, char* argv[])
{
	// Initialize SDL by calling Setup class?

	//Run "game loop" and wait for event to close window.

	//I should probably do it the c++ way instead of the c# way...

	mousePosition = point(0, 0);
	rayCaster = RayCaster();
	rays = rayCaster.GetRays();

	SDL_Window* window = display.InitializeWindow(800, 600);

	InitializeWalls();

	while (!quit)
	{
		Uint32 startTicks = SDL_GetTicks();
		Uint64 startPerf = SDL_GetPerformanceCounter();
		Update();

	}
	//SDL_Delay(5000); // Wait for 3 seconds
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void InitializeWalls()
{
	// Window borders
	walls[0] = line(point(0, 0), point(799, 0)); // Top
	walls[1] = line(point(799, 0), point(799, 599)); // Right
	walls[2] = line(point(799, 599), point(0, 599)); // Bottom
	walls[3] = line(point(0, 599), point(0, 0)); // Left

	// Rectangle
	walls[4] = line(point(50, 50), point(50, 100));
	walls[5] = line(point(50, 100), point(150, 100));
	walls[6] = line(point(150, 100), point(150, 50));
	walls[7] = line(point(150, 50), point(50, 50));

	// Triangle
	walls[8] = line(point(200, 200), point(300, 200));
	walls[9] = line(point(300, 200), point(250, 100));
	walls[10] = line(point(250, 100), point(200, 200));

	// Hexagon
	walls[11] = line(point(400, 300), point(450, 300));
	walls[12] = line(point(450, 300), point(475, 350));
	walls[13] = line(point(475, 350), point(450, 400));
	walls[14] = line(point(450, 400), point(400, 400));
	walls[15] = line(point(400, 400), point(375, 350));
	walls[16] = line(point(375, 350), point(400, 300));

	// Zigzag wall
	walls[17] = line(point(500, 100), point(550, 150));
	walls[18] = line(point(550, 150), point(500, 200));
	walls[19] = line(point(500, 200), point(550, 250));
	walls[20] = line(point(550, 250), point(500, 300));

	// Star/cross
	walls[21] = line(point(600, 400), point(700, 500));
	walls[22] = line(point(700, 400), point(600, 500));
	walls[23] = line(point(650, 350), point(650, 550));
	walls[24] = line(point(550, 450), point(750, 450));
}

void GetInputs()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		mousePosition.x = static_cast<float>(event.motion.x);
		mousePosition.y = static_cast<float>(event.motion.y);
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			quit = true;
		}
	default: 
		break;
	}
}

void Update()
{
	Uint64 start = SDL_GetPerformanceCounter();
	rayCaster.CastRays(mousePosition);
	GetInputs();
	Render();
	Uint64 end = SDL_GetPerformanceCounter();


	float elapsedMS = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency()) * 1000.0f;

	// Cap to 60 FPS
	SDL_Delay(floor(16.666f - elapsedMS));


}

void Render()
{
	display.ClearFrameBuffer(0x00000000);
	//draw rectangle at mouse, with offset of 5 pixels to center it over the tip
	//display.DrawRectangle(mousePosition.x-5, mousePosition.y-5, 10, 10, 0xFFFFFF00);


	//perhaps check which walls are closest to the mouse and only checkhit on those?

	for (int i = 0; i < nrOfWalls; i++)
	{
		display.DrawLine(walls[i], 0xFFFFFFFF);
	}

	for (int i = 0; i < rayCaster.NrOfRays(); i++)
	{
		bool rayHasHit = false;
		float closestDistance = FLT_MAX;
		point closestHitPoint;

		for (int j = 0; j < nrOfWalls; j++)
		{
			RayHitResult hit = rayCaster.CheckHit(rays[i], walls[j]);

			if (hit.hasHit)
			{
				const float distance = sqrtf(pow(hit.hitPoint.x - rays[i].start.x, 2) +
					powf(hit.hitPoint.y - rays[i].start.y, 2));
				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestHitPoint = hit.hitPoint;
					rayHasHit = true;
				}
			}
		}

		// Update ray color based on hit status
		if (rayHasHit)
		{
			rays[i].color = 0xFFFF00FF;
			display.DrawCircle(closestHitPoint.x, closestHitPoint.y, 5, 0xFF0000FF, false);
		}
		else
		{
			rays[i].color = 0x00FFFFFF;
			closestDistance = rays[i].length;
		}

		// Draw the ray
		line line = {
			rays[i].start,
			point(
				rays[i].start.x + (rays[i].direction.x * closestDistance),
				rays[i].start.y + (rays[i].direction.y * closestDistance))
		};
		display.DrawLine(line, rays[i].color);

		// Draw the ray start point
		display.DrawCircle(rays[i].start.x, rays[i].start.y, 3, 0xFF00FF00, false);
	}

	//display.DrawRectangle(200, 200, 100, 100, 0xFFFFFF00);
	display.Render();
}
