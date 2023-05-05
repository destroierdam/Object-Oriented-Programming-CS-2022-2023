#pragma once

#include <cassert>

template<typename T>
class List {
public:
	struct Node;

	class Iterator {
	public:
		Iterator(List<T>::Node* pointer): pointer(pointer) {}
		bool operator!=(const Iterator& other) const {
			return this->pointer != other.pointer;
		}
		Iterator& operator++() {
			this->pointer = this->pointer->next;
			return *this;
		}
		T& operator*() {
			return this->pointer->data;
		}
	private:
		Node* pointer;
	};
public:
	List();
	List(const List& other);
	List& operator=(const List& other);
	~List();
	List& add(const T& elem);
	void print() const;

	List::Iterator begin() {
		return List::Iterator(this->first);
	}

	List::Iterator end() {
		return List::Iterator(nullptr);
	}

private:
	struct Node {
		T data;
		Node* next;
	};

private:
	void copyWithAdd(const List& other);
	void copyNoAdd(const List& other);
	void destroy();

private:
	Node* first;
};

/// ------------ IMPLEMENTATION ------------

template<typename T>
List<T>::List<T>() :first(nullptr) {}

template<typename T>
List<T>::List(const List<T>& other) {
	copyNoAdd(other);
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
	if (this != &other) {
		this->destroy();
		this->copyNoAdd(other);
	}
	return *this;
}

template<typename T>
List<T>::~List() {
	this->destroy();
}

template<typename T>
List<T>& List<T>::add(const T& elem) {
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

template<typename T>
void List<T>::print() const {
	Node* current = this->first;
	while (current != nullptr) {
		std::cout << current->data << " -> ";
		current = current->next;
	}
	std::cout << "nullptr\n";
}

template<typename T>
void List<T>::copyWithAdd(const List& other) {
	Node* current = other.first;
	while (current != nullptr) {
		this->add(current->data);
		current = current->next;
	}
}
template<typename T>
void List<T>::copyNoAdd(const List& other) {
	Node* other_current = other.first;
	Node* this_current = nullptr;
	while (other_current != nullptr) {
		Node* newNode = new Node{ other_current->data,
								  nullptr };
		if (this->first == nullptr) {
			this->first = newNode;
			this_current = this->first;
		}
		else {
			assert(this_current != nullptr);
			this_current->next = newNode;
			this_current = this_current->next;
		}
		other_current = other_current->next;
	}
}

template<typename T>
void List<T>::destroy() {
	while (this->first != nullptr) {
		Node* next = this->first->next;
		delete this->first;
		this->first = next;

		// alternative
		// delete std::exchange(this->first,
		//			 this->first->next);
	}
}
