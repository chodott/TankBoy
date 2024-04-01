#pragma once
#include "object.h"

#define OBSTACLE_SIZE 1.f

class Obstacle : public Object
{
public:

	static GLuint VAO[2];
	static GLuint VBO[2][3];
	static unsigned int block_texture
		; //장애물 텍스처는 한 파일로 처리했음
	static int block_obj[2];

public:
	int type; //1: 1x1 / 2: 2x1 / 3: 1x2
	float block_y = 0.0f;
	float block_x;
	float block_z;

	void setPos(float x, float z, int type)
	{
		block_x = x;
		block_z = z;
		this->type = type;
		switch (type)
		{
		case 1:
			this->x = block_x;
			this->z = block_z;
			break;
		case 2:
			this->x = block_x + OBSTACLE_SIZE/2;
			this->z = block_z;
			break;
		case 3:
			this->x = block_x;
			this->z = block_z + OBSTACLE_SIZE/2;
		}
		setBoundary(OBSTACLE_SIZE, OBSTACLE_SIZE);
	}
	void setBoundary(float width, float height);
	void draw(unsigned int modelLocation, unsigned int objColorLocation);
};



class Wall : public Plate
{
public:
	static unsigned int wall_texture;
	static unsigned int ground_texture;
	

	int type; //1: left / 0: floor / -1 : right

public:
	Wall(float x, float y, float z, int t): type(t)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void draw(unsigned int modelLocation, unsigned int objColorLocation);

};

