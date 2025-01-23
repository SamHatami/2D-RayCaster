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
	initialize_world_polygons();

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

//TODO: Replace with polygons and initialize from a PolygonCreator and SceneManager
void initialize_world_polygons()
{
	//TODO Create Primitives in a PolygonCreator

	std::vector<Vertex> corners;
	std::vector<Edge> edges;

	// Rectangle
	corners = {
		{50, 50},
		{50, 200},
		{100, 200},
		{100, 50}
	};
	edges = {
		{0, 1, false},
		{1, 2, false},
		{2, 3, false},
		{3, 0, false}
	};
	Polygon rect = Polygon(corners, edges);
	world_polygons.emplace_back(rect);

	// Triangle
	corners = {
		{200, 200},
		{300, 200},
		{250, 100}
	};
	edges = {
		{0, 1, false},
		{1, 2, false},
		{2, 0, false}
	};
	Polygon triangle = Polygon(corners, edges);
	world_polygons.emplace_back(triangle);

	// Hexagon
	corners = {
		{400, 300},
		{375, 350},
		{400, 400},
		{450, 400},
		{475, 350},
		{450, 300}
	};
	edges = {
		{0, 1, false},
		{1, 2, false},
		{2, 3, false},
		{3, 4, false},
		{4, 5, false},
		{5, 0, false}
	};
	Polygon hexagon = Polygon(corners, edges);
	world_polygons.emplace_back(hexagon);

	// Hexagon with a hole
	corners = {
		// Outer hexagon
		{600, 300},
		{575, 350},
		{600, 400},
		{650, 400},
		{675, 350},
		{650, 300},
		// Inner hexagon (hole)
		{625, 325},
		{600, 350},
		{625, 375},
		{650, 375},
		{675, 350},
		{650, 325}
	};
	edges = {
		// Outer hexagon
		{0, 1, false},
		{1, 2, false},
		{2, 3, false},
		{3, 4, false},
		{4, 5, false},
		{5, 0, false},
		// Inner hexagon (hole)
		{6, 7, true},
		{7, 8, true},
		{8, 9, true},
		{9, 10, true},
		{10, 11, true},
		{11, 6, true}
	};
	Polygon hexagonWithHole = Polygon(corners, edges);
	world_polygons.emplace_back(hexagonWithHole);

	// Zigzag wall (enclosed)
	corners = {
		{500, 100},
		{550, 150},
		{500, 200},
		{550, 250},
		{500, 300},
		{450, 250},
		{500, 200},
		{450, 150}
	};
	edges = {
		{0, 1, false},
		{1, 2, false},
		{2, 3, false},
		{3, 4, false},
		{4, 5, false},
		{5, 6, false},
		{6, 7, false},
		{7, 0, false}
	};
	Polygon zigzag = Polygon(corners, edges);
	world_polygons.emplace_back(zigzag);

	// Star/cross (enclosed)
	corners = {
		{600, 400},
		{700, 500},
		{700, 400},
		{600, 500},
		{650, 350},
		{650, 550},
		{550, 450},
		{750, 450}
	};
	edges = {
		{0, 1, false},
		{1, 2, false},
		{2, 3, false},
		{3, 0, false},
		{4, 5, false},
		{5, 6, false},
		{6, 7, false},
		{7, 4, false}
	};
	Polygon star = Polygon(corners, edges);
	world_polygons.emplace_back(star);

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

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
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
		display.drawLine(Line{ normalStart,normalEnd }, 0xFF00FFFF);
	}
}

void update()
{
	pointLight.setPosition(mousePosition);
	pointLight.updateBoundary();
	lightingSystem.updatePointLight(pointLight, world_polygons);

	std::vector<Ray> rays = mainDirectional.getRays();

	//calculateRayHits();
	render();
}

void displayRays()
{
	// Update ray color based on hit status

	rays = pointLight.getRays();

	for (int i = 0; i < pointLight.getCurrentResolution(); i++)
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

	for (Polygon& world_polygon : world_polygons)
	{
		display.drawPolygon(world_polygon);
		//draw_wall_normals(); //Replace with option to show wall 


	}

	if (showRays)
		displayRays();


	for (const auto& ray : mainDirectional.getRays())
	{
		if (ray.active)
			display.drawLine(Line{ ray.start,ray.end }, 0xFFFF00FF);
	}


	display.render();
}