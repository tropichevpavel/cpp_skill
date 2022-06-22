#include <iostream>

using namespace std;

int main() 
{
	int x, y;
	char operation;

	while (true) {
		cout << "Введите операцию ( + , - , *, / , ! , ^ ), для выхода q:" << endl;
		cin >> operation;

		if (operation == 'q') break;
		
		else if (!(operation == '+' || operation == '-' || operation == '*' || operation == '/' ||
				 operation == '!' || operation == '^')) {

			cout << "Введена неправельная операция!" << endl;
			continue;
		}

		if (operation == '!') {
			cout << "Введите число:" << endl;
			cin >> x;
			
			long long fact = 1;
			for (int i = 1; i <= x; i++) {
				fact *= i;
			}

			cout << x << "! = " << fact << endl;

		} else {
			cout << "Введите последовательно 2 числа через Enter:" << endl;
			cin >> x >> y;

			cout << "Результат " << x << " " << operation << " " << y << " = ";

			if (operation == '+') cout << (x + y);

			else if (operation == '-') 	cout << (x - y);
				
			else if (operation == '*')	cout << (x * y);

			else if (operation == '/') {
				if (y) {
					cout << ((double) x / y);
				
				} else cout << "На ноль делить нельзя!";
			}

			else {
				int m = 1;
				for (;y > 0; y--) {
					m *= x;
				}
				cout << m;
			}

			cout << endl << endl;
		}
	}

	return 0;
}
