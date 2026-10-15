#include <cstddef>
#include <optional>
#include <utility>
#include <vector>
#include <iostream>


template<typename T>
class DequeLinkedList {
	struct Node {
		T data;
		Node* next;
		Node* prev;

		Node(const T& value, Node* nextNode = nullptr, Node* previousNode = nullptr)
			: data(value), next(nextNode), prev(previousNode) {}
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	std::size_t count = 0;

public:
	DequeLinkedList() = default;

	DequeLinkedList(const DequeLinkedList& other) {
		for (Node* current = other.head; current != nullptr; current = current->next) {
			push_back(current->data);
		}
	}

	DequeLinkedList& operator=(const DequeLinkedList& other) {
		if (this == &other) return *this;

		DequeLinkedList copy(other);
		swap(copy);
		return *this;
	}

	~DequeLinkedList() {
		clear();
	}

	void push_front(const T& value) {
		Node* newNode = new Node(value, head, nullptr);
		if (head != nullptr) {
			head->prev = newNode;
		} else {
			tail = newNode;
		}
		head = newNode;
		++count;
	}

	void push_back(const T& value) {
		Node* newNode = new Node(value, nullptr, tail);
		if (tail != nullptr) {
			tail->next = newNode;
		} else {
			head = newNode;
		}
		tail = newNode;
		++count;
	}

	void pop_front() {
		if (head == nullptr) return;

		Node* oldHead = head;
		head = head->next;
		if (head != nullptr) {
			head->prev = nullptr;
		} else {
			tail = nullptr;
		}
		delete oldHead;
		--count;
	}

	void pop_back() {
		if (tail == nullptr) return;

		Node* oldTail = tail;
		tail = tail->prev;
		if (tail != nullptr) {
			tail->next = nullptr;
		} else {
			head = nullptr;
		}
		delete oldTail;
		--count;
	}

	std::optional<T> front() const {
		if (head == nullptr) return std::nullopt;
		return head->data;
	}

	std::optional<T> back() const {
		if (tail == nullptr) return std::nullopt;
		return tail->data;
	}

	bool empty() const {
		return count == 0;
	}

	std::size_t size() const {
		return count;
	}

private:
	void clear() {
		while (head != nullptr) pop_front();
	}

	void swap(DequeLinkedList& other) {
		std::swap(head, other.head);
		std::swap(tail, other.tail);
		std::swap(count, other.count);
	}
};

template<typename Deque>
void showDeque(const Deque& deque) {
	std::cout << "Tamano: " << deque.size() << '\n';

	if (!deque.empty()) {
		std::cout << "Frente: " << *deque.front() << '\n';
		std::cout << "Final: " << *deque.back() << '\n';
	}
}

int main() {
	DequeLinkedList<int> deque;

	std::cout << "Deque con lista doblemente enlazada\n";

	deque.push_back(20);
	deque.push_back(30);
	deque.push_front(10);
	deque.push_front(5);

	std::cout << "Despues de push_back(20), push_back(30), "
		<< "push_front(10), push_front(5):\n";
	showDeque(deque);

	deque.pop_front();
	std::cout << "\nDespues de pop_front():\n";
	showDeque(deque);

	deque.pop_back();
	std::cout << "\nDespues de pop_back():\n";
	showDeque(deque);

	deque.pop_front();
	deque.pop_back();
	std::cout << "\nDespues de eliminar todos los elementos:\n";
	std::cout << "Vacia: " << (deque.empty() ? "si" : "no") << '\n';
	std::cout << "Tamano: " << deque.size() << '\n';

	return 0;
}