
#include <iostream>
#include <algorithm>

#include "SocialConnects.h"

auto SocialConnects::addHuman(const std::string& name) -> Human* {
	Human* h = new Human(humans.size(), name);
	humans.push_back(h);
	return h;
}

bool SocialConnects::humanExists(const Human* human) {
	for (const auto* h : humans)
		if (h == human) return true;
	return false;
}

void SocialConnects::addConnect(Human* h1, Human* h2) {
	if (!humanExists(h1)) {
		std::cout << "Ошибка добавления связи! " << h1 << " изгой, не входящий в этот круг общения! Добавьте его!" << std::endl;
		return;
	}
	if (!humanExists(h2)) {
		std::cout << "Ошибка добавления связи! " << h2 << " изгой, не входящий в этот круг общения! Добавьте его!" << std::endl;
		return;
	}

	auto& connectsH1 = connects[h1];

	if (std::find(connectsH1.begin(), connectsH1.end(), h2) == connectsH1.end()) {
		connectsH1.push_back(h2);
		connects[h2].push_back(h1);
	}
}

void SocialConnects::printConnects(const int& length) {
	humanPairs pairs;
	findNodeWithMaxDist(pairs, length);

	for (const auto& [h1, h2] : pairs)
		std::cout << h1 << " <---> " << h2 << std::endl;
}

void SocialConnects::findNodeWithMaxDist(humanPairs& pairs, const int& max) {

	int curPath = -1;
	bool visit[humans.size()];
	for (int i = 0; i < humans.size(); ++i)
		visit[i] = false;

	for (auto* human : humans)
		findNodeWithMaxDistInner(human, curPath, visit, pairs, human, max);
}

void SocialConnects::findNodeWithMaxDistInner(Human* cur, int& curPath, bool* visit, humanPairs& pairs, Human* start, const int& maxPath) {
	if (curPath > maxPath) return;
	if (++curPath <= maxPath && curPath)
		pairs.insert(start->getID() < cur->getID() ? std::make_pair(start, cur) : std::make_pair(cur, start));

	visit[cur->getID()] = true;
	
	for (auto* human : connects[cur])
		if (!visit[human->getID()])
			findNodeWithMaxDistInner(human, curPath, visit, pairs, start, maxPath);

	visit[cur->getID()] = false;
	--curPath;
}

SocialConnects::~SocialConnects() {
	for (auto& human : humans) delete human;
}
