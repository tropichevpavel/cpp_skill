
#include <iostream>
#include <string>

int findPeriodic(const std::string& str) {

	int strSize = str.size();
	int posEnd = 0;

	if (!strSize) {
		std::cout << "Empty String ";
		return 0;
	}

	for (int i = 0; i < strSize - 1;) {
		
		for (int j = -1; j < posEnd;) {
			if (str[++i] != str[++j]) {
				posEnd = i;
				break;
			}
		}

		if (posEnd > (strSize / 2)) return strSize;
	}

	return ++posEnd;
}

bool isKPeriodic(const std::string& str, const int& k) {
	if (k < 1) {
		std::cout << "k должно быть больше 0!";
		return false;
	}
	
	if (str.size() % k != 0) return false;

	int periods = str.size() / k;
	auto part = str.substr(0, k);

	for (int i = 0; i < periods; ++i)
		if (str.substr(k * i, k) != part)
			return false;
	return true;
}

int main() {
	std::cout << "Минимальная кратность строки \"a\" = " << findPeriodic("a") << std::endl << std::endl;
	std::cout << "Минимальная кратность строки \"aaaaaaaaaaaaaa\" = " << findPeriodic("aaaaaaaaaaaaaa") << std::endl << std::endl;

	std::cout << "Минимальная кратность строки \"abcabcdabcabcd\" = " << findPeriodic("abcabcabcabc") << std::endl << std::endl;
	std::cout << "Минимальная кратность строки \"abcabcabcabcd\" = "  << findPeriodic("abcabcabcabcd") << std::endl << std::endl;
	std::cout << "Минимальная кратность строки \"abcabcdabcabcd\" = " << findPeriodic("abcabcdabcabcd") << std::endl << std::endl << std::endl;

	std::cout << "Строка \"abcabcdabcabc\" кратна 3-м ? = " << (isKPeriodic("abcabcabcabc", 3) ? "да" : "нет") << std::endl << std::endl;
	std::cout << "Строка \"abcabcdabcabc\" кратна 4-м ? = " << (isKPeriodic("abcabcabcabc", 4) ? "да" : "нет") << std::endl << std::endl;
	std::cout << "Строка \"abcabcdabcabc\" кратна 6-и ? = " << (isKPeriodic("abcabcabcabc", 6) ? "да" : "нет") << std::endl << std::endl;

	return 0;
}
