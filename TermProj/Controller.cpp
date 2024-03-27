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
		else break;
	}
}

void Controller::keyInput(int key, bool bPush)
{
	switch (key) {
	case 100: keyStates[4] = true; break;
	case 101: {keyStates[7] = false; keyStates[5] = true; break; }
	case 102: keyStates[6] = true; break;
	case 103: {keyStates[5] = false; keyStates[7] = true; break; }
	}
}
