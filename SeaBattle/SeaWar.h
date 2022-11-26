#pragma once
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class SeaWar {
public:
	char field[12][12] = { ' ' };
	vector <vector <int>> player1_ship[10][10] = { 0 };
	int player2_ship[10][10] = { 0 };
	int player1_attack[10][10] = { 0 };
	int player2_attack[10][10] = { 0 };
	int cnt_ship_1[5] = { 0 };
	int cnt_ship_2[5] = { 0 };

	SeaWar();
	bool check_cnt_ship(int a[5], int size);
	void start_map();
	bool correct_ship_and_fill_array(int x, int y, char a, int size, int m[10][10], int cnt1[5]);
	bool correct_cnt_ship(int a[5]);
	bool check_way(string s);
	void fill_ship(bool random, int m[10][10], int cnt_ship[5]);
	void print_field();
};