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
	pointLight = PointLight(400, 250, 0xFF0000FF, mousePosition);
 	mainDirectional = DirectionalLight();
	mainDirectional.direction = vector2{ -0.25,0.25 };
	rays = pointLight.getRays();
	initialize_walls();

	lightingSystem.updateDirectionalLight(mainDirectional, walls);



	const int targetFPS = 32;
	const int frameDelay = 1000 / targetFPS;

	while (!quit) // listen to esc key event
	{
		Uint32 frameStart = SDL_GetTicks();
		get_inputs();
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

//TODO: Replace with polygons
void initialize_walls()
{
	//TODO Create Primitives in the Geometry name space

	std::vector<Vertex> corners;
	corners.emplace_back(50,50); 
	corners.emplace_back(50,200);
	corners.emplace_back(100,200);
	corners.emplace_back(50,200);

	std::vector<Edge> edges;


	walls.resize(NR_OF_WALLS);
	// Window borders (counter-clockwise, normals pointing outward)
	walls[0] = Wall{ 0, Line(Point(0, 0), Point(799, 0)) };      // Top
	walls[1] = Wall{ 0, Line(Point(799, 0), Point(799, 599)) };  // Right
	walls[2] = Wall{ 0, Line(Point(799, 599), Point(0, 599)) };  // Bottom
	walls[3] = Wall{ 0, Line(Point(0, 599), Point(0, 0)) };      // Left

	// Rectangle (counter-clockwise)
	walls[4] = Wall{ 0, Line(Point(50, 50), Point(50, 100)) };     // Left
	walls[5] = Wall{ 0, Line(Point(50, 100), Point(150, 100)) };   // Bottom
	walls[6] = Wall{ 0, Line(Point(150, 100), Point(150, 50)) };   // Right
	walls[7] = Wall{ 0, Line(Point(150, 50), Point(50, 50)) };     // Top

	// Triangle (counter-clockwise)
	walls[8] = Wall{ 0, Line(Point(200, 200), Point(300, 200)) };  // Bottom
	walls[9] = Wall{ 0, Line(Point(300, 200), Point(250, 100)) };  // Right side
	walls[10] = Wall{ 0, Line(Point(250, 100), Point(200, 200)) }; // Left side

	// Hexagon (counter-clockwise)
	walls[11] = Wall{ 0, Line(Point(400, 300), Point(375, 350)) };   // Upper left
	walls[12] = Wall{ 0, Line(Point(375, 350), Point(400, 400)) };   // Lower left
	walls[13] = Wall{ 0, Line(Point(400, 400), Point(450, 400)) };   // Bottom
	walls[14] = Wall{ 0, Line(Point(450, 400), Point(475, 350)) };   // Lower right
	walls[15] = Wall{ 0, Line(Point(475, 350), Point(450, 300)) };   // Upper right
	walls[16] = Wall{ 0, Line(Point(450, 300), Point(400, 300)) };   // Top

	// Zigzag wall (not an enclosed shape, but maintaining consistent direction top to bottom)
	walls[17] = Wall{ 0, Line(Point(500, 100), Point(550, 150)) };
	walls[18] = Wall{ 0, Line(Point(550, 150), Point(500, 200)) };
	walls[19] = Wall{ 0, Line(Point(500, 200), Point(550, 250)) };
	walls[20] = Wall{ 0, Line(Point(550, 250), Point(500, 300)) };

	// Star/cross (keeping original since it's not an enclosed shape)
	walls[21] = Wall{ 0, Line(Point(600, 400), Point(700, 500)) };
	walls[22] = Wall{ 0, Line(Point(700, 400), Point(600, 500)) };
	walls[23] = Wall{ 0, Line(Point(650, 350), Point(650, 550)) };
	walls[24] = Wall{ 0, Line(Point(550, 450), Point(750, 450)) };
}

void get_inputs()
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

void draw_wall_normals()
{
	for (const Wall& wall : walls)
	{
		int normalLength = 10;
		Point normalStart = getMidPoint(wall.definition);
		Point normalEnd = Point{
			wall.normal.x * normalLength + normalStart.x,
			wall.normal.y * normalLength + normalStart.y
		};
		display.drawLine(Line{normalStart,normalEnd}, 0xFF00FFFF);
	}
}

void update()
{

	pointLight.setPosition(mousePosition);
	pointLight.updateBoundary();
	lightingSystem.updatePointLight(pointLight, walls);

	std::vector<Ray> rays = mainDirectional.getRays();

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

	display.drawLight(mainDirectional);


	display.drawLight(pointLight);


	if (showRays)
		displayRays();

	for (const auto& wall : walls)
	{
		display.drawLine(wall.definition, 0xFFFFFFFF);
	}

	for (const auto& ray : mainDirectional.getRays())
	{
		if (ray.active)
			display.drawLine(Line{ ray.start,ray.end }, 0xFFFF00FF);
	}

	draw_wall_normals();

	display.render();
}

