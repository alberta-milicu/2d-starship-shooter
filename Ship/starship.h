#pragma once

#include "..\dependente\glew\glew.h"

#include "..\dependente\glfw\glfw3.h"

#include "..\dependente\glm\glm.hpp"
#include "..\dependente\glm\gtc\matrix_transform.hpp"
#include "..\dependente\glm\gtc\type_ptr.hpp"

class Starship
{
	private: 
		glm::vec3 starshipPosition;
		int HP;

	public:
		Starship();
		Starship(glm::vec3 starshipPosition, int HP);
		~Starship();

		void applyTrans(glm::mat4 trans, GLuint programID);

		void moveUp(GLFWwindow* window, float unit, GLuint programID);
		void moveDown(GLFWwindow* window, float unit, GLuint programID);
		void moveLeft(GLFWwindow* window, float unit, GLuint programID);
		void moveRight(GLFWwindow* window, float unit, GLuint programID);

		void checkMotion(GLFWwindow* window, float unit, GLuint programID);

		glm::vec3 getStarshipPosition();
		float getStarshipPositionX();
		float getStarshipPositionY();
		int getStarshipHP();

		void setStarshipPosition(glm::vec3 starshipPosition);
		void setStarshipPositionX(float x);
		void setStarshipPositionY(float y);
		void setStarshipHP(int HP);
};
