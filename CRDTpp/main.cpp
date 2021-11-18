#include <iostream>
#include "IntVector.h"
#include "GCounter.h"
#include "PNCounter.h"
#include "GSet.h"
#include "TwoPhaseSet.h"
#include "LWWSet.h"
#include "ORSet.h"
#include "RGA.h"

using namespace std;

int main() {
	// IntVector testing
	/*IntVector<5> vec1;
	IntVector<5> vec2;
	IntVector<3> vec3;
	
	vec1.inc(0);
	vec1.inc(1);
	vec1.inc(2);
	vec1.inc(3);
	vec1.inc(4);
	vec1.inc(5);
	vec2.inc(0);
	vec2.inc(2);
	vec2.inc(2);

	vec1.merge(vec2);
	for(unsigned int i = 0; i < 5; i++) {
		std::cout << vec1.value()[i] << ", ";
	}
	std::cout << "\n";
	//vec1.merge(vec3); // Doesn't compile :)*/

	// GCounter testing
	/*GCounter<3> counter;
	counter.inc(0);
	counter.inc(1);
	counter.inc(2);
	std::cout << counter.value() << '\n';
	GCounter<3> counter2;
	counter2.merge(counter);
	counter2.inc(2);
	counter2.inc(2);
	counter2.inc(2);
	counter2.inc(2);
	counter.merge(counter2);
	std::cout << counter.value() << '\n';*/

	// PNCounter testing
	/*PNCounter<2> counter;
	counter.inc(0);
	counter.inc(0);
	counter.inc(0);
	counter.inc(1);
	counter.inc(1);
	counter.dec(0);
	counter.dec(1);
	std::cout << counter.value() << '\n';
	PNCounter<2> counter2;
	counter2.merge(counter);
	counter2.inc(1);
	counter2.inc(1);
	counter2.inc(1);
	counter.merge(counter2);
	std::cout << counter.value() << '\n';*/

	// GSet testing
	/*GSet<int> a;
	a.add(1);
	a.add(2);
	a.add(3);
	GSet<int> b;
	b.add(3);
	b.add(4);
	a.merge(b);
	std::cout << '{';
	for(int x : a.value()) {
		std::cout << x << ',';
	}
	std::cout << "}\n";

	b.add(6);
	b.merge(a);
	std::cout << '{';
	for(int x : b.value()) {
		std::cout << x << ',';
	}
	std::cout << "}\n";

	b.merge(b); // Test idempotence
	std::cout << '{';
	for(int x : b.value()) {
		std::cout << x << ',';
	}
	std::cout << "}\n";*/

	// 2PSet testing
	/*TwoPhaseSet<int> a;
	a.add(1);
	a.add(2);
	a.add(3);
	for(int x : a.value()) {
		std::cout << x << ',';
	}
	std::cout << '\n';

	a.remove(1); // Test remove
	for(int x : a.value()) {
		std::cout << x << ',';
	}
	std::cout << '\n';

	TwoPhaseSet<int> b;
	b.add(5);
	b.add(6);
	b.add(7);
	a.merge(b);
	for(int x : a.value()) {
		std::cout << x << ',';
	}
	std::cout << '\n';

	b.add(1);
	b.merge(a);
	for(int x : b.value()) { // 1 isn't in the output since it has been removed from set A
		std::cout << x << ',';
	}
	std::cout << '\n';

	b.add(4);
	a.remove(4);
	a.merge(b);
	for(int x : a.value()) { // 4 is in the output, even though we tried to remove it from A. This is because removes only apply if the element has already been added
		std::cout << x << ',';
	}
	std::cout << '\n';*/

	// LWWSet testing
	/*LWWSet<int> a;
	int a_timestamp = 0;
	a.add(1, a_timestamp++);
	a.add(2, a_timestamp++);
	a.add(3, a_timestamp++);
	a.remove(3, a_timestamp++);
	for(const auto& x : a.value()) {
		std::cout << x << ',';
	}
	std::cout << '\n';

	LWWSet<int> b;
	int b_timestamp = 0;
	b.remove(2, b_timestamp++); // This remove doesn't work since the remove happened before the add (at A)
	b.add(6, b_timestamp++);
	b.add(7, b_timestamp++);
	b.remove(1, b_timestamp++);
	b.add(3, b_timestamp++); // Since this add happens after 3 was removed from A, 3 appears in the merged output
	a.merge(b);
	for(const auto& x : a.value()) {
		std::cout << x << ',';
	}
	std::cout << '\n';*/

	// ORSet testing
	/*ORSet<int> a;
	auto a_add_1 = a.add(3);
	auto a_add_2 = a.add(5);
	auto a_add_3 = a.add(7);
	auto a_remove_1 = a.remove(5);
	for(int x : a.value()) {
		cout << x << ", ";
	}
	cout << '\n';
	ORSet<int> b;
	b.mergeAdd(a_add_1);
	b.mergeAdd(a_add_2);
	b.mergeAdd(a_add_3);
	b.mergeRemove(a_remove_1);
	for(int x : b.value()) {
		cout << x << ", ";
	}
	cout << '\n';
	auto b_remove_1 = b.remove(7);
	for(int x : b.value()) {
		cout << x << ", ";
	}
	cout << '\n';
	a.mergeRemove(b_remove_1);
	for(int x : a.value()) {
		cout << x << ", ";
	}
	cout << '\n';

	auto a_add_4 = a.add(6);
	b.mergeAdd(a_add_4);
	auto a_add_5 = a.add(6);
	auto b_remove_2 = b.remove(6);
	b.mergeAdd(a_add_5);
	a.mergeRemove(b_remove_2);
	for(int x : b.value()) { // Add wins in the case of concurrent adds and removes
		cout << x << ", ";
	}
	cout << '\n';
	a.mergeRemove(b_remove_1);
	for(int x : a.value()) {
		cout << x << ", ";
	}
	cout << '\n';

	auto a_add_6 = a.add(12);
	auto a_add_7 = a.add(12);
	for(int x : a.value()) { // Can add an element twice but it only appears in output once
		cout << x << ", ";
	}
	cout << '\n';
	auto a_remove_2 = a.remove(12); // Remove only needs to be called once
	for(int x : a.value()) {
		cout << x << ", ";
	}
	cout << '\n';*/

	// RGA testing
	RGA a(1);
	RGA b(2);
	auto a_add_1 = a.addRight({-1, {2147483647, 2147483647}}, 'C');
	b.mergeAddRight(a_add_1);
	auto b_add_1 = b.addRight(a_add_1.second, 'r');
	auto a_add_2 = a.addRight(a_add_1.second, 'a');
	auto a_add_3 = a.addRight(a_add_2.second, 'm');
	a.mergeAddRight(b_add_1);
	b.mergeAddRight(a_add_2);
	b.mergeAddRight(a_add_3);
	std::cout << a.value() << '\n';
	std::cout << b.value() << '\n';
	std::cout << '\n';
	auto b_remove_1 = b.remove(a_add_3.second);
	auto b_add_2 = b.addRight(b_add_1.second, 'b');
	a.mergeRemove(b_remove_1);
	a.mergeAddRight(b_add_2);
	std::cout << a.value() << '\n';
	std::cout << b.value() << '\n';
	std::cout << '\n';
	auto a_remove_1 = a.remove(b_add_2.second);
	auto a_add_4 = a.addRight(b_add_1.second, 't');
	auto b_add_3 = b.addRight(b_add_2.second, 'e');
	b.mergeRemove(a_remove_1);
	b.mergeAddRight(a_add_4);
	a.mergeAddRight(b_add_3);
	std::cout << a.value() << '\n';
	std::cout << b.value() << '\n';
	std::cout << '\n';
	auto a_remove_2 = a.remove(a_add_1.second);
	auto b_remove_2 = b.remove(a_add_1.second);
	b.mergeRemove(a_remove_2);
	a.mergeRemove(b_remove_2);
	std::cout << a.value() << '\n';
	std::cout << b.value() << '\n';
	std::cout << '\n';
	return 0;
}