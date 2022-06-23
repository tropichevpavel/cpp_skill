
#define SIZE 10

class Tree {
	struct Node {
		int id;

		Node* parent;
		Node* children[SIZE];
		int childCount;
		
		Node(int id, Node* parent = nullptr) : id(id), parent(parent), childCount(0) {}
		~Node() {
			for (int i = 0; i < childCount; ++i)
				delete children[i];
		}

		void add(Node* child) {
			children[childCount++] = child;
		}

		void del(Node* child) {
			--childCount;
			while (child->childCount)
				children[childCount++] = child->children[--child->childCount];
			delete child;
		}
	};

	Node* root = nullptr;

public:
	Tree() {}
	~Tree() {
		if (root) delete root;
	}

	void setRoot(int id) {
		if (root) delete root;

		root = new Node(id);
	}

	Node* getNode(int id, Node* node) {
		if (node->id == id) return node;

		Node* found = nullptr;
		for (int i = 0; i < node->childCount; ++i)
			if (found = getNode(i, node->children[i]))
				return found;
		return found;
	}

	void add(int parent, int id) {
		Node* node = getNode(id, root);
		if (node)
			node->add(new Node(id, node));
	}

	void del(int id) {
		Node* node = getNode(id, root);
		if (node) node->parent->del(node);
	}
};

int main() {

	Tree tree;
    
    tree.setRoot(2);
    tree.add(2, 4);
    tree.add(2, 0);
    tree.add(2, 3);
    tree.add(4, 1);
    tree.add(1, 5);
    tree.add(1, 6);
    
    tree.del(4);

	return 0;
}