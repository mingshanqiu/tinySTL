#pragma once

#include "Deque.h"

namespace tinySTL {
	template <class T, class Container = deque<T>>
	class queue {
	public:
		typedef Container         container_type;
		typedef typename          Container::value_type  value_type;
		typedef typename          Container::size_type  size_type;
		typedef typename          Container::refernce reference;
		typedef typename          Container::const_reference const_reference;

	private:
		container_type cont_;
	public:
		/* Constructors and Destructor */
		explicit queue(const container_type &cont) : cont_(cont) {}
		explicit queue(container_type &&cont = container_type()) : cont_(std::move(cont)) {}
		queue(const queue &que) : cont_(que.cont_) {}
		queue(queue &&que) : cont_(std::move(que.cont_)) {}
		~queue() {}

		/* Overload opertaors */
		queue &operator=(const queue &que);
		queue &operator=(queue &&que);

		friend bool operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs);
		friend bool operator!= (const queue<T, Container> &lhs, const queue<T, Container> &rhs);

		/* Member functions */
		reference front();
		const_reference front() const;

		reference back();
		const_reference back() const;

		bool empty() const;
		size_type size() const;

		void push(const value_type &value);
		void pop();

		void swap(queue &que) noexcept;
	};
}