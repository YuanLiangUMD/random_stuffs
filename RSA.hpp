#include <string>
#include <vector>
#include <cstdint>
namespace{
	constexpr  uintmax_t gcd(uintmax_t n,uintmax_t r){
		if (n == 0) return r;
		return gcd(r % n,n);
	}
}
class RSA{
	public:
		//prime number p and q
		constexpr RSA(uintmax_t p,uintmax_t q):n(0),e(0),d(1){
			n = p*q;
			uintmax_t euler_n = (p - 1)*(q - 1);

			for (e = 10; e < euler_n; ++e)
				if (gcd(e,euler_n) == 1) 
					break;

			d = e + 1;
			while(1){	
				if ( (e*d%euler_n) == 1)
					break;
				++d;
			}
		}

		std::string encrypt(const std::string& s) const;
		std::string decrypt(const std::string& s) const;
		uintmax_t encrypt(uintmax_t m) const ;
		uintmax_t decrypt(uintmax_t c) const ;
		static uintmax_t encrypt(uintmax_t m, uintmax_t e, uintmax_t n);
		static uintmax_t decrypt(uintmax_t c, uintmax_t d, uintmax_t n);
		uintmax_t n, e, d;
	private:
		constexpr static uintmax_t pow_mod(uintmax_t b,
				uintmax_t e,uintmax_t m) ;
};
