#include "game.h"

int computePositionRelativityX(Starship starship, Asteroid asteroid)
{
	if (starship.getStarshipPositionX() >= asteroid.getAsteroidPositionX() - 0.2 &&
		starship.getStarshipPositionX() <= asteroid.getAsteroidPositionX() + 0.2)
		return 1;
	return 0;
}

int computePositionRelativityY(Starship starship, Asteroid asteroid)
{	
	if (starship.getStarshipPositionY() <= asteroid.getAsteroidPositionY())
		return 1;
	return 0;
}

Game::Game(GLFWwindow* window)
{
	this->window = window;
}

Game::~Game()
{
}

int Game::checkShoot(Starship starship, Asteroid asteroid)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{	
		if (computePositionRelativityX(starship,asteroid) && computePositionRelativityY(starship,asteroid))
			return 1;
	}
	return 0;
}
