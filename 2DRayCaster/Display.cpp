#include <SDL.h>
#include "Display.h"
#include "Geometry.h"

uint32_t* frameBuffer = NULL;
SDL_Texture* colorBufferTexture = NULL;
SDL_Renderer* renderer = NULL;
int window_width;
int window_height;

SDL_Window* Display::InitializeWindow(int width, int height)
{
	window_width = width;
	window_height = height;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}


    SDL_Window* window = SDL_CreateWindow(
        "2D Point Light - Ray Casting",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
		window_width, window_height,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return nullptr;
    }

	frameBuffer = new uint32_t[window_width * window_height]();
	renderer = SDL_CreateRenderer(window, -1, 0);
	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
    return window;
}

void Display::Render(void) {
	SDL_UpdateTexture(colorBufferTexture, NULL, frameBuffer, (int)(window_width * sizeof(uint32_t))); //Swithc to streaming in the future
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

}


void Display::DestroyWindow(SDL_Window* window)
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Display::ClearFrameBuffer(uint32_t color) {
	for (int i = 0; i < window_width*window_height; i++) {
		frameBuffer[i] = color;
	}
}




void Display::DrawRectangle(int start_x, int start_y, int width, int height, uint32_t color) {
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

void Display::DrawPixel(int x, int y, uint32_t color) {

	if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
		frameBuffer[(window_width * y) + x] = color;
	}
}


void Display::DrawPoint(int pos_x, int pos_y, int size, uint32_t color) {
	//Check if start values and size values are within the window,
	// else the for loop below will not be able to compute,
	// index out of bound on color buffer

	if (pos_x >= window_width || pos_x <= 0)
		return;
	if (pos_y >= window_height || pos_y <= 0)
		return;


	if (pos_x >= 0 && pos_y >= 0 && pos_x <= window_height && pos_y <= window_width) {

		for (int y = pos_y; y < pos_y + size; y++)
		{
			for (int x = pos_x; x < pos_x + size; x++)
			{
				frameBuffer[(window_width * y) + x] = color;
			}
		}
	}

}

void Display::DrawCircle(int pos_x, int pos_y, int radius, uint32_t color, bool fill)
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
		DrawPixel(pos_x + x, pos_y + y, color);
		DrawPixel(pos_x + y, pos_y + x, color);
		DrawPixel(pos_x - y, pos_y + x, color);
		DrawPixel(pos_x - x, pos_y + y, color);
		DrawPixel(pos_x - x, pos_y - y, color);
		DrawPixel(pos_x - y, pos_y - x, color);
		DrawPixel(pos_x + y, pos_y - x, color);
		DrawPixel(pos_x + x, pos_y - y, color);

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

void Display::DrawLine(line line, uint32_t color) {

	int delta_x = (line.end.x - line.start.x);
	int delta_y = (line.end.y - line.start.y);

	int side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

	float x_inc = delta_x / (float)side_length;
	float y_inc = delta_y / (float)side_length;

	float current_x = (int)line.start.x;
	float current_y = (int)line.start.y;

	for (int i = 0; i <= side_length; i++) {
		DrawPixel(round(current_x), round(current_y), color);
		current_x += x_inc;
		current_y += y_inc;
	}

}

void Display::DrawRay(ray&)
{

}
