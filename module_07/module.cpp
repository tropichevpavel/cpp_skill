
#include <iostream>

class BadDivision {
	int _a, _b;

public:
	BadDivision(const int& a, const int& b) : _a(a), _b(b) {}
	BadDivision(const int& a) {
		if (!a) throw "ERROR: a can't be zero";
	}
	void show() {
		std::cout << "ERROR: can't divide zero" << std::endl;
		std::cout << "Division -  a = " << _a << ", b = " << _b << std::endl;
	}
};

class BadDivisionExc : public std::exception {

public:
	virtual const char* what() const noexcept override {
		return "ERROR: Bad Division Arguments!";
	}
};

void divOn0(const int& a, const int& b) {
	if (b == 0) abort();

	std::cout << "Division - " << a / b << std::endl;
}

void divOn0Assert(const int& a, const int& b) {
	// assert(b);
	assert(b &&  "Trying to divide on zero!");

	std::cout << "Division - " << a / b << std::endl;
}

bool divOn0Assert(const int& a, const int& b, float& result) {
	if (b == 0) {
		result = 0;
		return false;
	}

	std::cout << "Division - " << a / b << std::endl;
	return true;
}

void divOn0Thow(const int& a, const int& b) {
	if (b == 0) throw "ERROR: can't divide zero";

	std::cout << "Division - " << a / b << std::endl;
}

void divOn0ThowBad(const int& a, const int& b) {
	if (b == 0) throw BadDivisionExc(); // BadDivision(a, b);

	std::cout << "Division - " << a / b << std::endl;
}

void onExit() {
	std::cout << "Exit Now!" << std::endl;
}

void onTerminateExit() {
	std::cout << "Exit Now With Terminate!" << std::endl;
	exit(5);
}

int Main() {
	std::set_terminate(onTerminateExit);
	
	try { divOn0ThowBad(1, 0); }
	catch(BadDivision& db) { db.show(); }
	catch(const char* e) { std::cout << "Exception: " << e << std::endl; }
	catch(std::exception& e) { std::cout << e.what() << std::endl; }
	catch(std::bad_alloc& e) { std::cout << "bad_alloc caught!" << std::endl << e.what() << std::endl; }
	catch(...) { std::cout << "Some thing wrong, but we mast stand!" << std::endl; }

	throw "ExTerminate!!!";

	atexit(onExit);
	return 0;
}