#include <iostream>
#include <vector>
#include <algorithm>

void resolver(int n){
	std::vector<int> weights(n);
	for (int& weight : weights) {
		std::cin >> weight;
	}

	int totalCases = 1;
	for (int i = 0; i < n; i++) {
		totalCases *= 3;
	}

	int answer = 0;
	for (int weight : weights) {
		answer += weight;
	}

	for (int currentCase = 0; currentCase < totalCases; currentCase++) {
		int load[3] = {0, 0, 0};
		int assignment = currentCase;

		for (int weight : weights) {
			int person = assignment % 3;
			load[person] += weight;
			assignment /= 3;
		}

		int heaviest = std::max(load[0], std::max(load[1], load[2]));
		answer = std::min(answer, heaviest);
	}

	std::cout << answer << "\n";
}

int main(){
	int n;
	std::cin >> n;
	resolver(n);

	return 0;
}
