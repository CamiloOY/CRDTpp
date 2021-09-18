#pragma once

#include <unordered_set>
#include <algorithm>

template<typename T>
class GSet {
public:
	const std::unordered_set<T>& value() const {
		return payload;
	};
	void add(T elem) {
		payload.insert(elem);
	};
	void merge(const GSet& other) {
		for(const auto& el : other.value()) {
			payload.insert(el);
		}
	};

private:
	std::unordered_set<T> payload;
};