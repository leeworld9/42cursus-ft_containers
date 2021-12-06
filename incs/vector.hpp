/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 01:57:42 by dohelee           #+#    #+#             */
/*   Updated: 2021/12/06 15:48:06 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "./utils/iterator.hpp"
# include "./utils/algorithm.hpp"

// reference : https://wikidocs.net/29955

namespace ft
{
    template< class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef typename ft::normal_iterator<pointer, vector>   iterator;
            typedef typename ft::normal_iterator<const_pointer, vector> const_iterator;
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
            typedef size_t size_type;

            //(1) empty container constructor (default constructor)
            explicit vector (const allocator_type& alloc = allocator_type())
            :
                alloc(alloc),
                start(NULL),
                finish(NULL),
                end_of_storage(NULL)
            {}

            //(2) fill constructor
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            :
                alloc(alloc),
                start(NULL),
                finish(NULL),
                end_of_storage(NULL)
            {
                this->insert(this->begin(), n, val);
            }
            
            //(3) range constructor
            // reference 1 : http://egloos.zum.com/sweeper/v/3059985
            // reference 2 : https://int-i.github.io/cpp/2020-03-25/cpp-sfinae/
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()
                , typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            :
                alloc(alloc),
                start(NULL),
                finish(NULL),
                end_of_storage(NULL)
            {
                this->insert(this->begin(), first, last);
            }

            //(4) copy constructor
            vector (const vector& x)
            {
                *this = x;
            }

            // destructor
            ~vector()
            {
                this->clear();
                alloc.deallocate(this->start, this->capacity());
            }
            
            // Assign content
            vector& operator= (const vector& x)
            {
                if (this != &x)
                {
                    this->alloc = std::allocator<T>();
                    this->start = this->alloc.allocate(x.capacity());
                    this->finish = this->start;
                    pointer tmp = x.start;
                    while (tmp != x.finish)
                        this->alloc.construct(this->finish++, *tmp++);
                    this->end_of_storage = this->start + x.capacity();
                }
                return (*this); 
            }

            // Iterators
            iterator begin()
            { 
                return iterator(this->start);
            }

            const_iterator begin() const
            {
                return const_iterator(this->start);
            }

            iterator end()
            {
                return iterator(this->finish);
            }

            const_iterator end() const
            {
                return const_iterator(this->finish);
            }
        
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
            size_type size() const
            {
                return (this->finish - this->start);
            }
            
            size_type max_size() const
            {
                return (allocator_type().max_size());
            }

            void resize (size_type n, value_type val = value_type())
            {
                if (n > this->max_size())
                    throw (std::length_error("vector::resize"));
                else if (n < this->size())
                {
                    while (this->size() > n)
                    {
                        --this->finish;
                        this->alloc.destroy(this->finish);
                    }
                }
                else
                    this->insert(this->end(), n - this->size(), val);
            }

            size_type capacity() const
            {
                return (this->end_of_storage - this->start);
            }
            
            bool empty() const
            {
                if (this->size() == 0)
                    return (true);
                else
                    return (false);
            }
            
            void reserve (size_type n)
            {
                if (this->max_size() < n)
                    throw (std::length_error("vector::reserve"));
                else if (this->capacity() > n)
                    return ;
                else
                {
                    pointer prev_start = this->start;
                    pointer prev_finish = this->finish;
                    size_type prev_capacity = this->capacity();

                    this->start = this->alloc.allocate(n);
                    this->end_of_storage = this->start + n;
                    this->finish = this->start;

                    pointer tmp = prev_start;
                    while (tmp != prev_finish)
                    {
                        this->alloc.construct(this->finish, *tmp);
                        this->alloc.destroy(tmp);
                        this->finish++;
                        tmp++;
                    }
                    this->alloc.deallocate(prev_start, prev_capacity);
                }
            }

            //Element access
            reference operator[] (size_type n)
            { 
                return *(this->start + n);
            
            }
            const_reference operator[] (size_type n) const
            {
                return *(this->start + n);
            }

            reference at (size_type n)
            {
                if (n >= this->size())
                    throw std::out_of_range("vector::at");
                return ((*this)[n]);
            }

            const_reference at (size_type n) const
            {
                if (n >= this->size())
                    throw std::out_of_range("vector::at");
                return ((*this)[n]);
            }

            reference front()
            {
                return *(this->start);
            }

            const_reference front() const
            {
                return *(this->start);
            }

            reference back()
            {
                return *(this->finish - 1);
            }

            const_reference back() const
            {
                return *(this->finish - 1);
            }

            // Modifiers
            // assign : range (1)   
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last
                    , typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
                this->clear();
                size_type dist = ft::distance(first, last);
                if (this->capacity() > dist)
                {
                    while (dist--)
                    {
                        this->alloc.construct(this->finish++, *first++);
                    }
                }
                else
                {
                    pointer new_start = alloc.allocate(dist);
                    pointer new_finish = new_start;
                    pointer new_eos = new_start + dist;

                    while(dist--)
                        this->alloc.construct(new_finish++, *first++);
                    
                    this->alloc.deallocate(this->start, this->capacity());
                    this->start = new_start;
                    this->finish = new_finish;
                    this->end_of_storage = new_eos;
                }
            }

            // assign : fill (2)    
            void assign (size_type n, const value_type& val)
            {
                this->clear();
                if (n == 0)
                    return ;
                if (this->capacity() >= n)
                {
                    while (n)
                    {
                        this->alloc.construct(this->finish++ , val);
                        n--;
                    }
                }
                else
                {
                    this->alloc.deallocate(this->start, this->capacity());
                    this->start = this->alloc.allocate(n);
                    this->finish = this->start;
                    this->end_of_storage = this->start + n;
                    while (n)
                    {
                        this->alloc.construct(this->finish++, val);
                        n--;
                    }
                }
            }

            void push_back (const value_type& val)
            {
                if (this->finish == this->end_of_storage)
                {
                    size_type next_capacity = (this->size() > 0) ? (this->size() * 2) : 1;
                    this->reserve(next_capacity);
                }
                this->alloc.construct(this->finish, val);
                this->finish++;
            }

            void pop_back()
            {
                alloc.destroy(&this->back());
                this->finish--;
            }

            iterator erase (iterator position)
            {
                pointer p_pos = &(*position);
                if (p_pos + 1 == this->finish)
                    this->alloc.destroy(p_pos);
                else
                {
                    for (int i = 0; i < this->finish - p_pos - 1; i++)
                        this->alloc.construct(p_pos + i, *(p_pos + i + 1));
                }
                this->alloc.destroy(this->finish - 1);
                this->finish--;
                return (iterator(p_pos));
            }

            iterator erase (iterator first, iterator last)
            {
                pointer p_first = &(*first);
                pointer p_last = &(*last);
                size_type dist = ft::distance(first, last);

                for (int i = 0; i < this->finish - p_last; i++)
                    this->alloc.construct(p_first + i, *(last + i));

                for (size_type i = 0; i < dist ; i++)
                    this->alloc.destroy(p_first + (this->finish - p_last) + i);
                    
                this->finish -= dist;
                return (iterator(p_first));
            }

            void swap (vector& x)
            {
                if (&x == this)
                    return;
                
                pointer tmp_start = x.start;
                pointer tmp_finish = x.finish;
                pointer tmp_eos = x.end_of_storage;
                allocator_type tmp_alloc = x.alloc;

                x.start = this->start;
                x.finish = this->finish;
                x.end_of_storage = this->end_of_storage;
                x.alloc = this->alloc;

                this->start = tmp_start;
                this->finish = tmp_finish;
                this->end_of_storage = tmp_eos;
                this->alloc = tmp_alloc;
            }

            void clear()
            {
                size_type tmp_size = this->size();
                for (size_type i = 0; i < tmp_size; i++)
                {
                    this->finish--;
                    this->alloc.destroy(this->finish);
                }
            }
                        
            // insert : single element (1)  
            iterator insert (iterator position, const value_type& val)
            {
                size_type pos_len = &(*position) - this->start;
                if (this->capacity() >= this->size() + 1)
                {
                    for (size_type i = 0; i < this->size() - pos_len; i++)
                        this->alloc.construct(this->finish - i, *(this->finish - i - 1));
                    this->finish++;
                    this->alloc.construct(&(*position), val);
                }
                else
                {
                    pointer prev_start = this->start;
                    pointer prev_finish = this->finish;
                    size_type prev_capacity = this->capacity();
                    
                    size_type next_capacity = (this->size() * 2 > 0) ? this->size() * 2 : 1; 
                    pointer new_start = this->alloc.allocate(next_capacity);
                    pointer new_finish = new_start + this->size() + 1;
                    pointer new_eos = new_start + next_capacity;
                    
                    size_type i = 0;
                    pointer tmp = prev_start;
                    while (i < pos_len)
                    {
                        this->alloc.construct(new_start + i, *tmp++);
                        i++;
                    }
                    this->alloc.construct(new_start + i, val);
                    for (size_type i = 1; i <= this->size() - pos_len; i++)
                    {
                        this->alloc.construct(new_finish - i, *(prev_finish - i));
                    }
                    
                    this->start = new_start;
                    this->finish = new_finish;
                    this->end_of_storage = new_eos;

                    tmp = prev_start;
                    while (tmp != prev_finish)
                    {
                        this->alloc.destroy(tmp);
                        tmp++;
                    }
                    this->alloc.deallocate(prev_start, prev_capacity);
                }
                return (this->begin() + pos_len);
            }

            // insert : fill (2)    
            void insert (iterator position, size_type n, const value_type& val)
            {
                if (n == 0)
                    return ;
                if (n > this->max_size())
                    throw (std::length_error("vector::insert (fill)"));
                size_type pos_len = &(*position) - this->start;
                if (this->capacity() >= this->size() + n)
                {
                    //뒤에서 부터 옮겨야함 (앞에서 부터 하면 덮어 씌워지는 경우가 있음)
                    for (size_type i = this->size() - pos_len; i > 0; i--)
                        this->alloc.construct(&(*position) + n + (i - 1), *(position + i - 1));
                    while(n--)
                    {
                        this->alloc.construct(&(*position) + n, val);
                        this->finish++;
                    }
                }
                else
                {
                    pointer prev_start = this->start;
                    pointer prev_finish = this->finish;
                    size_type prev_capacity = this->capacity();
                    
                    size_type next_capacity = (this->size() * 2 > this->size() + n) ? this->size() * 2 : this->size() + n; 
                    pointer new_start = this->alloc.allocate(next_capacity);
                    pointer new_finish = new_start + this->size() + n;
                    pointer new_eos = new_start + next_capacity;

                    size_type i = 0;
                    pointer tmp = prev_start;
                    while (i < pos_len)
                    {
                        this->alloc.construct(new_start + i, *tmp++);
                        i++;
                    }
                    for (size_type i = 0; i < this->size() - pos_len; i++)
                        this->alloc.construct((new_start + pos_len) + n + i, *(prev_start + pos_len + i));
                    while(n--)
                    {
                        this->alloc.construct((new_start + pos_len) + n, val);
                    }
                    
                    this->start = new_start;
                    this->finish = new_finish;
                    this->end_of_storage = new_eos;

                    tmp = prev_start;
                    while (tmp != prev_finish)
                    {
                        this->alloc.destroy(tmp);
                        tmp++;
                    }
                    this->alloc.deallocate(prev_start, prev_capacity);
                }
            }

            // insert : range (3)   
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last
                        , typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
            {
                size_type pos_len = &(*position) - this->start;
                size_type dist = ft::distance(first, last);
                if (this->capacity() >= this->size() + dist)
                {
                    for (size_type i = this->size() - pos_len; i > 0; i--)
                        this->alloc.construct(&(*position) + dist + (i - 1), *(position + i - 1));
                    size_type i = 0;
                    while (i < dist)
                    {
                        this->alloc.construct(&(*position) + i, *first++);
                        i++;
                        this->finish++;
                    }
                }
                else
                {
                    pointer prev_start = this->start;
                    pointer prev_finish = this->finish;
                    size_type prev_capacity = this->capacity();
                    
                    size_type next_capacity = (this->size() * 2 > this->size() + dist) ? this->size() * 2 : this->size() + dist; 
                    pointer new_start = this->alloc.allocate(next_capacity);
                    pointer new_finish = new_start + this->size() + dist;
                    pointer new_eos = new_start + next_capacity;

                    size_type i = 0;
                    pointer tmp = prev_start;
                    while (i < pos_len)
                    {
                        this->alloc.construct(new_start + i, *tmp++);
                        i++;
                    }
                    for (size_type i = 0; i < this->size() - pos_len; i++)
                        this->alloc.construct((new_start + pos_len + dist) + i, *(prev_start + pos_len + i));
                    i = 0;
                    while (i < dist)
                    {
                        this->alloc.construct((new_start + pos_len) + i, *first++);
                        i++;
                    }
                    
                    this->start = new_start;
                    this->finish = new_finish;
                    this->end_of_storage = new_eos;

                    tmp = prev_start;
                    while (tmp != prev_finish)
                    {
                        this->alloc.destroy(tmp);
                        tmp++;
                    }
                    this->alloc.deallocate(prev_start, prev_capacity);
                }
            }

            // Allocator
            allocator_type get_allocator() const
            {
                return (this->alloc);
            }

        private:
            allocator_type  alloc;
            pointer start;
            pointer finish;
            pointer end_of_storage;
    };

    // Non-member function overloads
    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }

    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(rhs < lhs));
    }

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
    {
        vector<T,Alloc> tmp(x);
        x = y;
        y = tmp;
    }  
}

#endif
