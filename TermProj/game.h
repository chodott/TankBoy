#pragma once
#include "figure.h"
int GAME_LEVEL = 1;
int check = 0; //�� ������ ���� �����ҰԿ�
void draw(unsigned int modelLocation, unsigned int objColorLocation);
void update();
void collide_check();
void update_level(time_t start);


void draw(unsigned int modelLocation, unsigned int objColorLocation) {
	tank.draw(modelLocation, objColorLocation);
	for (int i = 0; i < BLOCK_AMOUNT; i++) block[i].draw(modelLocation, objColorLocation); //��ֹ� ���
	for (int i = 0; i < RIFLE_AMOUNT; i++) rifle[i].draw(modelLocation, objColorLocation); //���Ѻ� ���
	for (int i = 0; i < ITEM_AMOUNT; i++) item[i].draw(modelLocation, objColorLocation); //������ ���
}

void update() {
	update_level(start);
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
	//������ ����
	if ((time(NULL) - start) % 7 == 0 && (time(NULL) - start) != check) {
		for (int i = 0; i < ITEM_AMOUNT; i++) {
			if (!item[i].active) {
				check = (time(NULL) - start);
				item[i].spawn();
				break;
			}
		}
	}
	for (int i = 0; i < RIFLE_AMOUNT; i++) rifle[i].update(tank.x, tank.z); //���Ѻ� ������Ʈ
	for (int i = 0; i < ITEM_AMOUNT; i++) item[i].update();
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

	//�÷��̾� + ������
	for (int i = 0; i < ITEM_AMOUNT; i++) {
		if (tank.collide(item[i].x, item[i].y, item[i].z, item[i].size) && item[i].active){
			tank.upgrade(item[i].skill);
			item[i].active = 0;
		}
	}

	//�÷��̾� + ��ֹ�
	for (int i = 0; i < BLOCK_AMOUNT; i++) {
		if (tank.block_collide(block[i].x, block[i].y, block[i].z,block[i].shape)) {
			cout << block[i].shape;
			tank.x = tank.x - cos(-tank.tankR * PI) * tank.tankSpeed;
			tank.z = tank.z - sin(-tank.tankR * PI) * tank.tankSpeed;
			tank.moving = 0;
		}
	}
}

void update_level(time_t start) {
	if (time(NULL) - start >= 80 && GAME_LEVEL != 5) GAME_LEVEL = 5;
	else 	if (time(NULL) - start >= 60 && GAME_LEVEL != 4) GAME_LEVEL = 4;
	else 	if (time(NULL) - start >= 40 && GAME_LEVEL != 3) GAME_LEVEL = 3;
	else 	if (time(NULL) - start >= 20 && GAME_LEVEL != 2) GAME_LEVEL = 2;
}