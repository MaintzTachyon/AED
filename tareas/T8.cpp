#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

template<typename T, typename V>
class BST {
public:
	struct node {
		T key;
		V value;
		node* child[2] = {}; // [0] left | [1] right

		node(const T& keyValue, const V& mappedValue)
			: key(keyValue), value(mappedValue) {}
	};

private:
	node* root = nullptr;
	std::size_t count = 0;

	node* find_node(const T& key) const {
		node* current = root;
		while (current != nullptr) {
			if (key == current->key) return current;
			current = current->child[key > current->key];
		}
		return nullptr;
	}

public:
	BST() = default;

	BST(const BST& other) {
		if (other.root == nullptr) return;

		root = new node(other.root->key, other.root->value);
		std::queue<std::pair<node*, node*>> pending;
		pending.push({root, other.root});

		while (!pending.empty()) {
			node* current = pending.front().first;
			node* source = pending.front().second;
			pending.pop();

			for (int side = 0; side < 2; ++side) {
				if (source->child[side] != nullptr) {
					current->child[side] = new node(
						source->child[side]->key,
						source->child[side]->value);
					pending.push({current->child[side], source->child[side]});
				}
			}
		}
		count = other.count;
	}

	BST& operator=(const BST& other) {
		if (this == &other) return *this;
		BST copy(other);
		swap(copy);
		return *this;
	}

	BST(BST&& other) noexcept
		: root(other.root), count(other.count) {
		other.root = nullptr;
		other.count = 0;
	}

	BST& operator=(BST&& other) noexcept {
		if (this == &other) return *this;
		clear();
		root = other.root;
		count = other.count;
		other.root = nullptr;
		other.count = 0;
		return *this;
	}

	~BST() {
		clear();
	}

	void clear() {
		if (root == nullptr) return;

		std::stack<node*> pending;
		pending.push(root);
		while (!pending.empty()) {
			node* current = pending.top();
			pending.pop();
			if (current->child[0] != nullptr) pending.push(current->child[0]);
			if (current->child[1] != nullptr) pending.push(current->child[1]);
			delete current;
		}
		root = nullptr;
		count = 0;
	}

	node* search(const T& key) {
		return find_node(key);
	}

	const node* search(const T& key) const {
		return find_node(key);
	}

	bool insert(const T& key, const V& value) {
		if (root == nullptr) {
			root = new node(key, value);
			++count;
			return true;
		}

		node* current = root;
		while (true) {
			if (key == current->key) return false;

			const int side = key > current->key;
			if (current->child[side] == nullptr) {
				current->child[side] = new node(key, value);
				++count;
				return true;
			}
			current = current->child[side];
		}
	}

	bool remove(const T& key) {
		node* parent = nullptr;
		node* current = root;

		while (current != nullptr && current->key != key) {
			parent = current;
			current = current->child[key > current->key];
		}
		if (current == nullptr) return false;

		if (current->child[0] != nullptr && current->child[1] != nullptr) {
			node* successorParent = current;
			node* successor = current->child[1];
			while (successor->child[0] != nullptr) {
				successorParent = successor;
				successor = successor->child[0];
			}
			current->key = successor->key;
			current->value = successor->value;
			parent = successorParent;
			current = successor;
		}

		node* replacement = current->child[current->child[1] != nullptr];
		if (parent == nullptr) {
			root = replacement;
		} else {
			parent->child[parent->child[1] == current] = replacement;
		}
		delete current;
		--count;
		return true;
	}

	node* predecessor(const T& key) const {
		node* current = root;
		node* result = nullptr;
		while (current != nullptr) {
			if (key == current->key) {
				if (current->child[0] != nullptr) {
					result = current->child[0];
					while (result->child[1] != nullptr) result = result->child[1];
				}
				return result;
			}
			if (key < current->key) {
				current = current->child[0];
			} else {
				result = current;
				current = current->child[1];
			}
		}
		return nullptr;
	}

	node* successor(const T& key) const {
		node* current = root;
		node* result = nullptr;
		while (current != nullptr) {
			if (key == current->key) {
				if (current->child[1] != nullptr) {
					result = current->child[1];
					while (result->child[0] != nullptr) result = result->child[0];
				}
				return result;
			}
			if (key > current->key) {
				current = current->child[1];
			} else {
				result = current;
				current = current->child[0];
			}
		}
		return nullptr;
	}

	std::size_t size() const { return count; }
	bool empty() const { return root == nullptr; }

	template<typename Fn>
	void in_order(Fn visit) const {
		std::stack<node*> pending;
		node* current = root;
		while (current != nullptr || !pending.empty()) {
			while (current != nullptr) {
				pending.push(current);
				current = current->child[0];
			}
			current = pending.top();
			pending.pop();
			visit(*current);
			current = current->child[1];
		}
	}

	template<typename Fn>
	void pre_order(Fn visit) const {
		if (root == nullptr) return;
		std::stack<node*> pending;
		pending.push(root);
		while (!pending.empty()) {
			node* current = pending.top();
			pending.pop();
			visit(*current);
			if (current->child[1] != nullptr) pending.push(current->child[1]);
			if (current->child[0] != nullptr) pending.push(current->child[0]);
		}
	}

	template<typename Fn>
	void post_order(Fn visit) const {
		if (root == nullptr) return;
		std::stack<std::pair<node*, bool>> pending;
		pending.push({root, false});
		while (!pending.empty()) {
			auto [current, expanded] = pending.top();
			pending.pop();
			if (expanded) {
				visit(*current);
				continue;
			}
			pending.push({current, true});
			if (current->child[1] != nullptr) pending.push({current->child[1], false});
			if (current->child[0] != nullptr) pending.push({current->child[0], false});
		}
	}

	template<typename Fn>
	void level_order(Fn visit) const {
		if (root == nullptr) return;
		std::queue<node*> pending;
		pending.push(root);
		while (!pending.empty()) {
			node* current = pending.front();
			pending.pop();
			visit(*current);
			if (current->child[0] != nullptr) pending.push(current->child[0]);
			if (current->child[1] != nullptr) pending.push(current->child[1]);
		}
	}

	class iterator {
		std::stack<node*> pending;

		void push_left(node* current) {
			while (current != nullptr) {
				pending.push(current);
				current = current->child[0];
			}
		}

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = node;
		using difference_type = std::ptrdiff_t;
		using pointer = node*;
		using reference = node&;

		iterator() = default;
		explicit iterator(node* root) { push_left(root); }

		reference operator*() const { return *pending.top(); }
		pointer operator->() const { return pending.top(); }

		iterator& operator++() {
			node* current = pending.top();
			pending.pop();
			push_left(current->child[1]);
			return *this;
		}

		bool operator==(const iterator& other) const {
			return pending.empty() == other.pending.empty() &&
				(pending.empty() || pending.top() == other.pending.top());
		}
		bool operator!=(const iterator& other) const { return !(*this == other); }
	};

	iterator begin() { return iterator(root); }
	iterator end() { return iterator(); }

private:
	void swap(BST& other) noexcept {
		std::swap(root, other.root);
		std::swap(count, other.count);
	}
};

int main() {
	BST<int, std::string> tree;
	tree.insert(50, "cincuenta");
	tree.insert(30, "treinta");
	tree.insert(70, "setenta");
	tree.insert(20, "veinte");
	tree.insert(40, "cuarenta");
	tree.insert(60, "sesenta");
	tree.insert(80, "ochenta");

	auto show = [](const BST<int, std::string>::node& current) {
		std::cout << current.key << ':' << current.value << ' ';
	};

	std::cout << "In-order: ";
	tree.in_order(show);
	std::cout << "\nPre-order: ";
	tree.pre_order(show);
	std::cout << "\nPost-order: ";
	tree.post_order(show);
	std::cout << "\nPor niveles: ";
	tree.level_order(show);

	std::cout << "\n\nIterador in-order: ";
	for (auto& entry : tree) std::cout << entry.key << ':' << entry.value << ' ';

	if (auto* found = tree.search(40))
		std::cout << "\nSearch 40: " << found->value;
	if (auto* previous = tree.predecessor(50))
		std::cout << "\nPredecessor de 50: " << previous->key;
	if (auto* next = tree.successor(50))
		std::cout << "\nSucesor de 50: " << next->key;

	tree.remove(70);
	std::cout << "\n\nDespues de remove(70): ";
	tree.in_order(show);
	std::cout << '\n';
	return 0;
}
