
#include <iostream>
#include <string>

int IsKPeriodic(const std::string& str) {

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

int main() {
	std::cout << "Кратность строки \"a\" = " << IsKPeriodic("a") << std::endl << std::endl;
	std::cout << "Кратность строки \"aaaaaaaaaaaaaaaa\" = " << IsKPeriodic("aaaaaaaaaaaaaaaa") << std::endl << std::endl;

	std::cout << "Кратность строки \"abcabcdabcabcd\" = " << IsKPeriodic("abcabcabcabc") << std::endl << std::endl;
	std::cout << "Кратность строки \"abcabcabcabcd\" = " << IsKPeriodic("abcabcabcabcd") << std::endl << std::endl;
	std::cout << "Кратность строки \"abcabcdabcabcd\" = " << IsKPeriodic("abcabcdabcabcd") << std::endl << std::endl;

	std::cout << "Кратность строки \"\" = " << IsKPeriodic("") << std::endl << std::endl;
	return 0;
}