#pragma comment (lib,"winmm.lib")
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "objRead.h"

#define STB_IMAGE_IMPLEMENTATION //�̹������� �ε�
#include "stb_image.h"
using namespace std;

time_t start; //�ð� ����

bool* keyStates = new bool[256]; //Ű ���� ����

// 0=���, 1=������ü
GLuint VAO[4];
GLuint VBO_position[4];
GLuint VBO_normal[4];
GLuint VBO_texture[4];



//bool map[100][100]; // ��
bool map[50][50]; // �� ������ 50x50
