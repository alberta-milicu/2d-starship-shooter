#include "game.h"

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
		if (starship.getStarshipPositionX() >= asteroid.getAsteroidPositionX() - 0.1 &&
			starship.getStarshipPositionX() <= asteroid.getAsteroidPositionX() + 0.1)
			return 1;
	return 0;
}

//int Game::destroyAsteroid(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
//
//		glm::mat4 trans(1.0f);
//		if (starship.getStarshipPositionX() >= asteroid.getAsteroidPositionX() - 0.1 &&
//			starship.getStarshipPositionX() <= asteroid.getAsteroidPositionX() + 0.1)
//		{
//			glTranslatef(asteroid.getAsteroidPositionX(), asteroid.getAsteroidPositionY(),
//				0.0f);
//			glClear(GL_TRIANGLES);
//			return 0;
//		}
//		return 1;
//}