/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree_iterator.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:46:28 by dohelee           #+#    #+#             */
/*   Updated: 2021/12/06 19:48:03 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_ITERATOR_HPP
# define AVL_TREE_ITERATOR_HPP

# include <iostream>
# include "./utility.hpp"
# include "./iterator.hpp"
# include "./Node.hpp"

namespace ft
{
	template <class V, class N, class Compare>
	class avl_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, N>
	{
		public :
			typedef V    value_type;
            typedef Compare key_compare;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

			avl_tree_iterator(const key_compare& comp = key_compare())
			: node(), comp(comp)
			{}

			avl_tree_iterator(N * node, const key_compare& comp = key_compare())
			: node(node), comp(comp)
			{}

			avl_tree_iterator(const avl_tree_iterator& copy)
			{
				*this = copy;
			}

			virtual ~avl_tree_iterator() { }

			avl_tree_iterator &operator=(const avl_tree_iterator& avl_it)
			{
				if (this != &avl_it)
                {
                    this->node = avl_it.node;
                    this->comp = avl_it.comp;
                }
				return (*this);
			}

			bool operator==(const avl_tree_iterator& avl_it)
			{ return (this->node == avl_it.node); }

			bool operator!=(const avl_tree_iterator& avl_it)
			{ return (this->node != avl_it.node); }

			reference operator*() const
			{ return (this->node->value); }

			pointer operator->() const
			{ return (&this->node->value); }

			avl_tree_iterator& operator++(void)
			{
				N* cursor = node;

				if (cursor->right != NULL)
				{
					cursor = cursor->right;
					while (1)
					{
						if (cursor->left != NULL)
							cursor = cursor->left;
						else
							break;
					}
				}
                else
                {
					while (!comp(node->value.first, cursor->value.first)) // node->value.first >= cursor->value.first
					{
						//spuer_root(end_node)에서 멈춤
						if (cursor->parent == NULL)
						{
							*this = cursor;
							return (*this);
						}
						cursor = cursor->parent;
					}
				}
				*this = cursor;
				return (*this);
			}

			avl_tree_iterator operator++(int)
			{
				avl_tree_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			avl_tree_iterator& operator--(void)
			{
				N* cursor = node;
                
                if (cursor->left != NULL)
				{
					cursor = cursor->left;
                    while (1)
					{
						if (cursor->right != NULL)
							cursor = cursor->right;
						else
							break;
					}
				}
                else
				{
					cursor = cursor->parent;
					while (comp(node->value.first, cursor->value.first)) // node->value.first < cursor->value.first
					{
						cursor = cursor->parent;
					}
				}
				*this = cursor;
				return (*this);
			}

			avl_tree_iterator operator--(int)
			{
				avl_tree_iterator tmp(*this);
				operator--();
				return (tmp);
			}

			N*			node; // current node
            key_compare comp;
	};

	template <class V, class N, class Compare>
	class avl_tree_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, N>
    {
		public :
            typedef V   value_type;
            typedef Compare key_compare;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;
            typedef avl_tree_iterator<typename N::value_type, N, Compare> non_const_iterator;

			avl_tree_const_iterator(const key_compare& comp = key_compare())
			: node(), comp(comp)
			{}

			avl_tree_const_iterator(N* node, const key_compare& comp = key_compare())
			: node(node), comp(comp)
			{}

			avl_tree_const_iterator(const avl_tree_const_iterator& copy)
            : node(copy.node), comp(copy.comp)
		    {}

            //non_const_iterator -> avl_tree_const_iterator
            avl_tree_const_iterator(non_const_iterator it)
            : node(it.node), comp(it.comp) 
            {}
            
			virtual ~avl_tree_const_iterator() { }

			avl_tree_const_iterator &operator=(const avl_tree_const_iterator& avl_it)
			{
				if (this != &avl_it)
                {
                    this->node = avl_it.node;
                    this->comp = avl_it.comp;
                }
				return (*this);
			}

			bool operator==(const avl_tree_const_iterator& avl_it)
			{ return (this->node == avl_it.node); }

			bool operator!=(const avl_tree_const_iterator& avl_it)
			{ return (this->node != avl_it.node); }

			reference operator*() const
			{
               return (this->node->value); 
            }

			pointer operator->() const
			{ 
                return (&this->node->value); 
            }

			avl_tree_const_iterator& operator++(void)
			{
				N* cursor = node;

				if (cursor->right != NULL)
				{
					cursor = cursor->right;
					while (1)
					{
						if (cursor->left != NULL)
							cursor = cursor->left;
						else
							break;
					}
				}
                else
                {
					while (!comp(node->value.first, cursor->value.first)) // node->value.first >= cursor->value.first
					{
						//spuer_root(end_node)에서 멈춤
						if (cursor->parent == NULL)
						{
							*this = cursor;
							return (*this);
						}
						cursor = cursor->parent;
					}
				}
				*this = cursor;
				return (*this);
			}

			avl_tree_const_iterator operator++(int)
			{
				avl_tree_const_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			avl_tree_const_iterator& operator--(void)
			{
				N* cursor = node;
                
                if (cursor->left != NULL)
				{
					cursor = cursor->left;
                    while (1)
					{
						if (cursor->right != NULL)
							cursor = cursor->right;
						else
							break;
					}
				}
                else
				{
					cursor = cursor->parent;
					while (comp(node->value.first, cursor->value.first)) // node->value.first < cursor->value.first
					{
						cursor = cursor->parent;
					}
				}
				*this = cursor;
				return (*this);
			}

			avl_tree_const_iterator operator--(int)
			{
				avl_tree_const_iterator tmp(*this);
				operator--();
				return (tmp);
			}

			N*		    node; // current node
            key_compare comp;
	};
}

#endif