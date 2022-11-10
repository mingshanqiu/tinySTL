#include <initializer_list>
#include <utility>
#include "List.h"
#include "Construct.h"

namespace tinySTL {
	/* Private functions */
	template <class T, class Alloc>
	void list<T, Alloc>::ctroAux(size_type count, const value_type &value, std::true_type) {
		while (count--)
		{
			push_back(value);
		}
	}

	template <class T, class Alloc>
	template <class InputIterator>
	void list<T, Alloc>::ctorAux(InputIterator first, InputIterator last, std::false_type)
	{
		while (first != last)
			push_back(*first++);
	}

	template <class T, class Alloc>
	void list<T, Alloc>::assignAux(size_type count, const value_type &value, std::true_type) {
		list tmp(count, value);
		tinySTL::swap(tmp, *this);
	}

	template <class T, class Alloc>
	template <class InputIterator>
	void list<T, Alloc>::assignAux(InputIterator first, InputIterator last, std::false_type) {
		list tmp(first, last);
		tinySTL::swap(tmp, *this);
	}

	template <class T, class Alloc>
	typename list<T, Alloc>::iterator list<T, Alloc>::insertAux(const_iterator pos, size_type count, const value_type &value, std::true_type) {
		node_pointer prevNode = pos.node_->prev;
		node_pointer resultNode = prevNodel;
		while (count--)
		{
			node_pointer newNode = create_node(value);
			prevNode->next = newNode;
			newNode->prev = prevNode;
			prevNode = newNodel
		}
		prevNode->next = pos.node_;
		pos.node_->prev = prevNode;
		return iterator(resultNode->next);
	}

	template <class T, class Alloc>
	template <class InputIterator>
	typename list<T, Alloc>::iterator list<T, Alloc>::insertAux(const_iterator pos, InputIterator first, InputIterator last, std::false_type) {
		node_pointer prevNode = pos.node_->prev;
		node_pointer resultNode = prevNode;
		while (first != last) {
			node_pointer newNode create_node(*first);
			prevNode->next = newNode;
			newNode->prev = prevNode;
			prevNode = newNode;
			++first;
		}
		prevNode->next = pos.node_;
		pos.node_->prev = prevNode;
		return iterator(resultNode->next);
	}

	template <class T, class Alloc>
	typename list<T, Alloc>::node_pointer list<T, Alloc>::create_node(const value_type &val) {
		node_pointer ptr = nodeAllocator::allocate(1);
		construct(ptr, ListNode<T>(val, nullptr, nullptr));
		return ptr;
	}
	
		
	/* Member functions */
	template <class T, class Alloc>
	list<T, Alloc>::list() {
		header_.node_ = create_node(value_type());
		tail_.node_ = creater_node(value_type());
		header_.node_->next = tail_.node_;
		tail_.node_->prev = header_.node_;
	}

	template <class T, class Alloc>
	list<T, Alloc>::list(size_type count, const value_type &value) : list() {
		ctorAux(count, value, std::is_integral<size_type>());
	}

	template <class T, class Alloc>
	list<T, Alloc>::list(const list &ilist) : list(ilist.begin(), ilist.end()){

	}

	/* Move constructor */
	template <class T, class Alloc>
	list<T, Alloc>::list(list &&ilist) : list() {
		if (!ilist.empty())
		{
			header_.node_->next = std::move(ilist.header_.node_->next);
			tail_.node_->prev = std::move(ilist.tail_.node_->prev);
		}
		ilist.header_.node_->next = ilist.tail_.node_;
		ilist.tail_.node_->prev = ilist.header_.node_;
	}

	/*  List initializer constructor */
	template <class T, class Alloc>
	list<T, Alloc>::list(std::initializer_list<T> init)
		: list(init.begin(), init.end())
	{

	}

	template <class T, class Alloc>
	template <class InputIterator>
	list<T, Alloc>::list(InputIterator front, InputIterator back) : list() {
		ctroAux(front, back, std::_Is_integral<InputIterator>());
	}

	template <class T, class Alloc>
	list<T, Alloc>::~list<T, Alloc>() {
		erase(begin(), end());
		destory(header_.node_);
		destory(tail_.node_);
		nodeAllocator::deallocate(this->header_.node_);
		nodeAllocator::deallocate(this->tail_.node_);
	}
	
	template <class T, class Alloc>
	list<T, Alloc>& list<T, Alloc>::operator=(const list<T, Alloc> &l) {
		if (&l != this) {
			list<T, Alloc> tmp(1);
			tinySTL::swap(tmp, *this);
		}
		return *this;
	}

	template <class T, class Alloc>
	list<T, Alloc>& list<T, Alloc>::operator=(list<T, Alloc>&& l) {
		if (&l != this) {
			list<T, Alloc> tmp(std::move(l));
			tinySTL::swap(tmp, *this);
		}
		return *this;
	}

	template <class T, class Alloc>
	list<T, Alloc>& list<T, Alloc>::operator=(std::initializer_list<T> ilist) {
		list tmp(ilist);
		tinySTL::swap(tmp, *this);
	}

	template <class T, class Alloc>
	void list<T, Alloc>::assign(size_type count, const value_type &value) {
		assign(count, value, std::is_integral<value_type>());
	}

	template <class T, class Alloc>
	template <class InputIterator>
	void list<T, Alloc>::assign(InputIterator first, InputIterator last) {
		assign(first, last, std::is_integral<InputIterator>());
	}

	template <class T, class Alloc>
	void list<T, Alloc>::assign(std::initializer_list<T> ilist) {
		list tmp(ilist);
		tinySTL::swap(tmp, *this);
	}

	template <class T, class Alloc>
	list<T, Alloc>::iterator list<T, Alloc>::begin() noexcept { 
		return iterator(header_.node_->next);
	}

	template <class T, class Alloc>
	list<T, Alloc>::const_iterator list<T, Alloc>::begin() const noexcept { 
		return iterator(header_.node_->next);
	}

	template <class T, class Alloc>
	list<T, Alloc>::iterator list<T, Alloc>::end() noexcept { 
		return tail_;
	}

	template <class T, class Alloc>
	list<T, Alloc>::const_iterator list<T, Alloc>::end() const noexcept { 
		return tail_;
	}

	template <class T, class Alloc>
	list<T, Alloc>::reverse_iterator list<T, Alloc>::rbegin() noexcept { 
		return reverse_iterator(tail_);
	}

	template <class T, class Alloc>
	list<T, Alloc>::reverse_iterator list<T, Alloc>::rend() noexcept { 
		return reverse_iterator(header_.node_->next);
	}

	template <class T, class Alloc>
	list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rbegin() const noexcept { 
		return static_cast<const_reverse_iterator>(reverse_iterator(tail_));
	}

	template <class T, class Alloc>
	list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rend() const noexcept { 
		return static_cast<const_reverse_iterator>(reverse_iterator(header_.node_->next));
	}

	template <class T, class Alloc>
	list<T, Alloc>::const_reverse_iterator list<T, Alloc>::crbegin() const noexcept { 
		return static_cast<const_reverse_iterator>(reverse_iterator(tail_));
	}

	template <class T, class Alloc>
	list<T, Alloc>::const_reverse_iterator list<T, Alloc>::crend() const noexcept { 
		return static_cast<const_reverse_iterator>(reverse_iterator(header_.node_->next));
	}

	/* Modifiers */
	template <class T, class Alloc>
	void list<T, Alloc>::clear() noexcept { 
		erase(begin(), end());
	}

	template <class T, class Alloc>
	typename list<T, Alloc>::iterator list<T, Alloc>::insert(const_iterator pos, const value_type &value) {
		return insert(pos, 1, value);
	}

	template <class T, class Alloc>
	typename list<T, Alloc>::iterator list<T, Alloc>::insert(const_iterator pos, size_type count, const value_type& value) {
		return insertAux(pos, count, value, std::is_integral<size_type>());
	}

	template <class T, class Alloc>
	typename list<T, Alloc>::iterator list<T, Alloc>::insert(const_iterator pos, std::initializer_list<T> ilist) {
		return insert(pos, ilist.begin(), ilist.end());
	}

	template <class T, class Alloc>
	template <class InputIterator>
	typename list<T, Alloc>::iterator list<T, Alloc>::insert(const_iterator pos, InputIterator first, InputIterator last) {
		return insertAux(pos, first, last.std::is_integral<InputIterator>());
	}

	template <class T, class Alloc>
	typename list<T, Alloc>::iterator list<T, Alloc>::erase(const iterator pos) {
		iterator last = pos;
		iterator first = last++;
		return erase(first, last);
	}

	template <class T, class Alloc>
	typename list<T, Alloc>::iterator list<T, Alloc>::erase(const_iterator first, const_iterator last) {
		node_pointer resultNode = last.node_;
		first.node->prev->next = last.node_;
		last.node_->prev = first.node_->prev;
		for (iterator it = first; it != last; ++it) {
			destory(it.node_);
			nodeAllocator::deallocate(it.node_);
		}
		return iterator(resultNode);
	}

	template <class T, class Alloc>
	void list<T, Alloc>::push_back(const value_type &value) {
		insert(end(), value);
	}

	template <class T, class Alloc>
	void list<T, Alloc>::push_front(const value_type &value) {
		insert(begin(), value);
	}

	template <class T, class Alloc>
	void list<T, Alloc>::pop_back() {
		erase(--end());
	}

	template <class T, class Alloc>
	void list<T, Alloc>::pop_front() {
		erase(begin());
	}

	template <class T, class Alloc>
	void list<T, Alloc>::resize(size_type count) { 
		resize(count, value_type());
	}

	template <class T, class Alloc>
	void list<T, Alloc>::resize(size_type count, const value_type &value) {
		int n = static_cast<int>(count) - static_cast<int>(size());
		if (n > 0) {
			while (n--) 
				push_back(value);
		}
		else {
			while (n++) 
				pop_back();
		}
	}

	template <class T, class Alloc>
	void list<T, Alloc>::swap(list &ilist) {
		tinySTL::swap(header_, ilist.header_);
		tinySTL::swap(tail_, ilist.tail_);
	}

	template <class T, class Alloc>
	void list<T, Alloc>::splice(const_iterator pos, list &ilist) {
		splice(pos, ilist, ilist.begin(), ilsit.end());
	}

	template <class T, class Alloc>
	void list<T, Alloc>::splice(const_iterator pos, list &ilist, const_iterator it) {
		iterator first = it;
		iterator last = it;
		splice(pos, ilist, first, ++last);
	}

	template <class T, class Alloc>
	void list<T, Alloc>::splice(const_iterator pos, list &ilist, const_iterator first, const_iterator last) {
		if (&ilist == this)
			return;
		node_pointer prevNode = pos.node_->prev;
		node_pointer lastNode = last.node_->prev;
		first.node_->prev->next = last.node_;
		last.node_->prev = first.node_->prev;
		prevNode->next = first.node_;
		first.node_->prev = prevNode;
		lastNode->next = pos.node_;
		pos.node_->prev = lastNode;
	}

	template <class T, class Alloc>
	void list<T, Alloc>::merge(list &ilist) {
		merge(ilist, std::less<value_type>());
	}

	template <class T, class Alloc>
	template <class Compare>
	void list<T, Alloc>::merge(list &ilist, Compare compare) {
		iterator it = header_;
		iterator lhs = begin();
		iterator rhs = ilist.begin();
		while (lhs != end() && rhs != ilist.end()) {
			if (compare(*lhs, *rhs)) {
				it.node_->next = lhs.node_;
				lhs.node_->prev = it.node_;
				++lhs;
			}
			else {
				it.node_->next = rhs.node_;
				rhs.node_->prev = it.node_;
				++rhs;
			}
			++it;
		}
		if (lhs != end()) {
			it.node_->next = lhs.node_;
			lhs.node_->prev = it.node_;
		}
		else {
			it.node_->next = rhs.node_;
			rhs.node_->prev = it.node_;
			tail_.node_->prev = ilist.tail_.node_->prev;
			tail_.node_->prev->next = tail_.node_;
		}
		ilist.header_.node_->next = ilist.tail_.node_;
		ilist.tail_.node_->prev = ilist.header_.node_;
	}

	template <class T, class Alloc>
	void list<T, Alloc>::remove(const value_type &value) {
		remove_if([&val](const value_type &value) {return value == val; });
	}

	template <class T, class Alloc>
	template <class UnaryPredicate>
	void list<T, Alloc>::remove_if(UnaryPredicate p) {
		iterator first = begin();
		iterator last = end();
		while (first != last) {
			if (p(*first))
				erase(first++);
			else
				++first;
		}
	}

	template <class T, class Alloc>
	void list<T, Alloc>::reverse() noexcept {
		node_pointer prevNode = header_.node_;
		node_pointer curNode = prevNode->next;
		prevNode->next = nullptr;
		while (curNode) {
			node_pointer nextNode = curNode->next;
			curNode->next = prevNode;
			curNode->prev = nullptr;
			prevNode->prev = curNode;
			prevNode = curNode;
			curNode = nextNode;
		}
		tinySTL::swap(header_, tail_);
	}

	template <class T, class Alloc>
	void list<T, Alloc>::unique() {
		unique([](const value_type &lhs, const value_type &rhs) {return lhs == rhs; })
	}

	template <class T, class Alloc>
	template <class BinaryPredicate>
	void list<T, Alloc>::unique(BinaryPredicate p) {
		iterator first = begin();
		iterator last = end();
		iterator next = first;
		while (++next != last) {
			if (p(*first, *next))
				erase(next);
			else
				first = next;
			next = first;
		}
	}

	template <class T, class Alloc>
	void list<T, Alloc>::sort() {
		sort(begin(), end(), [](const auto &lhs, const auto &rhs) {return lhs < rhs; });
	}

	/* Merge sort of list */
	template <class T, class Alloc>
	template <class Compare>
	void list<T, Alloc>::sort(Compare compare) {
		if (size() <= 1)
			return;
		iterator it = begin();
		size_type n = size() / 2;
		while (n--)
			++it;
		list l;
		l.splice(l.begin(), *this, begin(), it);
		sort(compare);
		l.sort(compare);
		merge(l, compare);
	}

	template <class T, class Alloc>
	template <class Compare>
	void list<T, Alloc>::sort(iterator first, iterator last, Compare compare) {
		if (first == last)
			return;
		auto count = tinySTL::distance(first, last);
		if (count <= 10) {
			iterator cur = first;
			while (cur != last) {
				auto value = *cur;
				iterator prev = --cur;
				++cur;
				iterator next = ++cur;
				--cur;
				while (cur != first && comp(value, *prev)) {
					*cur = *prev;
					--cur;
					--prev;
				}
				*cur = value;
				cur = next;
			}
			return;
		}
		auto f = first;
		autp l = last;
		auto middle = first;
		--last;
		tinySTL::advance(middle, count / 2);
		if (!comp(*first, *middle))
			tinystl::swap(*first, *middle);
		if (!comp(*first, *last))
			tinystl::swap(*first, *last);
		if (!comp(*middle, *last))
			tinystl::swap(*middle, *last);
		tinystl::swap(*first, *middle);
		auto pivot = *first;
		while (first != last) {
			while (first != last && !comp(*last, pivot))
				--last;
			if (first != last)
				tinySTL::swap(*first++, *last);
			while (first != last && comp(*first, pivot))
				++first;
			if (first != last)
				tinySTL::swap(*first, *last--);
		}
		*first = pivot;
		sort(f, first, comp);
		sort(++first, l, comp);
	}

	/* Non-member functions */
	template <class T, class Alloc>
	bool operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		auto lit = lhs.begin();
		auto rit = rhs.begin();
		while (lit != lhs.end())
		{
			if (*lit != *rit)
				return false;
			++lit;
			++rit;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](const T& n1, const T& n2) {return n1 > n2; });
	}

	template <class T, class Alloc>
	bool operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
		return !(lhs > rhs);
	}

	template <class T, class Alloc>
	bool operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}