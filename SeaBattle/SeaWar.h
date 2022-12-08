#pragma once
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <vector>
//#include <SFML/Graphics.hpp>

//using namespace sf;

class SeaWar {
public:

	//получены ли координаты для стрельбы от первого игрока нажатием кнопки мыши
	bool move_recieved;
	//полученные координаты
	int coord_player_1[2];

	bool debug = true;
	//было полезно для отладки
	int k = 0;
	//Игрок_1 ходит?
	bool player_1_move;
	//Рандомное поле
	bool is_random_field;
	//второй игрок попал корабль
	bool player_2_under_destroyed;
	//прошлое попадание второго игрока
	int hit_past_move[2];
	//направления для бота, куда он может стрелять, direction[1] - навверх, direction[2] - направо, 3 - вниз, 4 - налево, direction[0] - не используется
	bool direction[5] = { true, true, true, true, true };
	//куда лучше боту стрелять, если попал, если 0, то выбор рандомный из доступных сторон
	int hit_direction = 0;
	//Поля для вывода на экран
	char field_1[12][12];
	char field_2[12][12];
	//Поля, куда стреляли, для вывода на экран
	char field_attack_1[12][12];
	char field_attack_2[12][12];
	//поля с кораблями
	int player1_ship[10][10] = { 0 };
	int player2_ship[10][10] = { 0 };
	//поля, куда стреляли
	int player1_attack[10][10] = { 0 };
	int player2_attack[10][10] = { 0 };
	//количество кораблей, нужно, чтобы правильно генерировать поле с кораблями
	int cnt_ship_1[5] = { 0 };
	int cnt_ship_2[5] = { 0 };

	SeaWar();
	//инициализация стартового поля, поле с координатами без кораблей
	void start_map(char a[12][12]);
	//проверка количества кораблей при генерации
	bool check_cnt_ship(int a[5], int size);
	//получение координат для атаки от человека свой алгоритм, от бота свой алгоритм
	int get_coord(bool player1);
	//проверка ввода направления корабля при генерации кораблей человеком
	bool check_way(std::string s);
	//количество кораблей == максимуму тогда true, для генерации поля
	bool correct_cnt_ship(int a[5]);
	//Проверка координат, в которую хотят поставить корабль, если подходит, то ставит и заполняет необходимые массивы
	bool correct_ship_and_fill_array(int x, int y, char a, int size, int m[10][10], int cnt1[5], char f[12][12]);
	//если количество оставшихся кораблей == 0, игра заканчивается, выигрывает тот, кто первее уничтожит все корабли
	bool zero_ship(bool player1);
	//уничтожение корабля, если соблюдены все условия
	void destroy_ship(int x, int y, int m[10][10], int a[10][10], bool player1);
	//функция, которая влияет на смену хода, при промахе, заполняет необходимые массивы для корректной работы
	void attack(bool player1, int x, int y);
	void next_move();

	//заполнение поля кораблями, пока количетсво != максимуму
	void fill_ship(bool random, int m[10][10], int cnt_ship[5], char f[12][12]);	
	//вывод поля на экран
	void print_field(char f[12][12]);
	//вывод поля кораблей и поля атак на экран
	void print_field(char f[12][12], char a[12][12]);
	//выбор режима заполнения поля
	void mode_selection_fill();
	//выбор первого хода
	void first_move();
	void graphic_print();
};