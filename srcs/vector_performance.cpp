/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_performance.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:49:40 by dohelee           #+#    #+#             */
/*   Updated: 2021/12/06 15:49:54 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iterator>
#include <typeinfo> 
#include <iostream>
#include <utility>
#include <ctime>
#include <ios>

#include "../incs/vector.hpp"
#include "../incs/utils/algorithm.hpp"
#include "../incs/utils/utility.hpp"
#include "../incs/utils/type_traits.hpp"
#include "../incs/utils/iterator.hpp"

void show_time(std::string msg, clock_t start, clock_t finish)
{
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout << "[" << msg << duration << "초]" << std::endl;
}

int main()
{
    clock_t start, finish;

    std::cout << std::fixed;
    std::cout << "==============================" << std::endl;

    // std
    start = clock();
    std::vector<int> myvector (3,100);
    std::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert ( it , 200 );
    
    myvector.insert (it,2,300);
    it = myvector.begin();

    std::vector<int> anothervector (2,400);
    myvector.insert (it+2,anothervector.begin(),anothervector.end());

    int myarray [] = { 501,502,503 };
    myvector.insert (myvector.begin(), myarray, myarray+3);

    myvector.erase (myvector.begin()+5);
    myvector.erase (myvector.begin(),myvector.begin()+3);

    std::cout << "size : " << myvector.size() << " capacity : " << myvector.capacity() << std::endl;

    std::vector<int> cp_myvector = myvector;
    std::vector<int>::iterator cp_it;

    std::cout << "cp_myvector contains\t:";
    for (cp_it=cp_myvector.begin(); cp_it<cp_myvector.end(); cp_it++)
        std::cout << ' ' << *cp_it;
    std::cout << '\n';

    finish = clock();
    show_time("std time : ", start, finish);
    
    // ft 
    start = clock();

    ft::vector<int> ft_myvector (3,100);
    ft::vector<int>::iterator ft_it;

    ft_it = ft_myvector.begin();
    ft_it = ft_myvector.insert ( ft_it , 200 );

    ft_myvector.insert (ft_it,2,300);
    ft_it = ft_myvector.begin();
  
    ft::vector<int> ft_anothervector (2,400);
    ft_myvector.insert (ft_it+2,ft_anothervector.begin(),ft_anothervector.end());

    int ft_myarray [] = { 501,502,503 };
    ft_myvector.insert (ft_myvector.begin(), ft_myarray, ft_myarray+3);

    ft_myvector.erase (ft_myvector.begin()+5);
    ft_myvector.erase (ft_myvector.begin(),ft_myvector.begin()+3);

    std::cout << "size : " << ft_myvector.size() << " capacity : " << ft_myvector.capacity() << std::endl;

    std::vector<int> cp_ft_myvector = myvector;
    std::vector<int>::iterator cp_ft_it;

    std::cout << "cp_ft_myvector contains\t:";
    for (cp_ft_it=cp_ft_myvector.begin(); cp_ft_it<cp_ft_myvector.end(); cp_ft_it++)
        std::cout << ' ' << *cp_ft_it;
    std::cout << '\n';
   
    finish = clock();
    show_time("ft  time : ", start, finish);
  
    return 0;
}