/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 01:57:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/10/24 07:56:12 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> > class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

			explicit stack (const container_type& ctnr = container_type()) 
			: ct(ctnr) {}
			
			~stack() {}
			
			// Member functions
			bool empty() const { return (this->ct.empty()); }
			size_type size() const { return (this->ct.size()); }
			value_type& top() { return (this->ct.back()); }
			const value_type& top() const { return (this->ct.back()); }
			void push (const value_type& val) { this->ct.push_back(val); }
			void pop() { this->ct.pop_back(); }

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
			container_type ct;
	};

	// Non-member function overloads
	template <class T, class Container>
	bool operator== (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.ct == rhs.ct); }

	template <class T, class Container>
	bool operator!= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.ct != rhs.ct); }

	template <class T, class Container>
	bool operator< (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.ct < rhs.ct); }

	template <class T, class Container>
	bool operator<= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.ct <= rhs.ct); }	
	
	template <class T, class Container>
	bool operator> (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.ct > rhs.ct); }

	template <class T, class Container>
	bool operator>= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{ return (lhs.ct >= rhs.ct); }	
}

#endif