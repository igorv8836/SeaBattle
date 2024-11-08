#include "SeaWar.h"
//������������� ����
SeaWar::SeaWar() {

	move_recieved = false;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			field_1[i][j] = ' ';
			field_2[i][j] = ' ';
			field_attack_1[i][j] = ' ';
			field_attack_2[i][j] = ' ';
		}
	}
	player_2_under_destroyed = false;

	//������������� ����
	mode_selection_fill();
	first_move();
	start_map(field_1);
	start_map(field_2);
	start_map(field_attack_1);
	start_map(field_attack_2);
	fill_ship(true, player2_ship, cnt_ship_2, field_2);
	fill_ship(is_random_field, player1_ship, cnt_ship_1, field_1);
	print_field(field_1, field_attack_1);
	if (debug){
		print_field(field_2, field_attack_2);
	}
	//����� ������������� ����
}
//������, ����������� ��� �������� ����, ���������� ��� �������������
void SeaWar::mode_selection_fill() {
	double s;
	std::cout << "�������� ����� ������������ ��������(1-��������, 0-��������� �����): ";
	while (!(std::cin >> s) || !(s == 1 || s == 0)) {
		std::cin.clear();
		std::cin.ignore();
		system("cls");
		std::cout << "�� ��������� ������!" << std::endl;
		std::cout << "�������� ����� ������������ ��������(1-��������, 0-��������� �����): ";
	}
	if (s == 1)
		is_random_field = true;
	else
		is_random_field = false;
}
void SeaWar::first_move() {
	double s;
	std::cout << "�� ������ ������? (1-��, 0-���): ";
	while (!(std::cin >> s) || !(s == 1 || s == 0)) {
		std::cin.clear();
		std::cin.ignore();
		system("cls");
		std::cout << "�� ��������� ������!std::" << std::endl;
		std::cout << "�� ������ ������? (1-��, 0-���): ";
	}
	if (s == 1)
		player_1_move = true;
	else
		player_1_move = false;
	system("cls");
}
//������-��������(�������)
bool SeaWar::check_cnt_ship(int a[5], int size) {
	a[size]++;
	if (a[1] <= 4 && a[2] <= 3 && a[3] <= 2 && a[4] <= 1) {
		a[size]--;
		return true;
	}
	a[size]--;
	return false;
}
bool SeaWar::correct_cnt_ship(int a[5]) {
	if (a[1] == 4 && a[2] == 3 && a[3] == 2 && a[4] == 1)
		return true;
	return false;
}
bool SeaWar::zero_ship(bool player1) {
	int cnt = 0;
	if (player1) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (player1_attack[i][j] == 2) {
					cnt++;
				}
			}
		}
	}
	else {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (player2_attack[i][j] == 2) {
					cnt++;
				}
			}
		}
	}
	if (cnt == 20)
		return true;
	return false;
}
bool SeaWar::check_way(std::string s) {
	if (s.length() == 1 && (s[0] == 'e' || s[0] == 's' || s[0] == 'w' || s[0] == 'n'))
		return true;
	return false;
}
//������ ��� ����������� ������ �� �����
void SeaWar::start_map(char a[12][12]) {
	for (int i = 1; i < 11; i++) {
		for (int j = 0; j < 12; j++)
			a[i][j] = ' ';
		a[0][i] = std::to_string((i - 1))[0];
		a[i][0] = std::to_string((i - 1))[0];
		a[i][11] = '|';
		a[11][i] = '�';
	}
	a[11][0] = 'Y';
	a[0][11] = 'X';
	a[11][11] = '-';
}
void SeaWar::print_field(char f[12][12]) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++)
			std::cout << f[i][j];
		std::cout << std::endl;
	}
}
void SeaWar::print_field(char f[12][12], char a[12][12]) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++)
			std::cout << f[i][j];
		std::cout << "		";

		for (int k = 0; k < 12; k++)
			std::cout << a[i][k];
		std::cout << std::endl;
	}
}
//������ ��� ���������� ���� ���������
bool SeaWar::correct_ship_and_fill_array(int x, int y, char a, int size, int m[10][10], int cnt1[5], char f[12][12]) {
	int x0, y0, x1, y1;

	x0 = x - 1;
	y0 = y - 1;
	x1 = x + 1;
	y1 = y + 1;

	if (!(check_cnt_ship(cnt1, size)))
		return false;

	switch (a) {
	case 's':
		if (y + size - 1 > 9)
			return false;
		for (int i = 0; i < size; i++) {
			if (m[y + i][x] != 0)
				return false;
		}

		for (int i = 0; i < size; i++) {
			m[y + i][x] = i + 1 + 10 * size + 300;
			f[y + i + 1][x + 1] = '*';
		}

		y1 += size - 1;
		break;
	case 'w':
		if (x - size + 1 < 0)
			return false;
		for (int i = 0; i < size; i++) {
			if (m[y][x - i] != 0)
				return false;
		}

		for (int i = 0; i < size; i++) {
			m[y][x - size + 1 + i] = i + 1 + 10 * size + 400;
			f[y + 1][x - i + 1] = '*';
		}

		x0 -= (size - 1);
		break;
	case 'n':
		if (y - size + 1 < 0)
			return false;

		for (int i = 0; i < size; i++) {
			if (m[y - i][x] != 0)
				return false;
		}

		for (int i = 0; i < size; i++) {
			m[y - size + 1 + i][x] = i + 1 + 10 * size + 100;
			f[y - i + 1][x + 1] = '*';
		}

		y0 -= (size - 1);
		break;
	case 'e':
		if (x + size - 1 > 9)
			return false;

		for (int i = 0; i < size; i++) {
			if (m[y][x + i] != 0)
				return false;
		}

		for (int i = 0; i < size; i++) {
			m[y][x + i] = i + 1 + 10 * size + 200;
			f[y + 1][x + i + 1] = '*';
		}

		x1 += size - 1;
		break;
	}
	if (x0 < 0)
		x0 = 0;
	if (y0 < 0)
		y0 = 0;
	if (y1 > 9)
		y1 = 9;
	if (x1 > 9)
		x1 = 9;

	for (int i_y = y0; i_y <= y1; i_y++) {
		for (int i_x = x0; i_x <= x1; i_x++) {
			if (m[i_y][i_x] == 0)
				m[i_y][i_x] = 5;
		}
	}
	cnt1[size]++;
	return true;
}
void SeaWar::fill_ship(bool random, int m[10][10], int cnt_ship[5], char f[12][12]) {
	int cnt = 0;
	char symbol[4] = { 'n', 'e', 's', 'w' };
	if (random) {
		while (cnt != 1) {
			if (correct_ship_and_fill_array(rand() % 10, rand() % 10, symbol[rand() % 4], 4, m, cnt_ship, f))
				cnt++;
		}
		while (cnt != 3) {
			if (correct_ship_and_fill_array(rand() % 10, rand() % 10, symbol[rand() % 4], 3, m, cnt_ship, f))
				cnt++;
		}
		while (cnt != 6) {
			if (correct_ship_and_fill_array(rand() % 10, rand() % 10, symbol[rand() % 4], 2, m, cnt_ship, f))
				cnt++;
		}
		while (cnt != 10) {
			if (correct_ship_and_fill_array(rand() % 10, rand() % 10, symbol[rand() % 4], 1, m, cnt_ship, f))
				cnt++;
		}
	}
	else {
		print_field(f);
		int x0, y0, size;
		double x00, y00, size0;

		std::string way;
		std::cout << "�� ������� ��������������� ���������� ����" << std::endl;
		while (!correct_cnt_ship(cnt_ship)) {
			std::cout << "������ �������(x, y, size, course(e, w, s ��� n): ";

			while (!(std::cin >> x00) ||
				!(std::cin >> y00) ||
				!(std::cin >> size0) ||
				x00 - (int)(x00) != 0 ||
				y00 - (int)(y00) != 0 ||
				size0 - (int)(size0) != 0 ||
				!(x00 >= 0) ||
				!(x00 <= 9) ||
				!(y00 >= 0) ||
				!(y00 <= 9) ||
				!(size0 <= 4) ||
				!(size0 >= 0) ||
				!(std::cin >> way) ||
				!(check_way(way)) ||
				!(correct_ship_and_fill_array((int)(x00),
					(int)(y00),
					way[0],
					(int)(size0), m, cnt_ship, f))) {

				std::cin.clear();
				std::cin.ignore();
				system("cls");
				print_field(f);
				std::cout << "�� ��������� ������!!!" << std::endl;
				std::cout << "������ �������(x, y, size, course(e, w, s ��� n): ";
			}
			x0 = x00;
			y0 = y00;
			size = size0;
			system("cls");
			print_field(f);
		}
		std::cout << std::endl;
		std::cout << "���� ���������";
	}
}
//������ ��� �������� ���
int SeaWar::get_coord(bool player1) {
	int x, y;
	int a[2] = { 0, 0 };

	if (player1) {
		x = coord_player_1[0];
		y = coord_player_1[1];
		a[0] = x;
		a[1] = y;

		if (x > 9 || x < 0 || y > 9 || y < 0 || player1_attack[(int)(y)][(int)(x)] != 0) {
			move_recieved = false;
		}
		else
			move_recieved = true;
	}
	else {
		if (player_2_under_destroyed) {
			y = hit_past_move[1];
			x = hit_past_move[0];

			int direct;
			do {
				direct = 1 + rand() % 4;
			} while (direction[direct] == false);

			if (hit_direction != 0)
				direct = hit_direction;
			switch (direct) {
			case 1:
				for (int i = 1; i <= 3; i++) {
					if (y - i < 0) {
						direction[1] = false;
						a[0] = 10;
						a[1] = 10;
						if (i != 1)
							hit_direction = 3;
						break;
					}
					else if (player2_attack[y - i][x] == 0) {
						a[0] = x;
						a[1] = y - i;
						if (player1_ship[y - i][x] < 100) {
							if (i != 1)
								hit_direction = 3;
							direction[1] = false;
						}
						else
							hit_direction = 1;
						break;
					}
					else if (player2_attack[y - i][x] == 1) {
						direction[1] = false;
						if (i == 1)
							hit_direction = 0;
						else
							hit_direction = 3;
						a[0] = 10;
						a[1] = 10;
						break;
					}
					else if (i == 3) {
						hit_direction = 3;
						direction[1] = false;
					}
				}
				break;
			case 2:
				for (int i = 1; i <= 3; i++) {
					if (x + i > 9) {
						direction[2] = false;
						a[0] = 10;
						a[1] = 10;
						if (i != 1)
							hit_direction = 4;
						break;
					}
					else if (player2_attack[y][x + i] == 0) {
						a[0] = x + i;
						a[1] = y;
						if (player1_ship[y][x + i] < 100) {
							if (i != 1)
								hit_direction = 4;
							direction[2] = false;
						}
						else
							hit_direction = 2;
						break;
					}
					else if (player2_attack[y][x + i] == 1) {
						direction[2] = false;
						if (i == 1)
							hit_direction = 0;
						else
							hit_direction = 4;
						a[0] = 10;
						a[1] = 10;
						break;
					}
					else if (i == 3) {
						hit_direction = 4;
						direction[2] = false;
					}

				}
				break;
			case 3:
				for (int i = 1; i <= 3; i++) {
					if (y + i < 0) {
						direction[3] = false;
						a[0] = 10;
						a[1] = 10;
						if (i != 1)
							hit_direction = 1;
						break;
					}
					else if (player2_attack[y + i][x] == 0) {
						a[0] = x;
						a[1] = y + i;
						if (player1_ship[y + i][x] < 100) {
							if (i != 1)
								hit_direction = 1;
							direction[3] = false;
						}
						else
							hit_direction = 3;
						break;
					}
					else if (player2_attack[y + i][x] == 1) {
						direction[3] = false;
						if (i == 1)
							hit_direction = 0;
						else
							hit_direction = 1;
						a[0] = 10;
						a[1] = 10;
						break;
					}
					else if (i == 3) {
						hit_direction = 1;
						direction[3] = false;
					}

				}
				break;
			case 4:
				for (int i = 1; i <= 3; i++) {
					if (x - i < 0) {
						direction[4] = false;
						a[0] = 10;
						a[1] = 10;
						if (i != 1)
							hit_direction = 2;
						break;
					}
					else if (player2_attack[y][x - i] == 0) {
						a[0] = x - i;
						a[1] = y;
						if (player1_ship[y][x - i] < 100) {
							if (i != 1)
								hit_direction = 2;
							direction[4] = false;
						}
						else
							hit_direction = 4;
						break;
					}
					else if (player2_attack[y][x - i] == 1) {
						direction[4] = false;
						if (i == 1)
							hit_direction = 0;
						else
							hit_direction = 2;
						a[0] = 10;
						a[1] = 10;
						break;
					}
					else if (i == 3) {
						hit_direction = 2;
						direction[4] = false;
					}

				}
				break;
			default:
				system("pause");
			}
		}
		else {
			do {
				x = rand() % 10;
				y = rand() % 10;
			} while (player2_attack[y][x] != 0);
			a[0] = x;
			a[1] = y;
		}
	}
	return a[0] * 10 + a[1];
}
void SeaWar::attack(bool player1, int x, int y) {
	if (player1) {
		if (player2_ship[y][x] != 0 && player2_ship[y][x] != 5) {
			player1_attack[y][x] = 2;
			field_attack_1[y + 1][x + 1] = 'X';
		}
		else {
			player1_attack[y][x] = 1;
			field_attack_1[y + 1][x + 1] = '*';
			player_1_move = !player_1_move; 
		}
	}
	else {
		if (player1_ship[y][x] != 0 && player1_ship[y][x] != 5) {
			player2_attack[y][x] = 2;
			field_attack_2[y + 1][x + 1] = 'X';
			if (!player_2_under_destroyed) {
				player_2_under_destroyed = true;
				hit_past_move[0] = x;
				hit_past_move[1] = y;
			}
		}
		else {
			field_attack_2[y + 1][x + 1] = '*';
			player2_attack[y][x] = 1;
			player_1_move = !player_1_move;
		}
	}
}
void SeaWar::destroy_ship(int x, int y, int m[10][10], int a[10][10], bool player1) {
	bool destroy = true;
	int cnt = m[y][x] / 10 % 10;
	int direct = m[y][x] / 100;

	int x0 = 0;
	int x1 = 0;
	int y0 = 0;
	int y1 = 0;
	if (m[y][x] == 0 || m[y][x] == 5) {
		destroy = false;
	}
	else if (direct == 1 || direct == 3) {
		x0 = x;
		x1 = x;
		y0 = y - m[y][x] % 10 + 1;
		y1 = y + cnt - m[y][x] % 10;

		for (int i = y0; i <= y1; i++) {
			if (a[i][x] == 0 || a[i][x] == 5) {
				destroy = false;
				break;
			}
		}
	}
	else if (direct == 2 || direct == 4) {
		x0 = x - m[y][x] % 10 + 1;
		x1 = x + cnt - m[y][x] % 10;
		y0 = y;
		y1 = y;

		for (int i = x0; i <= x1; i++) {
			if (a[y][i] == 0 || a[y][i] == 5) {
				destroy = false;
				break;
			}
		}
	}

	if (destroy) {
		int x_d0 = x0 - 1;
		int x_d1 = x1 + 1;
		int y_d0 = y0 - 1;
		int y_d1 = y1 + 1;
		if (x_d0 < 0)
			x_d0 = 0;
		if (y_d0 < 0)
			y_d0 = 0;
		if (x_d1 > 9)
			x_d1 = 9;
		if (y_d1 > 9)
			y_d1 = 9;

		for (int i = x_d0; i <= x_d1; i++) {
			for (int j = y_d0; j <= y_d1; j++) {
				a[j][i] = 1;
				if (player1)
					field_attack_1[j + 1][i + 1] = '*';
				else
					field_attack_2[j + 1][i + 1] = '*';
				if (m[j][i] != 0 && m[j][i] != 5) {
					a[j][i] = 2;
					if (player1)
						field_attack_1[j + 1][i + 1] = 'X';
					else
						field_attack_2[j + 1][i + 1] = 'X';
				}
			}
		}
		if (!player_1_move) {
			player_2_under_destroyed = false;
			hit_direction = 0;
			for (int i = 0; i < 5; i++)
				direction[i] = true;
		}
	}
}
void SeaWar::next_move() {
	move_recieved = false;
	k = 0;
	int a = get_coord(player_1_move);
	//���� a == 110, �� ���������� ��� ���� ��������� �����, �� � ������� ���������
	while (a == 110) {
		k++;
		a = get_coord(player_1_move);

		//������ �� ������������ �����, ��� ������� ���� �������, ����� ������� ����
		if (k == 200) {
			continue;
			//system("pause");
			//break;
		}
	}
	if (move_recieved || !player_1_move) {
		int x = a / 10;
		int y = a % 10;
		attack(player_1_move, x, y);
		if (player_1_move)
			destroy_ship(x, y, player2_ship, player1_attack, player_1_move);
		else
			destroy_ship(x, y, player1_ship, player2_attack, player_1_move);
		if (player_1_move) {
			system("cls");
			print_field(field_1, field_attack_1);
			if (debug) {
				print_field(field_2, field_attack_2);
			}
		}
		else {
			system("cls");
			print_field(field_1, field_attack_1);
			if (debug) {
				print_field(field_2, field_attack_2);
			}
		}
	}
}