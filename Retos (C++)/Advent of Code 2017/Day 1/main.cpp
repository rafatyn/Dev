#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>

int main() {

	char* input = new char[10000];
	do {
		std::cout << "Introduce the digits of the captcha: ";
		std::cin >> input;
		
		std::vector<unsigned short> digits;
		for (int i=0; input[i] != '\0' ; ++i) {
			digits.push_back(static_cast<unsigned short>(input[i])-48);
		}

		int sum = 0;
		for (auto it = digits.cbegin(); it != digits.cend(); ++it) {
			if (it + 1 == digits.cend()) { if (*it == *digits.cbegin()) { sum += *it; } }
			else { if (*it == *(it + 1)) { sum += *it; } }
		}
		std::cout << "The solution is: " << sum << std::endl;
	} while (input[0] != '/0');

	return 0;
}