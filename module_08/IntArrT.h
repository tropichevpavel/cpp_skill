

template <typename T>
IntArr<T>::IntArr(const int& size) : _size(size) {
	if (size < 0)
		throw std::length_error("IntArr::new - Wrong size");

	_data = new T[size];
}

template <typename T>
IntArr<T>::IntArr(const IntArr& intArr) {
	this->_size = intArr._size;
	this->_data = new T[this->_size];

	for (int i = 0; i < this->_size; ++i)
		this->_data[i] = intArr._data[i];
}

template <typename T> template <typename U>
IntArr<T>::IntArr(const IntArr<U>& intArr) {
	this->_size = intArr.size();
	this->_data = new T[this->_size];

	for (int i = 0; i < this->_size; ++i)
		this->_data[i] = intArr[i];
}

template <typename T>
IntArr<T>::~IntArr() {
	delete[] _data;
}

template <typename T>
int IntArr<T>::size() const {
	return _size;
}

template <typename T>
void IntArr<T>::erase() {
	delete[] _data;
	_data = nullptr;
	_size = 0;
}

template <typename T>
void IntArr<T>::rebuild() {
	rebuild(_size);
}

template <typename T>
void IntArr<T>::rebuild(const int& size) {
	if (size < 0)
		throw std::length_error("IntArr::rebuild - Wrong size");

	erase();

	_data = new T[size];
	_size = size;
}

template <typename T>
void IntArr<T>::resize(const int& size) {
	if (size < 0)
		throw std::length_error("IntArr::resize - Wrong size");

	if (!size) {
		erase();
		return;
	}

	if (_size == size) return;

	T* data = new T[size];

	int minSize = _size > size ? size : _size;

	for (int i = 0; i < minSize; ++i)
		data[i] = _data[i];

	delete[] _data;
	_data = data;
	_size = size;
}

template <typename T>
void IntArr<T>::remove(const int& index) {
	if (index < 0 || index > _size)
		throw std::out_of_range("IntArr::remove - Index out of bound array");

	T* data = new T[_size - 1];

	for (int i = 0; i < index; ++i)
		data[i] = _data[i];

	for (int i = index + 1; i < _size; ++i)
		data[i - 1] = _data[i];

	delete[] _data;
	_data = data;
	--_size;
}

template <typename T>
void IntArr<T>::insertBefore(const int& index, const T& item) {
	if (index < 0 || index > _size)
		throw std::out_of_range("IntArr::insert - Index out of bound array");

	T* data = new T[_size + 1];

	for (int i = 0; i < index; ++i)
		data[i] = _data[i];

	data[index] = item;

	for (int i = index; i < _size; ++i)
		data[i + 1] = _data[i];

	delete[] _data;
	_data = data;
	++_size;
}

template <typename T>
void IntArr<T>::insertAfter(int& index, const T& item) {
	insertBefore(++index, item);
}

template <typename T>
void IntArr<T>::insertAtStart(const T& item) {
	insertBefore(0, item);
}

template <typename T>
void IntArr<T>::insertAtEnd(const T& item) {
	insertBefore(_size, item);
}

template <typename T>
int IntArr<T>::find(const T& item) const {
	for (int i = 0; i < _size; ++i)
		if (item == _data[i])
			return i;

	return -1;
}

template <typename T>
T& IntArr<T>::operator[](const int& index) const {
	if (index < 0 || index > _size)
		throw std::out_of_range("IntArr::get - Index out of bound array");
	return _data[index];
}

template <typename T>
std::string IntArr<T>::join(const char* sep) const {
	std::string join = "";

	for (int i = 0; i < _size; ++i)
		join += std::to_string(_data[i]) + (i == _size - 1 ? "" : sep);

	return join;
}
