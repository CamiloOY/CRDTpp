#pragma once

#include "GCounter.h"

template<int size>
class PNCounter {
public:
	void inc(int index) {
		inc_counter.inc(index);
	};
	void dec(int index) {
		dec_counter.inc(index);
	};
	int value() const {
		return inc_counter.value() - dec_counter.value();
	};
	void merge(const PNCounter& other) {
		inc_counter.merge(other.inc_counter);
		dec_counter.merge(other.dec_counter);
	}
	bool operator<=(const PNCounter& other) const {
		return inc_counter <= other.inc_counter && dec_counter <= other.dec_counter;
	};

private:
	GCounter<size> inc_counter;
	GCounter<size> dec_counter;
};