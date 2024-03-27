#pragma once
#include "figure.h"
int GAME_LEVEL = 1;
int bazooka_check = 0; 
int rifle_check = 0;
int item_check = 0;
void draw(unsigned int modelLocation, unsigned int objColorLocation);
void update();
void collide_check();
void update_level(time_t start);
bool select_button = 0;


void draw(unsigned int modelLocation, unsigned int objColorLocation) {
	tank.draw(modelLocation, objColorLocation);
	for (int i = 0; i < BLOCK_AMOUNT; i++) block[i].draw(modelLocation, objColorLocation); //장애물 출력
	for (int i = 0; i < RIFLE_AMOUNT; i++) rifle[i].draw(modelLocation, objColorLocation); //소총병 출력
	for (int i = 0; i < RIFLE_AMOUNT; i++) bazooka[i].draw(modelLocation, objColorLocation); //바주카병 출력
	for (int i = 0; i < ITEM_AMOUNT; i++) item[i].draw(modelLocation, objColorLocation); //아이템 출력
}

void update() {
	
	if (gameState == 1) {
		update_level(start);
		tank.update();
		//소총병 스폰
		if ((time(NULL) - start) % 5 == 0 && (time(NULL) - start) != rifle_check) {
			for (int i = 0; i < RIFLE_AMOUNT; i++) {
				if (!rifle[i].active) {
					rifle_check = (time(NULL) - start);
					rifle[i].spawn(GAME_LEVEL);
					break;
				}
			}
		}
		//바주카병 스폰
		if ((time(NULL) - start) % 10 == 0 && (time(NULL) - start) != bazooka_check) {
			for (int i = 0; i < BAZOOKA_AMOUNT; i++) {
				if (!bazooka[i].active) {
					bazooka_check = (time(NULL) - start);
					bazooka[i].spawn(GAME_LEVEL);
					break;
				}
			}
		}

		//아이템 스폰
		if ((time(NULL) - start) % 7 == 0 && (time(NULL) - start) != item_check) {
			for (int i = 0; i < ITEM_AMOUNT; i++) {
				if (!item[i].active) {
					item_check = (time(NULL) - start);
					item[i].spawn();
					break;
				}
			}
		}
		for (int i = 0; i < RIFLE_AMOUNT; i++) rifle[i].update(tank.x, tank.z); //소총병 업데이트
		for (int i = 0; i < BAZOOKA_AMOUNT; i++) bazooka[i].update(tank.x, tank.z); //바주카 업데이트
		for (int i = 0; i < ITEM_AMOUNT; i++) item[i].update(); //아이템 업데이트
		collide_check();
	}
}

void collide_check() {
	for (int i = 0; i < RIFLE_AMOUNT; i++) { //플레이어 + 라이플 탄환
		if (tank.collide(rifle[i].bullet[0].x, rifle[i].bullet[0].y, rifle[i].bullet[0].z, rifle[i].bullet[0].size) && rifle[i].bullet[0].active) {
			tank.hit(rifle[i].bullet[0].power);
			rifle[i].bullet[0].active = 0;
		}

		for (int j = 0; j < 10; j++) { //라이플맨 + 플레이어 탄환
			if (rifle[i].collide(tank.bullet[j]->x, tank.bullet[j]->y, tank.bullet[j]->z, tank.bullet[j]->size) && tank.bullet[j]->active && rifle[i].active) {
				rifle[i].hit(tank.bullet[j]->power);
				tank.bullet[j]->active = 0;
			}
		}

		for (int j = 0; j < BLOCK_AMOUNT; j++) { // 라이플맨 탄환 + 장애물
			if (rifle[i].bullet[0].block_collide(block[j].x, block[j].y, block[j].z, block[j].shape)) {
				rifle[i].bullet[0].active = 0;
			}
			if (rifle[i].block_collide(block[j].x, block[j].y, block[j].z, block[j].shape)) {
				rifle[i].x -= cos(rifle[i].rotate) * rifle[i].speed;
				rifle[i].z -= sin(rifle[i].rotate) * rifle[i].speed;
			}
		}
	}

	for (int i = 0; i < BAZOOKA_AMOUNT; i++) {
		if (tank.collide(bazooka[i].bullet[0].x, bazooka[i].bullet[0].y, bazooka[i].bullet[0].z, bazooka[i].bullet[0].size) && bazooka[i].bullet[0].active) {
			tank.hit(bazooka[i].bullet[0].power);
			bazooka[i].bullet[0].active = 0;
		}
		for (int j = 0; j < 10; j++) { //바주카맨 + 플레이어 탄환
			if (bazooka[i].collide(tank.bullet[j]->x, tank.bullet[j]->y, tank.bullet[j]->z, tank.bullet[j]->size) && tank.bullet[j]->active && bazooka[i].active) {
				bazooka[i].hit(tank.bullet[j]->power);
				tank.bullet[j]->active = 0;
			}
		}

		for (int j = 0; j < BLOCK_AMOUNT; j++) { // 바주카맨 탄환 + 장애물
			if (bazooka[i].bullet[0].block_collide(block[j].x, block[j].y, block[j].z, block[j].shape)) {
				bazooka[i].bullet[0].active = 0;
			}
			if (bazooka[i].block_collide(block[j].x, block[j].y, block[j].z, block[j].shape)) {
				bazooka[i].x -= cos(bazooka[i].rotate) * bazooka[i].speed;
				bazooka[i].z -= sin(bazooka[i].rotate) * bazooka[i].speed;
			}
		}
	}

	//플레이어 + 아이템
	for (int i = 0; i < ITEM_AMOUNT; i++) {
		if (tank.collide(item[i].x, item[i].y, item[i].z, item[i].size) && item[i].active){
			tank.upgrade(item[i].skill);
			item[i].active = 0;
		}
	}

	//플레이어 + 장애물
	for (int i = 0; i < BLOCK_AMOUNT; i++) {
		if (tank.block_collide(block[i].x, block[i].y, block[i].z,block[i].shape)) {
			cout << block[i].shape;
			tank.x = tank.x - cos(-tank.tankR * PI) * tank.tankSpeed;
			tank.z = tank.z - sin(-tank.tankR * PI) * tank.tankSpeed;
			tank.moving = 0;
		}
		for (int j = 0; j < 10; j++) { //플레이어 탄환 + 장애물
			if (tank.bullet[j]->block_collide(block[i].x, block[i].y, block[i].z, block[i].shape)) {
				tank.bullet[j]->active = 0;

			}
		}
	}
}

void update_level(time_t start) {
	if (time(NULL) - start >= 80 && GAME_LEVEL != 5) GAME_LEVEL = 5;
	else 	if (time(NULL) - start >= 60 && GAME_LEVEL != 4) GAME_LEVEL = 4;
	else 	if (time(NULL) - start >= 40 && GAME_LEVEL != 3) GAME_LEVEL = 3;
	else 	if (time(NULL) - start >= 20 && GAME_LEVEL != 2) GAME_LEVEL = 2;
}