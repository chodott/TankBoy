#pragma once
#include "game.h"
#define STB_IMAGE_IMPLEMENTATION //이미지파일 로드
#include "stb_image.h"
#include "framework.h"
GLvoid Timer(int value);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid UpKeyboard(unsigned char key, int x, int y);
GLvoid UpSpecial(int key, int x, int y);
GLvoid Special(int key, int x, int y);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid InitTexture();
GLvoid InitBuffer();

const int num_vertices = 3;
const int num_triangles = 1;

//--- load obj related variabales
int loadObj(const char* filename);
int loadObj_normalize_center(const char* filename);
float* sphere_object;
int num_Triangle;

Framework* framework = new Framework();

void keyOperations(void) { //키 상호작용 함수
	//if (keyStates[0] && tank.maxRange >= tank.range) tank.range += 0.1f;
	if (keyStates[1]) tank.headR += 5.0f;
	//if (keyStates[2] && tank.minRange <= tank.range) tank.range -= 0.1f;
	if (keyStates[3]) tank.headR -= 5.0f;
	if (keyStates[4]) tank.tankR += 1.0f; //왼
	if (keyStates[5]) tank.move(1); //앞
	if (keyStates[6]) tank.tankR -= 1.0f; //오
	if (keyStates[7]) tank.move(-1); //뒤
	if (keyStates[8]) tank.charge();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(s_program[0]);

	//unsigned int modelLocation = glGetUniformLocation(s_program[0], "modelTransform");
	//unsigned int viewLocation = glGetUniformLocation(s_program[0], "viewTransform");
	//unsigned int	projLoc = glGetUniformLocation(s_program[0], "projection");
	//unsigned int viewPos = glGetUniformLocation(s_program[0], "viewPos");
	//unsigned int objColorLocation = glGetUniformLocation(s_program[0], "objectColor");

	//

	////조명
	//unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos");
	//unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor");
	//glUniform3f(lightPosLocation, 0, 5.0f, 0);
	//glUniform3f(lightColorLocation, 1.0f,1.0f,1.0f);

	//draw(modelLocation, objColorLocation);

	//if (gameState == 0) {
	//	glm::mat4 GAME_START = glm::mat4(1.0f);
	//	GAME_START = glm::translate(GAME_START, glm::vec3(3.0, 5.0, 3.0));
	//	GAME_START = glm::rotate(GAME_START, glm::radians(-45.0f), glm::vec3(0, 1, 0));
	//	GAME_START = glm::rotate(GAME_START, glm::radians(-30.0f), glm::vec3(0, 0, 1));
	//	GAME_START = glm::scale(GAME_START, glm::vec3(0.01, 0.1, 0.03));
	//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GAME_START));
	//	if(!select_button) glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	//	else glUniform3f(objColorLocation, 0.6, 0.6, 0.6);
	//	glBindTexture(GL_TEXTURE_2D, title_texture);
	//	glBindVertexArray(title_start_VAO);
	//	glDrawArrays(GL_TRIANGLES, 0, title_start_obj);

	//	glm::mat4 GAME_END = glm::mat4(1.0f);
	//	GAME_END = glm::translate(GAME_END, glm::vec3(3.5, 5.0, 3.5));
	//	GAME_END = glm::rotate(GAME_END, glm::radians(-45.0f), glm::vec3(0, 1, 0));
	//	GAME_END = glm::rotate(GAME_END, glm::radians(-30.0f), glm::vec3(0, 0, 1));
	//	//GAME_END = glm::scale(GAME_END, glm::vec3(0.01, 0.1, 0.028));
	//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GAME_END));
	//	if (select_button) glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	//	else glUniform3f(objColorLocation, 0.6, 0.6, 0.6);
	//	glBindVertexArray(title_quit_VAO);
	//	glDrawArrays(GL_TRIANGLES, 0, title_quit_obj);

	//	glm::mat4 GAME_TITLE = glm::mat4(1.0f);
	//	GAME_TITLE = glm::translate(GAME_TITLE, glm::vec3(-0.0, 2.8, -0.0));
	//	GAME_TITLE = glm::rotate(GAME_TITLE, glm::radians(-45.0f), glm::vec3(0, 1, 0));
	//	GAME_TITLE = glm::rotate(GAME_TITLE, glm::radians(-30.0f), glm::vec3(0, 0, 1));
	//	GAME_TITLE = glm::scale(GAME_TITLE, glm::vec3(0.05, 0.1, 0.1));
	//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GAME_TITLE));
	//	glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
	//	glBindVertexArray(title_logo_VAO);
	//	glDrawArrays(GL_TRIANGLES, 0, title_logo_obj);
	//}

	framework->draw(s_program[0]);

	//더블 버퍼링
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{

	if (gameState == 0 && key == ' ') {
		if (select_button) exit(1);
		else gameState = 1;
	}

	framework->keyInput(key, true);
}

GLvoid UpKeyboard(unsigned char key, int x, int y) {
	framework->keyInput(key, false);
}

GLvoid Special(int key, int x, int y)
{
	if (gameState == 0) {
		if (key == 101) select_button = 0;
		else if(key == 103) select_button = 1;
	}
	framework->keyInput(key, true);
}

GLvoid UpSpecial(int key, int x, int y)
{
	if (gameState == 1) {
		switch (key) {
		case 100: keyStates[4] = false; break;
		case 101: tank.moving = 0; break;
		case 102: keyStates[6] = false; break;
		case 103: tank.moving = 0; break;
		}
	}
	framework->keyInput(key, false);
}

GLvoid Timer(int value)
{
	keyOperations();
	framework->update();
	update();
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

GLvoid InitBuffer()
{	
	framework->InitBuffer();
	glGenVertexArrays(4, VAO_);
	glGenBuffers(4, VBO_position);
	glGenBuffers(4, VBO_normal);
	glGenBuffers(4, VBO_texture);
	glUseProgram(s_program[0]);

	//장애물
	glBindVertexArray(VAO_[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//라이플맨
	rifle_obj = loadObj("rifle.obj");
	cout << "라이플맨 삼각형 수" << rifle_obj << endl;

	glGenBuffers(3, rifle_VBO);

	glGenVertexArrays(1, &rifle_VAO);
	glBindVertexArray(rifle_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, rifle_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, rifle_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, rifle_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	//바주카맨
	bazooka_obj = loadObj("bazooka.obj");
	cout << "바주카맨 삼각형 수" << bazooka_obj << endl;

	glGenBuffers(3, bazooka_VBO);

	glGenVertexArrays(1, &bazooka_VAO);
	glBindVertexArray(bazooka_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, bazooka_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, bazooka_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, bazooka_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	block_obj[0] = loadObj("obsta1x1.obj");

	glGenVertexArrays(2, block_VAO);

	glGenBuffers(3, block_VBO[0]); //1x1사이즈 장애물
	glBindVertexArray(block_VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, block_VBO[0][0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, block_VBO[0][1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, block_VBO[0][2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	block_obj[1] = loadObj("obsta2x1.obj");

	glGenBuffers(3, block_VBO[1]); //2x1사이즈 장애물
	glBindVertexArray(block_VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, block_VBO[1][0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, block_VBO[1][1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, block_VBO[1][2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	bullet_enemy_obj = loadObj("bullet_enemy.obj");

	glGenBuffers(3, bullet_enemy_VBO);

	glGenVertexArrays(1, &bullet_enemy_VAO);
	glBindVertexArray(bullet_enemy_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, bullet_enemy_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, bullet_enemy_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, bullet_enemy_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	title_logo_obj = loadObj("title_logo.obj");

	glGenBuffers(3, title_logo_VBO);

	glGenVertexArrays(1, &title_logo_VAO);
	glBindVertexArray(title_logo_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, title_logo_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, title_logo_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, title_logo_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	title_start_obj = loadObj("title_start.obj");

	glGenBuffers(3, title_start_VBO);

	glGenVertexArrays(1, &title_start_VAO);
	glBindVertexArray(title_start_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, title_start_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, title_start_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, title_start_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	title_quit_obj = loadObj("title_quit.obj");

	glGenBuffers(3, title_quit_VBO);

	glGenVertexArrays(1, &title_quit_VAO);
	glBindVertexArray(title_quit_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, title_quit_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, title_quit_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, title_quit_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	glEnable(GL_DEPTH_TEST);
}

GLvoid InitTexture() { //여기 평면이랑 탱크 순서 바꿔뒀어열
	int widthImage, heightImage, numberOfChannel;
	stbi_set_flip_vertically_on_load(true);

	framework->InitTexture();

	widthImage = 512;
	heightImage = 512;
	numberOfChannel = 0;

	glGenTextures(1, &rifle_texture); //소총병, 탄환 색

	glBindTexture(GL_TEXTURE_2D, rifle_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data6 = stbi_load("rifle.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);

	glGenTextures(1, &bazooka_texture); //소총병, 탄환 색

	glBindTexture(GL_TEXTURE_2D, bazooka_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data7 = stbi_load("bazooka.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data7);

	glGenTextures(1, &title_texture);

	glBindTexture(GL_TEXTURE_2D, title_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data8 = stbi_load("title.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data8);

	stbi_image_free(data6);
	stbi_image_free(data7);
	stbi_image_free(data8);
}