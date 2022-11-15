#include "asteroid.h"

Asteroid::Asteroid(glm::vec3 asteroidPosition, int HP, float fallSpeed)
{
	this->asteroidPosition = asteroidPosition;
	this->HP = HP;
	this->fallSpeed = fallSpeed;
}

Asteroid::Asteroid()
{
	this->asteroidPosition = glm::vec3(0.0f, -0.5f, 0.0f);
}

Asteroid::~Asteroid()
{
}

void Asteroid::applyTrans(glm::mat4 trans, GLuint programID)
{
	//trans = glm::translate(trans, glm::vec3(this->asteroidPosition.x, this->asteroidPosition.y, 0.0));
	unsigned int transformLoc = glGetUniformLocation(programID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void Asteroid::moveDown(float unit, GLuint programID)
{
	if (this->getAsteroidPositionY() > -1) {

		glm::mat4 trans(1.0f);
		this->setAsteroidPositionY(this->getAsteroidPositionY() - unit);
		trans = glm::translate(trans, glm::vec3(this->asteroidPosition.x, this->asteroidPosition.y, 0.0));
		this->applyTrans(trans, programID);

	}
}

void Asteroid::checkMotion(GLuint programID,GLuint VAO)
{
	this->moveDown(fallSpeed, programID);

	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Asteroid::shootDown()
{
	glTranslatef(this->getAsteroidPositionX(), this->getAsteroidPositionY(),
		0.0f);
	glClear(GL_TRIANGLES);
}

glm::vec3 Asteroid::getAsteroidPosition()
{
	return this->asteroidPosition;
}

float Asteroid::getAsteroidPositionX()
{
	return this->asteroidPosition.x;
}

float Asteroid::getAsteroidPositionY()
{
	return this->asteroidPosition.y;
}

int Asteroid::getAsteroidHP()
{
	return this->HP;
}

void Asteroid::setAsteroidPosition(glm::vec3 asteroidPosition)
{
	this->asteroidPosition = asteroidPosition;
}

void Asteroid::setAsteroidPositionX(float x)
{
	this->asteroidPosition.x = x;
}

void Asteroid::setAsteroidPositionY(float y)
{
	this->asteroidPosition.y = y;
}

void Asteroid::setAsteroidHP(int HP)
{
	this->HP = HP;
}