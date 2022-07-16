
#include <string>

#define ALPHABET_SIZE 26

class Trie {

	struct Node {
		Node* children[ALPHABET_SIZE];
		bool isEnd = false;
	};

	Node* newNode() {
		Node* node = new Node;

		for (int i = 0; i < ALPHABET_SIZE; ++i)
			node->children[i] = nullptr;

		return node;
	}

	void insert(Node* root, std::string str) {
		Node* node = root;

		for (int i = 0; i < str.size(); ++i) {
			int index = str[i] - 'a';

			if (!node->children[index])
				node->children[index] = newNode();
			
			node = node->children[index];
		}

		node->isEnd = true;
	}

	bool search(Node* root, std::string str) {
		Node* node = root;

		for (int i = 0; i < str.size(); ++i) {
			int index = str[i] - 'a';
			
			if (!node->children[index])
				return false;
			
			node = node->children[index];
		}

		return !node && node->isEnd;
	}

	bool isEmpty(Node* root) {
		for (int i = 0; i < ALPHABET_SIZE; i++)
			if (root->children[i])
				return false;
		return true;
	}

	Node* remove(Node* root, std::string str, int depth = 0) {
		if (!root) return nullptr;
		if (depth == str.size()) {
			root->isEnd = false;
			if (isEmpty(root)) {
				delete root;
				root = nullptr;
			}
			return root;
		}

		int index = str[depth] - 'a';
		root->children[index] = remove(root->children[index], str, ++depth);

		if (isEmpty(root) && !root->isEnd) {
			delete root;
			root = nullptr;
		}

		return root;
	}

// 	int count(TrieNode* root) {
//     int count = 0; 
//     for (int i = 0; i < ALPHABET_SIZE; i++) 
//         count += root->children[i] != nullptr;
//     return count;
// }

// bool isOne(TrieNode* root) {
//     while (root) {
//         if (isEmpty(root))
//             return true;

//         if (count(root) == 1 && !root->isEndOfWord) {
//             for (int i = 0; i < ALPHABET_SIZE; i++)
//                 if (root->children[i]) {
//                     root = root->children[i];
//                     break;
//                 }
//         }

//         else break;
//     }
    
//     return false;
// }

// void print(TrieNode* root, int uu) {
//     if (uu) return;
//    for (int i = 0; i < ALPHABET_SIZE; i++)
//         if (root->children[i]) {
//             char c = i + 'a';
//             std::cout << c;
//             if (root->children[i]->isEndOfWord) std::cout << "- end -";
//             print(root->children[i], 0);
//         }
//     std::cout << std::endl;
// } 

// // не изменияйте сигнатуру функции
// void findMinPrefixes(TrieNode* root, char* buf, int ind, string& res)
// {
//     TrieNode* node = root;
//     print(root, ind);

//     if (!isEmpty(root) && !isOne(root)) {
        
//         // if (root->isEndOfWord) {
//         //     res += std::string(buf) + " ";
//         //     // for (int i = ind; i < 8; ++i)
//         //     //     buf[i] = 0;
//         // }

//         for (int i = 0; i < ALPHABET_SIZE; i++)
//             if (root->children[i]) {
//                 buf[ind] = i + 'a';

//                 findMinPrefixes(root->children[i], buf, ind + 1, res);
//             }
//     } 
    
//     else {
//         for (int i = ind; i < 8; ++i)
//             buf[i] = 0;
//         std::cout << std::string(buf) << " --- end --- " << std::endl;
//         res += std::string(buf) + " ";
        
//     }
// }
};