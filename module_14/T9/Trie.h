#pragma once

#include <string>
#include <vector>
#include <map>

typedef std::vector<std::string> vectorStr;

class Trie {
	struct Node {
		std::map<char, Node*> childs;
		bool isEnd = false;

		Node() = default;
		bool empty();
		~Node();
	};

	Node* root;

public:
	Trie();

	void insert(const std::string& str);
	bool search(const std::string& str) const;
	void search(const std::string& str, vectorStr& found) const;
	void possible(const Node* root, vectorStr& possible, std::string& tmp) const;
	bool remove(const std::string& str, Node* root = nullptr);

	void clear();

	~Trie();
};
