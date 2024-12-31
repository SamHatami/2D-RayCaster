#pragma once
#include <SDL.h>
#include <iostream>
#include "Geometry.h"
#include "Ray.h"

class Display
{
public:
	SDL_Window* InitializeWindow(int width, int height);
	void Render(void);
	void DestroyWindow(SDL_Window* window);
	void ClearFrameBuffer(uint32_t color);
	static void DrawPixel(int x, int y, uint32_t color);
	void DrawPoint(int pos_x, int pos_y, int size, uint32_t color);
	void DrawCircle(int pos_x, int pos_y, int radius, uint32_t color, bool fill);
	void DrawRectangle(int start_x, int start_y, int width, int height, uint32_t color);
	void DrawLine(line line, uint32_t color);

};
