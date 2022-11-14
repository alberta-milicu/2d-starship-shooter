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


GLFWwindow* window;
const int width = 728, height = 728;

void applyTransf(glm::mat4 trans, glm::vec3 starship, GLuint programID)
{
	trans = glm::translate(trans, glm::vec3(starship.x, starship.y, 0.0));
	unsigned int transformLoc = glGetUniformLocation(programID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

//void window_callback(GLFWwindow* window, int new_width, int new_height)
//{
//	glViewport(0, 0, new_width, new_height);
//}

Starship starship(glm::vec3(0.0f, -0.5f, 0.0f));

//glm::vec3 starship(0.0f, -0.5f, 0.0f);
glm::vec3 asteroid(0.8f, 0.8f, 0.0f);
glm::vec3 asteroid2(0.8f, 0.8f, 0.0f);
float unit = 0.00035f;

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

	glViewport(0, 0, width, height);

	glClearColor(0.0f, 0.0f, 0.25f, 0.0f);

	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	GLuint programIDAst = LoadShaders("SimpleVertexShaderAst.vertexshader", "SimpleFragmentShaderAst.fragmentshader");

	GLfloat vertices[] = {
		-0.05f, -0.0f, 0.0f,
		0.05f, 0.0f, 0.0f,
		0.0f, 0.1f, 0.0f
	};

	GLuint indices[] = {
		0,1,2
	};


	GLfloat verticesAst[] = {
		-0.05f, 0.0f, 0.0f,
		0.05f, 0.0f, 0.0f,
		0.0f, 0.1f, 0.0f,
		0.0f, -0.1f, 0.0f

		//- 0.05f, 0.0f, 0.0f,
		//0.05f, 0.0f, 0.0f,
		//0.0f, 0.1f, 0.0f,
		//0.0f, -0.1f, 0.0f

		//- 0.05f, 0.0f, 0.0f,
		//0.05f, 0.0f, 0.0f,
		//0.0f, 0.1f, 0.0f,
		//0.0f, -0.1f, 0.0f
	};

	GLuint indicesAst[] = {
		0,1,2,
		0,3,1
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

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(GL_FLOAT),
		0
	);

	//glEnableVertexAttribArray(0);

	/*glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(GL_FLOAT),
		0
	);*/

	glm::mat4 trans(1.0f);

	//glfwSetFramebufferSizeCallback(window, window_callback);
	int drawAsteroidOk = 1;


	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		glfwSwapBuffers(window);

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);

		glBindVertexArray(VAO);

		starship.moveUp(window, unit, programID);
		starship.moveDown(window, unit, programID);
		starship.moveLeft(window, unit, programID);
		starship.moveRight(window, unit, programID);


		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glUseProgram(programIDAst);

		glm::mat4 trans(1.0f);

		applyTransf(trans, asteroid, programIDAst);

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {

			glm::mat4 trans(1.0f);
			if (starship.getStarshipPositionX() >= asteroid.x - 0.1 &&
				starship.getStarshipPositionX() <= asteroid.x + 0.1)
				/*asteroid.x = asteroid.x - unit;*/
			{
				glTranslatef(asteroid.x, asteroid.y, asteroid.z);
				glClear(GL_TRIANGLES);
				drawAsteroidOk = 0;
			}
			else
			{
				glEnableVertexAttribArray(0);

				glBindVertexArray(VAOAst);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			//std::cout << starship.x << std::endl;
			std::cout << asteroid.x << std::endl;
			applyTransf(trans, asteroid, programIDAst);

		}

		if (drawAsteroidOk == 1)
		{
			glEnableVertexAttribArray(0);

			glBindVertexArray(VAOAst);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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


