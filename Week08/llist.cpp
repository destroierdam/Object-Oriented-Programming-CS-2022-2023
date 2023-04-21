#include <iostream>
#include <cassert>

template<typename T>
class List {
public:
	List():first(nullptr) {}
	List(const List& other) {
		copyNoAdd(other);
	}
	List& operator=(const List& other) {
		if (this != &other) {
			this->destroy();
			this->copyNoAdd(other);
		}
		return *this;
	}
	~List() {
		this->destroy();
	}
	List& add(const T& elem) {
		if (this->first == nullptr) {
			this->first = new Node{ elem, nullptr };
			return *this;
		}

		Node* current = this->first;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = new Node{ elem, nullptr };
		return *this;
	}

	void print() const {
		Node* current = this->first;
		while (current != nullptr) {
			std::cout << current->data << " -> ";
			current = current->next;
		}
		std::cout << "nullptr\n";
	}
private:

	void copyWithAdd(const List& other) {
		Node* current = other.first;
		while (current != nullptr) {
			this->add(current->data);
			current = current->next;
		}
	}

	void copyNoAdd(const List& other) {
		Node * other_current = other.first;
		Node * this_current = nullptr;
		while (other_current != nullptr) {
			Node* newNode = new Node{ other_current->data,
									  nullptr };
			if (this->first == nullptr) {
				this->first = newNode;
				this_current = this->first;
			} else {
				assert(this_current != nullptr);
				this_current->next = newNode;
				this_current = this_current->next;
			}
			other_current = other_current->next;
		}
	}

	void destroy() {
		while (this->first != nullptr) {
			Node* next = this->first->next;
			delete this->first;
			this->first = next;

			// alternative
			// delete std::exchange(this->first,
			//			 this->first->next);
		}
	}

	struct Node {
		T data;
		Node *next;
	};

	Node* first;
};

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

	List<int> l2(list);

	list.add(5);

	//std::cout << "l2:\n";
	//l2.print();

	
}

int main() {
	while (true) {
		work();
	}
}
