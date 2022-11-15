#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "dependente\glew\glew.h"

#include "dependente\glfw\glfw3.h"

#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

#include "shader.hpp"

#include "Ship\starship.h"
#include "Asteroid\asteroid.h"
#include "Game\game.h"

GLFWwindow* window;
const int width = 728, height = 728;


//void applyRotation(glm::mat4 trans, glm::vec3 starship, GLuint programID)
//{
//	trans = glm::rotate(trans, 45.0f, glm::vec3(starship.x, starship.y, 0.0));
//	unsigned int transformLoc = glGetUniformLocation(programID, "transform");
//	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
//}

void window_callback(GLFWwindow* window, int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

int main(void)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	window = glfwCreateWindow(width, height, "Space ship", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}


	/*Starship starship(glm::vec3(0.0f, -0.5f, 0.0f));
	Asteroid asteroid1(glm::vec3(0.0f, 0.8f, 0.0f), 1, 0.0001f);
	Game game(window);*/

	float unit = 0.00035f;
	float fallSpeed = 0.0001f;


	glViewport(0, 0, width, height);

	glClearColor(0.0f, 0.0f, 0.25f, 0.0f);

	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	GLfloat vertices[] = {
		-0.05f, -0.0f, 0.0f,
		0.05f, -0.0f, 0.0f,
		0.0f, 0.1f, 0.0f
	};
	GLuint indices[] = {
		0,1,2
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO_ID;
	GLuint EBO_ID;
	glGenBuffers(1, &VBO_ID);
	glGenBuffers(1, &EBO_ID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(GL_FLOAT),
		0
	);

	glEnableVertexAttribArray(0);



	GLuint programIDAst = LoadShaders("SimpleVertexShaderAst.vertexshader", "SimpleFragmentShaderAst.fragmentshader");

	GLfloat verticesAst[] = {
	-0.2f,  0.2f, 1.0f, 0.0f, 0.0f, // Top-left
	 0.2f,  0.2f, 0.0f, 1.0f, 0.0f, // Top-right
	 0.2f, -0.2f, 0.0f, 0.0f, 1.0f, // Bottom-right
	-0.2f, -0.2f, 1.0f, 1.0f, 1.0f  // Bottom-left

	};
	GLuint indicesAst[] = {
		0,1,2,
		1,3,2
	};


	GLuint VAOAst;
	glGenVertexArrays(1, &VAOAst);
	glBindVertexArray(VAOAst);

	GLuint VBO_IDAst;
	GLuint EBO_IDAst;
	glGenBuffers(1, &VBO_IDAst);
	glGenBuffers(1, &EBO_IDAst);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_IDAst);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAst), verticesAst, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_IDAst);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesAst), indicesAst, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(GL_FLOAT),
		0
	);

	glEnableVertexAttribArray(0);

	glm::mat4 trans(1.0f);

	glfwSetFramebufferSizeCallback(window, window_callback);
	int drawAsteroidOk = 1;

	Starship starship(glm::vec3(0.0f, -0.5f, 0.0f));
	Asteroid asteroid1(glm::vec3(0.0f, 0.8f, 0.0f), 1, 0.0001f);
	Game game(window);


	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glfwSwapBuffers(window);

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);
		glBindVertexArray(VAO);



		starship.checkMotion(window, unit, programID);



		glUseProgram(programIDAst);
		glBindVertexArray(VAOAst);



		glm::mat4 trans(1.0f);


		if (asteroid1.getAsteroidHP())
		{	
			asteroid1.applyTrans(trans, programIDAst);
			asteroid1.checkMotion(programIDAst, VAOAst);

			if (game.checkShoot(starship, asteroid1))
			{
				asteroid1.setAsteroidHP(asteroid1.getAsteroidHP()-1);

				if (!asteroid1.getAsteroidHP())
					asteroid1.spawnAsteroid(trans, programIDAst);

			}

		asteroid1.despawnAsteroid(trans, programIDAst);

		}
			
	}


	glDeleteBuffers(1, &VBO_ID);
	glDeleteBuffers(1, &EBO_ID);
	glDeleteBuffers(1, &VAO);
	glDeleteProgram(programID);

	glDeleteBuffers(1, &VBO_IDAst);
	glDeleteBuffers(1, &EBO_IDAst);
	glDeleteBuffers(1, &VAOAst);
	glDeleteProgram(programIDAst);

	glfwTerminate();

	return 0;
}


