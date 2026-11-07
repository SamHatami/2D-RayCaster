#pragma once
#include <SDL.h>
#include <iostream>
#include "Geometry.h"
#include "Light.h"
#include "vector2Light.h"
#include "Polygon.h"
#include "Ray.h"

class Display
{
public:
	SDL_Window* InitializeWindow(int width, int height);
	void render(void);
	void destroyWindow(SDL_Window* window);
	void clearFrameBuffer(uint32_t color);
	void drawPixel(int x, int y, uint32_t color);
	void drawvector2(int pos_x, int pos_y, int size, uint32_t color);
	void drawCircle(int pos_x, int pos_y, int radius, uint32_t color, bool fill);
	void fillScene(uint32_t color);
	void drawRectangle(int start_x, int start_y, int width, int height, uint32_t color);
	void drawLine(Line line, uint32_t color);
	void drawLightBoundary(vector2Light& light);
	void drawLight(Light& light);
	void drawPolygon(Polygon& polygon);
	void drawCastShadows(Shadow& shadow);
	void rasterizeTriangle(vector2& vector2A, vector2& vector2B, vector2& vector2C, BoundingBox& boundingBox, uint32_t color, Light& light, vector2& centervector2, float
	                       lightIntensity);
	// Gets the window dimensions, returns (width, height) in pixels
	static std::pair<int,int> getWindowDimensions();
	static std::vector<Line> getWindowBorders();
private:
	float baryCentricCoordinates(const vector2& a, const vector2& b, const vector2& p);
};
