#include "./RSA.hpp"
#include<iostream>
namespace {
 intmax_t pow(intmax_t b, intmax_t e){
	if (e == 0) return 1;
	else return b*pow(b,e-1);
 }

}
std::string RSA::encrypt(const std::string& s) const{
	std::string rs;
	for (auto c:s){
		auto i = this->encrypt((uintmax_t)c);
		std::string w;
		do{
			auto t = i % 10;
			std::cout<<t;
			w = (char)(t+48) + w;
		}while (i /= 10);
		rs += w + " ";
	}
	return rs;
}
std::string RSA::decrypt(const std::string& s) const{
	std::string num;
	std::vector<std::string> vs;
	for (auto c:s)
		if (c != ' ')
			num += c;
		else{
			vs.push_back(num);
			num = "";
		}

	std::string rs;
	for (auto str:vs){
		uintmax_t t = 0;
		auto i = 0;
		for (auto c = str.rbegin(); c != str.rend(); c++){
			t += pow(10,i)*(uintmax_t)(*c - 48);
			++i;
		}
		rs += this->decrypt(t);
	}
	return rs;
}
uintmax_t RSA::encrypt(uintmax_t m) const {
	return this->encrypt(m,this->e,this->n);
}
uintmax_t RSA::decrypt(uintmax_t c) const {
	return this->decrypt(c,this->d,this->n);
}
uintmax_t RSA::encrypt(uintmax_t m, uintmax_t e, uintmax_t n){
	m = m % n;
	return pow_mod(m,e,n);
}
uintmax_t RSA::decrypt(uintmax_t c, uintmax_t d, uintmax_t n){
	c = c % n;
	return pow_mod(c,d,n);
}

constexpr uintmax_t RSA::pow_mod(uintmax_t b,
		uintmax_t e,uintmax_t m)  {
	if (e == 0) return 1;
	return (b*pow_mod(b,e-1,m) )%m;
}
