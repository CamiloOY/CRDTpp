#include <iostream>
#include "IntVector.h"
#include "GCounter.h"
#include "PNCounter.h"

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
	PNCounter<2> counter;
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
	std::cout << counter.value() << '\n';
	return 0;
}