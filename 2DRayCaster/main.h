#pragma once
#include "Display.h"
#include "PointLight.h"
#include "RayCaster.h"
#include "LightingSystem.h"


bool quit = false;
Display display;
RayCaster rayCaster;
Point mousePosition;
constexpr int NR_OF_WALLS = 25;
std::vector<Line> walls;
std::vector<Ray> rays;
SDL_Event event;
PointLight pointLight;
LightingSystem lightingSystem;
bool showRays;
bool showLightBoundary;

int main(int argc, char* argv[]);
void update();
void calculateRayHits();
void render();
void initializeWalls();
void getInputs();
void displayRays(bool draw, Point hitPoint, Ray ray, float closestDistance);
