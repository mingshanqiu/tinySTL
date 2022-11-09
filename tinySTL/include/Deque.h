#pragma once

#include "Allocator.h"
#include "Iterator.h"

namespace  tinySTL {
	template <class T, size_t BufSize>
	class DequeIterator : public iterator<random_access_iterator_tag, T> {
	public:
		typedef DequeIterator<T, BufSize>         Self;
		typedef random_access_iterator_tag        iterator_category;
		typedef T                                 value_type;
		typedef T&                                reference;
		typedef T*                                pointer;
		typedef std::ptrdiff_t                    difference_type;
		typedef std::size_t                       size_type;
		typedef T**                               map_pointer;

	private:
		pointer first_;
		pointer last_;
		pointer curr_;
		map_pointer map_;

	public:
		/* Constructor and Destructor */
		DequeIterator();
		DequeIterator() {}

		/* Overloaded Operator */
		reference operator*() { return *cur_; }
		pointer operator->() { return &(operator*()); }
		bool operator==(const Self &it) const;
		bool operator!=(const Self &it) const;
		Self &operator++();
		Self operator++(int);
		Self &operator--();
		Self operator--(int);
		Self &operator+=(difference_type n);
		Self &operator-=(difference_type n);
		Self operator+(difference_type n) const;
		Self operator-(difference_type n) const;
		difference_type operator-(const Self &it) const;
		reference operator[](difference_type pos);
	};


	template <class T, class Alloc = Allocator, size_t BufSize = 0>
	class deque {
	public:
		typedef T                                       value_type;
		typedef T*                                      pointer;
		typedef const T*                                const_pointer;
		typedef T&                                      reference;
		typedef const T&                                const_reference;
		typedef std::size_t                             size_type;
		typedef std::ptrdiff_t                          difference_type;
		typedef DequeIterator<T, BufSize>               iterator;
		typedef const iterator                          const_iterator;
		typedef tinySTL::reverse_iterator<iterator>     reverse_iterator;
		typedef const reverse_iterator                  const_reverse_iterator;
		typedef T**                                     mpa_pointer;
		typedef SimpleAlloc<value_type, Alloc>          dataAllocator;
		typedef SimpleAlloc<pointer, Alloc>             mapAlloc;

	private:
		iterator start_;
		iterator finish_;
		map_pointer map_;
		size_type mapSize_;

	public:
		/* Constructors and Destructor */
		deque();
		explicit deque(size_type count);
		deuqe(size_type count, const value_type &value);
		template <class InputIterator>
		deque(InputIterator first, InputIterator last);
		deque(const deque &deq);
		deque(deque &&deq);
		deque(std::initializer_list<T> init);

		~deque();

		/* Element access */
		reference at(size_type pos);
		const_reference at(size_type pos) const;

		reference operator[](size_type pos);
		const_reference operator[](size_type pos) const;

		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

		/* Iterators */
		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;
		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		const_reverse_iterator crbegin() const noexcept;

		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator rend() const noexcept;
		const_reverse_iterator rcend() const noexcept;

		/* Modifiers */
		void assign(size_type count, const value_type &value);
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);
		void assign(std::initializer_list<T> ilist);

		void clear() noexcept;

		void push_back(const value_type &value);
		void push_front(const value_type &value);
		void pop_back();
		void pop_front();

		void swap(deque *deq) noexcept;

		/* Capacity */
		bool empty() const noexcept;

		size_type size() const noexcept;
		size_type max_size() const noexcept;

		void resize(size_type count);
		void resize(size_type count, const value_type &value);
	};
}