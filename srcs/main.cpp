/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 02:28:47 by dohelee           #+#    #+#             */
/*   Updated: 2021/10/24 02:17:14 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/vector.hpp"
#include "../incs/iterator.hpp"
#include <vector>
#include <map>
#include <stack>
#include <iterator>
#include <typeinfo>     // typeid
#include <iostream>     // std::cout

int main()
{
	int myarray [] = { 501,502,503 };

	std::vector<int> first;
	std::vector<int> second (4, 75);
	std::vector<int> third (second.begin(),second.end());
	std::vector<int> fourth (third);

	//third.reserve(10);
	std::vector<int>::iterator its = third.begin();
	its++;
	its++;
	std::cout << third.capacity() << std::endl;
	third.insert(its, myarray, myarray+3);

	std::cout <<  third.capacity() << std::endl;

	its = third.begin();
	third.assign(5, 10);

	for (std::vector<int>::iterator i = third.begin(); i < third.end() ; i++)
	{
		std::cout << *i << std::endl;
		std::cout << &i << std::endl;
	}

	std::cout << "-------------------" << std::endl;

	ft::vector<int> ft_first;
	ft::vector<int> ft_second (4, 75);
	ft::vector<int> ft_third (ft_second.begin(), ft_second.end());
	ft::vector<int> ft_fourth (ft_third);

	//ft_third.reserve(10);
	ft::vector<int>::iterator ft_its = ft_third.begin();
	ft_its++;
	ft_its++;
	std::cout << ft_third.capacity() << std::endl;
	ft_third.insert(ft_its, myarray, myarray+3);
	std::cout <<  ft_third.capacity() << std::endl;

	ft_its = ft_third.begin();
	ft_third.assign(5, 10);
	
	for (ft::vector<int>::iterator i = ft_third.begin() ; i < ft_third.end() ; i++)
	{
		std::cout << *i << std::endl;
		std::cout << &i << std::endl;
	}

	return 0;

}