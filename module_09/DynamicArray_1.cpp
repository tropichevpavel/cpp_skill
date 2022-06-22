
#include <iostream>

template <typename T>
class DynamicArray {
	T* _data;
	int _size;

public:
	DynamicArray(const int& size) : _size(size) {
		std::cout << "Конструктор" << std::endl;
		if (size < 0)
			throw std::length_error("IntArr::new - Wrong size");

		_data = new T[size];
		for (int i = 0; i < _size; ++i)
			_data[i] = i;
	}
	~DynamicArray() {
		std::cout << "Деструктор" << std::endl;
		delete[] _data;
	}

	DynamicArray(const DynamicArray& arr) {
		std::cout << "Конструктор копирования" << std::endl;

		this->_size = arr._size;
		this->_data = new T[this->_size];

		for (int i = 0; i < this->_size; ++i)
			this->_data[i] = arr._data[i];
	}

	int size() const {
		return _size;
	}

	T& operator[](const int& index) const {
		if (index < 0 || index > _size)
			throw std::out_of_range("IntArr::get - Index out of bound array");
		return _data[index];
	}

	DynamicArray& operator=(const DynamicArray& arr) {
		if (this != &arr) {
			std::cout << "Оператор присваивания" << std::endl;
			delete[] _data;

			this->_size = arr._size;
			this->_data = new T[this->_size];

			for (int i = 0; i < this->_size; ++i)
				this->_data[i] = arr._data[i];

		} else
			std::cout << "Самоприсваивание" << std::endl;

		return *this;
	}
};
