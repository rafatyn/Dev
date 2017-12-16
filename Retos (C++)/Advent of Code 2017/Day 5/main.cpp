#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

int main() {

	std::ifstream fp;
	fp.open("input.txt");

	std::vector<int> vector;
	while (!fp.eof()) {
		std::string input;
		std::getline(fp, input);
		vector.push_back(atoi(input.c_str()));		
	}
	int index = 0, steps  = 0;
	while (index >= 0 && index < vector.size()) {
		vector[index]++;
		index += vector[index] - 1;
		steps++;
	}
	std::cout << "Steps needed to reach the exit: " << steps << std::endl;
	system("PAUSE");

	return 0;
}