#pragma once
#include "Display.h"
#include "Light.h"
#include "RayCaster.h"


bool quit = false;
Display display;
RayCaster rayCaster;
Point mousePosition;
constexpr int NR_OF_WALLS = 25;
Line walls[NR_OF_WALLS];
Ray* rays;
SDL_Event event;
Light light;
bool showRays;
bool showLightBoundary;

int main(int argc, char* argv[]);
void update();
void calculateRayHits();
void render();
void initializeWalls();
void getInputs();
void displayRays(bool draw, Point hitPoint, Ray ray, float closestDistance);
