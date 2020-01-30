/*
 * Particle.h
 *
 *  Created on: 25/01/2020
 *      Author: VeraPi
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <cstdlib>

namespace simulator {

struct Particle {
	double m_x; //member of the screen object.
	double m_y;
private:
	double m_speed;
	double m_direction;
private:
	void init();
public:
	Particle();
	virtual ~Particle();
	void move(int interval);
};

} /* namespace simulator */

#endif /* PARTICLE_H_ */
