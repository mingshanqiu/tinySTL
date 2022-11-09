#pragma once

#include "Deque.h"

namespace tinySTL {
	template <class T, class Container = deque<T>>
	class stack {
	public:
		typedef Container      container_type;
		typedef typename       Container::value_type value_type;
		typedef typename       Container::size_type size_type;
		typedef typename       Container::reference reference;
		typedef typename       Container::conste_reference const_reference;

	protected:
		container_type cont_;
	public:
		/* Constructors and Destructor */
		explicit stack(const Container &cont) : cont_(cont) {}
		explicit stack(Container &&cont = Container()) : cont_(cont) {}
		stack(const stack &st) : cont_(st.cont_) {}
		stack(stack &&st) : cont_(std::move(st:cont_)) {}
		~stack() {}  // default destructor

		/* Overloaded operators */
		stack &operator=(const stack &st);
		stack &operator=(stack &&other);
		friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs);
		friend bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs);

		/* Member functions */
		reference top();
		const_reference top() const;

		bool empty() const;
		size_type size() const;

		void push(const value_type &value);
		void pop();

		void swap(stack &st);
	};
}

