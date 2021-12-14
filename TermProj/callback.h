#pragma once
#include "game.h"

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

	unsigned int modelLocation = glGetUniformLocation(s_program[0], "modelTransform");
	unsigned int viewLocation = glGetUniformLocation(s_program[0], "viewTransform");
	unsigned int	projLoc = glGetUniformLocation(s_program[0], "projection");
	unsigned int viewPos = glGetUniformLocation(s_program[0], "viewPos");
	unsigned int objColorLocation = glGetUniformLocation(s_program[0], "objectColor");

	//뷰 변환
	glm::vec3 cameraPos = glm::vec3(tank.x + 5.0f, 10.0f, tank.z + 5.0f); //--- 카메라 위치
	glm::vec3 cameraTarget = glm::vec3(tank.x, 0.5f, tank.z);
	glm::vec3 cameraDirection = glm::normalize(-cameraPos + cameraTarget); //--- 카메라 바라보는 방향
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::vec3 cameraRight = glm::cross(Up, cameraDirection);
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniform3fv(viewPos, 1, glm::value_ptr(cameraPos));
	//투영 변환
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 50.0f);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);

	//조명
	unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos");
	unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor");
	glUniform3f(lightPosLocation, 0, 5.0f, 0);
	glUniform3f(lightColorLocation, 1.0f,1.0f,1.0f);

	//평면 출력
	glm::mat4 PLATE = glm::mat4(1.0f);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(PLATE));
	glUniform3f(objColorLocation, 0.7, 0.7, 0.7);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ground_texture);
	glBindVertexArray(VAO_[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glm::mat4 WALL_left = glm::mat4(1.0f);
	WALL_left = glm::translate(WALL_left, glm::vec3(-25.0f, 25.0f, 0.0f));
	WALL_left = glm::rotate(WALL_left, (GLfloat)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	WALL_left = glm::rotate(WALL_left, (GLfloat)glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(WALL_left));
	glBindTexture(GL_TEXTURE_2D, wall_texture);
	glBindVertexArray(VAO_[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glm::mat4 WALL_right = glm::mat4(1.0f);
	WALL_right = glm::translate(WALL_right, glm::vec3(0.0f, 25.0f, -25.0f));
	WALL_right = glm::rotate(WALL_right, (GLfloat)glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(WALL_right));
	glBindTexture(GL_TEXTURE_2D, wall_texture);
	glBindVertexArray(VAO_[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	draw(modelLocation, objColorLocation);

	if (gameState == 0) {
		glm::mat4 GAME_START = glm::mat4(1.0f);
		GAME_START = glm::translate(GAME_START, glm::vec3(3.0, 5.0, 3.0));
		GAME_START = glm::rotate(GAME_START, glm::radians(-45.0f), glm::vec3(0, 1, 0));
		GAME_START = glm::scale(GAME_START, glm::vec3(0.01, 0.1, 0.03));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GAME_START));
		if(!select_button) glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
		else glUniform3f(objColorLocation, 0.8, 0.8, 0.8);
		glBindTexture(GL_TEXTURE_2D, wall_texture);
		glBindVertexArray(VAO_[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glm::mat4 GAME_END = glm::mat4(1.0f);
		GAME_END = glm::translate(GAME_END, glm::vec3(3.5, 5.0, 3.5));
		GAME_END = glm::rotate(GAME_END, glm::radians(-45.0f), glm::vec3(0, 1, 0));
		GAME_END = glm::scale(GAME_END, glm::vec3(0.01, 0.1, 0.03));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GAME_END));
		if (select_button) glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
		else glUniform3f(objColorLocation, 0.6, 0.6, 0.6);
		glBindTexture(GL_TEXTURE_2D, wall_texture);
		glBindVertexArray(VAO_[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	//더블 버퍼링
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (gameState == 1) {
		switch (key) {
		case 'w': keyStates[0] = true; break;
		case 'a': keyStates[1] = true; break;
		case 's': keyStates[2] = true; break;
		case 'd': keyStates[3] = true; break;
		case ' ': keyStates[8] = true; break;
		}
	}
	else if (gameState == 0 && key == ' ') {
		if (select_button) exit(1);
		else gameState = 1;
	}
}

GLvoid UpKeyboard(unsigned char key, int x, int y) {
	if (gameState == 1) {
		switch (key) {
		case 'w': keyStates[0] = false; break;
		case 'a': keyStates[1] = false; break;
		case 's': keyStates[2] = false; break;
		case 'd': keyStates[3] = false; break;
		case ' ': tank.attack(); keyStates[8] = false; break;
		}
	}
}

GLvoid Special(int key, int x, int y)
{
	if (gameState == 1) {
		switch (key) {
		case 100: keyStates[4] = true; break;
		case 101: {keyStates[7] = false; tank.moving = 1; keyStates[5] = true; break; }
		case 102: keyStates[6] = true; break;
		case 103: {keyStates[5] = false; tank.moving = 1; keyStates[7] = true; break; }
		}
	}
	else if (gameState == 0) {
		if (key == 101) select_button = 0;
		else if(key == 103) select_button = 1;
	}
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
}

GLvoid Timer(int value)
{
	keyOperations();
	update();
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

GLvoid InitBuffer()
{	
	glGenVertexArrays(4, VAO_);
	glGenBuffers(4, VBO_position);
	glGenBuffers(4, VBO_normal);
	glGenBuffers(4, VBO_texture);
	glUseProgram(s_program[0]);

	//평면
	glBindVertexArray(VAO_[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plate), plate, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//장애물
	glBindVertexArray(VAO_[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//탱크(임의)
	tank.obj_body = loadObj("tank_body.obj");
	cout << "탱크 삼각형 수" << tank.obj_body << endl;
	 
	glGenBuffers(4, tank.VBO_pos);
	glGenBuffers(4, tank.VBO_nor);
	glGenBuffers(4, tank.VBO_tex);

	glGenVertexArrays(4, tank.VAO);
	glBindVertexArray(tank.VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_pos[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_nor[0]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_tex[0]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	//포물선 점
	glBindVertexArray(tank.VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_pos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(track), track, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_nor[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(track), track, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//탱크 머리
	tank.obj_head = loadObj("tank_head.obj");

	glBindVertexArray(tank.VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_pos[2]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_nor[2]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_tex[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	//탱크 포신
	tank.obj_cannon = loadObj("tank_cannon.obj");

	glBindVertexArray(tank.VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_pos[3]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_nor[3]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, tank.VBO_tex[3]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

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
	bazooka_obj = loadObj("rifle.obj");
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

	bullet_ally_obj = loadObj("bullet_ally.obj");

	glGenBuffers(3, bullet_ally_VBO);

	glGenVertexArrays(1, &bullet_ally_VAO);
	glBindVertexArray(bullet_ally_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, bullet_ally_VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	outvertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, bullet_ally_VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	outnormal.clear();

	glBindBuffer(GL_ARRAY_BUFFER, bullet_ally_VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, outuv.size() * sizeof(glm::vec2), &outuv[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	outuv.clear();

	glEnable(GL_DEPTH_TEST);
}

GLvoid InitTexture() { //여기 평면이랑 탱크 순서 바꿔뒀어열
	int widthImage, heightImage, numberOfChannel;
	stbi_set_flip_vertically_on_load(true);

	widthImage = 512;
	heightImage = 512;
	numberOfChannel = 0;

	glGenTextures(1, &ground_texture);

	glBindTexture(GL_TEXTURE_2D, ground_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data0 = stbi_load("room_ground.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data0);

	glGenTextures(1, &tank.body_texture);

	glBindTexture(GL_TEXTURE_2D, tank.body_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data1 = stbi_load("tank_body_diffuse.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);

	glGenTextures(1, &tank.head_texture);

	glBindTexture(GL_TEXTURE_2D, tank.head_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("tank_head_diffuse.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);

	glGenTextures(1, &tank.cannon_texture);

	glBindTexture(GL_TEXTURE_2D, tank.cannon_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data3 = stbi_load("tank_cannon_diffuse.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);

	glGenTextures(1, &block_texture);

	glBindTexture(GL_TEXTURE_2D, block_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data4 = stbi_load("obsta_diffuse.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);

	glGenTextures(1, &wall_texture); //벽

	glBindTexture(GL_TEXTURE_2D, wall_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data5 = stbi_load("room_wall.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);

	glGenTextures(1, &rifle_texture); //소총병, 탄환 색

	glBindTexture(GL_TEXTURE_2D, rifle_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data6 = stbi_load("rifle.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);

	glGenTextures(1, &rifle_texture); //소총병, 탄환 색

	glBindTexture(GL_TEXTURE_2D, rifle_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data7 = stbi_load("rifle.jpg", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data7);

	stbi_image_free(data0);
	stbi_image_free(data1);
	stbi_image_free(data2);
	stbi_image_free(data3);
	stbi_image_free(data4);
	stbi_image_free(data5);
	stbi_image_free(data6);
}