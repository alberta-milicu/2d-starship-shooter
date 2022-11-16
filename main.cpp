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

static int max_level = -1;

int lvl1Score = 25000;
int lvl2Score = 75000;
int lvl3Score = 150000;
int lvl4Score = 250000;
int lvl5Score = 400000;

int lvlScores[5] = { lvl1Score, lvl2Score, lvl3Score, lvl4Score, lvl5Score };
int lvls[6] = { 0, 1, 2, 3, 4, 5 };

//void display(Game game)
//{
	
	//if (game.getScore() < lvlScores[0] && max_level < 0)
	//{
	//	max_level++;
	//	std::cout << "LEVEL 0" << std::endl;
	//	game.setLevel(lvls[0]);

	//}

	//if (game.getScore() >= lvlScores[0] && game.getScore() <= lvlScores[1] && max_level < 1)
	//{
	//	max_level++;
	//	std::cout << "LEVEL 1" << std::endl;
	//	game.setLevel(lvls[1]);

	//}

	//if (game.getScore() >= lvlScores[1] && game.getScore() <= lvlScores[2] && max_level < 2)
	//{
	//	max_level++;
	//	std::cout << "LEVEL 2" << std::endl;
	//	game.setLevel(lvls[2]);
	//}

	//if (game.getScore() >= lvlScores[2] && game.getScore() <= lvlScores[3] && max_level < 3)
	//{
	//	max_level++;
	//	std::cout << "LEVEL 3" << std::endl;
	//	game.setLevel(lvls[3]);
	//}

	//if (game.getScore() >= lvlScores[3] && game.getScore() <= lvlScores[4] && max_level < 4)
	//{
	//	max_level++;
	//	std::cout << "LEVEL 4" << std::endl;
	//	game.setLevel(lvls[4]);
	//}

	//if (game.getScore() >= lvlScores[4] && max_level < 5)
	//{
	//	max_level++;
	//	std::cout << "MAX LEVEL" << std::endl;
	//	game.setLevel(lvls[5]);
	//}
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
	0.0f,   0.0f, 0.0f,    //center
	-0.075f,   0.15f, 0.0f,    // left top
	0.075f,   0.15f, 0.0f,    // right top
	0.15f,   0.0f, 0.0f,    // right
	0.075f,   -0.15f, 0.0f,    // right bottom (notice sign)
	-0.075f,  -0.15f, 0.0f,    // left bottom
	-0.15f,   0.0f, 0.0f     // left

	};
	GLuint indicesAst[] = {
		0, 1, 2, 3, 4, 5, 6, 1
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


	GLuint programIDAst2 = LoadShaders("SimpleVertexShaderAst2.vertexshader", "SimpleFragmentShaderAst2.fragmentshader");

	GLfloat verticesAst2[] = {
	0.0f,   0.0f, 0.0f,    //center
	-0.075f,   0.15f, 0.0f,    // left top
	0.075f,   0.15f, 0.0f,    // right top
	0.15f,   0.0f, 0.0f,    // right
	0.075f,   -0.15f, 0.0f,    // right bottom (notice sign)
	-0.075f,  -0.15f, 0.0f,    // left bottom
	-0.15f,   0.0f, 0.0f     // left

	};
	GLuint indicesAst2[] = {
		0, 1, 2, 3, 4, 5, 6, 1
	};


	GLuint VAOAst2;
	glGenVertexArrays(1, &VAOAst2);
	glBindVertexArray(VAOAst2);

	GLuint VBO_IDAst2;
	GLuint EBO_IDAst2;
	glGenBuffers(1, &VBO_IDAst2);
	glGenBuffers(1, &EBO_IDAst2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_IDAst2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAst2), verticesAst2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_IDAst2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesAst2), indicesAst2, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(GL_FLOAT),
		0
	);

	glEnableVertexAttribArray(0);

	GLuint programIDAst3 = LoadShaders("SimpleVertexShaderAst3.vertexshader", "SimpleFragmentShaderAst3.fragmentshader");

	GLfloat verticesAst3[] = {
	0.0f,   0.0f, 0.0f,    //center
	-0.075f,   0.15f, 0.0f,    // left top
	0.075f,   0.15f, 0.0f,    // right top
	0.15f,   0.0f, 0.0f,    // right
	0.075f,   -0.15f, 0.0f,    // right bottom (notice sign)
	-0.075f,  -0.15f, 0.0f,    // left bottom
	-0.15f,   0.0f, 0.0f     // left

	};
	GLuint indicesAst3[] = {
		0, 1, 2, 3, 4, 5, 6, 1
	};


	GLuint VAOAst3;
	glGenVertexArrays(1, &VAOAst3);
	glBindVertexArray(VAOAst3);

	GLuint VBO_IDAst3;
	GLuint EBO_IDAst3;
	glGenBuffers(1, &VBO_IDAst3);
	glGenBuffers(1, &EBO_IDAst3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_IDAst3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAst3), verticesAst3, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_IDAst3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesAst3), indicesAst3, GL_STATIC_DRAW);

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

	float unit = 0.0005f;
	//float fallSpeed = 0.0001f;

	Starship starship(glm::vec3(0.0f, -0.5f, 0.0f),10, 0.001f);
	Asteroid asteroid1(glm::vec3(0.0f, 0.8f, 0.0f), 1, 0.0001f);
	Asteroid asteroid2(glm::vec3(0.0f, 0.8f, 0.0f), 1, 0.0001f);
	Asteroid asteroid3(glm::vec3(0.0f, 0.8f, 0.0f), 1, 0.0001f);

	int score = 0, level = 0;
	
	Game game(window,score,level);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 &&
		starship.getStarshipHP()) {
		
		glfwSwapBuffers(window);

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

	
		glUseProgram(programID);
		glBindVertexArray(VAO);

		
		if (game.getScore() < lvlScores[0] && max_level < 0)
		{
			max_level++;
			std::cout << "LEVEL 0" << std::endl;
			game.setLevel(lvls[0]);

		}

		if (game.getScore() >= lvlScores[0] && game.getScore() <= lvlScores[1] && max_level < 1)
		{
			max_level++;
			std::cout << "LEVEL 1" << std::endl;
			game.setLevel(lvls[1]);
			asteroid1.asteroidLevelUp();
			asteroid2.asteroidLevelUp();
			asteroid3.asteroidLevelUp();

			starship.starshipLevelUp();

		}

		if (game.getScore() >= lvlScores[1] && game.getScore() <= lvlScores[2] && max_level < 2)
		{
			max_level++;
			std::cout << "LEVEL 2" << std::endl;
			game.setLevel(lvls[2]);
			asteroid1.asteroidLevelUp();
			asteroid2.asteroidLevelUp();
			asteroid3.asteroidLevelUp();

			starship.starshipLevelUp();
		}

		if (game.getScore() >= lvlScores[2] && game.getScore() <= lvlScores[3] && max_level < 3)
		{
			max_level++;
			std::cout << "LEVEL 3" << std::endl;
			game.setLevel(lvls[3]);
			asteroid1.asteroidLevelUp();
			asteroid2.asteroidLevelUp();
			asteroid3.asteroidLevelUp();

			starship.starshipLevelUp();
		}

		if (game.getScore() >= lvlScores[3] && game.getScore() <= lvlScores[4] && max_level < 4)
		{
			max_level++;
			std::cout << "LEVEL 4" << std::endl;
			game.setLevel(lvls[4]);
			asteroid1.asteroidLevelUp();
			asteroid2.asteroidLevelUp();
			asteroid3.asteroidLevelUp();

			starship.starshipLevelUp();
		}

		if (game.getScore() >= lvlScores[4] && max_level < 5)
		{
			max_level++;
			std::cout << "MAX LEVEL" << std::endl;
			game.setLevel(lvls[5]);
			asteroid1.asteroidLevelUp();
			asteroid2.asteroidLevelUp();
			asteroid3.asteroidLevelUp();

			starship.starshipLevelUp();
		}



		std::cout << game.getLevel() << std::endl;

		starship.checkMotion(window, programID);

		

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
				{
					game.setScore(game.getScore() + 100);
					//std::cout << "SCORE: " << game.getScore() << std::endl;
					asteroid1.spawnAsteroid1(trans, programIDAst);
				}

			}

			if (game.checkGotShot(starship, asteroid1))
			{
				starship.setStarshipHP(starship.getStarshipHP() - 1);
				asteroid1.spawnAsteroid1(trans, programIDAst);
				std::cout << starship.getStarshipHP() << std::endl;

			}

		asteroid1.despawnAsteroid1(trans, programIDAst);

		}

		glUseProgram(programIDAst2);
		glBindVertexArray(VAOAst2);



		trans = glm::mat4(1.0f);


		if (asteroid2.getAsteroidHP())
		{
			asteroid2.applyTrans(trans, programIDAst2);
			asteroid2.checkMotion(programIDAst2, VAOAst2);

			if (game.checkShoot(starship, asteroid2))
			{
				asteroid2.setAsteroidHP(asteroid2.getAsteroidHP() - 1);

				if (!asteroid2.getAsteroidHP())
				{
					game.setScore(game.getScore() + 100);
					//std::cout << "SCORE: " << game.getScore() << std::endl;
					asteroid2.spawnAsteroid2(trans, programIDAst);
				}

			}

			if (game.checkGotShot(starship, asteroid2))
			{
				starship.setStarshipHP(starship.getStarshipHP() - 1);
				asteroid2.spawnAsteroid2(trans, programIDAst2);
				std::cout << starship.getStarshipHP() << std::endl;
			}

			asteroid2.despawnAsteroid2(trans, programIDAst2);

		}

		glUseProgram(programIDAst3);
		glBindVertexArray(VAOAst3);



		trans = glm::mat4(1.0f);


		if (asteroid3.getAsteroidHP())
		{
			asteroid3.applyTrans(trans, programIDAst3);
			asteroid3.checkMotion(programIDAst3, VAOAst3);

			if (game.checkShoot(starship, asteroid3))
			{
				asteroid3.setAsteroidHP(asteroid3.getAsteroidHP() - 1);

				if (!asteroid3.getAsteroidHP())
				{
					game.setScore(game.getScore() + 100);
					//std::cout << "SCORE: " << game.getScore() << std::endl;
					asteroid3.spawnAsteroid3(trans, programIDAst);
				}

			}

			if (game.checkGotShot(starship, asteroid3))
			{
				starship.setStarshipHP(starship.getStarshipHP() - 1);
				asteroid3.spawnAsteroid2(trans, programIDAst3);
				std::cout << starship.getStarshipHP() << std::endl;
			}

			asteroid3.despawnAsteroid3(trans, programIDAst3);

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


