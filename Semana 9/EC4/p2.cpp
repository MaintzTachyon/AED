#include <iostream>
#include <algorithm>
#include <vector>

void resolver(int n){
    std::vector<int> numbers(n);
    for (int& number : numbers) {
        std::cin >> number;
    }

    std::vector<int> values = numbers;
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());

    std::vector<bool> exist(values.size(), false);

    int blocks = 0;

    for (int position = 0; position < n; position++){
        int number = numbers[position];
        int index = std::lower_bound(values.begin(), values.end(), number) - values.begin();

        if (!exist[index]) {
            bool hasPrevious = index > 0 && values[index - 1] == number - 1 && exist[index - 1];
            bool hasNext = index + 1 < static_cast<int>(values.size()) && values[index + 1] == number + 1 && exist[index + 1];

            blocks += !hasPrevious && !hasNext;
            blocks -= hasPrevious && hasNext;

            exist[index] = true;
        }

        std::cout << blocks;
        if (position < n - 1) std::cout << " ";
    }
    std::cout << "\n";
}

int main(){
    int n;
    std::cin >> n;
    resolver(n);

    return 0;
}