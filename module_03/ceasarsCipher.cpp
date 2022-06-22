#include <iostream>

using namespace std;

int main() 
{
	char operation;
	char *str;
	int step;

	cout << "Программа для шифрования строки методом Цезаря!" << endl;

	while (true) {
		while (true) {
			cout << "Выберете режим: 1 - шифрование, 2 - дешифровка, q - для выхода" << endl;
			cin >> operation;

			if (operation == '1' || operation == '2' || operation == 'q')
				break;

			cout << "Неверный режим!" << endl << endl;
		}

		if (operation == 'q') break;

		string input;

		cout << "Введите строку" << endl;
		cin >> input;

		int inputSize = input.length() / sizeof(input[0]);
		int strSize = 0;

		for (int i = 0; i < inputSize; i++) {
			int c = input[i];
			strSize += ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
		}

		str = new char[strSize];
		int j = 0;

		for (int i = 0; i < inputSize; i++) {
			int c = input[i];
			if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
				str[j++] = c;
		}

		if (inputSize != strSize)
			cout << "Строка содержит недопустимые символы! Они были автоматически удалены" << endl;

		cout << "Введите шаг смещения" << endl;
		while (true) {
			cin >> input;
		
			bool haveInvalidChars = false;
			inputSize = input.length() / sizeof(input[0]);
			
			for (int i = 0; i < inputSize; i++) {
				if (!(('0' <= input[i] && input[i] <= '9') || input[i] == '-')) {
					cout << "Неверный шаг смещения! Повторите ввод!" << endl;
					haveInvalidChars = true;
					break;
				}
			}

			if (haveInvalidChars) continue;

			step = stoi(input);
			break;
		}

		step = operation == '1' ? step : -step;
		step %= 'z' - 'a';

		int size = strSize;

		cout << (operation == '1' ? "Зашиврованная" : "Расшифрованная") << " строка:" << endl;
		while (size > 0) {
			int c = str[--size];

			if (c == ' ') continue;
			
			int start = c <= 'Z' ? 'A' : 'a';
			int end = c <= 'Z' ? 'Z' : 'z';

			c += step;
			
			if (step > 0)
				str[size] = (c > end) ? start + (c - end - 1) : c;
			else
				str[size] = (c < start) ? end - (start - c - 1) : c;
		}

		for (; size < strSize; size++) {
			cout << str[size];
		}
		cout << endl << endl;
		delete[] str;
	}

	return 0;
}
