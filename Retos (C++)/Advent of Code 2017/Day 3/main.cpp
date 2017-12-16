#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
#include <cmath>

#define PRINT_MAT 0

enum Directions { left, up, right, down };

template<class T>
auto lnext(T &list, int number) -> decltype(std::next(list.begin(), 0))
{
	auto iter = list.begin();
	if (number) {
		for (int i = 1; i <= number; i++) {
			iter = std::next(list.begin(), i);
			if (iter == list.end()) {
				list.emplace_back();
			}
		}
	}
	else {
		if (iter == list.end()) {
			list.emplace_back();
		}
	}
	return std::next(list.begin(), number);
}

int lsize(std::list<std::list<int>> &list, int number) {
	if (number < 0) {
		return -1;
	}
	auto iter = std::next(list.begin(), number);
	if (iter == list.end()) {
		return -1;
	}
	return static_cast<int>(iter->size());
}

int main()
{
	int number = 0;
	std::cout << "Introduce the number you want to find: ";
	std::cin >> number;
	
	clock_t begin = clock();
	
	std::list<std::list<int>> father;
	lnext(father, 0)->push_back(1);
	Directions direction = right;
	int column = 1;
	bool sym = false;
	for (int i = 2; i <= number || !sym; ++i) {
		Directions dirBefore = direction;
		if (column >= static_cast<int>(father.size()) && direction == right) {
			direction = up;
		}
		else if (column < 0 && direction == left) {
			father.emplace_front();
			column++;
			direction = down;
		}
		else if (lsize(father, column) == lsize(father, column - 1) && direction == up) {
			direction = left;
		}
		else if (lsize(father, column) == lsize(father, column + 1) && direction == down) {
			direction = right;
		}
		if (dirBefore == down || dirBefore == right) {
			lnext(father, column)->push_back(i);
			if (!(dirBefore == right && direction == up) && !(dirBefore == down && direction == down)) {
				column++;
			}
		}
		else if (dirBefore == up || dirBefore == left) {
			lnext(father, column)->push_front(i);
			if (!(dirBefore == left && direction == down) && !(dirBefore == up && direction == up)) {
				column--;
			}
		}
		if (i >= number) {
			int size = lsize(father, 0);
			bool tmp = false;
			for (int j = 1; j < static_cast<int>(father.size()); j++) {
				if (lsize(father, j) != size) {
					tmp = true;
					break;
				}
			}
			if (tmp) {
				sym = false;
			}
			else {
				sym = true;
			}
		}
	}

#if PRINT_MAT
	int numberCopy = number, length = 0;
	for (; numberCopy != 0; numberCopy /= 10, length++);
	for (int j = 0; j < lsize(father, 0); j++) {
		for (int i = 0; i < static_cast<int>(father.size()); i++) {
			std::cout << std::setw(length + 2) << *lnext(*lnext(father, i), j);
		}
		std::cout << std::endl;
	}
#endif
	int posXCentre = 0, posYCentre = 0, posXObj = 0, posYObj = 0;
	for (int j = 0; j < lsize(father, 0); j++) {
		for (int i = 0; i < static_cast<int>(father.size()); i++) {
			if (*lnext(*lnext(father, i), j) == 1) {
				posXCentre = i; posYCentre = j;
			}
			else if (*lnext(*lnext(father, i), j) == number) {
				posXObj = i; posYObj = j;
			}
		}
	}
	int steps = std::abs(posXCentre - posXObj) + std::abs(posYCentre - posYObj);
	std::cout << "Steps to reach number " << number << ": " << steps << std::endl;
	
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Time expended: " << elapsed_secs << "s" << std::endl;
	
	system("PAUSE");

	return 0;
}