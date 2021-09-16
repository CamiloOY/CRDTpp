#pragma once

#include <vector>
#include <algorithm>

template<int size>
class IntVector {
public:
	IntVector() {
		payload.resize(size);
		std::fill(payload.begin(), payload.end(), 0);
	};
	const std::vector<int>& value() const {
		return payload;
	};
	void inc(int index) {
		if(index < size) {
			payload[index]++;
		}
	};
	void merge(const IntVector& other) {
		std::vector<int> vec(other.value());
		for(unsigned int c = 0; c < size; c++) {
			payload[c] = std::max(payload[c], vec[c]);
		}
	};

private:
	std::vector<int> payload;
};