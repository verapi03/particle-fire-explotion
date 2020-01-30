/*
 * Particle.cpp
 *
 *  Created on: 25/01/2020
 *      Author: VeraPi
 */

#include "Particle.h"
#include <iostream>
#include <math.h>

namespace simulator {

Particle::Particle(): m_x(0), m_y(0) {
	init();
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

void Particle::init() {
	m_x = 0;
	m_y = 0;
	m_direction = (2 * M_PI * rand()) / RAND_MAX;
	m_speed = (0.04 * rand()) / RAND_MAX;
	m_speed *= m_speed;
}

void Particle::move(int interval) {
	m_direction += interval * 0.0003;

	double speedx = m_speed * cos(m_direction);
	double speedy = m_speed * sin(m_direction);

	m_x += speedx * interval;
	m_y += speedy * interval;

	//If a particles goes off the edge of the screen it is reinitialised on the center of the screen.
	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
		init();
	}
}

} /* namespace simulator */
