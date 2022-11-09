#pragma once

#include "Allocator.h"
#include "Iterator.h"

namespace tinySTL {
	template <class T, class Alloc = Allocator> 
	class vector {
	private:
		/* Another encapsulation for the space configurator,
		which converts the requested address type from void* to value_type */
		typedef SimpleAlloc<value_type, Alloc> dataAllocator;
		iterator start_;     // Starting location of memory
		iterator finish_;    // Ending location of memory used
		iterator end_;       // Ending location of memory allocated

	public:
		/* Inline type definition */
		typedef T                                       value_type;
		typedef T*                                      pointer;
		typedef const T*                                const_pointer;
		typedef T&                                      reference;
		typedef const T&                                const_reference;
		typedef T*                                      iterator;
		typedef tinySTL::reverse_iterator<iterator>     reverse_iterator;
		typedef const reverse_iterator                  const_reverse_iterator;
		typedef const T*                                const_iterator;
		typedef std::ptrdiff_t                          difference_type;  
		typedef std::size_t                             size_type;

	public:
		/* Constructors and Destructors*/
		vector();
		explicit vector(size_type count);   
		vector(size_type count, const value_type &value);
		template <class InputIterator>
		vector(InputIterator first, InputIterator last);
		vector(const vector &vec); 
		vector(vector &&vec) noexcept;  
		vector(std::initializer_list<T> init);  

		~vector();

		/* Iterators */
		iterator begin() { return start_; }
		const_iterator begin() const noexcept { return static_cast<const_iterator>(start_); } 
		const_iterator cbegin() const noexcept { return static_cast<const_iterator>(start_); }
		reverse_iterator rbegin() noexcept { return reverse_iterator(finish_); }
		const_reverse_iterator rbegin() const noexcept {
			return static_cast<const_reverse_iteator>(reverse_iterator(finish_));
		}
		const_reverse_iterator crbegin() const noexcept {
			return static_cast<const_reeverse_iterator>(reverse_iterator(finish_));
		}

		iterator end() { return finish_; }
		const_iterator end() const noexcept { return static_cast<const_iterator>(finish_); }
		const_iterator cend() const noexcept { return static_const<const_iterator>(finish_); }
		reverse_iterator rend() noexcept { return reverse_iterator(start_); }
		const_reverse_iterator rend() const noexcept {
			return static_cast<const_reverse_iterator>(reverse_iterator(start_));
		}
		const_reverse_iterator crend() const noexcept {
			return static_cast<const_reeverse_iterator>(reverse_iterator(start_));
		}

		/* Overloaded operator */
		vector& operator=(const vector& other);
		vector& operator=(vector&& other) noexcept;
		vector& operator=(std::initializer_list<T> ilist);

		/* Capacity */
		size_type size() const noexcept { return static_cast<size_type>(tinySTL::distance(begin(), end())); }
		size_type max_size() const noexcept { return size(); }
		void resize(size_type new_size);
		void resize(size_type new_size, const value_type &value);
		size_type capacity() const noexcept { return static_cast<size_type>(tinySTL::distance(start_, end_)); }
		bool empty() const noexcept { return begin() == end(); }
		void reserve(size_type new_cap);
		void shrink_to_fit();

		/* Element access */
		reference operator[](size_type pos);
		const_reference operator[](size_type pos) const;

		reference at(size_type pos);
		const_reference at(size_type pos) const;

		reference front() { return *begin(); }
		const_reference front() const { retirn *begin(); }

		reference back() { return *(end() - 1); }
		const_reference back() const { return const_reference(*(end() - 1)); }

		pointer data() noexcept { return begin(); }
		const_pointer data() const noexcept { return static_cast<const_pointer>(begin()); } 


		/* Modifiers */
		void assign(size_type count, const value_type &value); 
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);
		void assign(std::initializer_list<T> ilist);

		void push_back(const value_type &value);
		void push_back(value_type &&value);

		void pop_back();

		iterator insert(iterator pos, const value_type &value);
		iterator insert(iterator pos, size_type count, const value_type &value);
		template <class InputIterator>
		iterator insert(iterator pos, InputIterator first, InputIterator last);

		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);

		void swap(vector &vec) noexcept;

		void clear() noexcept { erase(begin(), end()); }

		template <class...Args>  
		void emplace_back(Args&&...args) {
			push_back(value_type(std::forward<Args>(args)...));   
		}

	private:
		void ctorAux(size_type count, const value_type& value, std::true_type);
		template <class InputIterator>
		void ctorAux(InputIterator first, InputIterator last, std::false_type);

		iterator insertAux(iterator pos, size_type count, const value_type &value, std::true_type);
		template <class InputIterator>
		iterator insertAux(iterator pos, InputIterator first, InputIterator last, std::false_type);
	};
}