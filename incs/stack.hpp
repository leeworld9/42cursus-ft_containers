/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 01:57:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/12/07 16:22:26 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "./vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> > class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

			explicit stack (const container_type& ctnr = container_type()) 
			: c(ctnr) {}
			
			~stack() {}
			
			// Member functions
			bool empty() const { return (this->c.empty()); }
			size_type size() const { return (this->c.size()); }
			value_type& top() { return (this->c.back()); }
			const value_type& top() const { return (this->c.back()); }
			void push (const value_type& val) { this->c.push_back(val); }
			void pop() { this->c.pop_back(); }

			//relational operators
			template <class Tn, class ContainerN>
			friend bool operator== (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
			friend bool operator!= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
			
			template <class Tn, class ContainerN>
			friend bool operator< (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
			friend bool operator<= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
			friend bool operator> (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
			friend bool operator>= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

		protected:
			container_type c;
	};

	// Non-member function overloads
	template <class T, class Container>
	bool operator== (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.c == rhs.c); }

	template <class T, class Container>
	bool operator!= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.c != rhs.c); }

	template <class T, class Container>
	bool operator< (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.c < rhs.c); }

	template <class T, class Container>
	bool operator<= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.c <= rhs.c); }	
	
	template <class T, class Container>
	bool operator> (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.c > rhs.c); }

	template <class T, class Container>
	bool operator>= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.c >= rhs.c); }	
}

#endif