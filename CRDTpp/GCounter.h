#pragma once

#include "IntVector.h"
#include <numeric>

template<int size>
class GCounter {
public:
	void inc(int index) {
		payload.inc(index);
	};
	int value() const {
		return std::accumulate(payload.value().begin(), payload.value().end(), 0);
	};
	void merge(const GCounter& other) {
		payload.merge(other.payload);
	};
	bool operator<=(const GCounter& other) const {
		return payload <= other.payload;
	};

private:
	IntVector<size> payload;
};