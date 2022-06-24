#pragma once

#include <vector>
#include <map>
#include <set>
#include <utility>

#include "Human.h"

typedef std::set<std::pair<Human*, Human*>> humanPairs;

class SocialConnects {
	std::vector<Human*> humans;
	std::map<Human*, std::vector<Human*>> connects;

public:
	SocialConnects() = default;
	~SocialConnects();

	auto addHuman(const std::string& name) -> Human*;
	bool humanExists(const Human* human);

	void addConnect(Human* h1, Human* h2);

	void printConnects(const int& length);

	void findNodeWithMaxDist(humanPairs& pairs, const int& max);
	void findNodeWithMaxDistInner(Human* cur, int& curPath, bool* visit, humanPairs& pairs, Human* start, const int& maxPath);
};
