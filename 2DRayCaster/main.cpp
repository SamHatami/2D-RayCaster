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

	//lightingSystem.updateDirectionalLight(mainDirectional, walls);

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
    // Rectangle
    std::vector<Vertex> rect_corners = {
        {50, 50, 0xFFFFFFFF},
        {50, 200, 0xFFFFFFFF},
        {100, 200, 0xFFFFFFFF},
        {100, 50, 0xFFFFFFFF}
    };

    std::vector<Edge> rect_edges = {
        {rect_corners[0], rect_corners[1], false},
        {rect_corners[1], rect_corners[2], false},
        {rect_corners[2], rect_corners[3], false},
        {rect_corners[3], rect_corners[0], false}
    };

    Polygon rect(rect_corners, rect_edges);
    world_polygons.emplace_back(rect);

    // Triangle
    std::vector<Vertex> triangle_corners = {
        {200, 200, 0xFFFFFFFF},
        {300, 200, 0xFFFFFFFF},
        {250, 100, 0xFFFFFFFF}
    };

    std::vector<Edge> triangle_edges = {
        {triangle_corners[0], triangle_corners[1], false},
        {triangle_corners[1], triangle_corners[2], false},
        {triangle_corners[2], triangle_corners[0], false}
    };

    Polygon triangle(triangle_corners, triangle_edges);
    world_polygons.emplace_back(triangle);

    // Hexagon
    std::vector<Vertex> hexagon_corners = {
        {400, 300, 0xFFFFFFFF},
        {375, 350, 0xFFFFFFFF},
        {400, 400, 0xFFFFFFFF},
        {450, 400, 0xFFFFFFFF},
        {475, 350, 0xFFFFFFFF},
        {450, 300, 0xFFFFFFFF}
    };

    std::vector<Edge> hexagon_edges = {
        {hexagon_corners[0], hexagon_corners[1], false},
        {hexagon_corners[1], hexagon_corners[2], false},
        {hexagon_corners[2], hexagon_corners[3], false},
        {hexagon_corners[3], hexagon_corners[4], false},
        {hexagon_corners[4], hexagon_corners[5], false},
        {hexagon_corners[5], hexagon_corners[0], false}
    };

    Polygon hexagon(hexagon_corners, hexagon_edges);
    world_polygons.emplace_back(hexagon);

    // Hexagon with a hole
    std::vector<Vertex> hexagonWithHole_corners = {
        // Outer hexagon
        {600, 300, 0xFFFFFFFF},
        {575, 350, 0xFFFFFFFF},
        {600, 400, 0xFFFFFFFF},
        {650, 400, 0xFFFFFFFF},
        {675, 350, 0xFFFFFFFF},
        {650, 300, 0xFFFFFFFF},
        // Inner hexagon (hole)
        {625, 325, 0xFFFFFFFF},
        {600, 350, 0xFFFFFFFF},
        {625, 375, 0xFFFFFFFF},
        {650, 375, 0xFFFFFFFF},
        {675, 350, 0xFFFFFFFF},
        {650, 325, 0xFFFFFFFF}
    };

    std::vector<Edge> hexagonWithHole_edges = {
        // Outer hexagon
        {hexagonWithHole_corners[0], hexagonWithHole_corners[1], false},
        {hexagonWithHole_corners[1], hexagonWithHole_corners[2], false},
        {hexagonWithHole_corners[2], hexagonWithHole_corners[3], false},
        {hexagonWithHole_corners[3], hexagonWithHole_corners[4], false},
        {hexagonWithHole_corners[4], hexagonWithHole_corners[5], false},
        {hexagonWithHole_corners[5], hexagonWithHole_corners[0], false},
        // Inner hexagon (hole)
        {hexagonWithHole_corners[6], hexagonWithHole_corners[7], true},
        {hexagonWithHole_corners[7], hexagonWithHole_corners[8], true},
        {hexagonWithHole_corners[8], hexagonWithHole_corners[9], true},
        {hexagonWithHole_corners[9], hexagonWithHole_corners[10], true},
        {hexagonWithHole_corners[10], hexagonWithHole_corners[11], true},
        {hexagonWithHole_corners[11], hexagonWithHole_corners[6], true}
    };

    Polygon hexagonWithHole(hexagonWithHole_corners, hexagonWithHole_edges);
    world_polygons.emplace_back(hexagonWithHole);

    // Zigzag wall (enclosed)
    std::vector<Vertex> zigzag_corners = {
        {500, 100, 0xFFFFFFFF},
        {550, 150, 0xFFFFFFFF},
        {500, 200, 0xFFFFFFFF},
        {550, 250, 0xFFFFFFFF},
        {500, 300, 0xFFFFFFFF},
        {450, 250, 0xFFFFFFFF},
        {500, 200, 0xFFFFFFFF},
        {450, 150, 0xFFFFFFFF}
    };

    std::vector<Edge> zigzag_edges = {
        {zigzag_corners[0], zigzag_corners[1], false},
        {zigzag_corners[1], zigzag_corners[2], false},
        {zigzag_corners[2], zigzag_corners[3], false},
        {zigzag_corners[3], zigzag_corners[4], false},
        {zigzag_corners[4], zigzag_corners[5], false},
        {zigzag_corners[5], zigzag_corners[6], false},
        {zigzag_corners[6], zigzag_corners[7], false},
        {zigzag_corners[7], zigzag_corners[0], false}
    };

    Polygon zigzag(zigzag_corners, zigzag_edges);
    world_polygons.emplace_back(zigzag);

    // Star/cross (enclosed)
    std::vector<Vertex> star_corners = {
        {600, 400, 0xFFFFFFFF},
        {700, 500, 0xFFFFFFFF},
        {700, 400, 0xFFFFFFFF},
        {600, 500, 0xFFFFFFFF},
        {650, 350, 0xFFFFFFFF},
        {650, 550, 0xFFFFFFFF},
        {550, 450, 0xFFFFFFFF},
        {750, 450, 0xFFFFFFFF}
    };

    std::vector<Edge> star_edges = {
        {star_corners[0], star_corners[1], false},
        {star_corners[1], star_corners[2], false},
        {star_corners[2], star_corners[3], false},
        {star_corners[3], star_corners[0], false},
        {star_corners[4], star_corners[5], false},
        {star_corners[5], star_corners[6], false},
        {star_corners[6], star_corners[7], false},
        {star_corners[7], star_corners[4], false}
    };

    Polygon star(star_corners, star_edges);
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

	//lightingSystem.updateDirectionalLight(mainDirectional, world_polygons);

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

 /*   if (mainDirectional.isActive())
    {
	    display.drawLight(mainDirectional);

	    for (auto worldPolygon : world_polygons)
	    {
			display.drawCastShadows(worldPolygon.get_shadow());
	    }
    }*/

	if (showLightBoundary)
		display.drawLightBoundary(pointLight);

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