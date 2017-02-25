#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP
#include <iostream>
#include<thread>
#include<memory>
#include<mutex>
#include<exception>
#include<vector>
#include<random>
template<typename T>
class node{
	public:
		node(const T& data,uintmax_t height);
		void connect(node<T>* n,uintmax_t height);
		uintmax_t get_height();
		T& get_data();
		node<T>* get_next(uintmax_t height);
	
	private:
		std::vector<node<T>* > next;
		T data;
		uintmax_t height;
};
template<typename T>
class skip_list{
	public:
		skip_list();
		~skip_list();

		void print();

		bool contain(const T& data);

		bool remove(const T& data);

		void add(const T& data);
	private:
		std::vector<node<T>*> find(const T& data);
		std::mutex m;
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution{0,1};
		uintmax_t max_height;
		std::vector<node<T>*> head;
};
#include "./skip_list.cpp"
#endif
