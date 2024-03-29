#pragma once
#include "tank.h"
class Controller
{
private:
	ATank* tank = nullptr;

public:
	bool keyStates[256]; //키 상태 변수
	Controller(ATank* tk) : tank(tk) {};
	void keyInput(unsigned char key, bool bPush);
	void keyInput(int key, bool bPush);
	glm::vec3 getPlayerPos();
	inline Object* getPlayer() { return tank; }
};

