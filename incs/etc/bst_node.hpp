#ifndef BST_NODE_HPP
# define BST_NODE_HPP

# include <iostream>

namespace ft
{
	template <typename T>
	struct BST_Node
	{
		public :
			typedef T   value_type;

			value_type value;
			BST_Node* parent;
			BST_Node* left;
			BST_Node* right;

			BST_Node ()
			:
				value(),
				parent(NULL),
				left(NULL),
				right(NULL)
			{}
			
			BST_Node (const value_type& val, BST_Node* parent = NULL,
					BST_Node* left = NULL, BST_Node* right = NULL)
			:
				value(val),
				parent(parent),
				left(left),
				right(right)
			{}

			BST_Node (const BST_Node& nd)
			:
				value(nd.value),
				parent(nd.parent),
				left(nd.left),
				right(nd.right)
			{}

			virtual ~BST_Node() {}

			BST_Node &operator=(const BST_Node& nd)
			{
				if (nd == *this)
					return (*this);
				
				this->value = nd.value;
				this->parent = nd.parent;
				this->left = nd.left;
				this->right = nd.right;
				
				return (*this);
			}

			bool operator==(const BST_Node& nd)
			{
				if (value == nd.value)
					return (true);
				return (false);
			}
	};
};
#endif