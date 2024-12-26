#pragma once
#include "object.h"
#define ITEM_SPAWN_Y 5.f

class Item : public Plate
{
public:
	static GLuint VAO;
	static GLuint VBO[3];
	static int item_obj;
	static unsigned int item_texture;

	static time_t spawnTime;
	static time_t spawnLength;
	static float size;
	float speed = 0.005;
	bool onfoot = false;

	Item(float x, float y, float z) : Plate(x, y, z) { setBoundary(size, size); }

	void draw(unsigned int modelLocation, unsigned int objColorLocation);
	void update();
	void reset();
	void initialize(float x, float y, float z);

	//Debug
	static int itemCnt;
};

