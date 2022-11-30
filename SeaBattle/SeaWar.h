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

	//�����_1 ����� ������
	bool player_1_move;
	//��������� ����
	bool is_random_field;
	//������ ����� �����
	bool hit_player_1;
	//������ ����� �����
	bool hit_player_2;
	//������ ����� ��������� �������
	bool player_1_destroy;
	//������ ����� ��������� �������
	bool player_2_destroy;
	//������� ��������� ������� ������
	int hit_past_move[2];
	char direction;

	//���� ��� ������ �� �����
	char field_1[12][12];
	char field_2[12][12];
	//����, ���� ��������
	char field_attack_1[12][12];
	char field_attack_2[12][12];

	//���� � ���������
	int player1_ship[10][10] = { 0 };
	int player2_ship[10][10] = { 0 };

	//����, ���� ��������
	int player1_attack[10][10] = { 0 };
	int player2_attack[10][10] = { 0 };

	//���������� ���������� ��������
	int cnt_ship_1[5] = { 0 };
	int cnt_ship_2[5] = { 0 };


	SeaWar();
	//������������� ���������� ����
	void start_map(char a[12][12]);

	//�������� ���������� ��������
	bool check_cnt_ship(int a[5], int size);
	//��������� ��������� ��� �����
	int get_coord(bool player1);
	//�������� ����������� �������
	bool check_way(string s);
	//���������� �������� == ���������
	bool correct_cnt_ship(int a[5], bool win);
	//�������� ���������, � ������� ����� ��������� �������
	bool correct_ship_and_fill_array(int x, int y, char a, int size, int m[10][10], int cnt1[5], char f[12][12]);
	bool zero_ship(bool player1);

	//���
	void move();
	//
	void destroy_ship(int x, int y, int m[10][10], int a[10][10], bool player1);
	void attack(bool player1, int x, int y);

	//���������� ���� ���������
	void fill_ship(bool random, int m[10][10], int cnt_ship[5], char f[12][12]);	
	//����� ���� �� �����
	void print_field(char f[12][12]);
	//����� ���� �������� � ���� ���� �� �����
	void print_field(char f[12][12], char a[12][12]);


	//����� ������ ���������� ����
	void mode_selection_fill();
	//����� ������� ����
	void first_move();
};