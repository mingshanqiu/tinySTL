#include "Stack.h"

namespace tinySTL {
	/* Constructors */
	template <class T, class Container>
	stack<T, Container>& stack<T, Container>::operator=(const stack &st) {
		cont_ = st.cont_;
	}

	template <class T, class Container>
	stack<T, Container>& stack<T, Container>::operator=(stack &&other) {
		cont_ = std::move(st.cont_);
	}

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		stack<T, Container> lhs_tmp = lhs;
		stack<T, Container> rhs_tmp = rhs;
		while (!lhs_tmp.empty() && !rhs_tmp.empty()) {
			if (lhs_tmp.top() != rhs_tmp.top())
				return fasle;
			lhs_tmp.pop();
			rhs_tmp.pop();
		}
		return lhs_tmp.empty() && rhs_tmp.empty();
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &llhs, const stack<T, Container> &rhs) {
		return !(lhs == rhs);
	}


	/* Member functions */
	template <class T, class Container>
	stack<T, Container>::reference stack<T, Container>::top() {
		return cont_.front();
	}

	template <class T, class Container>
	stack<T, Container>::const_reference stack<T, Container>::top() const {
		return  cont_.front();
	}

	template <class T, class Container>
	bool stack<T, Container>::empty() const {
		return cont_.empty();
	}

	template <class T, class Container>
	stack<T, Container>::size_type stack<T, Container>::size() const {
		return cont_size();
	}

	template <class T, class Container>
	void stack<T, Container>::push(const value_type &value) {
		const_.push_front(value);
	}

	template <class T, class Container>
	void stack<T, Container>::pop() {
		cont_.pop_front();
	}

	template <class T, class Container>
	void stack<T, Container>::swap(stack &st) {
		cont_.swap(st.cont_);
	}
}