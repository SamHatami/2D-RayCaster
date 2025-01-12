#pragma once
#include <SDL.h>
#include <iostream>
#include "Geometry.h"
#include "Light.h"
#include "PointLight.h"
#include "Ray.h"

class Display
{
public:
	SDL_Window* InitializeWindow(int width, int height);
	void render(void);
	void destroyWindow(SDL_Window* window);
	void clearFrameBuffer(uint32_t color);
	void drawPixel(int x, int y, uint32_t color);
	void drawPoint(int pos_x, int pos_y, int size, uint32_t color);
	void drawCircle(int pos_x, int pos_y, int radius, uint32_t color, bool fill);
	void drawRectangle(int start_x, int start_y, int width, int height, uint32_t color);
	void drawLine(Line line, uint32_t color);
	void drawLightBoundary(PointLight& light);
	void drawLight(Light& light);
	void rasterizeTriangle(Point& pointA, Point& pointB, Point& pointC, BoundingBox& boundingBox, uint32_t color, Light& light, Point& centerPoint, float
	                       lightIntensity);

private:
	float baryCentricCoordinates(const Point& a, const Point& b, const Point& p);
};
