#pragma once
#include "figure.h"
int GAME_LEVEL = 1;
int check = 0; //�� ������ ���� �����ҰԿ�
void draw(unsigned int modelLocation, unsigned int objColorLocation, GLuint* VAO);
void update();
void collide_check();


void draw(unsigned int modelLocation, unsigned int objColorLocation, GLuint* VAO) {
	tank.draw(modelLocation, objColorLocation);
	for (int i = 0; i < BLOCK_AMOUNT; i++) block[i].draw(modelLocation, objColorLocation, VAO[1]); //��ֹ� ���
	for (int i = 0; i < RIFLE_AMOUNT; i++) rifle[i].draw(modelLocation, objColorLocation); //���Ѻ� ���
}

void update() {
	tank.update();
	//���Ѻ� ����
	if ((time(NULL) - start) % 5 == 0 && (time(NULL)-start) != check) {
		for (int i = 0; i < RIFLE_AMOUNT; i++) {
			if (!rifle[i].active) {
				check = (time(NULL) - start);
				rifle[i].spawn(GAME_LEVEL);
				break;
			}
		}
	}
	for (int i = 0; i < RIFLE_AMOUNT; i++) rifle[i].update(tank.x, tank.z); //���Ѻ� ������Ʈ
	collide_check();
}

void collide_check() {
	for (int i = 0; i < RIFLE_AMOUNT; i++) { //�÷��̾� / ������ źȯ
		if (tank.collide(rifle[i].bullet[0].x, rifle[i].bullet[0].y, rifle[i].bullet[0].z, rifle[i].bullet[0].size) && rifle[i].bullet[0].active) {
			tank.hit();
			rifle[i].bullet[0].active = 0;
		}

		for (int j = 0; j < 10; j++) { //�����ø� // �÷��̾� źȯ
			if (rifle[i].collide(tank.bullet[j]->x, tank.bullet[j]->y, tank.bullet[j]->z, tank.bullet[j]->size) && tank.bullet[j]->active && rifle[i].active) {
				rifle[i].hit();
				tank.bullet[j]->active = 0;
			}
		}
	}
}