#pragma once
#include "Display.h"
#include "RayCaster.h"


bool quit = false;
Display display;
RayCaster rayCaster;
point mousePosition;
int const nrOfWalls = 24;
line walls[nrOfWalls];
ray* rays;


int main(int argc, char* argv[]);
void Update();
void Render();
void InitializeWalls();
void GetInputs();
