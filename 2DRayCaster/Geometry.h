#pragma once
#include <SDL.h>
struct point
{
	float x;
	float y;

	point(float x = 0, float y = 0) : x(x), y(y) {}

};

struct line
{
	point start;
	point end;
	uint32_t color;

	line() : start(point()), end(point()), color(0) {}

	line(point start, point end, uint32_t color = 0xFFFFFF)
		: start(start), end(end), color(color) {}
};

struct circle {
	point center;
	float radius;
	uint32_t color;

	circle(point center, float radius, uint32_t color = 0xFFFFFF)
		: center(center), radius(radius), color(color) {}
};

struct rectangle {
	point start;
	int width;
	int height;
	uint32_t color;

	rectangle(point start, int width, int height, uint32_t color = 0xFFFFFF)
		: start(start), width(width), height(height), color(color) {}
};

