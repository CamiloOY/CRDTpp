#pragma once

#include "GSet.h"

template<typename T>
class TwoPhaseSet {
public:
	void add(T elem) {
		add_set.add(elem);
	};
	void remove(T elem) {
		if(add_set.value().count(elem)) {
			remove_set.add(elem);
		}
	};
	std::unordered_set<T> value() const {
		const std::unordered_set<T>& a = add_set.value();
		const std::unordered_set<T>& r = remove_set.value();
		std::unordered_set<T> result;
		std::copy_if(a.begin(), a.end(), std::inserter(result, result.begin()), [&result, &r](T item) {
			return r.find(item) == r.end();
		});
		return result;
	};
	void merge(const TwoPhaseSet& other) {
		add_set.merge(other.add_set);
		remove_set.merge(other.remove_set);
	};

private:
	GSet<T> add_set;
	GSet<T> remove_set;
};