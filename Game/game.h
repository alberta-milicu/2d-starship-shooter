#pragma once

#include "..\dependente\glew\glew.h"

#include "..\dependente\glfw\glfw3.h"

#include "..\dependente\glm\glm.hpp"
#include "..\dependente\glm\gtc\matrix_transform.hpp"
#include "..\dependente\glm\gtc\type_ptr.hpp"

#include <iostream>

#include "..\Ship\starship.h"
#include "..\Asteroid\asteroid.h"


class Game
{
private:
	GLFWwindow* window;

public:
	Game(GLFWwindow* window);
	~Game();

	int checkShoot(Starship starship, Asteroid asteroid);
	int checkGotShot(Starship starship, Asteroid asteroid);
};