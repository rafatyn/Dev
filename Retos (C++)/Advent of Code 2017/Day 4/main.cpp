#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
	int valid = 0;
	std::ifstream fp;
	fp.open("input.txt");
	while(!fp.eof()) {
		char *tok, *next;
		std::string input;
		std::getline(fp, input);
		std::vector<std::string> row;
		tok = strtok_s(const_cast<char*>(input.c_str()), " ,\t", &next);
		while (tok != nullptr) {
			row.emplace_back(tok);
			tok = strtok_s(nullptr, " ,\t", &next);
		}
		bool dif = false;
		for (int i = 0; i < row.size() && !dif; i++) {
			for (int j = 0; j < row.size() && !dif; j++) {
				if (row[i] == row[j] && i != j) {
					dif = true;
				}
			}
		}
		if (!dif) {
			valid++;
		}
	}	
	std::cout << "Number of passwords valid: " << valid << std::endl;
	fp.close();

	system("PAUSE");

	return 0;
}