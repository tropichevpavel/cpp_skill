
#include "Trie.h"

Trie::Trie() {
	root = new Node();
}

void Trie::insert(const std::string& str) {
	Node* node = root;

	for (const auto& ch : str)
		if (node->childs.find(ch) != node->childs.end())
			node = node->childs[ch];
		else
			node = node->childs[ch] = new Node();

	node->isEnd = true;
}

bool Trie::search(const std::string& str) const {
	Node* node = root;

	for (const auto& ch : str) {
		if (node->childs.find(ch) == node->childs.end())
			return false;
		node = node->childs[ch];
	}

	return node->isEnd;
}

void Trie::search(const std::string& str, vectorStr& found) const {
	found = {};
	Node* node = root;
	std::string tmp;

	for (const auto& ch : str)
		if (node->childs.find(ch) != node->childs.end()) {
			tmp += ch;
			node = node->childs[ch];
		} else return;

	possible(node, found, tmp);
}

void Trie::possible(const Node* root, vectorStr& found, std::string& tmp) const {
	if (root->isEnd) found.push_back(tmp);

	for (const auto& [ch, node] : root->childs) {
		tmp += ch;
		possible(node, found, tmp);
		tmp = tmp.substr(0, tmp.length() - 1);
	}
}

bool Trie::remove(const std::string& str, Node* node) {
	if (!node) node = this->root;
	if (!str.size()) {
		node->isEnd = false;
		return node->empty();
	}

	char ch = str[0];
	if (node->childs.find(ch) != node->childs.end())
		if (remove(str.substr(1, str.size()), node->childs[ch])) {
			delete node->childs[ch];
			node->childs.erase(ch);
		}

	return !node->isEnd && node->empty();
}

bool Trie::Node::empty() {
	return !childs.size();
}

void Trie::clear() {
	delete root;
	root = new Node;
}

Trie::~Trie() {
	delete root;
}

Trie::Node::~Node() {
	for (const auto& [ch, node] : childs)
		delete node;
}
