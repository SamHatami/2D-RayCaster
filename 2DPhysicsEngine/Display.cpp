#include <SDL.h>
#include "Display.h"

uint32_t* frameBuffer = NULL;
SDL_Texture* colorBufferTexture = NULL;
SDL_Renderer* renderer = NULL;
int window_height;
int window_width;

SDL_Window* Display::InitializeWindow(int width, int height)
{
	window_width = width;
	window_height = height;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	SDL_Window* window = SDL_CreateWindow(
		"2D vector2 Light - Ray Casting",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width, window_height,
		SDL_WINDOW_SHOWN
	);

	if (window == nullptr)
	{
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return nullptr;
	}

	frameBuffer = new uint32_t[window_width * window_height]();
	renderer = SDL_CreateRenderer(window, -1, 0);
	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width,
		height);
	return window;
}

void Display::render(void)
{
	SDL_UpdateTexture(colorBufferTexture, nullptr, frameBuffer, (int)(window_width * sizeof(uint32_t)));
	//Swithc to streaming in the future
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, colorBufferTexture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void Display::destroyWindow(SDL_Window* window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::clearFrameBuffer(uint32_t color)
{
	for (int i = 0; i < window_width * window_height; i++)
	{
		frameBuffer[i] = color;
	}
}

void Display::drawRectangle(int start_x, int start_y, int width, int height, uint32_t color)
{
	//Check if start values and size values are within the window,
	// else the for loop below will not be able to compute,
	// index out of bound on color buffer

	if (start_x >= window_width || start_x <= 0)
		return;
	if (start_y >= window_height || start_y <= 0)
		return;

	for (int y = start_y; y < height + start_y; y++)
	{
		for (int x = start_x; x < width + start_x; x++)
		{
			frameBuffer[(window_width * y) + x] = color;
		}
	}
}

void Display::drawPixel(int x, int y, uint32_t color)
{
	if (x >= 0 && x < window_width && y >= 0 && y < window_height)
	{
		frameBuffer[(window_width * y) + x] = color;
	}
}

void Display::drawVector2(int pos_x, int pos_y, int size, uint32_t color)
{
	//Check if start values and size values are within the window,
	// else the for loop below will not be able to compute,
	// index out of bound on color buffer

	if (pos_x >= window_width || pos_x <= 0)
		return;
	if (pos_y >= window_height || pos_y <= 0)
		return;

	if (pos_x >= 0 && pos_y >= 0 && pos_x <= window_height && pos_y <= window_width)
	{
		for (int y = pos_y; y < pos_y + size; y++)
		{
			for (int x = pos_x; x < pos_x + size; x++)
			{
				frameBuffer[(window_width * y) + x] = color;
			}
		}
	}
}

void Display::drawCircle(int pos_x, int pos_y, int radius, uint32_t color, bool fill)
{
	//Check if start values and size values are within the window,
	// else the for loop below will not be able to compute,
	// index out of bound on color buffer

	if (pos_x >= window_width || pos_x <= 0)
		return;
	if (pos_y >= window_height || pos_y <= 0)
		return;

	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		drawPixel(pos_x + x, pos_y + y, color);
		drawPixel(pos_x + y, pos_y + x, color);
		drawPixel(pos_x - y, pos_y + x, color);
		drawPixel(pos_x - x, pos_y + y, color);
		drawPixel(pos_x - x, pos_y - y, color);
		drawPixel(pos_x - y, pos_y - x, color);
		drawPixel(pos_x + y, pos_y - x, color);
		drawPixel(pos_x + x, pos_y - y, color);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void Display::fillScene(uint32_t color)
{
	for (int i = 0; i < window_width * window_height; i++)
	{
		frameBuffer[i] = color;
	}
}

//Bresenham's line algorithm
void Display::drawLine(Line line, uint32_t color)
{
	const int dX = (line.end.x - line.start.x);
	const int dY = (line.end.y - line.start.y);

	const int sideLength = abs(dX) >= abs(dY) ? abs(dX) : abs(dY);

	const float xStep = dX / static_cast<float>(sideLength);
	const float yStep = dY / static_cast<float>(sideLength);

	float xPos = line.start.x;
	float yPos = line.start.y;

	for (int i = 0; i <= sideLength; i++)
	{
		drawPixel(static_cast<int>(roundf(xPos)), static_cast<int>(roundf(yPos)), color);
		xPos += xStep;
		yPos += yStep;
	}
}

std::pair<int, int> Display::getWindowDimensions()
{
	return { window_width, window_height };
}

std::vector<Line> Display::getWindowBorders()
{
	std::vector<Line> boundaries;
	boundaries.resize(4);

	//Clockwise: up, right, down, left
	boundaries[0] = Line{ vector2{0, 0}, vector2{0, static_cast<float>(window_width)} };
	boundaries[1] = Line{
		vector2{0, static_cast<float>(window_width)},
		vector2{static_cast<float>(window_height), static_cast<float>(window_width)}
	};
	boundaries[2] = Line{
		vector2{static_cast<float>(window_height), static_cast<float>(window_width)},
		vector2{static_cast<float>(window_height), 0}
	};
	boundaries[3] = Line{ vector2{static_cast<float>(window_height), 0}, vector2{0, 0} };

	return boundaries;
}

//https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage.html
float Display::baryCentricCoordinates(const vector2& a, const vector2& b, const vector2& c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}