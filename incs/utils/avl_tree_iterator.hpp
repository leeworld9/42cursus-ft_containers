#ifndef AVL_TREE_ITERATOR_HPP
# define AVL_TREE_ITERATOR_HPP

namespace ft
{

	template <typename T, class Compare>
	class BST_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :

			typedef typename T::value_type    value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

			BST_iterator(const Compare& comp = Compare())
			: node(NULL), comp(comp)
			{}

			BST_iterator(T * node, const Compare& comp = Compare())
			: node(node), comp(comp)
			{}

			BST_iterator(const BST_iterator& copy)
			{
				*this = copy;
			}

			virtual ~BST_iterator() { }

			BST_iterator &operator=(const BST_iterator& bst_it)
			{
				if (*this == bst_it)
					return (*this);
				this->node = bst_it.node;
				this->comp = bst_it.comp;
				return (*this);
			}

			bool operator==(const BST_iterator& bst_it)
			{ return (this->node == bst_it.node); }

			bool operator!=(const BST_iterator& bst_it)
			{ return (this->node != bst_it.node); }

			reference operator*() const
			{ return (this->node->value); }

			pointer operator->() const
			{ return (&this->node->value); }

			BST_iterator& operator++(void)
			{
				T* cursor = node;

				if (cursor->right == NULL)
				{
					while (!comp(node->value, cursor->value))
					{
						//end_node에서 멈춤
						if (cursor->parent == NULL)
						{
							*this = cursor;
							return (*this);
						}
						cursor = cursor->parent;
					}
				}
				else
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
				*this = cursor;
				return (*this);
			}

			BST_iterator operator++(int)
			{
				BST_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			BST_iterator& operator--(void)
			{
				T* cursor = node;
				
				//end_node 일때 처리
				if (cursor->parent == NULL)
				{
					cursor = cursor->right;
					while (1)
					{
						if (cursor->right != NULL)
							cursor = cursor->right;
						else
							break;
					}
				}
				else if (cursor->left == NULL)
				{
					cursor = cursor->parent;
					while (comp(node->value, cursor->value))
					{
						cursor = cursor->parent;
					}
				}
				else
				{
					cursor = cursor->left;
					if (cursor->right != NULL)
						cursor = cursor->right;
				}
				*this = cursor;
				return (*this);
			}

			BST_iterator operator--(int)
			{
				BST_iterator tmp(*this);
				operator--();
				return (tmp);
			}            

			T*			node; // current node
			Compare		comp; // 임시 -> 필요없으면 템플릿등에서 제거 하자
	};

	//////////////////////////BST_const_iterator//////////////////////////

	//아래도 위랑 똑같이 바꿔저야힘
	template <typename T>
	class BST_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :

			typedef typename T::value_type    value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer   pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

			BST_const_iterator()
			: node(NULL)
			{}

			BST_const_iterator(T * node)
			: node(node)
			{}

			BST_const_iterator(const BST_const_iterator& copy)
			{
				*this = copy;
			}

			virtual ~BST_const_iterator() { }

			BST_const_iterator &operator=(const BST_const_iterator& bst_it)
			{
				if (*this == bst_it)
					return (*this);
				this->node = bst_it.node;
				return (*this);
			}

			bool operator==(const BST_const_iterator& bst_it)
			{ return (this->node == bst_it.node); }

			bool operator!=(const BST_const_iterator& bst_it)
			{ return (this->node != bst_it.node); }

			reference operator*() const
			{ return (this->node->value); }

			pointer operator->() const
			{ return (&this->node->value); }

			BST_const_iterator& operator++(void)
			{
				T* cursor = node;

				if (cursor->right == NULL)
				{
					cursor = cursor->parent;
				} 
				else
				{
					cursor = cursor->right;
					while (1)
					{
						if (cursor->left != NULL)
							cursor = cursor->left;
						else if (cursor->right != NULL)
							cursor = cursor->right;
						else
							break;
					}
				}
				*this = cursor;
				return (*this);
			}

			BST_const_iterator operator++(int)
			{
				BST_const_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			BST_const_iterator& operator--(void)
			{
				T* cursor = node;

				if (cursor->left == NULL)
				{
					cursor = cursor->left;
				} 
				else
				{
					cursor = cursor->left;
					while (1)
					{
						if (cursor->right != NULL)
							cursor = cursor->right;
						else if (cursor->left != NULL)
							cursor = cursor->left;
						else
							break;
					}
				}
				*this = cursor;
				return (*this);
			}

			BST_const_iterator operator--(int)
			{
				BST_const_iterator tmp(*this);
				operator--();
				return (tmp);
			}            

			T *			node; // current node
	};
}

#endif