#include "blaster.h"

Blaster::Blaster(glm::vec3 blasterPosition, float blasterSpeed, int damage)
{
	this->blasterPosition = blasterPosition;
	this->blasterSpeed = blasterSpeed;
	this->damage = damage;
}

Blaster::Blaster()
{
}

Blaster::~Blaster()
{
}

glm::vec3 Blaster::getBlasterPosition()
{
	return this->blasterPosition;
}

float Blaster::getBlasterSpeed()
{
	return this->blasterSpeed;
}

int Blaster::getBlasterDamage()
{
	return this->damage;
}

void Blaster::setBlasterPosition(glm::vec3 blasterPosition)
{
	this->blasterPosition = blasterPosition;
}

void Blaster::setBlasterSpeed(float blasterSpeed)
{
	this->blasterSpeed = blasterSpeed;
}

void Blaster::setBlasterDamage(int damage)
{
	this->damage = damage;
}