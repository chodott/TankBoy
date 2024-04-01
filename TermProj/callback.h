#pragma once
#define STB_IMAGE_IMPLEMENTATION //이미지파일 로드
#include "stb_image.h"
#include "framework.h"
#include "shader.h"

GLvoid Timer(int value);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid UpKeyboard(unsigned char key, int x, int y);
GLvoid UpSpecial(int key, int x, int y);
GLvoid Special(int key, int x, int y);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid InitTexture();
GLvoid InitBuffer();

//--- load obj related variabales
int loadObj(const char* filename);
int loadObj_normalize_center(const char* filename);

Framework* framework = new Framework();

GLvoid drawScene(GLvoid)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(s_program[0]);

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
	framework->keyInput(key, true);
}

GLvoid UpKeyboard(unsigned char key, int x, int y) {
	framework->keyInput(key, false);
}

GLvoid Special(int key, int x, int y)
{
	framework->keyInput(key, true);
}

GLvoid UpSpecial(int key, int x, int y)
{
	framework->keyInput(key, false);
}

GLvoid Timer(int value)
{
	framework->update();
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

GLvoid InitBuffer()
{	
	glUseProgram(s_program[0]);

	framework->InitBuffer();

	glEnable(GL_DEPTH_TEST);
}

GLvoid InitTexture() { //여기 평면이랑 탱크 순서 바꿔뒀어열
	stbi_set_flip_vertically_on_load(true);

	framework->InitTexture();
}