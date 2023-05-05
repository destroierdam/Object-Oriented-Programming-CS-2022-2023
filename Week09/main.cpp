#include <iostream>
#include <cassert>

#include "List.hpp"

void work() {
	List<int> list;
	list.add(1);
	//list.print();
	list.add(2);
	//list.print();
	list.add(3);
	//list.print();
	list.add(4);
	//	list.print();

	const List<int> l2(list);

	list.add(5);

	//std::cout << "l2:\n";
	//l2.print();

	for (List<int>::Iterator it = list.begin();
			it != list.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n-----\n";

	for (int& elem : list) {
		elem = 777;
	}
	for (int elem : list) {
		std::cout << elem << " ";
	}


}

int main() {
	// while (true) {
		work();
	// }
}
