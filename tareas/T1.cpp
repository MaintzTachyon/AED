#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using Array = std::vector<int>;
using SortFunction = void (*)(Array&);

void bubble_sort(Array& values) {
	for (std::size_t end = values.size(); end > 1; --end) {
		bool changed = false;
		for (std::size_t index = 1; index < end; ++index) {
			if (values[index - 1] > values[index]) {
				std::swap(values[index - 1], values[index]);
				changed = true;
			}
		}
		if (!changed) return;
	}
}

void insertion_sort(Array& values) {
	for (std::size_t index = 1; index < values.size(); ++index) {
		int current = values[index];
		std::size_t position = index;
		while (position > 0 && values[position - 1] > current) {
			values[position] = values[position - 1];
			--position;
		}
		values[position] = current;
	}
}

void merge_ranges(Array& values, Array& buffer,
		std::size_t first, std::size_t middle, std::size_t last) {
	std::size_t left = first;
	std::size_t right = middle;
	std::size_t output = first;

	while (left < middle && right < last) {
		if (values[left] <= values[right]) buffer[output++] = values[left++];
		else buffer[output++] = values[right++];
	}
	while (left < middle) buffer[output++] = values[left++];
	while (right < last) buffer[output++] = values[right++];

	for (std::size_t index = first; index < last; ++index) {
		values[index] = buffer[index];
	}
}

void merge_sort_ranges(Array& values, Array& buffer,
		std::size_t first, std::size_t last) {
	if (last - first < 2) return;

	const std::size_t middle = first + (last - first) / 2;
	merge_sort_ranges(values, buffer, first, middle);
	merge_sort_ranges(values, buffer, middle, last);
	merge_ranges(values, buffer, first, middle, last);
}

void merge_sort(Array& values) {
	Array buffer(values.size());
	merge_sort_ranges(values, buffer, 0, values.size());
}

struct Algorithm {
	const char* name;
	SortFunction function;
	bool quadratic;
};

struct Result {
	double seconds = 0.0;
	bool executed = false;
	bool valid = false;
};

Result run_experiment(const Array& input, const Array& expected,
		const Algorithm& algorithm, std::size_t quadratic_limit) {
	if (algorithm.quadratic && input.size() > quadratic_limit) return {};

	Array values = input;
	const auto start = std::chrono::steady_clock::now();
	algorithm.function(values);
	const auto finish = std::chrono::steady_clock::now();

	const std::chrono::duration<double> elapsed = finish - start;
	return {elapsed.count(), true, values == expected};
}

int main() {
	const std::vector<Algorithm> algorithms = {
		{"Bubble", bubble_sort, true},
		{"Insertion", insertion_sort, true},
		{"Merge", merge_sort, false}
	};

	const std::vector<std::size_t> sizes = {
		10, 100, 1000, 10000, 100000, 1000000, 10000000
	};
	const std::size_t quadratic_limit = 10000;
	std::mt19937 generator(20260926);
	std::uniform_int_distribution<int> distribution(0, 1000000);

	std::cout << "Limite para algoritmos cuadraticos: "
		<< quadratic_limit << " elementos\n\n";
	std::cout << std::left << std::setw(12) << "n";
	for (const Algorithm& algorithm : algorithms) {
		std::cout << std::setw(18) << algorithm.name + std::string(" (s)");
	}
	std::cout << "\n" << std::string(84, '-') << '\n';

	for (std::size_t size : sizes) {
		Array input(size);
		for (int& value : input) value = distribution(generator);

		Array expected = input;
		std::sort(expected.begin(), expected.end());

		std::cout << std::left << std::setw(12) << size;
		for (const Algorithm& algorithm : algorithms) {
			const Result result = run_experiment(
				input, expected, algorithm, quadratic_limit);
			if (!result.executed) {
				std::cout << std::setw(18) << "omitido";
			} else {
				std::cout << std::fixed << std::setprecision(6)
					<< std::setw(18) << result.seconds;
				if (!result.valid) {
					std::cerr << "Error: " << algorithm.name
						<< " no coincide con std::sort para n=" << size << '\n';
					return 1;
				}
			}
		}
		std::cout << '\n';
	}

	std::cout << "\nTodas las salidas ejecutadas fueron validadas contra std::sort.\n";
	return 0;
}
