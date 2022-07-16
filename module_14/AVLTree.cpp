
#include <cstddef>
#include <queue>

class AVLTree {
	struct Node {
		int key;
		Node* left = nullptr;
		Node* right = nullptr;
		size_t height = 0;

		Node(int& key) : key(key) {}
		Node(int&& key) : key(key) {}
	};

	Node* root = nullptr;

public:

	AVLTree() = default;

	auto height(Node* node) -> size_t { return node ? node->height : 0; }
	auto bfactor(Node* node) -> int { return height(node->right) - height(node->left); }

	void fixHeight(Node* node) {
		size_t left = height(node->left);
		size_t right = height(node->right);

		node->height = (left > right ? left : right) + 1;
	}

	Node* rotateRight(Node* node) {
		Node* temp = node->left;
		node->left = temp->right;
		temp->right = node;

		fixHeight(temp);
		fixHeight(node);

		return temp;
	}

	Node* rotateLeft(Node* node) {
		Node* temp = node->right;
		node->right = temp->left;
		temp->left = node;

		fixHeight(temp);
		fixHeight(node);

		return temp;
	}

	Node* balance(Node* const node) { // https://habr.com/ru/post/59558/
		fixHeight(node);

		int bf = bfactor(node);

		if (bf == 2) {
			if (bfactor(node->right) < 0)
				node->right = rotateRight(node->right);
			return rotateLeft(node);
		}

		if (bf == -2) {
			if (bfactor(node->left) > 0)
				node->left = rotateLeft(node->left);
			return rotateRight(node);
		}

		return node;
	}

	auto bfs(const int& key) -> const Node* {
		if (!root) return nullptr;

		std::queue<Node*> q;
		q.push(root);

		while (!q.empty()) {
			Node* node = q.front();
			q.pop();

			if (node->key == key) return node;
			if (node->left) q.push(node->left);
			if (node->right) q.push(node->right);
		}

		return nullptr;
	}

	auto dfs(const Node* node, const int& key) -> const Node* {
		if (node->key == key) return node;

		const Node* tmp = nullptr;
		if (node) {
		if (node->left) tmp = dfs(node->left, key);
		if (node->right && !tmp) tmp = dfs(node->right, key);
		}

		return tmp;
	}

	void insert(int&& key) {
		root = insert(root, new Node(key));
	}

	auto insert(Node* root, Node* const node) -> Node* {
		if (!root) return node;

		if (node->key < root->key)
			root->left = insert(node->left, node);
		else
			root->right = insert(node->right, node);

		return balance(root);
	}

	void remove(const int& key) {
		root = remove(root, key);
	}

	auto remove(Node* node, const int& key) -> Node* {
		if (!node) return nullptr;

		if (key < node->key)
			node->left = remove(node->left, key);
		else if (key > node->key)
			node->right = remove(node->right, key);
		else {
			Node* l = node->left;
			Node* r = node->right;
			delete node;

			if (!r) return l;

			Node* min = findMin(r);

			min->right = removeMin(r);
			min->left = l;

			return balance(min);
		}

		return balance(node);
	}

	auto findMin(Node* node) -> Node* {
		return node->left ? findMin(node->left) : node;
	}

	auto removeMin(Node* node) -> Node* {
		if (!node->left) return node->right;

		node->left = removeMin(node->right);

		return balance(node);
	}
};

int main() {



	// https://habr.com/ru/post/59558/
	return 0;
}