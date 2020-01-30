/*
 * Swarm.h
 *
 *  Created on: 25/01/2020
 *      Author: VeraPi
 */

#ifndef SWARM_H_
#define SWARM_H_
#include "Particle.h"

namespace simulator {

class Swarm {
public:
	static int const AMOUNT_PARTICLES = 5000;
private:
	Particle *m_pParticles;
	int LastExecutingTime;
public:
	Swarm();
	virtual ~Swarm();
	const Particle * const getParticles() { return m_pParticles; };
	void move(int elapsed);
};

} /* namespace simulator */

#endif /* SWARM_H_ */
