#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include <iostream>
# include "bst_node.hpp"
# include "../utility.hpp"

namespace ft
{
	template <class T, class Compare = std::less<T>, class Node = ft::BST_Node<T>,
			class Node_Alloc = std::allocator<Node> >
	class binary_search_tree
	{
		public :
			typedef binary_search_tree  self;
			typedef self&   self_reference;
			typedef T   value_type;
			typedef Node node_type;
			typedef Node *  node_pointer;
			typedef Node_Alloc  node_alloc;
			typedef ft::BST_iterator<Node, Compare> iterator;
			typedef ft::BST_const_iterator<Node> const_iterator;
			typedef size_t size_type;

			binary_search_tree (const node_alloc& alloc = node_alloc(), const Compare& comp = Compare())
			: alloc(alloc), cnt(0), comp(comp)
			{
				root_node = this->alloc.allocate(1);
				this->alloc.construct(root_node, Node());		
			}

			virtual ~binary_search_tree ()
			{
				//작성필요

			}

			void insertPair(value_type to_insert)
			{
				//std::cout << "---------------" << std::endl;
				if (cnt == 0)
				{
					this->alloc.construct(root_node, Node(to_insert));
					cnt++;
					//std::cout << "root : " <<  root_node->value.first << std::endl;
				}
				else
				{
					Node* new_node = alloc.allocate(1);
					this->alloc.construct(new_node, Node(to_insert));
					cnt++;

					Node* cursor = root_node;
					while (1)
					{
						//std::cout << "cursor : " << cursor->value.first << std::endl;
						if (comp(new_node->value, cursor->value))
						{
							if (cursor->left != NULL)
								cursor = cursor->left;
							else
							{
								new_node->parent = cursor;
								cursor->left = new_node;
								//std::cout << "cursor : " << (cursor->left)->value.first << std::endl;
								break ;
							}
						}
						else
						{
							if (cursor->right != NULL)
								cursor = cursor->right;
							else
							{
								new_node->parent = cursor;
								cursor->right = new_node;
								//std::cout << "cursor : " << (cursor->right)->value.first << std::endl;
								break ;
							}
						}
					}
				}

			}

			//private:
				node_pointer root_node;
				node_alloc alloc;
				int	cnt;
				Compare comp;
	};
};
#endif