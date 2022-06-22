#include <iostream>

using namespace std;

int main() 
{
	int x, y;

	cout << "Ведите первое число" << endl;

	cin >> x;

	cout << "Ведите второе число" << endl;

	cin >> y;

	cout << endl;
	cout << "Сложение  - " << x + y << endl;
	cout << "Вычитание - " << x - y << endl;
	cout << "Умножение - " << x * y << endl;
	cout << "Деление   - " << x / y << endl;
	cout << "Остаток   - " << x % y << endl << endl;

	cout << "Бит И   - " << (x & y) << endl;
	cout << "Бит ИЛИ - " << (x | y) << endl;
	cout << "Бит XOR - " << (x ^ y) << endl;

	return 0;
}
