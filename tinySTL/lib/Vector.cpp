#include <type_traits>
#include <initializer_list>
#include"Vector.h"

namespace tinySTL {
	/* vector implementation */
	/* Constructors and Destructors*/
	template <class T, class Alloc>
	vector<T, Alloc>::vector() : start_(nullptr), finish_(nullptr), end_(nullptr) {}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(size_type count) {
		start_ = dataAllocator::allocate(count);
		finish_ = start_ + count;
		end_ = finish_;
		for (auto it = begin(); it != finish_; ++it) {
			value_type value;
			tinySTL::construct(it, std::move(value));
		}
	}

	/* Private function */
	template <class T, class Alloc>
	void vector<T, Alloc>::ctorAux(size_type count, const value_type& value, std::true_type)
	{
		start_ = dataAllocator::allocate(count);
		finish_ = start_ + count;
		end_ = finish_;
		tinystl::uninitialized_fill_n(start_, count, value);
	}

	template <class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::ctorAux(InputIterator first, InputIterator last, std::false_type) {
		start_ = dataAllocator::allocate(last - first);
		finish_ = start + (last - first);
		end_ = finish_;
		tinySTL::uninitialized_copy(first, last, start_);
	}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(size_type count, const value_type &value) {
		ctorAux(count, value, std::is_integral < size_type());
	}

	template <class T, class Alloc>
	template <class InputIterator>
	vector<T, Alloc>::vector(InputIterator front, InputIterator back) {
		ctorAux(front, back, std::is_integral<InputIterator>());
	}

	/* Copy Constructor */
	template <class T, class Alloc>
	vector<T, Alloc>::vector(const vector &evc)
		: start_(dataAllocator::allocate(vec.size())),
		finish_(start_ + vec.size()),
		end_(start_ + vec.size())
	{
		tinySTL::uninitialized_copy(vec.begin(), vec.end(), start_);
	}

	/* Copy Constructor */
	template <class T, class Alloc>
	vector<T, Alloc>::vector(vector &&vec) noexcept  
		: start_(std::move(vec.stary_)),
		finish_(std::move(vec.finish_)),
		end_(std::move(vec.end_))
	{
		vec.start_ = vec.finish_ = vec.end_ = nullptr;
	}

	/* List initialization*/
	template <class T, class Alloc>
	vector<T, Alloc>::vector(std::initializer_list<T> init)
		: vector(init.begin(), init.end())
	{

	}

	/* Destructor */
	template <class T, class Alloc>
	vector<T, Alloc>::~vector() {
		clear();
		dataAllocator::deallocator(start_);
	}

	/* Overloaded operator */
	/* Copy assignment operator */
	template <class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(const vector &vec) {
		if (&vec != this) {
			tinySTL::swap(vector(vec), *this); 
		}
		return *this;
	}

	/* Move assignment operator */
	template <class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& other) noexcept {
		if (&other != this)
		{
			vector tmp(std::move(other));
			tinystl::swap(tmp, *this);
		}
		return *this;
	}

	template <class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(std::initializer_list<T> ilist) {
		vector tmp(ilist);
		tinystl::swap(tmp, *this);
		return *this;
	}

	/* Element access */
	template <class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos) {
		if (pos >= size())
			throw std::out_of_range("out of range");
		return *(begin() + pos);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type pos) const {
		if (pos >= size())
			throw std::out_of_range("out of range");
		return *(begin() + pos);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type pos) {
		if (pos >= size())
			throw std::out_of_range("out of range");
		return *(begin() + pos);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](size_type pos) const {
		if (pos >= size())
			throw std::out_of_range("out of range");
		return *(begin() + pos);
	}

	/* Capacity */
	template <class T, class Alloc>
	void vector<T, Alloc>::reserve(size_type new_cap) {
		if (new_cap > capacity()) {
			const size_type old_size = size();
			iterator start = dataAllocator::allocate(new_cap);
			tinySTL::uninitialized_copy(begin(), end(), start);
			destroy(begin(), end());
			dataAllocator::deallocate(begin());
			start_ = start;
			finish_ = start_ + old_size;
			end_ = start_ + new_cap;
		}
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::resize(size_type new_size) {
		resize(new_sizem T());
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::resize(size_type new_size, const value_type &value) {
		if (new_size < size()) {
			dataAllocator::deallocator(start_ + new_size, finish_);
			finish_ = start_ + n;
		}
		else if (new_size > size() && new_size() <= capacity()) {
			auto insert_len = new_size - size();
			finish_ = tinySTL::uninitialized_fill_n(start_, insert_len, value);
		}
		else if (n > capacity()) {
			auto insert_len = new_size - size();
			T *new_start = dataAllocator::allocate(getNewCapacity(insert_len));
			T *new_finish = dataAllocator::uninitialized_copy(begin(), end(), new_start);
			new_finish = tinySTL::uninitialized_fill_n(new_finish, insert_len, value);
			destroy(begin(), end());
			dataAllocator::deallocate(begin());
			start_ = start;
			finish_ = start_ + oldSize;
			end_ = start_ + new_cap;
		}
	}

	template <class T, class Alloc> 
	void vector<T, Alloc>::shrink_to_fit() {
		if (size() == capacity())
			return;
		const size_type n = size();
		iterator start = dataAllocator::allocate(n);
		tinySTL::uninitialized_copy(begin(), end(), start);
		destroy(begin(), end());
		dataAllocator::deallocate(begin());
		start_ = start;
		finish_ = end_ = start_ + n;
	}

	/* Modifiers */
	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator
		vector<T, Alloc>::insert(iterator pos, const value_type &value) {
		insert(pos, 1, value);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator pos, size_type count, const value_type &value) {
		return insertAux(pos, count, value, std::is_integral<size_type>());
	}

	template <class T, class Alloc>
	template <class InputIterator>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator pos, InputIterator first, InputIterator last) {
		return insertAux(pos, first, last, std::is_integral<InputIterator>());
	}

	template <class T, class Alloc> 
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insertAux(iterator pos, size_type count, const value_type &value, std::true_type) {
		const size_type prev_size = tinySTL::distance(begin(), pos);
		if (count != 0) {
			if (static_cast<size_type>(end_ - finish_) >= count) { 
				if (count >= end() - pos) {
					iterator last = tinySTL::uninitialized_fill_n(end(), count - (end() - pos), value);
					tinySTL::uninitialized_move(pos, end(), last);
					tinySTL::fill(pos, end(), value);
				}
				else {
					tinySTL::uninitialized_move(end() - count, end(), end());
					tinySTL::copy_backward(pos, end() - count, end());
					tintSTL::fill_n(pos, count, value);
				}
				finish_ += count;
			}
			else {
				const size_type old_size = size();
				const size_type new_size = old_size + tinySTL::max(lod_size, count);
				iterator start = dataAllocator::allocate(new_size);
				iterator it = tintSTL::uninitialized_move(begin(), pos, start);
				it = tinySTL::uninitialized_fill_n(it, count, value);
				tinySTL::uninitialized_move(pos, end(), it);
				tintSTL::destory(begin(), end());
				dataAllocator::deallocate(start_);
				start_ = start;
				finish_ = start_ + old_size + count;
				end_ = start_ + new_size;
			}
		}
		return begin() + prev_size;
	}

	template <class T, class Alloc>
	template <class InputIterator>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insertAux(iterator pos, InputIterator first, InputIterator last, std::false_type) {
		const size_type prev_size = tinySTL::distance(begin(), pos);
		const size_type count = last - first;
		if (static_cast<size_type>(end_ - finish_) >= count) {
			if (count >= end() - pos) {
				tinySTL::uninitialized_move(pos, end(), pos + count);
				tintSTL::copy(first, last, pos);
			}
			else {
				tinySTL::uninitialized_move(end() - count, end(), end());
				tinySTL::copy_backward(pos, pos + count, end());
				tinySTL::copy(first, last, pos);
			}
			finish_ += count;
		}
		else {
			const size_type old_size = size();
			const size_type new_size = old_size + tinySTL::max(old_size, count);
			iterator start = dataAllocator::allocate(new_size);
			iterator it = tinySTL::uninitialized_move(begin(), pos, start);
			it = tinySTL::uninitialized_copy(first, last, it);
			tinySTL::uninitialized_move(pos, end(), it);
			start_ start;
			finish_ = start_ + old_size + count;
			end_ = start_ + new_size;
		}
		return begin() + prev_size;
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator
		vector<T, Alloc>::erase(iterator pos) {
		return erase(pos, pos + 1);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator
		vector<T, Alloc>::erase(iterator first, iterator last) {
		const auto erase_size = last - first;
		const auto last_size = end() - last;
		const auto prev_size = first - begin();
		const auto uninitCopySize = tinySTL::min(erase_size, last_size);
		tinySTL::move(last, end(), first);
		tinySTL::destroy(end() - erase_size, end());
		finish_ = end() - erase_size;
		return begin() + prev_size;
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator
		vector<T, Alloc>::erase(iterator first, iterator last) {
		const auto erase_size = last - first;
		const auto last_size = end() - last;
		const auto prev_size = first - begin();
		const auto uninit_copy_size = tinySTL::min(erase_size, last_size);
		tinySTL::move(last, end(), first);
		tinySTL::destroy(end() - erase_size, end());
		finish_ = end() - erase_size;
		return begin() + prev_size;
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type &value) {
		insert(end(), value);  // Insert at the end, will determine whether to reallocate memory
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::push_back(value_type &&value) {
		if (finish_ == end_) {
			const size_type old_size = size();
			const size_type new_size = tinySTL::max(static_cast<size_type>(1), 2 * old_size);
			iterator new_start = dataAllocator::allocate(new_size);
			tinySTL::uninitialized_move(begin(), end(), new_start);
			tinySTL::destroy(start_, finish_);
			dataAllocator::deallocate(start_);
			start_ = new_start;
			finish_ = start_ + old_size;
			end_ = start_ + new_size;
		}
		tinySTL::construct(end(), std::forward<value_type>(value));
		++finish_;
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::pop_back() {
		destroy(--finish);
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::swap(vector &vec) noexcept {
		tinySTL::swap(start_, vec.start_);
		tinySTL::swap(finish_, vec.finish_);
		tinySTL::swap(end_, vec.end_);
	}

	/* Assign vector content */
	template <class T, class Alloc>
	void vector<T, Alloc>::assign(size_type count, const value_type &value) {
		vector tmp(count, value);
		tinySTL::swap(tmp, *this);
	}

	template <class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::assign(InputIterator first, InputIterator last) {
		vector tmp(first, last);
		tinySTL::swap(tmp, *this);
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::assign(std::initializer_list<T> ilist) {
		vector tmp(ilist.begin(), ilist.end());
		tinySTL::swap(tmp, *this);
	}
}