#include <iostream>
#include <initializer_list>
#include <utility>

template<typename T>
class linked_list {

    struct Node {
        T data;
        Node* next;

        Node(const T& val, Node* n = nullptr)
            : data(val), next(n) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:

    linked_list() = default;

    linked_list(const linked_list& other) {

        Node* curr = other.head;

        while (curr != nullptr) {
            push_back(curr->data);
            curr = curr->next;
        }
    }

    linked_list(std::initializer_list<T> init) {

        for (const T& val : init) {
            push_back(val);
        }
    }

    linked_list& operator=(const linked_list& other) {

        if (this == &other)
            return *this;

        linked_list copy(other);

        std::swap(head, copy.head);
        std::swap(tail, copy.tail);

        return *this;
    }

    void push_front(const T& val) {

        Node* nNode = new Node(val, head);

        head = nNode;

        if (tail == nullptr)
            tail = head;
    }

    void push_back(const T& val) {

        Node* nNode = new Node(val);

        if (head == nullptr) {
            head = tail = nNode;
            return;
        }

        tail->next = nNode;
        tail = nNode;
    }

    void pop_front() {

        if (head == nullptr)
            return;

        Node* temp = head;

        head = head->next;

        if (head == nullptr)
            tail = nullptr;

        delete temp;
    }

    void pop_back() {

        if (head == nullptr)
            return;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }

        Node* curr = head;

        while (curr->next != tail) {
            curr = curr->next;
        }

        delete tail;

        tail = curr;
        tail->next = nullptr;
    }

    bool search(const T& val) {

        Node* curr = head;

        while (curr != nullptr) {

            if (curr->data == val)
                return true;

            curr = curr->next;
        }

        return false;
    }

    bool removeX(const T& x) {

        if (head == nullptr)
            return false;

        if (head->data == x) {

            Node* temp = head;

            head = head->next;

            if (head == nullptr)
                tail = nullptr;

            delete temp;

            return true;
        }

        Node* prev = head;
        Node* curr = head->next;

        while (curr != nullptr && curr->data != x) {

            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr)
            return false;

        prev->next = curr->next;

        if (curr == tail)
            tail = prev;

        delete curr;

        return true;
    }

    bool insertX(const T& ref, const T& x) {

        Node* curr = head;

        while (curr != nullptr && curr->data != ref) {
            curr = curr->next;
        }

        if (curr == nullptr)
            return false;

        Node* nNode = new Node(x, curr->next);

        curr->next = nNode;

        if (curr == tail)
            tail = nNode;

        return true;
    }

    void reverse() {

        Node* prev = nullptr;
        Node* curr = head;

        tail = head;

        while (curr != nullptr) {

            Node* next = curr->next;

            curr->next = prev;

            prev = curr;
            curr = next;
        }

        head = prev;
    }

    static linked_list join(const linked_list& list1,
                            const linked_list& list2) {

        linked_list newlist;

        Node* curr1 = list1.head;
        Node* curr2 = list2.head;

        while (curr1 != nullptr && curr2 != nullptr) {

            if (curr1->data <= curr2->data) {
                newlist.push_back(curr1->data);
                curr1 = curr1->next;
            }
            else {
                newlist.push_back(curr2->data);
                curr2 = curr2->next;
            }
        }

        while (curr1 != nullptr) {
            newlist.push_back(curr1->data);
            curr1 = curr1->next;
        }

        while (curr2 != nullptr) {
            newlist.push_back(curr2->data);
            curr2 = curr2->next;
        }

        return newlist;
    }

    virtual ~linked_list() {

        while (head != nullptr) {

            Node* temp = head;

            head = head->next;

            delete temp;
        }

        tail = nullptr;
    }
};