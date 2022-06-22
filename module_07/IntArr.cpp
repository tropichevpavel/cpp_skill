
#include "IntArr.h"

IntArr::IntArr(const int& size) : _size(size) {
	if (size < 0)
		throw std::length_error("IntArr::new - Wrong size");

	_data = new int[size];
}

IntArr::IntArr(const IntArr& intArr) {
	this->_size = intArr._size;
	this->_data = new int[this->_size];
	
	for (int i = 0; i < this->_size; ++i)
		this->_data[i] = intArr._data[i];
}

IntArr::~IntArr() {
	delete[] _data;
}

int IntArr::size() const {
	return _size;
}
	
void IntArr::erase() {
	delete[] _data;
	_data = nullptr;
	_size = 0;
}

void IntArr::rebuild() {
	rebuild(_size);
}

void IntArr::rebuild(const int& size) {
	if (size < 0)
		throw std::length_error("IntArr::rebuild - Wrong size");

	erase();

	_data = new int[size];
	_size = size;
}

void IntArr::resize(const int& size) {
	if (size < 0)
		throw std::length_error("IntArr::resize - Wrong size");

	if (!size) {
		erase();
		return;
	}

	if (_size == size) return;

	int* data = new int[size];

	int minSize = _size > size ? size : _size;

	for (int i = 0; i < minSize; ++i)
		data[i] = _data[i];

	delete[] _data;
	_data = data;
	_size = size;
}

void IntArr::remove(const int& index) {
	if (index < 0 || index > _size)
		throw std::out_of_range("IntArr::remove - Index out of bound array");

	int* data = new int[_size - 1];

	for (int i = 0; i < index; ++i)
		data[i] = _data[i];

	for (int i = index + 1; i < _size; ++i)
		data[i - 1] = _data[i];
	
	delete[] _data;
	_data = data;
	--_size;
}

void IntArr::insertBefore(const int& index, const int& item) {
	if (index < 0 || index > _size)
		throw std::out_of_range("IntArr::insert - Index out of bound array");

	int* data = new int[_size + 1];

	for (int i = 0; i < index; ++i)
		data[i] = _data[i];

	data[index] = item;

	for (int i = index; i < _size; ++i)
		data[i + 1] = _data[i];

	delete[] _data;
	_data = data;
	++_size;
}

void IntArr::insertAfter(int& index, const int& item) {
	insertBefore(++index, item);
}

void IntArr::insertAtStart(const int& item) {
	insertBefore(0, item);
}

void IntArr::insertAtEnd(const int& item) {
	insertBefore(_size, item);
}

int IntArr::find(const int& item) const {
	for (int i = 0; i < _size; ++i)
		if (item == _data[i])
			return i;

	return -1;
}

int& IntArr::operator[](const int& index) const {
	if (index < 0 || index > _size)
		throw std::out_of_range("IntArr::get - Index out of bound array");
	return _data[index];
}

std::string IntArr::join(const char* sep) const {
	std::string join = "";

	for (int i = 0; i < _size; ++i)
		join += std::to_string(_data[i]) + (i == _size - 1 ? "" : sep);

	return join;
}
