#include <iostream>
#include "IntVector.h"
#include "GCounter.h"
#include "PNCounter.h"
#include "GSet.h"
#include "TwoPhaseSet.h"

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
	TwoPhaseSet<int> a;
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
	for(int x : a.value()) { // 4 is in the output, even though we tried to remove it from A. This is because removes only work if the element has already been added
		std::cout << x << ',';
	}
	std::cout << '\n';
	return 0;
}