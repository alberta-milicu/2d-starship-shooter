#include "starship.h"

Starship::Starship(glm::vec3 starshipPosition)
{
	this->starshipPosition = starshipPosition;
}

Starship::Starship()
{
	this->starshipPosition = glm::vec3(0.0f, -0.5f, 0.0f);
}

Starship::~Starship()
{
}

void Starship::applyTrans(glm::mat4 trans, GLuint programID)
{
	trans = glm::translate(trans, glm::vec3(this->starshipPosition.x, this->starshipPosition.y, 0.0));
	unsigned int transformLoc = glGetUniformLocation(programID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void Starship::moveUp(GLFWwindow* window, float unit, GLuint programID)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && this->getStarshipPositionY() < 1) {

		glm::mat4 trans(1.0f);
		this->setStarshipPositionY(this->getStarshipPositionY() + unit);
		this->applyTrans(trans, programID);

	}
}

void Starship::moveDown(GLFWwindow* window, float unit, GLuint programID)
{
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && this->getStarshipPositionY() > -1) {

		glm::mat4 trans(1.0f);
		this->setStarshipPositionY(this->getStarshipPositionY() - unit);
		this->applyTrans(trans, programID);

	}
}

void Starship::moveLeft(GLFWwindow* window, float unit, GLuint programID)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && this->getStarshipPositionX() > -1) {

		glm::mat4 trans(1.0f);
		this->setStarshipPositionX(this->getStarshipPositionX() - unit);
		this->applyTrans(trans, programID);

	}
}

void Starship::moveRight(GLFWwindow* window, float unit, GLuint programID)
{
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && this->getStarshipPositionX() < 1) {

		glm::mat4 trans(1.0f);
		this->setStarshipPositionX(this->getStarshipPositionX() + unit);
		this->applyTrans(trans, programID);

	}
}


glm::vec3 Starship::getStarshipPosition()
{
	return this->starshipPosition;
}

float Starship::getStarshipPositionX()
{
	return this->starshipPosition.x;
}

float Starship::getStarshipPositionY()
{
	return this->starshipPosition.y;
}

void Starship::setStarshipPosition(glm::vec3 starshipPosition)
{
	this->starshipPosition = starshipPosition;
}

void Starship::setStarshipPositionX(float x)
{
	this->starshipPosition.x = x;
}

void Starship::setStarshipPositionY(float y)
{
	this->starshipPosition.y = y;
}