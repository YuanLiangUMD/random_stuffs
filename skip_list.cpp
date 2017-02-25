#include "./skip_list.hpp"
template<typename T>
skip_list<T>::skip_list(){
	max_height = 1;
	this->head.push_back(nullptr);
}
template<typename T>
skip_list<T>::~skip_list(){
	if (head.empty())
		return ;

	auto i = head[0];
	while( i != nullptr and i->get_next(0) != nullptr){
		auto t = i;
		i = i->get_next(0);
		delete t;
	}
	delete i;
}

template<typename T>
void skip_list<T>::print(){
	//for debugging
	uintmax_t m_h = 0;
	auto i = this->head[0];
	while (i != nullptr ){
		if (i->get_height() > m_h) m_h = i->get_height();
		i = i->get_next(0);
	}
	for (auto i = m_h; i < max_height; ++i){
		if (this->head[i] == nullptr)
			std::cout<<"\n head ["<<i<<"] is null\n";
		else std::cout<<"\n head ["<<i<<"] is not null\n";

	}
}
template<typename T>
std::vector<node<T>*> skip_list<T>::find(const T& data){
	//!search for position for data
	//!points to elements before the data position
	std::unique_lock<std::mutex> lk(m);
	auto tmp_head = this->head;

	lk.unlock();

	auto i = max_height - 1; 
	while(1){	
		while( tmp_head [i] != nullptr
				and tmp_head[i]->get_next(i) != nullptr
				and data > tmp_head[i]->get_next(i)->get_data() ){
			tmp_head[i] = tmp_head[i]->get_next(i);
		}
		if ( i == 0)
			break;
		--i;
	}

	return std::move(tmp_head);
}
template<typename T>
bool contain(const T& data){
	auto t = find(data)[0];
	if (t->get_data() == data or
			t->get_next(0)->get_data() == data)
		return true;

	return false;
}
template<typename T>
bool skip_list<T>::remove(const T& data){
	//not finish 
	//problem in find func
	//
	if (head[0] == nullptr) return false;
	auto ptrs = find(data);

	std::lock_guard<std::mutex> lk(m);
	if (ptrs[0] == head[0]){
		auto t = ptrs[0];
		if (ptrs[0]->get_data() == data){
			for (auto i = 0; i < t->get_height(); i++)
				head[i] = head[i]->get_next(i);
		}else{
			t = ptrs[0]->get_next(0);
			for (auto i = 0; i < t->get_height(); i++){
				if (ptrs[i]->get_data() == data){
					head[i] = head[i]->get_next(i);
				}else{
					head[i]->connect(head[i]->get_next(i)->get_next(i),i);

				}
			}
		}

		delete t;
		return true;
	}
	auto t = ptrs[0]->get_next(0);
	auto h = t->get_height();
	for (auto i = 0; i < h; i++){
		if (ptrs[i] == t){
			head[i] = head[i]->get_next(i);
		}else{
			ptrs[i]->connect(ptrs[i]->get_next(i)->get_next(i),i); 
		}
	}	
	delete t;
	return true;
}

template<typename T>
void skip_list<T>::add(const T& data){
	uintmax_t height = 1;
	auto ptrs = find(data);

	std::lock_guard<std::mutex> lk(m);
	while (distribution(generator) == 1){
		height++;
	}
	auto p = new node<T>(data,height);

	if (head[0] == nullptr){
		for (auto& i:head)
			i = p;
		if (p->get_height() > max_height){//can be get rid of
			for (auto i = max_height; i < p->get_height(); ++i){
				head.push_back(p);
			}
			max_height = p->get_height();
		}
		return ;
	}//when head is empty

	if (p->get_height() > max_height){
		for (auto i = max_height; i < p->get_height(); ++i){
			head.push_back(p);
		}
		for (auto i = 0; i < max_height ; i++){
			if (p->get_data() >  ptrs[i]->get_data()){
				p->connect(ptrs[i]->get_next(i),i);
				ptrs[i]->connect(p,i);
			}else{
				p->connect(ptrs[i],i);
				head[i] = p;
			}
		}
		max_height = p->get_height();
		return ;
	}


	for (auto i = 0; i < p->get_height() ; i++){
		if (p->get_data() > ptrs[i]->get_data() ){
			p->connect(ptrs[i]->get_next(i),i);
			ptrs[i]->connect(p,i);
		}else{
			p->connect(ptrs[i],i);
			head[i] = p;
		}
	}
	return ;
}

template<typename T>
node<T>::node(const T& data,uintmax_t height){

	this->data = data;
	this->height = height;

	this->next.reserve(this->height);

	for (auto i = 0; i < this->height; ++i){
		next.push_back(nullptr);
	}
}

template<typename T>
void node<T>::connect(node<T>* n,uintmax_t height){
	next[height] = n;
}

template<typename T>
uintmax_t node<T>::get_height(){
	return this->height;
}

template<typename T>
T& node<T>::get_data(){ 
	return data;
}

template<typename T>
node<T>* node<T>::get_next(uintmax_t height){
	return next[height];
}
