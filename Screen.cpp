/*
 * Screen.cpp
 *
 *  Created on: 24/01/2020
 *      Author: VeraPi
 */

#include "Screen.h"
#include <cstdio>
#include <cstring>

namespace simulator {

Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_blurredBuffer(
				NULL) {
}

/*
 * Initialises the SDL objects and renders all pixels on the screen to black.
 */
bool Screen::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	m_window = SDL_CreateWindow("Particle Fire Explosion",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == NULL) {
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_texture == NULL) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	memset(m_buffer, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	m_blurredBuffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	memset(m_blurredBuffer, 0x00,
			SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	return true;
}

/*
 * Uses left bit shifting to compound the color of a pixel, which is a SDL_PIXELFORMAT_RGBA8888,
 * then copies this information into the buffer using the coordinates passed as arguments.
 */
void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF; //Alpha byte.

	m_buffer[(y * SCREEN_WIDTH) + x] = color; //y is the row number, so it should be multiplied by the number of pixels in every row to get to the right row. Then x is added to get to the right colon (the right position of the pixel.)
}

/*
 * Blurs every pixel on the screen by calculating the average color of a 3*3 grid of pixels, assigning
 * said color to the pixel in the center of the grid. The result is a vanishing color effect.
 */
void Screen::blurBox() {
	Uint32 *temp = m_buffer;
	m_buffer = m_blurredBuffer;
	m_blurredBuffer = temp;
	int currentGridY;
	int currentGridX;
	Uint32 color;
	Uint8 red;
	Uint8 green;
	Uint8 blue;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			int totalRed = 0;
			int totalGreen = 0;
			int totalBlue = 0;

			// Calculates the average color of a grid of 9 pixels.
			for (int row = -1; row <= 1; row++) {
				currentGridY = y + row;
				if (currentGridY < 0 || currentGridY >= SCREEN_HEIGHT) {
					continue;
				}
				for (int column = -1; column <= 1; column++) {
					currentGridX = x + column;
					if (currentGridX < 0 || currentGridX >= SCREEN_WIDTH) {
						continue;
					}
					color = m_blurredBuffer[currentGridY * SCREEN_WIDTH
							+ currentGridX];

					red = color >> 24;
					green = color >> 16;
					blue = color >> 8;

					totalRed += red;
					totalGreen += green;
					totalBlue += blue;
				}
			}

			setPixel(x, y, totalRed / 9, totalGreen / 9, totalBlue / 9);
		}
	}
}

/*
 * Updates the screen upon copying the pixels in the buffer on the texture
 * and passing this to the render object which updates the screen.
 */
void Screen::update() {
	SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

/*
 * Captures any event on the screen and acts accordingly.
 */
bool Screen::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

/*
 * Destroys all SDL objects and memory allocated related to the screen.
 */
void Screen::close() {
	delete[] m_buffer;
	delete[] m_blurredBuffer;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

} /* namespace simulator */
