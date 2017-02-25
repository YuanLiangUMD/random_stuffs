#include "./skip_list.hpp"

#include <iostream>

int main(){
	skip_list<int> s;
	std::vector<int> v;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,10);
	for (auto k = 0; k < 10001; k++){
		auto i = distribution(generator);
		s.add(i);
		v.push_back(i);
	}


	for (auto i:v){
		s.remove(i);
	}
}
