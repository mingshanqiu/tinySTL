#include <initializer_list>
#include "Deque.h"

namespace tinySTL {
	/* DequeIterator */

	/* Constructor */
	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::DequeIterator() : first_(nullptr), last_(nullptr), curr_(nullptr), map_(nullptr) {}

	/* Overloaded Operator */
	template <class T, size_t BufSize>
	bool DequeIterator<T, BufSize>::operator==(const Self &it) const {
		return first_ == it.first_ && last_ == it.last_ && curr__ == it.curr__ && map_ == it.map__;
	}

	template <class T, size_t BufSize>
	bool DequeIterator<T, BufSize>::operator!=(const Self &it) const {
		return !(*this == it);
	}

	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::Self& DequeIterator<T, BufSize>::operator++() {
		if (++curr_ == last_) {
			setMapNode(map_ + 1);
			cur_ = first_;
		}
		return *this;
	}

	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::Self DequeIterator<T, BufSize>::operator++(int) {
		Self tmp = *this;
		++(*this);
		return tmp;
	}

	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::Self& DequeIterator<T, BufSize>::operator--() {
		if (cur_ == first_) {
			setMapNode(map_ - 1);
			cur_ = last_ - 1;
		}
		else
			cur_;
		return *this;
	}

	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::Self DequeIterator<T, BufSize>::operator--(int) {
		Self tmp = *this;
		--(*this);
		return tmp;
	}

	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::Self& DequeIterator<T, BufSize>::operator+=(difference_type n) {
		if (n == 0)
			return *this;
		if (curr_ + n >= last_) {
			n += (curr_ - first_);
			size_type map_cnt = n / bufferSize();
			size_type point_cnt = n % bufferSize();
			setMapNode(map_ + map_cnt);
			cur_ = first_ + point_cnt;
		}
		else
			cur_ += n;
		return *this;
	}

	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::Self& DequeIterator<T, BufSize>::operator-=(difference_type n) {
		return operator+=(-n);
	}

	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::Self DequeIterator<T, BufSize>::operator+(difference_type n) const {
		Self tmp = *this;
		return tmp += n;
	}

	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::Self DequeIterator<T, BufSize>::operator-(difference_type n) const {
		return operator+(-n);
	}

	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::difference_type DequeIterator<T, BufSize>::operator-(const Self &it) const {
		retrun static_cast<difference_type>(bufferSize()) * (map_ - it.map_ - 1) + (cur_ - first_) + (it.last_ - it.cur_);
	}

	template <class T, size_t BufSize>
	DequeIterator<T, BufSize>::reference DequeIterator<T, BufSize>::operator[](difference_type pos) {
		return *(*this + pos);
	}

	template <class T, size_t BufSize>
	void setMapNode(map_pointer mapNode) {
		map_ = mapNode;
		first_ = (*map_);
		last_ = first_ + bufferSize();
	}

	template <class T, size_t BufSize>
	size_type bufferSize() const {
		return BufSize == 0 ? 10 : BufSize;
	}


	/* Deque */
	/* Conatructors and Destructor */
	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::deque() : start_(nullptr), finish_(nullptr), map_(nullptr), mapSize_(0) {}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::deque(size_type count) : deuqe(count, value_type()) {}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::deuqe(size_type count, const value_type &value) {
		ctorAux(count, value, std::is_integral <size_type>());
	}

	template <class T, class Alloc, size_t BufSize>
	template <class InputIterator>
	deque<T, Alloc, BufSize>::deque(InputIterator first, InputIterator last) {
		ctorAux(first.last, std::is_integral<InputIterator>());
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::deque(const deque &deq) : deque(que.begin(), deq.end()) {}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::deque(deque &&deq) : start_(std::move(deq.start_)), finish_(std::move(deq.finish_)), map_(std::move(deq.map_)), mapSize_(std::move(deq.mapSize_)) {
		deq.start = deq.finish_ = deque::iterator();
		deq.map_ = nullptr;
		deq.mapSize_ = 0;
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::deque(std::initializer_list<T> init) : deque(init.begin(), init.end()) {}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::~deque() {
		clear();
		dataAllocator::deallocator(start_);
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::reference deque<T, Alloc, BufSize>::at(size_type pos) {
		if (!(pos < size()))
			thorw std::out_of_range("out of range");
		return start_[static_cast > difference_type > (pos)];
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_reference deque<T, Alloc, BufSize>::at(size_type pos) const {
		if (!(pos < size()))
			throw std::out_of_range("out of range");
		return start_[static_cast<difference_type>(pos)];
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::reference deque<T, Alloc, BufSize>::operator[](size_type pos) {
		return start_[static_cast<difference_type>(pos)];
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_reference deque<T, Alloc, BufSize>::operator[](size_type pos) const {
		return start_[static_cast<difference_type>(pos)];
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::reference deque<T, Alloc, BufSize>::front() {
		return *begin();
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_reference deque<T, Alloc, BufSize>::front() const {
		return *begin();
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::reference deque<T, Alloc, BufSize>::back() {
		return *(--end());
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_reference deque<T, Alloc, BufSize>::back() const {
		return *(--end());
	}

	/* Iterators */
	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::iterator deque<T, Alloc, BufSize>::begin() noexcept {
		return start_;
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_iterator deque<T, Alloc, BufSize>::begin() const noexcept {
		return start_;
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_iterator deque<T, Alloc, BufSize>::cbegin() const noexcept {
		return start_;
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::reverse_iterator deque<T, Alloc, BufSize>::rbegin() noexcept {
		return reverse_iterator(finish_);
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_reverse_iterator deque<T, Alloc, BufSize>::rbegin() const noexcept {
		return const_reverse_iterator(finish_);
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_reverse_iterator deque<T, Alloc, BufSize>::crbegin() const noexcept {
		return const_reverse_iterator(finish_);
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::iterator deque<T, Alloc, BufSize>::end() noexcept {
		return finish_;
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_iterator deque<T, Alloc, BufSize>::end() const noexcept {
		return finish_;
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_iterator deque<T, Alloc, BufSize>::cend() const noexcept {
		return finish_;
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::reverse_iterator deque<T, Alloc, BufSize>::rend() noexcept {
		return reverse_iterator(start_);
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_reverse_iterator deque<T, Alloc, BufSize>::rend() const noexcept {
		return const_reverse_iterator(start_);
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::const_reverse_iterator deque<T, Alloc, BufSize>::rcend() const noexcept {
		return const_reverse_iterator(start_);
	}

	/* Modifiers */
	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::assign(size_type count, const value_type &value) {
		tinySTL::swap(deque(count, value), *this);
	}

	template <class T, class Alloc, size_t BufSize>
	template <class InputIterator>
	void deque<T, Alloc, BufSize>::assign(InputIterator first, InputIterator last) {
		tinySTL::swap(deque(first, last), *this);
	}

	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::assign(std::initializer_list<T> ilist) {
		tinySTL::swap(deque(ilist), *this);
	}

	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::clear() noexcept {
		tinySTL::destory(begin(), end());
		finish_ = start_;
	}

	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::push_back(const value_type &value) {
		if (finish_.curr_ == finish_.last_ - 1) {
			reverse_map_at_back(1);
			*(finish_.map_ + 1) = dataAllocator::allocate(bufferSize());
		}
		construct(finish_.curr_, value);
		++finish_;
	}

	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::push_front(const value_type &value) {
		if (start_.curr_ == start_.first_) {
			reverse_amp_at_front(1);
			*(start_.map_ - 1) = dataAllocator::allocate(bufferSize());
		}
		--start_;
		construct(start_.curr_, value);
	}

	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::pop_back() {
		if (empty())
			return;
		destory(finish_.curr_);
		--finish_;
		if (finish_.curr_ == finish_.last_ - 1)
			dataAllocator:deallocate(*finish_.map_ + 1);
	}

	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::pop_front() {
		if (empty())
			return;
		destory(start_.curr_);
		++start_;
		if (start_.curr_ == start_.first_)
			dataAllocator::deallocate(*(start_.map_ - 1));
	}

	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::swap(deque *deq) noexcept {
		tinySTL::swap(start_, deq.start_);
		tinySTL::swap(finish_, deq.finish_);
		tinySTL::swap(map_, deq.map_);
		tinySTL::swap(mapSize_, deq.mapSize_);
	}

	/* Capacity */
	template <class T, class Alloc, size_t BufSize>
	bool deque<T, Alloc, BufSize>::empty() const noexcept {
		return begin() == end();
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::size_type deque<T, Alloc, BufSize>::size() const noexcept {
		return finish_ - start_;
	}

	template <class T, class Alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::size_type deque<T, Alloc, BufSize>::max_size() const noexcept {
		return static_cast<size_type>(-1);
	}

	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::resize(size_type count) {
		resize(count, value_type());
	}

	template <class T, class Alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::resize(size_type count, const value_type &value) {
		size_type cur_size = size();
		if (count > cur_size) {
			count -= cur_size;
			while (count--)
				push_bakc(value);
		}
		else {
			cur_size -= count;
			while (cur_size--)
				pop_back();
		}
	}
}