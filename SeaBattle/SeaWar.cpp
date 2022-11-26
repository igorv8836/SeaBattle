#include "SeaWar.h"

SeaWar::SeaWar() {
	start_map();
	//fill_ship(true, player1_ship, cnt_ship_1);
}

bool SeaWar::check_cnt_ship(int a[5], int size) {
	a[size]++;
	if (a[1] <= 4 && a[2] <= 3 && a[3] <= 2 && a[4] <= 1)
		return true;
	return false;
}
bool SeaWar::correct_cnt_ship(int a[5]) {
	if (a[1] == 4 && a[2] == 3 && a[3] == 2 && a[4] == 1)
		return true;
	return false;
}

void SeaWar::print_field() {
	for (int i = 0; i < )
}

void SeaWar::start_map() {
	for (int i = 0; i < 12; i++) {
		if (i != 0 && i != 11)
			field[i][0] = to_string((i - 1))[0];
			//cout << i - 1;


		for (int j = 0; j < 11; j++) {
			if (i == 0 && j == 0)
				cout << "";
			else if (i == 0 && j != 10)
				field[0][j + 1] = to_string((j))[0];
				//cout << j;
			else if (j == 9 && i != 0)
				field[i][j] = '#';
				//cout << "#";
			else if (i == 11 && j != 0 && j != 10)
				field[i][j] = '#';
				//cout << "#";
			//else
				//cout << " ";

		}





		cout << endl;
	}
}

bool SeaWar::correct_ship_and_fill_array(int x, int y, char a, int size, int m[10][10], int cnt1[5]) {
	int x0, y0, x1, y1;

	x0 = x - 1;
	y0 = y - 1;
	x1 = x + 1;
	y1 = y + 1;

	cnt1[size]++;
	if (!(check_cnt_ship(cnt1, size)))
		return false;
	cnt1[size]--;

	switch (a) {
	case 's':
		if (y + size - 1 > 9)
			return false;
		for (int i = 0; i < size; i++) {
			if (m[y + i][x] != 0)
				return false;
		}

		for (int i = 0; i < size; i++)
			m[y + i][x] = size;

		y1 += size - 1;
		break;
	case 'w':
		if (x - size + 1 < 0)
			return false;
		for (int i = 0; i < size; i++) {
			if (m[y][x - i] != 0)
				return false;
		}

		for (int i = 0; i < size; i++)
			m[y][x - i] = size;

		x0 -= (size - 1);
		break;
	case 'n':
		if (y - size + 1 < 0)
			return false;

		for (int i = 0; i < size; i++) {
			if (m[y - i][x] != 0)
				return false;
		}

		for (int i = 0; i < size; i++)
			m[y - i][x] = size;

		y0 -= (size - 1);
		break;
	case 'e':
		if (x + size - 1 > 9)
			return false;

		for (int i = 0; i < size; i++) {
			if (m[y][x + i] != 0)
				return false;
		}

		for (int i = 0; i < size; i++)
			m[y][x + i] = size;

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

void SeaWar::fill_ship(bool random, int m[10][10], int cnt_ship[5]) {
	int cnt = 0;
	char symbol[4] = { 'n', 'e', 's', 'w' };
	if (random) {
		while (cnt != 1) {
			if (correct_ship_and_fill_array(rand() % 10, rand() % 10, symbol[rand() % 4], 4, m, cnt_ship))
				cnt++;
		}
		while (cnt != 3) {
			if (correct_ship_and_fill_array(rand() % 10, rand() % 10, symbol[rand() % 4], 3, m, cnt_ship))
				cnt++;
		}
		while (cnt != 6) {
			if (correct_ship_and_fill_array(rand() % 10, rand() % 10, symbol[rand() % 4], 2, m, cnt_ship))
				cnt++;
		}
		while (cnt != 10) {
			if (correct_ship_and_fill_array(rand() % 10, rand() % 10, symbol[rand() % 4], 1, m, cnt_ship))
				cnt++;
		}
	}
	else {
		int x0, y0, size;
		char way[10];
		cout << "Вы выбрали самостоятельное заполнение поля" << endl;
		while (!correct_cnt_ship(cnt_ship)) {
			cout << "Данные корабля: ";
			//cout << "Введите координаты корабля(x, y),\nпалубность корабля(от 1 до 4), \nнаправление корабля от данных координат(w, e, n или s) (w-west(налево), e-east(направо), n-north(навверх), s-south(вниз):";
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
				!(correct_ship_and_fill_array(x0, y0, way[0], size, m, cnt_ship))) {

				cin.clear();
				cin.ignore();
				//cout << "Вы совершили ошибку, выбрав неправильный формат введеных данных, или превышаете необходимое количество кораблей одного вида !" << endl;
				cout << "Вы совершили ошибку!!!----------------------" << endl;
				//cout << "Введите координаты корабля(x, y), \nнаправление корабля от данных координат(w, e, n или s) (w-west(налево), e-east(направо), n-north(навверх), s-south(вниз),\nпалубность корабля(от 1 до 4):";
				cout << "Данные корабля: ";
			}
		}
		cout << endl;
		cout << "Поле заполнено";
	}
}






