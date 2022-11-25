#include <iostream>
#include <windows.h>
#include <cstdlib>


using namespace std;

void start_map() {
	for (int i = 0; i < 12; i++) {
		if (i != 0 && i != 11)
			cout << i - 1;

		for (int j = 0; j < 11; j++) {
			if (i == 0 && j == 0)
				cout << " ";
			else if (i == 0 && j != 10)
				cout << j;
			else if (j == 9 && i != 0)
				cout << "#";
			else if (i == 11 && j != 0 && j != 10)
				cout << "#";
			else
				cout << " ";

		}





		cout << endl;
	}
}
bool correct_ship_and_fill_random_array(int x, int y, char a, int size, int m[10][10]) {
	bool correct = true;

	switch (a) {
	case 's':
		if (y + size - 1 > 9)
			return false;

		for (int i = 0; i < size; i++) {
			if (m[y + i][x] != 0)
				return false;
			m[y + i][x] = size;
		}


		break;
	case 'w':
		if (x - size + 1 < 0)
			return false;

		for (int i = 0; i < size; i++) {
			if (m[y][x - i] != 0)
				return false;
			m[y + i][x] = size;
		}
		break;
	case 'n':
		if (y - size + 1 < 0)
			return false;

		for (int i = 0; i < size; i++) {
			if (m[y - i][x] != 0)
				return false;
			m[y + i][x] = size;
		}
		break;
	case 'e':
		if (x + size - 1 > 9)
			return false;

		for (int i = 0; i < size; i++) {
			if (m[y][x + i] != 0)
				return false;
			m[y + i][x] = size;
		}
		break;
	}
	return correct;
}


void fill_ship(bool random, int m[10][10]) {
	int cnt = 0;
	char symbol[4] = { 'n', 'e', 's', 'w' };
	if (random) {
		while (cnt != 1) {
			if (correct_ship_and_fill_random_array(rand() % 10, rand() % 10, symbol[rand() % 4], 4, m)) {
				cnt++;
			}
		}
	}
}



int main() {

	setlocale(LC_ALL, "ru");
	srand(time(0));

	int player1_ship[10][10] = { 0 };
	int player2_ship[10][10] = { 0 };
	int player1_attack[10][10] = { 0 };
	int player2_attack[10][10] = { 0 };


	start_map();
	fill_ship(true, player1_ship);
	//system("pause");
	//system("cls");

	cout << (char)(219);
}
