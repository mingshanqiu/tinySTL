#include"Queue.h"

namespace tinySTL {
	/* Overload opertaors */
	template <class T, class Container>
	queue<T, Container>& queue<T, Container>::operator=(const queue &que) {
		cont_ = que.cont_;
	}

	template <class T, class Container>
	queue<T, Container>& queue<T, Container>::operator=(queue &&que) {
		cont_ = std::move(que.cont_);
	}

	template <class T, class Container>
	bool operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs) {
		auto lhs_tmp(lhs);
		auto rhs_tmp(rhs);
		while (!lhs_tmp.empty() && !rhs.empty())
		{
			if (lhs_tmp.front() != rhs_tmp.front())
				return false;
			lhs_tmp.pop();
			rhs_tmp.pop();
		}
		return lhs_tmp.empty() && rhs_tmp.empty();
	}

	template <class T, class Container>
	bool operator!= (const queue<T, Container> &lhs, const queue<T, Container> &rhs) {
		return !(lhs == rhs);
	}


	/* Member functions */
	template <class T, class Container>
	queue<T, Container>::reference queue<T, Container>::front() {
		return cont_.front();
	}

	template <class T, class Container>
	queue<T, Container>::const_reference queue<T, Container>::front() const {
		return cont_.front();
	}

	template <class T, class Container>
	queue<T, Container>::reference queue<T, Container>::back() {
		return cont_.back();
	}

	template <class T, class Container>
	queue<T, Container>::const_reference queue<T, Container>::back() const {
		return cont_.back();
	}

	template <class T, class Container>
	bool queue<T, Container>::empty() const {
		return cont_.empty();
	}

	template <class T, class Container>
	queue<T, Container>::size_type queue<T, Container>::size() const {
		return cont_.size();
	}

	template <class T, class Container>
	void queue<T, Container>::push(const value_type &value) {
		cont_.push_back(value);
	}

	template <class T, class Container>
	void queue<T, Container>::pop() {
		cont_.pop_front();
	}

	template <class T, class Container>
	void queue<T, Container>::swap(queue &que) noexcept {
		cont_.swap(que.cont_);
	}
}