
#include <iostream>

template<typename... Args>
int printCount(Args... args) {
	return sizeof...(Args);
}

void print() {}

template<typename T, typename... Args>
void print(T elem, Args... other) {
	std::cout << elem << " ";
	print(other...);
}


int main() {
	std::cout << "Args count = " << printCount("Hi", 254, 'H', 90, 45, '4', ", World") << std::endl;
	print("Hi", 254, 'H', 90, 45, '4', ", World");
	return 0;
}
