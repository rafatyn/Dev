#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

#define INPUT_FILE 1

int main() {

	int rows = 0;
#if INPUT_FILE
	std::cout << "Introduce the numbers of rows: ";
	std::cin >> rows;
	getchar();
	std::cout << "Introduce the matrix of numbers: " << std::endl;
#else
	std::ifstream fp;
	fp.open("input.txt");
	fp >> rows;
	fp.get();
#endif
	std::vector<std::vector<int>> matrix;
	matrix.reserve(rows);
	for (int i = 0; i < rows; i++) {
		char *tok, *next;
		std::string input;
#if INPUT_FILE
		std::getline(std::cin, input);
#else
		std::getline(fp, input);
#endif
		std::vector<int> row;
		tok = strtok_s(const_cast<char*>(input.c_str()), " ,\t", &next);
		while (tok != nullptr) {
			row.push_back(atoi(tok));
			tok = strtok_s(nullptr, " ,\t", &next);
		}
		matrix.push_back(row);
	}
	int sum = 0;
	for (const auto & it : matrix) {
		int max = *std::max_element(it.cbegin(), it.cend());
		int min = *std::min_element(it.cbegin(), it.cend());
		sum += (max - min);
	}
	std::cout << "The checksum is: " << sum << std::endl;

	system("PAUSE");
	
	return 0;
}