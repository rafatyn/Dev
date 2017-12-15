#include <iostream>
#include <list>
#include <iterator>
#include <type_traits>

enum Directions { left, up, right, down };

template<class T> typename std::enable_if<std::is_base_of<std::iterator<std::input_iterator_tag, long, long, const long*, long>, T>::value, T>::type
next(T it, int number) {
	for (number) {
		it++;
	}
	return it;
}

int main() {

	int number = 0;
	std::cout << "Introduce the number you want to find: ";
	std::cin >> number;
	
	std::list<std::list<int>> father;
	father.emplace_back(); father.emplace_back();
	(*next(father.begin(), 0)).push_back(1);
	(*next(father.begin(), 1)).push_back(2);
	(*next(father.begin(), 1)).push_front(3);	
	Directions direction = down;
	int column = 0;
	for (int i = 1; i <= number; ++i) {
		(*next(father.begin(), column)).push_back(i);
		switch (direction) {
		case left:
			
			break;
		case up:

			break;
		case right:

			break;
		case down:
			if ((*std::next(father.begin(), column)).size() > (*std::next(father.begin(), column+1)).size()) {

			}
			break;
		}
	}
}