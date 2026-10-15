#include <cstddef>
#include <optional>
#include <utility>
#include <vector>
#include <iostream>
#include <stdexcept>


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


template<typename T>
class Queue{
    struct Node{
        T data;
        Node* next= nullptr;

        Node(const T& val, Node* n = nullptr) : data(val), next(n){}
    };
    Node* top = nullptr;
    Node* tail = nullptr;
    public:

    Queue():top(nullptr), tail(nullptr){}
    Queue(const Queue& other): top (nullptr){
        Node* curr = other.top;

        while (curr != nullptr){
            push(curr->data);
            curr = curr->next;
        }
    }


    Queue& operator=(const Queue& other){
        if (this == &other){
            return *this;
        }

        Queue copy(other);

        std::swap(top, copy.top);
        std::swap(tail, copy.tail);

        return *this;
    }

    void push(const T& val){
        Node* nNode = new Node(val, nullptr);
        if(top == nullptr){
            top = nNode;
            tail = nNode;
            return;
        }
        tail->next = nNode;
        tail = nNode;
    }

    void pop(){
        if (top == nullptr) return;
        if (top->next == nullptr){
            delete top;
            top = nullptr;
            tail = nullptr;
            return;
        }
        Node*temp = top;
        top = top->next;
        delete temp;
    }

    std::optional<T> front()const{
        if (top == nullptr){
            return std::nullopt;
        }
        return top->data;
    }

    std::optional<T> back() const{
        if (tail == nullptr){
            return std::nullopt;
        }
        return tail->data;
    }

    bool empty()const{
        if(top != nullptr) return false;
        else return true;
    }

    ~Queue(){
        Node* curr = top;
        while(top != nullptr){
            top = top->next;
            delete curr;
            curr = top;
        }
        top = nullptr;
        tail = nullptr;
    }
};


template<typename T>
class Stack{
    struct Node{
        T data;
        Node* next = nullptr;
        Node(const T& d, Node* n = nullptr): data(d), next(n){}
    };
    Node* top = nullptr;
    std::size_t count = 0;

    public:

    Stack() = default;

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& val){
        top = new Node(val, top);
        ++count;
    }

    void pop(){
        if (top == nullptr)return;

        Node*temp = top;
        top = top->next;
        delete temp;
        --count;
    }

    const T& peek()const{
        if(top == nullptr) throw std::runtime_error("Stack is empty");

        return top->data;
    }


    std::size_t size()const{
        return count;
    }

    bool isEmpty()const{
        return top == nullptr;
    }

    ~Stack(){
        while(top != nullptr){
            pop();
        }
    }
};

int main() {
    std::cout << "=== Deque con lista doblemente enlazada ===\n";
    DequeLinkedList<int> deque;

    deque.push_back(20);
    deque.push_back(30);
    deque.push_front(10);
    deque.push_front(5);

    std::cout << "Despues de push_back(20), push_back(30), "
              << "push_front(10), push_front(5):\n";
    std::cout << "Frente: " << *deque.front() << '\n';
    std::cout << "Final: " << *deque.back() << '\n';
    std::cout << "Tamano: " << deque.size() << "\n\n";

    deque.pop_front();
    deque.pop_back();
    std::cout << "Despues de pop_front() y pop_back():\n";
    std::cout << "Frente: " << *deque.front() << '\n';
    std::cout << "Final: " << *deque.back() << '\n';
    std::cout << "Tamano: " << deque.size() << "\n\n";

    std::cout << "=== Queue ===\n";
    Queue<std::string> queue;
    queue.push("primero");
    queue.push("segundo");
    queue.push("tercero");

    std::cout << "Despues de agregar tres elementos:\n";
    std::cout << "Frente: " << *queue.front() << '\n';
    std::cout << "Final: " << *queue.back() << '\n';

    queue.pop();
    std::cout << "Despues de pop():\n";
    std::cout << "Frente: " << *queue.front() << '\n';
    std::cout << "Final: " << *queue.back() << "\n\n";

    std::cout << "=== Stack ===\n";
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Despues de push(10), push(20), push(30):\n";
    std::cout << "Tope: " << stack.peek() << '\n';
    std::cout << "Tamano: " << stack.size() << '\n';

    stack.pop();
    std::cout << "Despues de pop():\n";
    std::cout << "Tope: " << stack.peek() << '\n';
    std::cout << "Tamano: " << stack.size() << '\n';

    stack.pop();
    stack.pop();
    queue.pop();
    queue.pop();
    deque.pop_front();
    deque.pop_back();

    std::cout << "\nEstados finales:\n";
    std::cout << "Deque vacio: " << (deque.empty() ? "si" : "no") << '\n';
    std::cout << "Queue vacio: " << (queue.empty() ? "si" : "no") << '\n';
    std::cout << "Stack vacio: " << (stack.isEmpty() ? "si" : "no") << '\n';

    return 0;
}

