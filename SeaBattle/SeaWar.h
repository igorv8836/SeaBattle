#pragma once
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class SeaWar {
public:

	bool debug;

	//Игрок_1 ходит первым
	bool player_1_move;
	//Рандомное поле
	bool is_random_field;
	//первый игрок попал
	bool hit_player_1;
	//второй игрок попал
	bool hit_player_2;
	//первый игрок уничтожил корабль
	bool player_1_destroy;
	//второй игрок уничтожил корабль
	bool player_2_destroy;
	//прошлое попадание второго игрока
	int hit_past_move[2];
	char direction;

	//Поля для вывода на экран
	char field_1[12][12];
	char field_2[12][12];
	//Поля, куда стреляли
	char field_attack_1[12][12];
	char field_attack_2[12][12];

	//поля с кораблями
	int player1_ship[10][10] = { 0 };
	int player2_ship[10][10] = { 0 };

	//поля, куда стреляли
	int player1_attack[10][10] = { 0 };
	int player2_attack[10][10] = { 0 };

	//количество оставшихся кораблей
	int cnt_ship_1[5] = { 0 };
	int cnt_ship_2[5] = { 0 };


	SeaWar();
	//инициализация стартового поля
	void start_map(char a[12][12]);

	//проверка количества кораблей
	bool check_cnt_ship(int a[5], int size);
	//получение координат для атаки
	int get_coord(bool player1);
	//проверка направления корабля
	bool check_way(string s);
	//количество кораблей == максимуму
	bool correct_cnt_ship(int a[5], bool win);
	//Проверка координат, в которую хотят поставить корабль
	bool correct_ship_and_fill_array(int x, int y, char a, int size, int m[10][10], int cnt1[5], char f[12][12]);
	bool zero_ship(bool player1);

	//ход
	void move();
	//
	void destroy_ship(int x, int y, int m[10][10], int a[10][10], bool player1);
	void attack(bool player1, int x, int y);

	//заполнение поля кораблями
	void fill_ship(bool random, int m[10][10], int cnt_ship[5], char f[12][12]);	
	//вывод поля на экран
	void print_field(char f[12][12]);
	//вывод поля кораблей и поля атак на экран
	void print_field(char f[12][12], char a[12][12]);


	//выбор режима заполнения поля
	void mode_selection_fill();
	//выбор первого хода
	void first_move();
};