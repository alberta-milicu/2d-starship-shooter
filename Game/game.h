#pragma once

#include "..\dependente\glew\glew.h"

#include "..\dependente\glfw\glfw3.h"

#include "..\dependente\glm\glm.hpp"
#include "..\dependente\glm\gtc\matrix_transform.hpp"
#include "..\dependente\glm\gtc\type_ptr.hpp"

#include <iostream>

#include "..\Ship\starship.h"
#include "..\Asteroid\asteroid.h"
#include "..\Health\health.h"


class Game
{
private:
	GLFWwindow* window;
	int score;
	int level;

public:
	Game(GLFWwindow* window, int score, int level);
	~Game();

	int checkHealth(Starship starship, Health health);
	int checkShoot(Starship starship, Asteroid asteroid);
	int checkGotShot(Starship starship, Asteroid asteroid);
	void moveBullet(Starship starship, Asteroid asteroid);


	GLFWwindow* getWindow();
	int getScore();
	int getLevel();

	void setWindow(GLFWwindow* window);
	void setScore(int score);
	void setLevel(int level);
};