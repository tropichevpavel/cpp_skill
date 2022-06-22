#include "Human.h"

#include <iostream>

namespace humans {
	
	Human::Human(const int& age) : age(age) {}

	Human::Human(const char*& name) {
		this->name = name;
	}

	Human::Human(const Human& other) {
		this->age = other.age;
	}

	Human &Human::operator++() {
		age++;
		return *this;
	}

	Human &Human::operator--() {
		age--;
		return *this;
	}

	Human Human::operator++(int) {
		Human old(*this);
		++(*this);
		return old;
	}

	Human Human::operator--(int) {
		Human old(*this);
		--(*this);
		return old;
	}

	bool Human::operator<(const Human &h) {
		return this->age < h.age;
	}

	bool Human::operator>(const Human &h) {
		return this->age > h.age;
	}

	std::ostream &operator<<(std::ostream &out, const Human &h) {
		out << "";
		return out;
	}


	void Human::setName(const char* &n) {
		name = n;
	}

	void Human::setAge(const int &a) {
		if (a > 0)
			age = a;
		else
			std::cout << "возраст не может быть меньше 0";
	}

	int Human::getAge() const {
		return age;
	}

	Human::~Human() {
		
	}
}
