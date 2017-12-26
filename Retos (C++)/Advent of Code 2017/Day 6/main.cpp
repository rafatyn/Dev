#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	int banks;
	std::cout << "Number of banks of memory: ";
	std::cin >> banks;

	char *tok, *next;
	std::string input;
	std::cout << "Initial state: ";
	std::vector<int> memory;
	std::vector<std::vector<int>> memoryHistory;
	for (int i = 0; i < banks; i++) {
		std::cin >> input;
		memory.emplace_back(atoi(input.c_str()));
	}
	int steps = 0;
	while (std::find(memoryHistory.begin(), memoryHistory.end(), memory) == memoryHistory.end()) {
		int max = *std::max_element(memory.begin(), memory.end());
		memoryHistory.push_back(memory);
		for (int i = 0; i < memory.size(); i++) {
			if (memory[i] == max) { 
				steps++;
				memory[i] = 0;
				for (int j = 1; j <= max; j++)
				{
					memory[(i + j) % memory.size()]++;
				}
				break;
			}
		}
	}
	std::cout << "Number of steps needed: " << steps << std::endl;

	system("PAUSE");

	return 0;
}