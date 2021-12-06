/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_performance.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:49:03 by dohelee           #+#    #+#             */
/*   Updated: 2021/12/06 15:49:36 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <iterator>
#include <typeinfo> 
#include <iostream>
#include <utility>
#include <ctime>
#include <ios>

#include "../incs/utils/avl_tree.hpp"
#include "../incs/utils/algorithm.hpp"
#include "../incs/utils/utility.hpp"
#include "../incs/utils/type_traits.hpp"
#include "../incs/utils/iterator.hpp"
#include "../incs/map.hpp"

void show_time(std::string msg, clock_t start, clock_t finish)
{
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << "[" << msg << duration << "초]" << std::endl;
}

int main()
{
    clock_t start, finish;
 
    ft::map<char,int> ft_mymap;
    ft::map<char,int>::iterator ft_it;

    ft::map<char,int> mymap;
    ft::map<char,int>::iterator it;

    std::cout << std::fixed;
    std::cout << "==============================" << std::endl;

    // std -> insert
    start = clock();
    mymap['d']=40;
    mymap['b']=20;
    mymap['a']=10;
    mymap['z']=100;
    mymap['c']=30;
    mymap['j']=80;
    mymap['e']=50;
    mymap['f']=60;
    finish = clock();
    show_time("insert(std) time : ", start, finish);
    
    // ft -> insert
    start = clock();
    ft_mymap['d']=40;
    ft_mymap['b']=20;
    ft_mymap['a']=10;
    ft_mymap['z']=100;
    ft_mymap['c']=30;
    ft_mymap['j']=80;
    ft_mymap['e']=50;
    ft_mymap['f']=60;
    finish = clock();
    show_time("insert( ft) time : ", start, finish);

    std::cout << "==============================" << std::endl;

    // std -> find && erase
    start = clock();
    it = mymap.find('b');
    mymap.erase (it); 
    mymap.erase ('c'); 
    it = mymap.find ('z');
    mymap.erase (it , mymap.end() ); 
    finish = clock();
    show_time("find && erase(std) time : ", start, finish);

    // ft -> find && erase
    start = clock();
    ft_it = ft_mymap.find('b');
    ft_mymap.erase (ft_it); 
    ft_mymap.erase ('c'); 
    ft_it = ft_mymap.find ('z');
    ft_mymap.erase (ft_it , ft_mymap.end()); 
    finish = clock();
    show_time("find && erase( ft) time : ",start, finish);

    std::cout << "==============================" << std::endl;

    // std -> search 
    start = clock();
    for (it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
    finish = clock();
    show_time("search(std) time : ",start, finish);

    // ft -> show
    start = clock();
    for (ft_it = ft_mymap.begin(); ft_it != ft_mymap.end(); ++ft_it)
        std::cout << ft_it->first << " => " << ft_it->second << '\n';
    finish = clock();
    show_time("search( ft) time : ", start, finish);

    std::cout << "==============================" << std::endl;

    return 0;
}