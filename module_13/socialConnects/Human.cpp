
#include "Human.h"

Human::Human(const int& id, const std::string& name) : id(id), name(name) {}

auto Human::getID() const -> const int& {
	return this->id;
}

auto Human::getName() const -> const std::string& {
	return this->name;
}

auto operator<< (std::ostream& out, const Human* h) -> std::ostream& {
	out << "(" << h->id << ") " << h->name;
	return out;
}
