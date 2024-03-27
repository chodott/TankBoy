#pragma once
#include "object.h"
class Obstacle : public Object
{
public:

	static GLuint VAO[2];
	static GLuint VBO[2][3];
	static unsigned int block_texture; //��ֹ� �ؽ�ó�� �� ���Ϸ� ó������
	static int block_obj[2];

public:
	int type; //1: 1x1 / 2: 2x1 / 3: 1x2
	float block_y = 0.0f;
	void draw(unsigned int modelLocation, unsigned int objColorLocation);
};

