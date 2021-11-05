/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 01:57:45 by dohelee           #+#    #+#             */
/*   Updated: 2021/10/28 19:52:16 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "./utils/utility.hpp"
# include "./utils/type_traits.hpp"
# include "./utils/iterator.hpp"
//# include "./utils/binary_search_tree.hpp"

namespace ft
{
	template < class Key,											// map::key_type
			class T,												// map::mapped_type
			class Compare = std::less<Key>,							// map::key_compare
			class Alloc = std::allocator<ft::pair<const Key, T> >	// map::allocator_type
			>
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Alloc>;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef	typename ft::binary_search_tree<value_type>::iterator	iterator;
			typedef	typename ft::binary_search_tree<value_type>::const_iterator	const_iterator;
			typedef	typename ft::reverse_iterator<iterator>	reverse_iterator;
			typedef	typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t size_type;

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:
				alloc(alloc),
				comp(comp),
				bst()
			{}

			template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			:	
				alloc(alloc),
				comp(comp),
				bst()
			{
				//first ~ last;
			}
			
			map(const map& x)
			:
				alloc(x.alloc),
				comp(x.comp),
				bst()
			{
				*this = x;
			}

			virtual ~map()
			{
				//아직 미구현
			}

			map& operator= (const map& x)
			{
				if (this != &x)
				{
					this->alloc = x.alloc;
					this->comp = x.comp;
					this->bst = x.bst;
				}
				return (*this);
			}

			// Iterators
			iterator begin()
			{
				return (bst.min_node());
			}

			const_iterator begin() const
			{
				return (bst.min_node());
			}

			iterator end()
			{
				return (bst.end_node);
			}  

			const_iterator end() const
			{
				return (bst.end_node);
			}

			// 아래 reverse_iterator 는 확인 필요
			reverse_iterator rbegin() 
			{ 
				return reverse_iterator(this->end());
			}

			const_reverse_iterator rbegin() const 
			{ 
				return const_reverse_iterator(this->end());
			}

			reverse_iterator rend() {
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(this->begin());
			}

			// Capacity



			// Element access
			mapped_type& operator[] (const key_type& k)
			{
				(*((this->insert(make_pair(k,mapped_type()))).first)).second;
			}

			// Modifiers
			//single element (1)	
			pair<iterator,bool> insert (const value_type& val)
			{
				/* 
				아 왜 pair<iterator,bool> 이런형태로 리턴하는거야... 다시해야하는거 아닌가;;
				bool은 어디서 쓰이는거고.....
				*/
			}

			//with hint (2)	
			//iterator insert (iterator position, const value_type& val);

			//range (3)	
			//template <class InputIterator>
			//void insert (InputIterator first, InputIterator last);

		private:
			allocator_type                          alloc;
			Compare                                 comp;
			ft::binary_search_tree<value_type, Compare>  bst;
	};
};

#endif
