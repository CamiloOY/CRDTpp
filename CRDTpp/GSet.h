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
	bool operator<=(const GSet& other) const {
		for(const auto& el : payload) {
			if(!other.value().count(el)) {
				return false;
			}
		}
		return true;
	};

private:
	std::unordered_set<T> payload;
};