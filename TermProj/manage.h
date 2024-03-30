#pragma comment (lib,"winmm.lib")
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <mmsystem.h>
#include <Digitalv.h>
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

using namespace std;

time_t start; //시간 측정

bool* keyStates = new bool[256]; //키 상태 변수

// 0=평면, 1=정육면체
GLuint VAO_[4];
GLuint VBO_position[4];
GLuint VBO_normal[4];
GLuint VBO_texture[4];

int gameState = 0;

//bool map[100][100]; // 맵
bool map[50][50]; // 맵 사이즈 50x50

#define BGM "background.wav"
#define RIFLE_SOUND "explosion.wav"
#define KILL_SOUND "kill_enemy.mp3"
#define SPAWN1_SOUND "spawn1.mp3"
#define SPAWN2_SOUND "spawn2.mp3"

MCI_OPEN_PARMS openBgm; //배경음악
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openRifleSound; //라이플 발사
MCI_PLAY_PARMS playRifleSound;
MCI_OPEN_PARMS openKillSound;
MCI_PLAY_PARMS playKillSound;
MCI_OPEN_PARMS openSpawn1Sound;
MCI_PLAY_PARMS playSpawn1Sound;
MCI_OPEN_PARMS openSpawn2Sound;
MCI_PLAY_PARMS playSpawn2Sound;
int dwID;

void playingBgm(void) {
	//openBgm.lpstrElementName = BGM;
	//openBgm.lpstrDeviceType = "waveaudio";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm);
}

void playingRifle(void) {
	//openRifleSound.lpstrElementName = RIFLE_SOUND;
	//openRifleSound.lpstrDeviceType = "waveaudio";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openRifleSound);
	dwID = openRifleSound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, NULL, (DWORD)(LPVOID)&openRifleSound);
}

void playingKill(void) {
	//openKillSound.lpstrElementName = KILL_SOUND;
	//openKillSound.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openKillSound);
	dwID = openKillSound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openKillSound);

}

void playingSpawn1(void) {
	//openSpawn1Sound.lpstrElementName = RIFLE_SOUND;
	//openSpawn1Sound.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openSpawn1Sound);
	dwID = openSpawn1Sound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, NULL, (DWORD)(LPVOID)&openSpawn1Sound);
	mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
}

void playingSpawn2(void) {
	//openSpawn2Sound.lpstrElementName = KILL_SOUND;
	//openSpawn2Sound.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openSpawn2Sound);
	dwID = openSpawn2Sound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, NULL, (DWORD)(LPVOID)&openSpawn2Sound);
}

