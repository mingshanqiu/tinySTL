#pragma once

#include <cstddef>



namespace tinySTL {
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	template <class Category,
		class T,
		class Distance = std::ptrdiff_t, 
		class Pointer = T * ,
		class Reference = T & >

		struct iterator {
		typedef Categroy             iterator_category;
		typedef T                    value_type;
		typedef Distance             difference_type;
		typedef Pointer              pointer;
		typedef Reference            reference;
	};

	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category        iterator_category;
		typedef typename Iterator::value_type               value_type;
		typedef typename Iterator::difference_type          difference_type;
		typedef typename Iterator::pointer                  pointer;
		typedef typename Iterator::reference                reference;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef random_accrss_iterator_tag    iterator_category;
		typedef T                             value_type;
		typedef std::ptrdiff_t                difference_type;
		typedef T*                            pointer;
		typedef T&                            reference;
	};

	/* 对const T*的偏特化 */
	template <class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag        iterator_category;
		typedef T                                 value_type;
		typedef std::ptrdiff_t                    difference_type;
		typedef T*                                pointer;
		typedef T&                                reference;
	};

	template <class T, class Distance>
	struct input_iterator {
		typedef input_iterator_tag      iterator_category;
		typedef T                       value_type;
		typedef Distance                difference_type;
		typedef T*                      pointer;
		typedef T&                      reference;
	};

	template <class T, class Distance>
	struct ouput_iterator {
		typedef output_iterator_tag    iterator_category;
		typedef T                      value_type;
		typedef Distance               difference_type;
		typedef T*                     pointer;
		typedef T&                     reference;
	};

	template <class T, class Distance>
	struct bidrectional_iterator {
		typedef bidirectional_iterator_tag  iterator_category;
		typedef T                           value_type;
		typedef Distance                    difference_type;
		typedef T*                          pointer;
		typedef T&                          reference;
	};

	template <class T, class Distance>
	struct random_access_iterator {
		typedef random_access_iterator_tag  iterator_category;
		typedef T                           value_type;
		typedef Distance                    difference_type;
		typedef T*                          pointer;
		typedef T&                          reference;
	};

	template <class InputIterator>
	inline typename tinySTL::iterator_traits<InputIterator>::iterator_category
		iterator_category(InputIterator) {
		typedef typename tinySTL::iterator_traits<InputIterator>::iterator_category category;
		return category();
	}

	template <class Iterator>
	inline typename tinySTL::iterator_traits<Iterator>::difference_type
		difference_type(Iterator) {
		return static_cast<typename iterator_traits<Iterator>::difference_type>(0);
	}

	namespace {
		template <class InputIterator, class Distance>
		inline void __advance(InputIterator &it, Distance n, tinySTL::input_iterator_tag) {
			while (n--)
				++it;
		}

		template <class Bidirectional_iterator_tag, class Distance>
		inline void __advance(Bidirectional_iterator_tag &it, Distance n, tinySTL::bidirectional_iterator_tag) {
			if (n > 0)
				while (n--) ++it;
			else
				while (n++) ++it;

		}

		template <class RanddomAccessIterator, class Distance>
		inline void __advance(RanddomAccessIterator &it, Distance n, tinySTL::random_access_iterator_tag) {
			it += n;
		}
	}

	template <class InputIterator, class Distance>
	void advance(InputIterator &it, Distance n) {
		__advance(it, n, iterator_category(it);
	}

	namespace {
		template <class InputIterator, class Distance>
		inline void __distance(InputIterator front, InputIterator back, Distance &n, tinySTL::input_iterator_tag) {
			while (front != back)
			{
				++front;
				++n;
			}
		}

		template <class RandomAccessIterator, class Distance>
		inline void __distance(RandomAccessIterator front, RandomAccessIterator back, Distance &n, tinySTL::random_access_iterator_tag) {
			n += back - front;
		}

		template <class InputIterator>
		inline typename tinySTL::iterator_traits<InputIterator>::difference_type
			__distance(InputIterator front, InputIterator back, tinySTL::input_iterator_tag) {
			auto n = difference_type(front);
			while (front != back) {
				++front;
				++n;
			}
			return n;
		}

		template <class RandomAccessIterator>
		inline typename tinySTL::iterator_traits<RandomAccessIterator>::difference_type
			__difference(RandomAccessIterator front, RandomAccessIterator back, tinySTL::random_access_iterator_tag) {
			return back - front;
		}
	}

	template <class InputIterator, class Distance>
	void distance(InputIterator front, InputIterator back, Distance &n) {
		__distance(front, back, n, iterator_category(front));
	}

	template <class InputIterator>
	inline typename tinySTL::iterator_traits<InputIterator>::difference_type
		distance(InputIterator front, InputIterator back) {
		return __distance(front, back, iterator_category(front));
	}


	template <class Iterator>
	class reverse_iterator {
	public:
		typedef typename iterator_traits<Iterator>::iterator_category           iterator_category;
		typedef typename iterator_traits<Iterator>::value_type                  value_type;
		typedef typename iterator_traits<Iterator>::difference_type             difference_type;
		typedef typename iterator_traits<Iterator>::pointer                     pointer;
		typedef typename iterator_traits<Iterator>::reference                   reference;
		typedef Iterator                                                        iterator_type;
		typedef reverse_iterator<Iterator>                                      Self;

	protected:
		iterator_type current_;

	public:
		reverse_iterator() {}
		explicit reverse_iterator(iterator_type x) : current_(x) {}
		template <class U>
		reverse_iterator(const reverse_iterator<U> &iter) : current_(iter.base()) {}
		template <class U> reverse_iterator &operator=(const reverse_iterator<U> &iter) {
			current_ = iter.base();
		}

		iterator_type base() const {
			iterator_type tmp(current_);
			return ++tmp;
		}

		reference operator*() const {
			iterator_type tmp(current_);
			return *(--tmp);
		}

		pointer operator->() const {
			iterator_type tmp(current_);
			return &(*(--tmp));
		}

		reference operatorp[](difference_type n) const {
			return *(current_ - (n + 1));
		}

		Self &operator++() {
			--current_;
			return *this;
		}

		Self &operator++(int) {
			Self tmp(*this);
			--current_;
			return tmp;
		}

		Self &operator--() {
			++current_;
			return *this;
		}

		Self &operator--(int) {
			Self tmp(*this);
			++current_;
			return tmp;
		}

		Self &operator+=(difference_type n) {
			tinySTL::advance(current_, -n);
			return *this;
		}

		Self &operator-=(difference_type n) {
			return operator+=(-n);
		}

		Self operator+(difference_type n) const {
			Self tmp(*this);
			return tmp += n;
		}

		Self operator-(difference_type n) const {
			Self tmp(*this);
			return tmp -= n;
		}
	};


	template <class Iterator_1, class Iterator_2>
	bool operator==(const reverse_iterator<Iterator_1> &lhs, const reverse_iterator<Iterator_2> &rhs) {
		return lhs, base() == rhs.base();
	}

	template <class Iterator_1, class Iterator_2>
	bool operator!=(const reverse_iterator<Iterator_1> &lhs, const reverse_iterator<Iterator_2> &rhs) {
		return !(lhs == rhs);
	}

	template <class Iterator_1, class Iterator_2>
	bool operator<(const reverse_iterator<Iterator_1> &lhs, const reverse_iterator<Iterator_2> &rhs) {
		return lhs.base() > rhs.base();
	}

	template <class Iterator_1, class Iterator_2>
	bool operator>(const reverse_iterator<Iterator_1> &lhs, const reverse_iterator<Iterator_2> &rhs) {
		return lhs.base() < rhs.base();
	}

	template <class Iterator_1, class Iterator_2>
	bool operator<=(const reverse_iterator<Iterator_1> &lhs, const reverse_iterator<Iterator_2> &rhs) {
		return !(lhs > rhs);
	}

	template <class Iterator_1, class Iterator_2>
	bool operator>=(const reverse_iterator<Iterator_1> &lhs, const reverse_iterator<Iterator_2> &rhs) {
		return !(lhs < rhs);
	}

	template <class Iterator>
	reverse_iterator<Iterator>
		operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &it) {
		reverse_iterator<Iterator> tmp(it);
		return tmp += n;
	}

	template <class Iterator_1, class Iterator_2>
	auto operator-(const reverse_iterator<Iterator_1> &lhs, const reverse_iterator<Iterator_2> &rhs) {
		return rhs.base() - lhs.base();
	}
}