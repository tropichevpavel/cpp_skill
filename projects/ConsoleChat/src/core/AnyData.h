#pragma once

#include <iostream>

class AnyData {
	struct Base {
		virtual ~Base() = default;
	};

	template <typename T>
	struct Data : public Base {
		T value;
		Data(const T& value) : value(value) {}
	};

	Base* ptr;

public:
	template <typename T>
	AnyData(const T& value) : ptr(new Data<T>(value)) {}

	AnyData(const AnyData&) = delete;
	AnyData(AnyData&& data) : ptr(data.ptr) {
		data.ptr = nullptr;
	};

	AnyData& operator= (const AnyData&) = delete;

	template <typename T>
	T& get() {
		return dynamic_cast<Data<T>&>(*this->ptr).value;
	}

	template <typename T>
	bool type() const {
		return dynamic_cast<Data<T>*>(this->ptr);
	}

	~AnyData() {
		if (this->ptr) delete this->ptr;
	}
};
