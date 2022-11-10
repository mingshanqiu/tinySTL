#include "Priority_queue.h"

namespace tinySTL{
	/* Constructors ans destructor */
	template <class T, class Container, class Compare>
	priority_queue<T, Container, Compare>::priority_queue(const value_compare& compare, const container_type& cont)
		: cont_(cont), comp_(compare) {
		tinystl::make_heap(cont_.begin(), cont_.end(), compare);
	}

	template <class T, class Container, class Compare>
	priority_queue<T, Container, Compare>::priority_queue(const value_compare& compare, container_type&& cont)
		: cont_(std::move(cont)), comp_(compare) {
		tinystl::make_heap(cont_.begin(), cont_.end(), compare);
	}

	template <class T, class Container, class Compare>
	priority_queue<T, Container, Compare>::priority_queue(const priority_queue& other)
		: cont_(other.cont_), comp_(other.comp_) {}

	template <class T, class Container, class Compare>
	priority_queue<T, Container, Compare>::priority_queue(priority_queue&& other)
		: cont_(std::move(other.cont_)), comp_(std::move(other.comp_)){}

	template <class T, class Container, class Compare>
	template <class InputIterator>
	priority_queue<T, Container, Compare>::priority_queue(InputIterator first,
		InputIterator last, const value_compare& compare, const container_type& cont)
		: cont_(cont), comp_(compare) {
		cont_.insert(cont_.end(), first, last);
		tinystl::make_heap(cont_.begin(), cont_.end(), compare);
	}

	template <class T, class Container, class Compare>
	template <class InputIterator>
	priority_queue<T, Container, Compare>::priority_queue(InputIterator first, InputIterator last, const value_compare &compare, container_type && cont)
		: cont_(std::move(cont)), comp_(compare) {
		cont_.insert(cont_.end(), first, last);
		tinySTL::make_heap(cont_.begin(), cont_.end(), compare);
	}

	template <class T, class Container, class Compare>
	priority_queue<T, Container, Compare>& priority_queue<T, Container, Compare>::operator=(const priority_queue &pri_que) {
		tinySTL::swap(priority_queue(pri_que), *this);
	}

	template <class T, class Container, class Compare>
	priority_queue<T, Container, Compare>& priority_queue<T, Container, Compare>::operator=(priority_queue &&pri_que) {
		tinySTL::swap(priority_queue(std::move(pri_que)), *this);
	}


	/* Element access */
	template <class T, class Container, class Compare>
	priority_queue<T, Container, Compare>::const_reference priority_queue<T, Container, Compare>::top() const { return cont_.front(); }
	
	/* Capacity */
	template <class T, class Container, class Compare>
	bool priority_queue<T, Container, Compare>::empty() const { return cont_.empty(); }

	template <class T, class Container, class Compare>
	priority_queue<T, Container, Compare>::size_type priority_queue<T, Container, Compare>::size() const { return cont_.size(); }

	/* Modifiers */
	template <class T, class Container, class Compare>
	void priority_queue<T, Container, Compare>::push(const value_type &value) {
		cont_.insert(cont_.end(), value);
		tinySTL::push_heap(cont_.begin(), cont_.end(), comp_);
	}

	template <class T, class Container, class Compare>
	void priority_queue<T, Container, Compare>::pop() {
		tinySTL::pop_heap(cont_.begin(), cont_.end(), comp_);
	}

	template <class T, class Container, class Compare>
	void priority_queue<T, Container, Compare>::swap(priority_queue &pri_que) noexcept {
		cont_.swap(pri_que.cont_);
	}
}