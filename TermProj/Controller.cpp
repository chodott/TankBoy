#include "Controller.h"

void Controller::keyInput(unsigned char key, bool bPush)
{
	switch (key) 
	{
	case 'a': 
		if(bPush) tank->turnHead(1); 
		else tank->stopHead(1);
		break;
	case 'd': 
		if (bPush) tank->turnHead(-1); 
		else  tank->stopHead(-1);
		break;
	case ' ':
		if (bPush) tank->charge();
		else tank->attack();
		break;
	}
}

void Controller::keyInput(int key, bool bPush)
{
	switch (key) {
	case 100: 
		if (bPush) tank->turnBody(1);
		else tank->stopBody(1);
		break;
	case 101: 
		if (bPush) tank->moveForward(1);
		else tank->stopMove(1);
		break;
	case 102: 
		if (bPush) tank->turnBody(-1);
		else tank->stopBody(-1);
		break;
	case 103: 
		if (bPush) tank->moveForward(-1);
		else tank->stopMove(-1);
		break;
	}
}

glm::vec3 Controller::getPlayerPos()
{
	return glm::vec3(tank->x, tank->y, tank->z);
}
