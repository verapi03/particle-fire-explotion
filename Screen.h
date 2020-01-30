/*
 * Screen.h
 *
 *  Created on: 24/01/2020
 *      Author: VeraPi
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
using namespace std;

namespace simulator {

class Screen {
public:
	static int const SCREEN_WIDTH = 800;
	static int const SCREEN_HEIGHT = 600;
private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer;
	Uint32 *m_blurredBuffer;
public:
	Screen();
	bool init();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void blurBox();
	void update();
	bool processEvents();
	void close();
};

} /* namespace simulator */

#endif /* SCREEN_H_ */
