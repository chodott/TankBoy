#pragma once
#include "tank.h"
class Controller
{
public:
	ATank* tank = nullptr;
	bool keyStates[256]; //키 상태 변수

	void keyInput(unsigned char key, bool bPush);
	void keyInput(int key, bool bPush);
	Controller(ATank* tk) : tank(tk) {};
};

