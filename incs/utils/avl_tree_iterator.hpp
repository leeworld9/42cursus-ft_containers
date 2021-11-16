#ifndef AVL_TREE_ITERATOR_HPP
# define AVL_TREE_ITERATOR_HPP

# include <iostream>
# include "./utility.hpp"
# include "./iterator.hpp"

namespace ft
{
	template <class T, class Compare>
	class avl_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :
			typedef typename T::value_type    value_type;
            typedef Compare key_compare;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

			avl_tree_iterator(const key_compare& comp = key_compare())
			: node(), comp(comp)
			{}

			avl_tree_iterator(T * node, const key_compare& comp = key_compare())
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
				T* cursor = node;

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
				T* cursor = node;
                
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

			T*			node; // current node
            key_compare comp;
	};

	template <class T, class Compare>
	class avl_tree_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
		public :
			typedef typename T::value_type    value_type;
            typedef Compare key_compare;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

			avl_tree_const_iterator(const key_compare& comp = key_compare())
			: node(), comp(comp)
			{}

			avl_tree_const_iterator(T * node, const key_compare& comp = key_compare())
			: node(node), comp(comp)
			{}

			avl_tree_const_iterator(const avl_tree_const_iterator& copy)
			{
				*this = copy;
			}

            // avl_tree_iterator Convert (아무래도 이방법은 아닌거 같긴하지만 임시...)
            avl_tree_const_iterator(const avl_tree_iterator<T, Compare>& it) : node(it.node), comp(it.comp) {}

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

            //이게 키 포인트일꺼 같음
            operator value_type(void) const
            {
			    return value_type(this->value);
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
				T* cursor = node;

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
				T* cursor = node;
                
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

			T*			node; // current node
            key_compare comp;
	};
}

#endif