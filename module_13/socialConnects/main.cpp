
#include "SocialConnects.h"
#include "Human.h"

void test1() {
	SocialConnects sc;

	Human* h0 = sc.addHuman("Олег");
	Human* h1 = sc.addHuman("Никита");
	Human* h2 = sc.addHuman("Настя");
	Human* h3 = sc.addHuman("Ваня");
	Human* h4 = sc.addHuman("Женя");

	sc.addConnect(h0, h1);
	sc.addConnect(h1, h2);
	sc.addConnect(h2, h3);
	sc.addConnect(h3, h4);

	sc.printConnects(3);
}

void test2() {
	SocialConnects sc;

	Human* h0 = sc.addHuman("Петя");
	Human* h1 = sc.addHuman("Василий");
	Human* h2 = sc.addHuman("Мария");
	Human* h3 = sc.addHuman("Иван");
	Human* h4 = sc.addHuman("Павел");
	Human* h5 = sc.addHuman("Анастасия");
	Human* h6 = sc.addHuman("Галина");
	Human* h7 = sc.addHuman("Юрий");
	Human* h8 = sc.addHuman("Виктор");
	Human* h9 = sc.addHuman("Александр");

	sc.addConnect(h0, h1);
	sc.addConnect(h0, h2);
	sc.addConnect(h0, h3);
	sc.addConnect(h1, h2);
	sc.addConnect(h1, h6);
	sc.addConnect(h2, h5);
	sc.addConnect(h3, h4);
	sc.addConnect(h4, h5);
	sc.addConnect(h5, h6);
	sc.addConnect(h5, h7);
	sc.addConnect(h5, h8);
	sc.addConnect(h6, h7);
	sc.addConnect(h8, h9);

	Human* h10 = new Human(0, "Ибрагим");

	sc.addConnect(h0, h10);

	delete h10;

	sc.printConnects(3);
}

int main() {
	test1();
	// test2();
	return 0;
}
