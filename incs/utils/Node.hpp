/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:44:15 by dohelee           #+#    #+#             */
/*   Updated: 2021/12/06 15:47:44 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

namespace ft
{
    template <typename T>
    struct Node
    {
        public :
            typedef T value_type;

            value_type      value;
            Node* left;
            Node* right;
            Node* parent;
            int height;

			Node ()
			:
				value(),
				left(NULL),
				right(NULL),
                parent(NULL),
                height(1)
			{}
			
			Node (const value_type& val)
			:
				value(val),
				left(NULL),
				right(NULL),
                parent(NULL),
                height(1)
			{}

            Node (const Node* copy)
            {
                *this = copy;
            }

			Node &operator=(const Node& nd)
			{
				if (*this != &nd)
				{
                    this->value = nd.value;
                    this->left = nd.left;
                    this->right = nd.right;
                    this->parent = nd.parent;
                    this->height = nd.height;
                }
				return (*this);
			}
            
            virtual ~Node() {}
	};

};
#endif
