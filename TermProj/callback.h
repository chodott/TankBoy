#pragma once
#include "game.h"

GLvoid Timer(int value);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid UpKeyboard(unsigned char key, int x, int y);
GLvoid UpSpecial(int key, int x, int y);
GLvoid Special(int key, int x, int y);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid InitBuffer();
GLuint VAO[4];
GLuint VBO_position[4];

const int num_vertices = 3;
const int num_triangles = 1;

//--- load obj related variabales
int loadObj(const char* filename);
int loadObj_normalize_center(const char* filename);
float* sphere_object;
int num_Triangle;

bool* keyStates = new bool[256]; //Ű ���� ����

void keyOperations(void) { //Ű ��ȣ�ۿ� �Լ�
	if (keyStates[0]) tank.range += 0.1f;
	if (keyStates[1]) tank.headR += 5.0f;
	if (keyStates[2]) tank.range -= 0.1f;
	if (keyStates[3]) tank.headR -= 5.0f;
	if (keyStates[4]) tank.tankR += 1.0f;
	if (keyStates[5]) tank.move(true);
	if (keyStates[6]) tank.tankR -= 1.0f;
	if (keyStates[7]) tank.move(false);
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

	//�� ��ȯ
	glm::vec3 cameraPos = glm::vec3(tank.x + 2.0f, 3.0f, tank.z + 2.0f); //--- ī�޶� ��ġ
	glm::vec3 cameraTarget = glm::vec3(tank.x, 0.5f, tank.z);
	glm::vec3 cameraDirection = glm::normalize(-cameraPos + cameraTarget); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	glm::vec3 cameraRight = glm::cross(Up, cameraDirection);
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniform3fv(viewPos, 1, glm::value_ptr(cameraPos));
	//���� ��ȯ
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 50.0f);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);

	//����
	unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos");
	unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor");
	glUniform3f(lightPosLocation, 0.0f, 0.0f, 0.0f);
	glUniform3f(lightColorLocation, 1.0f,1.0f,1.0f);

	//��� ���
	glm::mat4 PLATE = glm::mat4(1.0f);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(PLATE));
	glUniform3f(objColorLocation, 0.5, 0.5, 0.0);
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	draw(modelLocation, objColorLocation, VAO);

	//���� ���۸�
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w': keyStates[0] = true; break;
	case 'a': keyStates[1] = true; break;
	case 's': keyStates[2] = true; break;
	case 'd': keyStates[3] = true; break;
	case ' ': tank.attack();
	}
}

GLvoid UpKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': keyStates[0] = false; break;
	case 'a': keyStates[1] = false; break;
	case 's': keyStates[2] = false; break;
	case 'd': keyStates[3] = false; break;
	}
}

GLvoid Special(int key, int x, int y)
{
	switch (key) {
	case 100: keyStates[4] = true; break;
	case 101: keyStates[5] = true; break;
	case 102: keyStates[6] = true; break;
	case 103: keyStates[7] = true; break;
	}
}

GLvoid UpSpecial(int key, int x, int y)
{
	switch (key) {
	case 100: keyStates[4] = false; break;
	case 101: keyStates[5] = false; break;
	case 102: keyStates[6] = false; break;
	case 103: keyStates[7] = false; break;
	}
}

GLvoid Timer(int value)
{
	keyOperations();
	update();
	for (int i = 0; i < 10; i++) tank.bullet[i]->move();
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

GLvoid InitBuffer()
{
	num_Triangle = loadObj_normalize_center("sphere.obj");
	glGenVertexArrays(4, VAO);
	glGenBuffers(4, VBO_position);
	glUseProgram(s_program[0]);

	//���
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plate), plate, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//��ֹ�
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//��ũ(����)
	glGenVertexArrays(2, tank.VAO);
	glBindVertexArray(tank.VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//������ ��
	glBindVertexArray(tank.VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(track), track, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);




	glEnable(GL_DEPTH_TEST);

}