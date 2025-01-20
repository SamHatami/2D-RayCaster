#pragma once
#include "Display.h"
#include "PointLight.h"
#include "RayCaster.h"
#include "LightingSystem.h"
#include "Polygon.h"


bool quit = false;
Display display;
RayCaster rayCaster;
Point mousePosition;
constexpr int NR_OF_WALLS = 25;
std::vector<Wall> walls;
std::vector<Ray> rays;
std::vector<Polygon> world_polygons;
SDL_Event event;
PointLight pointLight;
DirectionalLight mainDirectional;
LightingSystem lightingSystem;
bool showRays;
bool showLightBoundary;

int main(int argc, char* argv[]);
void update();
void render();
void initialize_walls();
void get_inputs();
void draw_wall_normals();
