#pragma once

#include <iostream>

template <typename T> class IntArr {
	int _size;
	T* _data;

public:
	IntArr() = default;
	IntArr(const int& size);
	IntArr(const IntArr& intArr);
	template <typename U>
	IntArr(const IntArr<U>& intArr);
	~IntArr();

	void remove(const int& index);
	int size() const;
	void erase();

	void rebuild();
	void rebuild(const int& size);
	void resize(const int& size);

	void insertBefore(const int& index, const T& item);
	void insertAfter(int& index, const T& item);
	void insertAtStart(const T& item);
	void insertAtEnd(const T& item);

	int find(const T& item) const;

	std::string join(const char* sep = ", ") const;

	T& operator[](const int& index) const;
};

#include "IntArrT.h"
