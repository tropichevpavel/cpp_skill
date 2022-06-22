
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

	DynamicArray(const DynamicArray& arr) = delete;
	DynamicArray(DynamicArray&& arr) noexcept : _data(arr._data), _size(arr._size) {
		std::cout << "Конструктор перемещения" << std::endl;
		arr._size = 0;
		arr._data = nullptr;
	};

	int size() const {
		return _size;
	}

	T& operator[](const int& index) const {
		if (index < 0 || index > _size)
			throw std::out_of_range("IntArr::get - Index out of bound array");
		return _data[index];
	}

	DynamicArray& operator=(const DynamicArray& arr) = delete;

	DynamicArray& operator=(DynamicArray&& arr) noexcept {
		if (this != &arr) {
			std::cout << "Оператор перемещения" << std::endl;
			delete[] _data;

			this->_size = arr._size;
			this->_data = arr._data;
			arr._size = 0;
			arr._data = nullptr;

		} else
			std::cout << "Самопеперемещение" << std::endl;

		return *this;
	}
};
