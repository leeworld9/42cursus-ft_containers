/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 01:57:45 by dohelee           #+#    #+#             */
/*   Updated: 2021/12/06 19:39:07 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <limits>
# include "./utils/utility.hpp"
# include "./utils/type_traits.hpp"
# include "./utils/iterator.hpp"
# include "./utils/avl_tree.hpp"
# include "./utils/algorithm.hpp"
# include "./utils/Node.hpp"

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
			typedef	typename ft::avl_tree<value_type, allocator_type, key_compare>::iterator	iterator;
			typedef	typename ft::avl_tree<value_type, allocator_type, key_compare>::const_iterator	const_iterator;
			typedef	typename ft::reverse_iterator<iterator>	reverse_iterator;
			typedef	typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t size_type;

            // (1) empty constructor (default constructor)
			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:
				alloc(alloc),
				comp(comp),
				avl_tree(),
                root()
			{}
            
            // (2) range constructor
			template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			:	
				alloc(alloc),
				comp(comp),
                avl_tree(),
                root()
			{
                this->insert(first, last);
			}
			
            // (3) copy constructor
			map(const map& x)
			{
				*this = x;
			}

			~map()
			{
				this->clear();
			}

			map& operator= (const map& x)
			{
				if (this != &x)
				{
					this->alloc = allocator_type();
					this->comp = Compare();
                    this->avl_tree = ft::avl_tree<value_type, allocator_type, key_compare>();
                    this->root = NULL;
                    this->insert(x.begin(), x.end());
                }
				return (*this);
			}

			// Iterators
			iterator begin()
			{
                if (root == NULL)
                    return iterator(avl_tree.super_root);
                else
				    return iterator(avl_tree.min_node(root));
			}

			const_iterator begin() const
			{
				if (root == NULL)
                    return const_iterator(avl_tree.super_root);
                else
				    return const_iterator(avl_tree.min_node(root));
			}

			iterator end()
			{
				return iterator(avl_tree.super_root);
			}  

			const_iterator end() const
			{
				return const_iterator(avl_tree.super_root);
			}

			// 아래 reverse_iterator들은 확인 필요
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
            bool empty() const
            {
                if (root == NULL)
                    return (true);
                else
                    return (false);
            }

            size_type size() const
            {
                //this->avl_tree.display(root, root, 1);
                //std::cout << std::endl;

                int cnt = 0;
                const_iterator it = this->begin();

                while (it != this->end())
                {
                    //std::cout << "test : " << (*it).first << std::endl;
                    cnt++;
                    it++;
                }
                return (cnt);
            }

            size_type max_size() const
            {
                return (this->avl_tree.alloc.max_size());
                //위와 동일한 값
                //return (std::numeric_limits<size_type>::max() / sizeof(ft::Node<value_type>));
            }

			//Element access
			mapped_type& operator[] (const key_type& k)
			{
				return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
			}

			// Modifiers
			// (1) insert : single element	
			pair<iterator, bool> insert (const value_type& val)
			{
                //this->avl_tree.display(root, root, 1);
                //std::cout << std::endl;
                
                iterator find = this->find(val.first);

                if (find != this->end())
                    return (ft::make_pair(find, false));
                else
                {
                    root = avl_tree.insert(this->root, val);
                    find = this->find(val.first);
				    return (ft::make_pair(find, true));
                }
			}

			// (2) insert : with hint 
			iterator insert (iterator position, const value_type& val)
            {
                iterator it = position;
                while (it != this->end())
                {
                    if ((*it).first == val.first)
                        return (it);
                    it++;
                }
                root = avl_tree.insert(root, val);
                return (this->find(val.first));
            }

			// (3) insert : range	
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
            {
                InputIterator it = first;
                while (it != last)
                {
                    root = avl_tree.insert(root, *it);
                    it++;
                }
            }

            // (1)	erase
            void erase (iterator position)
            {
                root = avl_tree.remove(root, (*position).first);
            }

            // (2)	erase
            size_type erase (const key_type& k)
            {
                iterator it = this->find(k);
                if (it != this->end())
                {
                    root = avl_tree.remove(root, k);
                    return (1);
                }
                else
                    return (0);
            }

            // (3)	erase
            void erase (iterator first, iterator last)
            {
                iterator it = first;
                // avl_tree.display(root, root, 1);
                // std::cout << "\n--------target: " << (*it).first << "-------------" << std::endl;
                while (it != last)
                {
                    root = avl_tree.remove(root, (*it++).first);
                    //it++ // 이렇게 하면 leak이 난다. 제거된 it에서 ++을 시도해서??
                }
            }
            
            void swap (map& x)
            {
                ft::avl_tree<value_type, allocator_type, key_compare>    tmp_avl_tree = this->avl_tree;
                ft::Node<value_type>       *tmp_root = this->root;

                this->avl_tree = x.avl_tree;
                this->root = x.root;

                x.avl_tree = tmp_avl_tree;
                x.root = tmp_root;
            }

            void clear()
            {
                this->erase(this->begin(), this->end());
            }

            // Observers
            key_compare key_comp() const
            {
                return (this->comp);
            }

            value_compare value_comp() const
            {
                return (map::value_compare(this->comp));
            }

            // Operations
            iterator find (const key_type& k)
            {
                iterator it = this->begin();
               
                if (it == NULL)
                    return this->end();
                else
                {
                    while (it != this->end())
                    {
                        if ((*it).first == k)
                            return (it);
                        it++;
                    }
                    return (it);
                }
               
            }

            const_iterator find (const key_type& k) const
            {
                const_iterator it = this->begin();

                if (it == NULL)
                    return this->end();
                else
                {
                    while (it != this->end())
                    {
                        if ((*it).first == k)
                            return (it);
                        it++;
                    }
                    return (it);
                }
            }

            size_type count (const key_type& k) const
            {
                if (this->find(k) == this->end())
                    return (0);
                else
                    return (1);
            }

            iterator lower_bound (const key_type& k)
            {
                iterator it = this->begin();

                while (it != this->end())
                {
                    if (!this->comp((*it).first, k)) // it.frist <= k
                        return (it);
                    it++;
                }
                return (it);
            }

            const_iterator lower_bound (const key_type& k) const
            {
                const_iterator it = this->begin();

                while (it != this->end())
                {
                    if (!this->comp((*it).first, k))
                        return (it);
                    it++;
                }
                return (it);
            }

            iterator upper_bound (const key_type& k)
            {
                iterator it = this->begin();

                while (it != this->end())
                {
                    if (!this->comp(k, (*it).first))
                        it++;
                    else
                        break ;
                }
                return (it);
            }

            const_iterator upper_bound (const key_type& k) const
            {
                const_iterator it = this->begin();

                while (it != this->end())
                {
                    if (!this->comp(k, (*it).first))
                        it++;
                    else
                        break ;
                }
                return (it);
            }

            pair<const_iterator, const_iterator> equal_range (const key_type& k) const
            {
                return (ft::make_pair(lower_bound(k), upper_bound(k)));
            }

            pair<iterator, iterator>             equal_range (const key_type& k)
            {
                return (ft::make_pair(lower_bound(k), upper_bound(k)));
            }

            // Allocator
            allocator_type get_allocator() const
            {
                return (this->alloc);
            }


		private:
			allocator_type              alloc;
			Compare                     comp;
			ft::avl_tree<value_type, allocator_type, key_compare>    avl_tree; // 템플릿 인자를 위해 선언
            ft::Node<value_type>       *root;
	};

    // Non-member function overloads
	template< class Key, class T, class Compare, class Alloc >
    bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && 
                ft::equal(rhs.begin(), rhs.end(), lhs.begin()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()) || 
                !ft::equal(rhs.begin(), rhs.end(), lhs.begin()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
};

#endif
