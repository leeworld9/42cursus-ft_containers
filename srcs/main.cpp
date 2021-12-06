#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "../incs/map.hpp"
	#include "../incs/stack.hpp"
	#include "../incs/vector.hpp"
#endif

#include <stdlib.h>
#include <ctime>
#include <ios>

#define MAX_RAM 4294967296 / 4 // 가상환경에서는 맞춰서 변경 필요
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

void show_time(std::string msg, clock_t start, clock_t finish)
{
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << "[" << msg << duration << "초]" << std::endl;
}

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
	ft::map<int, int> map_int;
	clock_t start, finish;
	std::cout << std::fixed;

	start = clock();
	std::cout <<"=====vector chk start=====" <<std::endl;
	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
		
	}
	ft::vector<Buffer>().swap(vector_buffer);
	
	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	finish = clock();
    show_time("vector time : ", start, finish);

	start = clock();
	std::cout <<"=====map chk start=====" <<std::endl;
	for (int i = 0; i < COUNT; ++i)
	{
		int idx = rand();
		map_int.insert(ft::make_pair(idx, rand()));
		std::cout << "map insert[" << i << "] : " << map_int[idx] << std::endl;
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	finish = clock();
    show_time("map time : ", start, finish);

	start = clock();
	std::cout <<"=====stack chk start=====" <<std::endl;
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	finish = clock();
    show_time("stack time : ", start, finish);
	//std::cout << std::endl;
	return (0);
}
