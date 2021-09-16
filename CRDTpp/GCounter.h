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
		payload.merge(other.getPayload());
	};
	const IntVector<size>& getPayload() const {
		return payload;
	}

private:
	IntVector<size> payload;
};