#pragma once

#include "Iterator.h"
#include "Allocator.h"

namespace tinySTL {
	template <class T>
	struct ListNode
	{
		ListNode(const T &v, ListNode<T> *p, ListNode *n) : val(v), prev(p), next(n) {}
		T val;
		ListNode<T> *prev;
		ListNode<T> *next;
	};

	template <class U>
	class ListIterator : public iterator<bidirectional_iterator_tag, U> {
	public:
		ListNode<U> *node_;
	public:
		typedef ListIterator<U> Self;
		typedef U value_type;
		ListIterator() : node_(nullptr) {}
		ListIterator(ListNode<U> *header) : node_(header) {}
		ListIterator(const Self &it) : node_(it.node_) {}

		Self operator++(int) {
			Self old = *this;
			++(*this);
			return old;
		}

		Self& operator++()
		{
			node_ = node_->next;
			return *this;
		}

		Self operator--(int)
		{
			Self old = *this;
			--(*this);
			return old;
		}

		Self& operator--()
		{
			node_ = node_->prev;
			return *this;
		}

		bool operator==(const Self &it) const {
			return node_ == it.node_;
		}

		bool operator!=(const Self &it) const {
			return node_ ! = it.node_;
		}

		U &operator*() { return node_->val; }
		U *operator->() { return &node_->val; }
  	};

	template <class T, class Alloc = Allocator>
	class list {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef std::ptrdiff_t  difference_type;
		typedef std::size_t size_type;
		typedef ListIterator<T> iterator;
		typedef tinySTL::reverse_iterator<iterator> reverse_iterator;
		typedef const reverse_iterator const_reverse_iterator;
		typedef const ListIterator<T> const_iterator;
		typedef ListNode<T>* node_pointer;

	private:
		iterator header_;
		iterator tail_;
		typedef SimpleAlloc<ListNode<T>, Alloc> nodeAllocator;

	private:
		/* Private functions */
		void ctroAux(size_type count, const value_type &value, std::true_type);
		template <class InputIterator>
		void ctorAux(InputIterator first, InputIterator last, std::false_type);

		void assignAux(size_type count, const value_type &value, std::true_type);
		template <class InputIterator>
		void assignAux(InputIterator first, InputIterator last, std::false_type);

		iterator insertAux(const_iterator pos, size_type count, const value_type &value, std::true_type);
		template <class InputIterator>
		iterator insertAux(const_iterator pos, InputIterator first, InputIterator last, std::false_type);

		node_pointer create_node(const value_type &value);

	public:
		/* Member functions */
		list();
		explicit list(size_type count, const value_type& value = value_type());
		list(const list &ilist);
		list(list &&ilist);
		list(std::initializer_list<T> init);

		template <class InputIterator>
		list(InputIterator front, InputIterator back);
		~list();

		list &operator=(const list &l);
		list &operator=(list &&l);
		list &operator=(std::initializer_list<T> ilist);

		void assign(size_type count, const value_type &value);
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);
		void assign(std::initializer_list<T> ilist);

		/* Element access */
		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		iterator end() noexcept;
		const_iterator end() const noexcept;
		reverse_iterator rbegin() noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		const_reverse_iterator rend() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		const_reverse_iterator crend() const noexcept;

		/* Capacity */
		bool empty() const noexcept { return begin() == end(); }
		size_type size() const noexcept;
		size_type max_size() const noexcept { return size(); }

		/* Modifiers */
		void clear() noexcept;
		iterator insert(const_iterator pos, const value_type &value);
		iterator insert(const_iterator pos, size_type count, const value_type& value);
		iterator insert(const_iterator pos, std::initializer_list<T> ilist);
		template <class InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last);
		iterator erase(const_iterator pos);
		iterator erase(const_iterator first, const_iterator last);

		void push_back(const value_type &value);
		void push_front(const value_type &value);
		void pop_back();
		void pop_front();

		void resize(size_type count);
		void resize(size_type count, const value_type &value);

		void swap(list &ilist);

		/* Operations */
		void splice(const_iterator pos, list &ilist);
		void splice(const_iterator pos, list &ilist, const_iterator it);
		void splice(const_iterator pos, list &ilist, const_iterator first, const_iterator last);

		void merge(list &ilist);
		template <class Compare>
		void merge(list &ilist, Compare compare);

		void remove(const value_type &val);
		template <class UnaryPredicate>
		void remove_if(UnaryPredicate p);

		void reverse() noexcept;

		void unique();
		template <class BinaryPredicate>
		void unique(BinaryPredicate p);

		void sort();
		template <class Compare>
		void sort(Compare compare);
		template <class Compare>
		void sort(iterator first, iterator last, Compare comp);

		/* Non-member functions */
		friend bool operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		friend bool operator!=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		friend bool operator<(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		friend bool operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		friend bool operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		friend bool operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
		friend void swap(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
	};
}