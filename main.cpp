#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "dependente\glew\glew.h"

#include "dependente\glfw\glfw3.h"

#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

#include "shader.hpp"


GLFWwindow* window;
const int width = 728, height = 728;

void applyTrans(glm::mat4 trans, glm::vec3 starship, GLuint programID)
{
	trans = glm::translate(trans, glm::vec3(starship.x, starship.y, 0.0));
	unsigned int transformLoc = glGetUniformLocation(programID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

//void window_callback(GLFWwindow* window, int new_width, int new_height)
//{
//	glViewport(0, 0, new_width, new_height);
//}

glm::vec3 starship(0.0f, -0.5f, 0.0f);
//glm::vec3 asteroid(0.8f, 0.8f, 0.0f);
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

	GLfloat vertices[] = {
		-0.05f, -0.0f, 0.0f,
		0.05f, -0.0f, 0.0f,
		0.0f, 0.1f, 0.0f,
	};

	//GLfloat vertices2[] = {
	//	0.05f, -0.0f, 0.0f,
	//	0.05f, 0.8f, 0.0f,
	//	0.0f, 0.1f, 0.0f
	//};


	GLuint indices[] = {
		0,1,2
	};

	//GLuint indices2[] = {
	//	0,1,2
	//};


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

	/*GLuint VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);*/

	//GLuint VBO_ID2;
	//GLuint EBO_ID2;
	//glGenBuffers(1, &VBO_ID2);
	//glGenBuffers(1, &EBO_ID2);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO_ID2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID2);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		0,                  
		3,                  
		GL_FLOAT,           
		GL_FALSE,           
		3 * sizeof(GL_FLOAT),   
		0            
	);

	glm::mat4 trans(1.0f);

	//glfwSetFramebufferSizeCallback(window, window_callback);


	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0){
		glfwSwapBuffers(window);

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);

		glBindVertexArray(VAO);


		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && starship.y < 1) {

			glm::mat4 trans(1.0f);
			starship.y = starship.y + unit;
			//std::cout << starship.y << std::endl;
			applyTrans(trans, starship, programID);

		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && starship.x > -1) {

			glm::mat4 trans(1.0f);
			starship.x = starship.x - unit;
			//std::cout << starship.x<<std::endl;
			applyTrans(trans, starship, programID);

		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && starship.y > -1) {

			glm::mat4 trans(1.0f);
			starship.y = starship.y - unit;
			//std::cout << starship.y << std::endl;
			applyTrans(trans, starship, programID);

		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && starship.x < 1) {

			glm::mat4 trans(1.0f);
			starship.x = starship.x + unit;
			//std::cout << starship.x << std::endl;
			applyTrans(trans, starship, programID);

		}
		
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		/*glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);*/
	}

	glDeleteBuffers(1, &VBO_ID);
	glDeleteBuffers(1, &EBO_ID);
	glDeleteBuffers(1, &VAO);
	glDeleteProgram(programID);

	//glDeleteBuffers(1, &VBO_ID2);
	//glDeleteBuffers(1, &EBO_ID2);
	//glDeleteBuffers(1, &VAO2);

	glfwTerminate();

	return 0;
}


