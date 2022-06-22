#pragma once

#include <iostream>

class IntArr {
	int _size;
	int* _data;

public:
	IntArr() = default;
	IntArr(const int& size);
	IntArr(const IntArr& intArr);
	~IntArr();

	void remove(const int& index);
	int size() const;
	void erase();

	void rebuild();
	void rebuild(const int& size);
	void resize(const int& size);

	void insertBefore(const int& index, const int& item);
	void insertAfter(int& index, const int& item);
	void insertAtStart(const int& item);
	void insertAtEnd(const int& item);

	int find(const int& item) const;

	std::string join(const char* sep = ", ") const;

	int& operator[](const int& index) const;
};
