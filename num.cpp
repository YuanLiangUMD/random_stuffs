#include<iostream>
#include<vector>
#include<limits>
template <typename T>
constexpr T pow(T b,T e){ if (e == 0) return 1; return b*pow(b,e-1);}
class num{
	public:

		num() = default;

		num(const num& rhs){
			this->n = rhs.n;
		}

		num(num&& rhs){
			this->n = std::move(rhs.n);
		}


		num operator+(num& rhs){
			if(this->n.size() != rhs.n.size()){
				if (this->n.size() > rhs.n.size() ){
					for (auto i = n.size() - rhs.n.size(); i >= 0; --i)
						rhs.n.push_back(0);
				}else{
					for (auto i = rhs.n.size() - n.size(); i >= 0; --i)
						n.push_back(0);
				}
			}

			constexpr auto t = pow<uintmax_t>(10,std::numeric_limits<uintmax_t>().digits10);

			num result;
			uintmax_t carr = 0;

			std::vector<uintmax_t>::size_type i = 0;	

			while (i < this->n.size()){
				result.n[i] = carr;

				if (t < ( result.n[i] += this->n[i] + rhs.n[i]) ){
					carr = 1;
					result.n[i] = result.n[i] - t;
				}else {
					carr = 0;
				}
				++i;
			}

			return std::move(result);
		}

		num operator+(const intmax_t n){

			constexpr auto t = pow<uintmax_t>(10,std::numeric_limits<uintmax_t>().digits10);

			num result;
			uintmax_t carr = 0;

			std::vector<uintmax_t>::size_type i = 0;


			return result;
		}

		num operator*(const intmax_t n){
			num t = 0;
			for (auto i = 0; 
		}
		num& operator=(const intmax_t n){
			this->n.clear();	
			this->n.push_back(n);
			return *this;
		}
		num& operator=(const num& rhs){
			this->n = rhs.n;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os,num& rhs);
	private:
		std::vector<uintmax_t> n;
};
std::ostream& operator<<(std::ostream& os,num& rhs){
	for (auto i:rhs.n)
		os<<i;
	return os;
}

int main(){
	uintmax_t i = -1;
	std::cout<<"limit = "<<std::numeric_limits<uintmax_t>().digits10<<"\n";
	std::cout<<"limit max = "<<i<<"\n";
	num n;
	n = 101;
	std::cout<<"n = "<<n<<"\n";
}
