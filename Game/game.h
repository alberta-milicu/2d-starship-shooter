#pragma once

#include "..\dependente\glew\glew.h"

#include "..\dependente\glfw\glfw3.h"

#include "..\dependente\glm\glm.hpp"
#include "..\dependente\glm\gtc\matrix_transform.hpp"
#include "..\dependente\glm\gtc\type_ptr.hpp"

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


	//void spawnAsteroid(); //create asteroid
	//void despawnAsteroid(); //destroy on touching lower map limit
	//void destroyAsteroid(); //destroy on getting shot

	//int destroyAsteroid(GLFWwindow* window);
};