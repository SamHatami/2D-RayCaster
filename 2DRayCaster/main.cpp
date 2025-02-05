#include "main.h"
#include <string>

int main(int argc, char* argv[])
{
	// Initialize SDL by calling Setup class?

	//Run "game loop" and wait for event to close window.

	//I should probably do it the c++ way instead of the c# way...

	mousePosition = point(300, 300);
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

    std::vector<Vertex> corners = {};
    std::vector<Edge> edges = {};

    // Rectangle
    Polygon rect;
    corners = {
        {50, 50, 0xFFFFFFFF, &rect},
        {50, 200, 0xFFFFFFFF, &rect},
        {100, 200, 0xFFFFFFFF, &rect},
        {100, 50, 0xFFFFFFFF, &rect}
    };

    rect.set_vertices(corners);

    edges = {
        {0, 1, false, &rect},
        {1, 2, false, &rect},
        {2, 3, false, &rect},
        {3, 0, false, &rect}
    };

	rect.set_edges(edges);
    world_polygons.emplace_back(rect);

    // Triangle
    Polygon triangle;
    corners = {
        {200, 200, 0xFFFFFFFF, &triangle},
        {300, 200, 0xFFFFFFFF, &triangle},
        {250, 100, 0xFFFFFFFF, &triangle}
    };
	triangle.set_vertices(corners);
    edges = {
        {0, 1, false, &triangle},
        {1, 2, false, &triangle},
        {2, 0, false, &triangle}
    };
	triangle.set_edges(edges);
    world_polygons.emplace_back(triangle);

    // Hexagon
    Polygon hexagon;
    corners = {
        {400, 300, 0xFFFFFFFF, &hexagon},
        {375, 350, 0xFFFFFFFF, &hexagon},
        {400, 400, 0xFFFFFFFF, &hexagon},
        {450, 400, 0xFFFFFFFF, &hexagon},
        {475, 350, 0xFFFFFFFF, &hexagon},
        {450, 300, 0xFFFFFFFF, &hexagon}
    };
	hexagon.set_vertices(corners);
    edges = {
        {0, 1, false, &hexagon},
        {1, 2, false, &hexagon},
        {2, 3, false, &hexagon},
        {3, 4, false, &hexagon},
        {4, 5, false, &hexagon},
        {5, 0, false, &hexagon}
    };
	hexagon.set_edges(edges);
    world_polygons.emplace_back(hexagon);

    // Hexagon with a hole
    Polygon hexagonWithHole;
    corners = {
        // Outer hexagon
        {600, 300, 0xFFFFFFFF, &hexagonWithHole},
        {575, 350, 0xFFFFFFFF, &hexagonWithHole},
        {600, 400, 0xFFFFFFFF, &hexagonWithHole},
        {650, 400, 0xFFFFFFFF, &hexagonWithHole},
        {675, 350, 0xFFFFFFFF, &hexagonWithHole},
        {650, 300, 0xFFFFFFFF, &hexagonWithHole},
        // Inner hexagon (hole)
        {625, 325, 0xFFFFFFFF, &hexagonWithHole},
        {600, 350, 0xFFFFFFFF, &hexagonWithHole},
        {625, 375, 0xFFFFFFFF, &hexagonWithHole},
        {650, 375, 0xFFFFFFFF, &hexagonWithHole},
        {675, 350, 0xFFFFFFFF, &hexagonWithHole},
        {650, 325, 0xFFFFFFFF, &hexagonWithHole}
    };
	hexagonWithHole.set_vertices(corners);
    edges = {
        // Outer hexagon
        {0, 1, false, &hexagonWithHole},
        {1, 2, false, &hexagonWithHole},
        {2, 3, false, &hexagonWithHole},
        {3, 4, false, &hexagonWithHole},
        {4, 5, false, &hexagonWithHole},
        {5, 0, false, &hexagonWithHole},
        // Inner hexagon (hole)
        {6, 7, true, &hexagonWithHole},
        {7, 8, true, &hexagonWithHole},
        {8, 9, true, &hexagonWithHole},
        {9, 10, true, &hexagonWithHole},
        {10, 11, true, &hexagonWithHole},
        {11, 6, true, &hexagonWithHole}
    };
	hexagonWithHole.set_edges(edges);
    world_polygons.emplace_back(hexagonWithHole);

    // Zigzag wall (enclosed)
    Polygon zigzag;
    corners = {
        {500, 100, 0xFFFFFFFF, &zigzag},
        {550, 150, 0xFFFFFFFF, &zigzag},
        {500, 200, 0xFFFFFFFF, &zigzag},
        {550, 250, 0xFFFFFFFF, &zigzag},
        {500, 300, 0xFFFFFFFF, &zigzag},
        {450, 250, 0xFFFFFFFF, &zigzag},
        {500, 200, 0xFFFFFFFF, &zigzag},
        {450, 150, 0xFFFFFFFF, &zigzag}
    };
	zigzag.set_vertices(corners);
    edges = {
        {0, 1, false, &zigzag},
        {1, 2, false, &zigzag},
        {2, 3, false, &zigzag},
        {3, 4, false, &zigzag},
        {4, 5, false, &zigzag},
        {5, 6, false, &zigzag},
        {6, 7, false, &zigzag},
        {7, 0, false, &zigzag}
    };
	zigzag.set_edges(edges);
    world_polygons.emplace_back(zigzag);

    // Star/cross (enclosed)
    Polygon star;
    corners = {
        {600, 400, 0xFFFFFFFF, &star},
        {700, 500, 0xFFFFFFFF, &star},
        {700, 400, 0xFFFFFFFF, &star},
        {600, 500, 0xFFFFFFFF, &star},
        {650, 350, 0xFFFFFFFF, &star},
        {650, 550, 0xFFFFFFFF, &star},
        {550, 450, 0xFFFFFFFF, &star},
        {750, 450, 0xFFFFFFFF, &star}
    };
	star.set_vertices(corners);
    edges = {
        {0, 1, false, &star},
        {1, 2, false, &star},
        {2, 3, false, &star},
        {3, 0, false, &star},
        {4, 5, false, &star},
        {5, 6, false, &star},
        {6, 7, false, &star},
        {7, 4, false, &star}
    };
	star.set_edges(edges);
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
		point normalStart = getMidPoint(wall.definition);
		point normalEnd = point{
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
			point(
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

    if (mainDirectional.isActive())
        display.drawLight(mainDirectional);

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