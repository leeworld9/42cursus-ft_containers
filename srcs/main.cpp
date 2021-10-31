/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 02:28:47 by dohelee           #+#    #+#             */
/*   Updated: 2021/10/31 08:36:26 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../incs/map.hpp"
#include "../incs/vector.hpp"
#include "../incs/iterator.hpp"
#include <vector>
#include <map>
#include <stack>
#include <iterator>
#include <typeinfo> 
#include <iostream>
#include "../incs/etc/binary_search_tree.hpp"
#include "../incs/utility.hpp"

int main()
{
	// STL과 속도 비교하는 테스트 케이스 필요

	ft::binary_search_tree<ft::pair<std::string, int> > bst;

	bst.insertPair(ft::make_pair("a", 0));
	bst.insertPair(ft::make_pair("d", 1));
	bst.insertPair(ft::make_pair("c", 2));
	bst.insertPair(ft::make_pair("g", 3));
	bst.insertPair(ft::make_pair("e", 4));
	bst.insertPair(ft::make_pair("f", 5));
	bst.insertPair(ft::make_pair("b", 6));
	bst.insertPair(ft::make_pair("h", 7));

	ft::binary_search_tree<ft::pair<std::string, int> >::iterator it(bst.root_node);

	//이터레이터의 문제가 있음 (++ , -- 다시 확인)

	//begin , end 포함해서 9일텐데... 음...
	for (int i = 0; i < 9 ; i++)
	{
		std::cout << it.node->value.first << ", " << it.node->value.second << std::endl;
		it++;
	}
	std::cout << "---------------" << std::endl;
	for (int i = 0; i < 9 ; i++)
	{
		std::cout << it.node->value.first << ", " << it.node->value.second << std::endl;
		it--;
	}

	std::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['c'] = 300;
	mymap['a'] = 200;


	std::cout << "---------------" << std::endl;
	
	// show content:
	std::map<char,int>::iterator mit = mymap.begin();
	mit--;
	std::cout << mit->first << " => " << mit->second << '\n';
	mit++;
	std::cout << mit->first << " => " << mit->second << '\n';
	mit++;
	std::cout << mit->first << " => " << mit->second << '\n';
	mit++;
	std::cout << mit->first << " => " << mit->second << '\n';
	mit++;
	std::cout << mit->first << " => " << mit->second << '\n';
	mit++;
	std::cout << mit->first << " => " << mit->second << '\n';
	mit++;
	std::cout << mit->first << " => " << mit->second << '\n';
	mit++;
	std::cout << mit->first << " => " << mit->second << '\n';

	return 0;

}