#include "SeaWar.h"

SeaWar::SeaWar() {

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			field_1[i][j] = ' ';
			field_2[i][j] = ' ';
			field_attack_1[i][j] = ' ';
			field_attack_2[i][j] = ' ';
		}
	}

	mode_selection_fill();
	first_move();
	start_map(field_1);
	start_map(field_2);
	start_map(field_attack_1);
	start_map(field_attack_2);

	fill_ship(true, player2_ship, cnt_ship_2, field_2);
	fill_ship(is_random_field, player1_ship, cnt_ship_1, field_1);

	print_field(field_1, field_attack_1);
	//print_field(field_2);

}

void SeaWar::mode_selection_fill() {
	cout << "Выберите режим расставления кораблей(1-рандомно, 0-заполняет игрок): ";
	while (!(cin >> is_random_field)) {
		cin.clear();
		cin.ignore();
		system("cls");
		cout << "Вы допустили ошибку!" << endl;
		cout << "Выберите режим расставления кораблей(1-рандомно, 0-заполняет игрок): ";
	}
}
void SeaWar::first_move() {
	cout << "Вы ходите первым? (true-да, false-нет): ";
	while (!(cin >> player_move)) {
		cin.clear();
		cin.ignore();

		system("cls");
		cout << "Вы допустили ошибку!" << endl;
		cout << "Вы ходите первым? (true-да, false-нет): ";

	}
	system("cls");
}

void SeaWar::start_map(char a[12][12]) {
	for (int i = 1; i < 11; i++) {
		for (int j = 0; j < 12; j++)
			a[i][j] = ' ';

		a[0][i] = to_string((i - 1))[0];
		a[i][0] = to_string((i - 1))[0];

		a[i][11] = '|';
		a[11][i] = '–';
	}
	a[11][0] = 'Y';
	a[0][11] = 'X';
	a[11][11] = '-';
}
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
void SeaWar::print_field(char f[12][12]) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			cout << f[i][j];
		}
		cout << endl;
	}
}
void SeaWar::print_field(char f[12][12], char a[12][12]) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			cout << f[i][j];
		}

		cout << "		";

		for (int k = 0; k < 12; k++) {
			cout << a[i][k];
		}
		cout << endl;
	}
}

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
			m[y + i][x] = size;
			f[y + i+1][x+1] = '*';
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
			m[y][x - i] = size;
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
			m[y - i][x] = size;
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
			m[y][x + i] = size;
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

bool SeaWar::check_way(string s) {
	if (s.length() == 1 && (s[0] == 'e' || s[0] == 's' || s[0] == 'w' || s[0] == 'n'))
		return true;
	return false;
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
		char way[10];
		cout << "Вы выбрали самостоятельное заполнение поля" << endl;
		while (!correct_cnt_ship(cnt_ship)) {
			cout << "Данные корабля(x, y, size, course(e, w, s или n): ";
		
			while (!(cin >> x0) ||
				!(cin >> y0) ||
				!(cin >> size) ||
				!(x0 >= 0) ||
				!(x0 <= 9) ||
				!(y0 >= 0) ||
				!(y0 <= 9) ||
				!(size <= 4) ||
				!(size >= 0) ||
				!(cin >> way) ||
				!(check_way(way)) ||
				!(correct_ship_and_fill_array(x0, y0, way[0], size, m, cnt_ship, f))) {

				cin.clear();
				cin.ignore();
				system("cls");
				print_field(f);
				cout << "Вы совершили ошибку!!!" << endl;
				cout << "Данные корабля(x, y, size, course(e, w, s или n): ";
			}
			system("cls");
			print_field(f);
		}
		cout << endl;
		cout << "Поле заполнено";
	}
}






