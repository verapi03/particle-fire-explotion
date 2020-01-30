/*
 * Swarm.cpp
 *
 *  Created on: 25/01/2020
 *      Author: VeraPi
 */

#include "Swarm.h"

namespace simulator {

Swarm::Swarm(): LastExecutingTime(0) {
	m_pParticles = new Particle[AMOUNT_PARTICLES];
}

Swarm::~Swarm() {
	delete [] m_pParticles;
}

void Swarm::move(int elapsed) {
	int interval = elapsed - LastExecutingTime;
	LastExecutingTime = elapsed;
	for (int i = 0; i < Swarm::AMOUNT_PARTICLES; i++) {
		m_pParticles[i].move(interval);
	}
}

} /* namespace simulator */
