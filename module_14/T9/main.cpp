
#include <iostream>
#include <string>

#include "Trie.h"

int main() {

	Trie dict;

	dict.insert("hi");
	dict.insert("hell");
	dict.insert("hello");
	dict.insert("hollow");
	dict.insert("holland");
	dict.insert("holly");
	dict.insert("hollywood");

	std::string text = "";
	
	vectorStr found = {};
	std::string input = "";
	std::string sin = "";

	while (true) {

		std::cout << u8"\e[1;1H\e[2J";
		std::cout << " ~~ Console T9 ~~ " << std::endl << std::endl;

		if (!input.empty()) {
			dict.search(input, found);
			int i = 0;
			for (const auto& word : found)
				std::cout << ++i << " - " << word << std::endl;
		}

		if (input.empty())
				std::cout << "Enter part of word and press Enter";
		
		else if (found.empty())
			std::cout << "Add word";
		
		else
			std::cout << "Chose autocomplite word";
		
		std::cout << std::endl;

		std::cout << " -. Add to text ";
		
		if (!input.empty() && input.find(' ') == -1) {
			if (!dict.search(input))
				std::cout << "| +. Add to text & dict ";
			else
				std::cout << "| ~. Del from dict ";
		}

		if (!input.empty()) std::cout << "| 0. Clear input ";
		else if (!text.empty()) std::cout << "| 0. Clear text ";

		std::cout << "| #. Quit " << std::endl << std::endl;

		std::cout << " - Text : " << text << std::endl << std::endl;
		std::cout << " - Enter : " << input;
		std::getline(std::cin, sin);

		if (sin.length() == 1) {
			char in = sin[0];

			if (in == '#') break;
			else if (in == '0') (!input.empty() ? input : text) = "";
			else if (in == '~') {
				dict.remove(input);
				input = "";

			} else if (in == '-' || in == '+') {
				if (in == '+') dict.insert(input);
				text += " " + input;
				input = "";

			} else if (in > '0' && in < '9' && in - '0' <= found.size()) {
				text += " " + found[in - '1'];
				input = "";

			} else input += in;

		} else input += sin;
	}

	return 0;
}
