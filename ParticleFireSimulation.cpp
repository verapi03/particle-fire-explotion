//============================================================================
// Name        : ParticleFireSimulation.cpp
// Author      : Andres Vera
// Description : Particle Fire Simulation in C++, Ansi-style
//============================================================================

#include <Math.h>
#include "Screen.h"
#include "Particle.h"
#include "Swarm.h"
#include <time.h>
using namespace simulator;

int main() {
	//initialize random seed:
	srand(time(NULL));

	Screen screen;
	if (screen.init() == false) {
		cout << "Error initialising: " << SDL_GetError() << endl;
		return 1;
	}

	Swarm swarm;
	int screenWidth = Screen::SCREEN_WIDTH / 2;
	int screenHeight = Screen::SCREEN_HEIGHT / 2;

	//Game loop.
	while (true) {
		//Draw particles
		int elapsed = SDL_GetTicks();
		unsigned char red = (unsigned char)(1 + sin(elapsed * 0.00011) * 128); // Max value will be 256 which is the most a char can store.
		unsigned char green = (unsigned char)(1 + sin(elapsed * 0.00011) * 128); // The factor 0.0001 helps the function to oscillate slowly.
		unsigned char blue = (unsigned char)(1 + sin(elapsed * 0.0001) * 128);

		swarm.move(elapsed);

		const Particle * const pParticles = swarm.getParticles();
		int x, y;
		for (int i = 0; i < Swarm::AMOUNT_PARTICLES; i++) {
			Particle particle = pParticles[i];
			x = (particle.m_x + 1) * screenWidth; //Maps all particles to the screen (setting their origin to the center of the screen.)
			y = particle.m_y * screenWidth + screenHeight;
			screen.setPixel(x, y, red, blue, green);
		}

		//Draw the screen
		screen.blurBox();
		screen.update();

		//Check for messages/events
		if (!screen.processEvents()) {
			break;
		}
	}

	screen.close();
	return 0;
}
