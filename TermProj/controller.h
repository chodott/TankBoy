#pragma once
#include "tank.h"
class Controller
{
public:
	ATank* tank = nullptr;
	bool keyStates[256]; //Ű ���� ����

	void keyInput(unsigned char key, bool bPush);
	void keyInput(int key, bool bPush);
	Controller(ATank* tk) : tank(tk) {};
};

