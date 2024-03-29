#pragma once
#include "object.h"
class ABullet : public Object
{
public:
	static unsigned int texture;
	static GLuint bullet_enemy_VAO; //Àû ÅºÈ¯
	static GLuint bullet_enemy_VBO[3];
	static int bullet_enemy_obj;
	static GLuint bullet_VAO; //³» ÅºÈ¯
	static GLuint bullet_VBO[3];
	static int bullet_obj;

	float speed = 0.2f;
	float rotate;

	ABullet(float x, float y, float z, float r) : rotate(r) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update();

};

