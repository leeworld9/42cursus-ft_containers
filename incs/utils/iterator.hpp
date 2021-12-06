/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:44:10 by dohelee           #+#    #+#             */
/*   Updated: 2021/12/06 16:18:31 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "./type_traits.hpp"

namespace ft
{
	//////////////////////////iterator tags///////////////////////////////
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	//////////////////////////iterator base class///////////////////////////////
	template <class Category,			// iterator::iterator_category
			class T,					// iterator::value_type
			class Distance = std::ptrdiff_t,	// iterator::difference_type
			class Pointer = T*,			// iterator::pointer
			class Reference = T&>		// iterator::reference
	struct iterator
	{
		typedef T		   value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	//////////////////////////iterator_traits class///////////////////////////////
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type  	difference_type;
		typedef typename Iter::pointer		    	pointer;
		typedef typename Iter::reference			reference;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	///////////////////////////////normal_iterator///////////////////////////////
	template<typename Iterator, typename Container>
	class normal_iterator
	{		
		protected:
			Iterator current;
			typedef iterator_traits<Iterator>				traits_type;

		public:
			typedef Iterator								iterator_type;
			typedef typename traits_type::iterator_category iterator_category;
			typedef typename traits_type::value_type  		value_type;
			typedef typename traits_type::difference_type 	difference_type;
			typedef typename traits_type::reference 		reference;
			typedef typename traits_type::pointer   		pointer;

			normal_iterator() : current(Iterator()) { }
			explicit normal_iterator(const Iterator& i)  : current(i) { }
			// Allow iterator to const_iterator conversion
			template<typename Iter>
			normal_iterator(const normal_iterator<Iter,
					typename ft::enable_if<
					(ft::are_same<Iter, typename Container::pointer>::value),
					Container>::type>& i) 
				: current(i.base()) { }

			// Forward iterator requirements
			reference operator*() const 
			{ return *current; }

			pointer operator->() const 
			{ return current; }

			normal_iterator& operator++() 
			{
				++current;
				return *this;
			}

			normal_iterator operator++(int) 
			{ return normal_iterator(current++); }

			// Bidirectional iterator requirements
			normal_iterator& operator--() 
			{
				--current;
				return *this;
			}

			normal_iterator operator--(int) 
			{ return normal_iterator(current--); }

			// Random access iterator requirements
			reference operator[](difference_type n) const 
			{ return current[n]; }

			normal_iterator& operator+=(difference_type n) 
			{ current += n; return *this; }

			normal_iterator operator+(difference_type n) const 
			{ return normal_iterator(current + n); }

			normal_iterator& operator-=(difference_type n) 
			{ current -= n; return *this; }

			normal_iterator operator-(difference_type n) const 
			{ return normal_iterator(current - n); }

			const Iterator& base() const 
			{ return current; }
	};

	// Forward iterator requirements
	template<typename IteratorL, typename IteratorR, typename Container>
	bool operator==(const normal_iterator<IteratorL, Container>& lhs,
					const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() == rhs.base(); };

	template<typename Iterator, typename Container>
	bool operator==(const normal_iterator<Iterator, Container>& lhs,
					const normal_iterator<Iterator, Container>& rhs)
	{ return lhs.base() == rhs.base(); }

	template<typename IteratorL, typename IteratorR, typename Container>
	bool operator!=(const normal_iterator<IteratorL, Container>& lhs,
					const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() != rhs.base(); }

	template<typename Iterator, typename Container>
	bool operator!=(const normal_iterator<Iterator, Container>& lhs,
					const normal_iterator<Iterator, Container>& rhs)
	{ return lhs.base() != rhs.base(); }

	// Random access iterator requirements
	template<typename IteratorL, typename IteratorR, typename Container>
	bool operator<(const normal_iterator<IteratorL, Container>& lhs,
					const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() < rhs.base(); }

	template<typename Iterator, typename Container>
	bool operator<(const normal_iterator<Iterator, Container>& lhs,
					const normal_iterator<Iterator, Container>& rhs)
	{ return lhs.base() < rhs.base(); }

	template<typename IteratorL, typename IteratorR, typename Container>
	bool operator>(const normal_iterator<IteratorL, Container>& lhs,
					const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() > rhs.base(); }

	template<typename Iterator, typename Container>
	bool operator>(const normal_iterator<Iterator, Container>& lhs,
					const normal_iterator<Iterator, Container>& rhs)
	{ return lhs.base() > rhs.base(); }

	template<typename IteratorL, typename IteratorR, typename Container>
	bool operator<=(const normal_iterator<IteratorL, Container>& lhs,
					const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template<typename Iterator, typename Container>
	bool operator<=(const normal_iterator<Iterator, Container>& lhs,
						const normal_iterator<Iterator, Container>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template<typename IteratorL, typename IteratorR, typename Container>
	bool operator>=(const normal_iterator<IteratorL, Container>& lhs,
					const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template<typename Iterator, typename Container>
	bool operator>=(const normal_iterator<Iterator, Container>& lhs,
					const normal_iterator<Iterator, Container>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template<typename IteratorL, typename IteratorR, typename Container>
	typename normal_iterator<IteratorL, Container>::difference_type 
	operator-(const normal_iterator<IteratorL, Container>& lhs,
				const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() - rhs.base(); }

	template<typename Iterator, typename Container>
	typename normal_iterator<Iterator, Container>::difference_type
	operator-(const normal_iterator<Iterator, Container>& lhs,
				const normal_iterator<Iterator, Container>& rhs)
	{ return lhs.base() - rhs.base(); }

	template<typename Iterator, typename Container>
	normal_iterator<Iterator, Container>
	operator+(typename normal_iterator<Iterator, Container>::difference_type n,
				const normal_iterator<Iterator, Container>& i)
	{ return normal_iterator<Iterator, Container>(i.base() + n); }

	///////////////////////////////reverse_iterator///////////////////////////////
	template<typename Iterator>
	class reverse_iterator
	: public iterator<typename iterator_traits<Iterator>::iterator_category,
			typename iterator_traits<Iterator>::value_type,
			typename iterator_traits<Iterator>::difference_type,
			typename iterator_traits<Iterator>::pointer,
			typename iterator_traits<Iterator>::reference>
	{
		protected:
			Iterator current;
			typedef iterator_traits<Iterator>				traits_type;

		public:
			typedef Iterator								iterator_type;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;
	
			reverse_iterator() : current() { }
			explicit reverse_iterator(iterator_type x) : current(x) { }
			template<typename Iter>
			reverse_iterator(const reverse_iterator<Iter>& x) : current(x.base()) { }

			iterator_type base() const
			{ return current; }

			reference operator*() const
			{
				Iterator tmp = current;
				return *--tmp;
			}

			pointer operator->() const
			{
				Iterator tmp = current;
				--tmp;
				return S_to_pointer(tmp);
			}

			reverse_iterator& operator++()
			{
				--current;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				--current;
				return tmp;
			}

			reverse_iterator& operator--()
			{
				++current;
				return *this;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				++current;
				return tmp;
			}

			reverse_iterator operator+(difference_type n) const
			{ return reverse_iterator(current - n); }

			reverse_iterator& operator+=(difference_type n)
			{
				current -= n;
				return *this;
			}

			reverse_iterator operator-(difference_type n) const
			{ return reverse_iterator(current + n); }

			reverse_iterator& operator-=(difference_type n)
			{
				current += n;
				return *this;
			}

			reference operator[](difference_type n) const
			{ return *(*this + n); }
		
		private:
			template<typename T>
			static  T* S_to_pointer(T* p)
			{ return p; }

			template<typename T>
			static  pointer S_to_pointer(T t)
			{ return t.operator->(); }
	};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	};
					
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs == rhs);
	};

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	};

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs.base() < rhs.base());
	};

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	};

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return !(lhs.base() > rhs.base());
	};

	template <class Iterator>
  	reverse_iterator<Iterator>
	operator+ (typename reverse_iterator<Iterator>::difference_type n,
					const reverse_iterator<Iterator>& rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	};
	
	template <class Iterator>
  	typename reverse_iterator<Iterator>::difference_type
	operator- (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	};

	template<typename IteratorL, typename IteratorR>
	bool operator==(const reverse_iterator<IteratorL>& x,
			const reverse_iterator<IteratorR>& y)
	{ 
		return x.base() == y.base();
	}

	template<typename IteratorL, typename IteratorR>
	bool operator<(const reverse_iterator<IteratorL>& x,
			const reverse_iterator<IteratorR>& y)
	{ 
		return y.base() < x.base();
	}

	template<typename IteratorL, typename IteratorR>
	bool operator!=(const reverse_iterator<IteratorL>& x,
			const reverse_iterator<IteratorR>& y)
	{
		return !(x == y);
	}

	template<typename IteratorL, typename IteratorR>
	bool operator>(const reverse_iterator<IteratorL>& x,
			const reverse_iterator<IteratorR>& y)
	{
		return y < x;
	}

	template<typename IteratorL, typename IteratorR>
	bool operator<=(const reverse_iterator<IteratorL>& x,
			const reverse_iterator<IteratorR>& y)
	{
		return !(y < x);
	}

	template<typename IteratorL, typename IteratorR>
	bool operator>=(const reverse_iterator<IteratorL>& x,
			const reverse_iterator<IteratorR>& y)
	{ 
		return !(x < y);
	}

	template<typename IteratorL, typename IteratorR>
	typename reverse_iterator<IteratorL>::difference_type
	operator-(const reverse_iterator<IteratorL>& x,
			const reverse_iterator<IteratorR>& y)
	{ 
		return y.base() - x.base();
	}

	//////////////////////////back_insert_iterator//////////////////////////
	template <class Container>
	class back_insert_iterator :
		public iterator<output_iterator_tag,void,void,void,void>
	{
		protected:
			Container* container;

		public:
			typedef Container container_type;
			explicit back_insert_iterator (Container& x) : container(&x) {}
			back_insert_iterator<Container>& operator= (typename Container::const_reference value)
				{ container->push_back(value); return *this; }
			back_insert_iterator<Container>& operator* ()
				{ return *this; }
			back_insert_iterator<Container>& operator++ ()
				{ return *this; }
			back_insert_iterator<Container> operator++ (int)
				{ return *this; }
	};

	/////////////////////////front_insert_iterator//////////////////////////
	template <class Container>
	class front_insert_iterator :
		public iterator<output_iterator_tag,void,void,void,void>
	{
		protected:
			Container* container;

		public:
			typedef Container container_type;
			explicit front_insert_iterator (Container& x) : container(&x) {}
			front_insert_iterator<Container>& operator= (typename Container::const_reference value)
				{ container->push_front(value); return *this; }
			front_insert_iterator<Container>& operator* ()
				{ return *this; }
			front_insert_iterator<Container>& operator++ ()
				{ return *this; }
			front_insert_iterator<Container> operator++ (int)
				{ return *this; }
	};

	/////////////////////////insert_iterator////////////////////////////////
	template <class Container>
	class insert_iterator :
		public iterator<output_iterator_tag,void,void,void,void>
	{
		protected:
			Container* container;
			typename Container::iterator iter;

		public:
			typedef Container container_type;
			explicit insert_iterator (Container& x, typename Container::iterator i)
				: container(&x), iter(i) {}
			insert_iterator<Container>& operator= (typename Container::const_reference value)
				{ iter=container->insert(iter,value); ++iter; return *this; }
			insert_iterator<Container>& operator* ()
				{ return *this; }
			insert_iterator<Container>& operator++ ()
				{ return *this; }
			insert_iterator<Container>& operator++ (int)
				{ return *this; }
		};

	/////////////////////////istream_iterator///////////////////////////////
	template <class T, class charT=char, class traits=std::char_traits<charT>, class Distance=std::ptrdiff_t>
	class istream_iterator :
		public iterator<input_iterator_tag, T, Distance, const T*, const T&>
	{
		std::basic_istream<charT,traits>* in_stream;
		T value;

		public:
			typedef charT char_type;
			typedef traits traits_type;
			typedef std::basic_istream<charT,traits> istream_type;
			istream_iterator() : in_stream(0) {}
			istream_iterator(istream_type& s) : in_stream(&s) { ++*this; }
			istream_iterator(const istream_iterator<T,charT,traits,Distance>& x)
				: in_stream(x.in_stream), value(x.value) {}
			~istream_iterator() {}

			const T& operator*() const { return value; }
			const T* operator->() const { return &value; }
			istream_iterator<T,charT,traits,Distance>& operator++() {
				if (in_stream && !(*in_stream >> value)) in_stream=0;
				return *this;
			}
			istream_iterator<T,charT,traits,Distance> operator++(int) {
				istream_iterator<T,charT,traits,Distance> tmp = *this;
				++*this;
				return tmp;
			}
	};

	/////////////////////////ostream_iterator///////////////////////////////
	template <class T, class charT=char, class traits=std::char_traits<charT> >
	class ostream_iterator :
		public iterator<output_iterator_tag, void, void, void, void>
	{
			std::basic_ostream<charT,traits>* out_stream;
			const charT* delim;

		public:
			typedef charT char_type;
			typedef traits traits_type;
			typedef std::basic_ostream<charT,traits> ostream_type;
			ostream_iterator(ostream_type& s) : out_stream(&s), delim(0) {}
			ostream_iterator(ostream_type& s, const charT* delimiter)
				: out_stream(&s), delim(delimiter) { }
			ostream_iterator(const ostream_iterator<T,charT,traits>& x)
				: out_stream(x.out_stream), delim(x.delim) {}
			~ostream_iterator() {}

			ostream_iterator<T,charT,traits>& operator= (const T& value) {
				*out_stream << value;
				if (delim!=0) *out_stream << delim;
				return *this;
			}

			ostream_iterator<T,charT,traits>& operator*() { return *this; }
			ostream_iterator<T,charT,traits>& operator++() { return *this; }
			ostream_iterator<T,charT,traits>& operator++(int) { return *this; }
	};

	////////////////////////istreambuf_iterator/////////////////////////////
	template <class charT=char, class traits=std::char_traits<charT> >
	class istreambuf_iterator :
		public iterator<input_iterator_tag, charT,
						typename traits::off_type, charT*, charT&>
	{
			public:
			typedef charT char_type;
			typedef traits traits_type;
			typedef typename traits::int_type int_type;
			typedef std::basic_streambuf<charT,traits> streambuf_type;
			typedef std::basic_istream<charT,traits> istream_type;

			class proxy {
				charT keep_; streambuf_type* sbuf_;
				public:
						proxy (charT c, streambuf_type* sbuf) : keep_(c), sbuf_(sbuf) { }
						charT operator*() {return keep_;}
			};

			istreambuf_iterator() throw() : sbuf_(0) { }
			istreambuf_iterator(istream_type& s) throw(): sbuf_(s.rdbuf()) { }
			istreambuf_iterator(streambuf_type* s) throw(): sbuf_(s) { }
			istreambuf_iterator(const proxy& p) throw(): sbuf_(p.sbuf_) { }

			charT operator*() const { return sbuf_->sgetc(); }
			istreambuf_iterator<charT,traits>& operator++() { sbuf_->sbumpc(); return *this; }
			proxy operator++(int) {return proxy(sbuf_->sbumpc(),sbuf_);}

			bool equal (istreambuf_iterator& b) const {
				if ( sbuf_==0 || *(*this)==traits::eof() ) 
				{ if ( b.sbuf_==0 || *b==traits::eof() ) return true; }
				else if ( b.sbuf_!=0 && *b!= traits::eof() ) return true;
				return false;
			}

		private:
			streambuf_type* sbuf_;
	};

	////////////////////////ostreambuf_iterator/////////////////////////////
	template <class charT=char, class traits=std::char_traits<charT> >
	class ostreambuf_iterator :
		public iterator<output_iterator_tag, charT,
						typename traits::off_type, charT*, charT&>
	{
		public:
			typedef charT char_type;
			typedef traits traits_type;
			typedef typename traits::int_type int_type;
			typedef std::basic_streambuf<charT,traits> streambuf_type;
			typedef std::basic_ostream<charT,traits> ostream_type;

			ostreambuf_iterator(ostream_type& s) throw(): sbuf_(s.rdbuf()) { }
			ostreambuf_iterator(streambuf_type* s) throw(): sbuf_(s) { }
			ostreambuf_iterator& operator= (charT c)
			{ if (!failed()) last=sbuf_->sputc(c); return *this; }

			ostreambuf_iterator& operator*() { return *this; }
			ostreambuf_iterator& operator++() { return *this; }
			ostreambuf_iterator& operator++(int) { return *this;}

			bool failed() const throw() { return last==traits::eof(); }

		private:
			streambuf_type* sbuf_;
			charT last;
	};

	
	///////////////////////////////Functions///////////////////////////////
	template<class It, class Distance>
	void advance(It& it, Distance n)
	{
		it += n;
	}

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
		distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
		while (first != last)
		{
			first++;
			rtn++;
		}
		return (rtn);
	}

	template< class Container >
	ft::back_insert_iterator<Container> back_inserter( Container& c )
	{
		return ft::back_insert_iterator<Container>(c);
	}

	template< class Container >
	ft::front_insert_iterator<Container> front_inserter( Container& c )
	{
		return ft::front_insert_iterator<Container>(c);
	}

	template< class Container >
	ft::insert_iterator<Container> inserter( Container& c, typename Container::iterator i )
	{
		return ft::insert_iterator<Container>(c, i);
	}
}

#endif