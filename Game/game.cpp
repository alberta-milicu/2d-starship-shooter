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

int computePositionEquityY(Starship starship, Asteroid asteroid)
{
	if (starship.getStarshipPositionY() >= asteroid.getAsteroidPositionY() - 0.2 &&
		starship.getStarshipPositionY() <= asteroid.getAsteroidPositionY() + 0.2)
		return 1;
	return 0;
}

Game::Game(GLFWwindow* window, int score, int level)
{
	this->window = window;
	this->score = score;
	this->level = level;
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

int Game::checkGotShot(Starship starship, Asteroid asteroid)
{
	if (computePositionRelativityX(starship, asteroid) && computePositionEquityY(starship, asteroid))
		return 1;
	return 0;
}

void Game::moveBullet(Starship starship, Asteroid asteroid)
{
	if (checkShoot(starship, asteroid))
	{
		starship.getStarshipBlaster().setBlasterPositionX(starship.getStarshipPositionX());
		starship.getStarshipBlaster().setBlasterPositionY(starship.getStarshipPositionY());

		while (starship.getStarshipBlaster().getBlasterPositionY() < 1)
		{
			starship.getStarshipBlaster().setBlasterPositionY(starship.getStarshipBlaster().getBlasterPositionY() + 0.1f);
			
		}
	}
}


GLFWwindow* Game::getWindow()
{
	return this->window;
}

int Game::getScore()
{
	return this->score;
}

int Game::getLevel()
{
	return this->level;
}

void Game::setWindow(GLFWwindow* window)
{
	this->window = window;
}

void Game::setScore(int score)
{
	this->score = score;
}

void Game::setLevel(int level)
{
	this->level = level;
}