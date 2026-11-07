#include "SDL.h"
#include "Display.h"
#include "RigidBody.h"
#include "Simulation.h"
#include "Vector2.h"
#include "main.h"

auto simulation = Simulation();

int main(int argc, char* argv[])
{
	display = Display();

	auto window = display.InitializeWindow(1200, 1000);
	RigidBody particle = RigidBody::create_particle(11, vector2(0, 500));



	simulation.add_rigid_body(particle);


	vector2 position = simulation.rigid_bodies[0].get_position();


	const int targetFPS = 32;
	const int frameDelay = 1000 / targetFPS;

	update();

	while (!quit) // listen to esc key event
	{
		Uint32 frameStart = SDL_GetTicks();
		get_inputs();
		render();
		Uint32 frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();


	//SDL_DestroyWindow(window);
	//SDL_Quit();

	return 0;
}

void update()
{
	simulation.simulate();

}

void render()
{
	display.clearFrameBuffer(0x00000000);
	for (vector2 pos : simulation.rigid_bodies[0].get_trajectory())
	{
		display.drawPixel(pos.x, 1000-pos.y,  0xFFFFFFFF);
	}
	display.render();
}

void get_inputs()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			quit = true;
		}
	}
}