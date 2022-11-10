#pragma once

#include <functional>
#include <iostream>
#include "Vector.h"

namespace tinySTL {
	template <class T, 
		class Container = vector<T>,
		class Compare = std::less<typename Container::value_type>>
		class priority_queue {
		public:
			typedef Container container_type;
			typedef Compare value_compare;
			typedef typename Container::value_type  value_type;
			typedef typename Container::size_type size_type;
			typedef typename Container::reference reference;
			typedef typename Container::const_refernce const_reference;

		protected:
			container_type cont_;
			value_compare comp_;

		public:
			/* Constructors ans destructor */
			priority_queue(const value_compare& compare, const container_type& cont);

			/* 一般建议在声明中定义默认参数值，而不是在函数定义中，因为声明是用户可以看到的，但是定时是用户看不到的 */
			explicit priority_queue(const value_compare& compare = value_compare(), container_type&& cont = container_type());

			priority_queue(const priority_queue& other);

			priority_queue(priority_queue&& other);

			template <class InputIterator>
			priority_queue(InputIterator first, InputIterator last, const value_compare& compare, const container_type& cont);

			template <class InputIterator>
			priority_queue(InputIterator first, InputIterator last, const value_compare &compare = value_compare(), container_type && cont = container_type());

			~priority_queue() {}

			priority_queue &operator=(const priority_queue &pri_que);
			priority_queue &operator=(priority_queue &&pri_que);

			/* Element access */
			const_reference top() const;

			/* Capacity */
			bool empty() const;
			size_type size() const;

			/* Modifiers */
			void push(const value_type &value);
			void pop();
			void swap(priority_queue &pri_que) noexcept;			
	};
}