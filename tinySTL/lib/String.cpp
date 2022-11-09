#include"String.h"

#include <iostream>

namespace tinySTL {

	/* Constructors and Destructors */
	template <class T, class Alloc>
	string<T, Alloc>::string(const string& str) {
		allocateAndCopy(str.start_, str.finish_);
	}

	template <class T, class Alloc>
	string<T, Alloc>::string(string &&str) {
		moveData(str);
	}

	template <class T, class Alloc>
	string<T, Alloc>::string(const string &str, size_type pos, size_type len) {
		len = changeVarWhenEqualNPOS(len, str.size(), pos);
		allocateAndCopy(str.start_ + pos, str.start_ + pos + 1);
	}

	template <class T, class Alloc>
	string<T, Alloc>::string(const char *s) {
		allocateAndCopy(s, s + strlen(s));
	}

	template <class T, class Alloc>
	string<T, Alloc>::string(const char *s, size_type n) {
		allocateAndCopy(s, s + n);
	}

	template <class T, class Alloc>
	string<T, Alloc>::string(size_type n, char c) {
		allocateAndFillN(n, c);
	}

	template <class T, class Alloc>
	template <class InputIterator>
	string<T, Alloc>::string(InputIterator first, InputIterator last) {
		string_aux(first, last, typename std::is_integral<InputIterator>::type());
	}

	/* Destructor */
	template <class T, class Alloc>
	string<T, Alloc>::~string() {
		clear();
		dataAllocator::deallocator(start_);
	}

	/* Capacity */
	template <class T, class Alloc>
	void string<T, Alloc>::clear() {
		dataAllocator::destroy(start_, end_);
		start_ = finish_;
	}

	template <class T, class Alloc>
	void string<T, Alloc>::resize(size_type n) {
		resize(n, value_type());
	}

	template <class T, class Alloc>
	void string<T, Alloc>::resize(size_type n, char c) {
		if (n < size()) {
			dataAllocator::destory(start_ + n, finish_);
			finish_ = start_ + n;
		}
		else if (n > size() && n <= capacity()) {
			auto insert_len = n - size();
			finish_ = tinySTL::uninitialized_fill_n(finish_, instert_len, c);
		}
		else if (n > capacity()) {
			auto insert_len = n - size();
			iterator new_start = dataAllocator::allocate(getNewCapacity(insert_len));
			iterator new_finish = tinySTL::uninitialized_fill_n(finish_, instert_len, c);
			destoryAndDeallocate();
			start_ = new_start;
			finish_ = new_finish;
			end_ = start_ + n;
		}
	}

	template <class T, class Alloc>
	void string<T, Alloc>::reverse(size_type n) {
		if (n <= size())
			return;
		iterator new_start = dataAllocator::allocate(n);
		iterator new_finish_ = tinySTL::uninitialized_copy(begin(), end(), new_start);
		destoryAndDeallocate();
		start_ = new_start;
		finish_ = new_finish;
		end_ = start_ + n;
	}

	template <class T, class Alloc>
	void string<T, Alloc>::shrink_to_fit() {
		dataAllocator::deallocate(finish_, end_ - finish_);
		end_ = finish_;
	}

	/* Overloaded operator */
	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::operator=(const string &str) {
		if (this != &str) {
			destoryAndDeallocate();
			allocateAndCopy(str.start_, str.finish_);
		}
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::operator=(string &&str) {
		if (this != &str) {
			moveData(str);
		}
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>&
		string<T, Alloc>::operator=(const char *s) {
		destoryAndDeallocate();
		allocateAndCopy(s, s + strlen(s));
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::operator=(char c) {
		destoryAndDeallocate();
		allocateAndFillN(1, c);
		return *this;
	}

	/* Modifiers */
	template <class T, class Alloc>
	void string<T, Alloc>::push_back(char c) {
		insert(end(), c);
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::insert(size_type pos, const string &st) {
		insert(start_ + pos, str.begin(), str.end());
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::insert(size_type pos, const string &str, size_type subpos, size_type sublen) {
		sublen = changeVarWhenEuqalNPOS(sublen, str.size(), subpos);
		insert(begin() + pos, str.begin() + subpos, str.begin() + subpos + sublen);
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::insert(size_type pos, const char *s) {
		insert(begin() + pos, s, s + strlen(s));
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::insert(size_type pos, const char *s, size_type n) {
		insert(begin() + pos, s, s + n);
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::insert(size_type pos, size_type n, char c) {
		insert(begin() + pos, n, c);
		return *this;
	}

	template <class T, class Alloc>
	typename string<T, Alloc>::iterator string<T, Alloc>::insert(iterator p, size_type n, char c) {
		auto left_len = capacity() - size();
		if (n < left_len) {
			for (iterator it = finish_ - 1; it >= p; --it)
				*(it + n) = *(it);
			tinySTL::uninitialized_fill_n(p, n, c);
			finish_ += n;
			return (p + n);
		}
		else
			return insert_aux_filln(p, n, c);
	}

	template <class T, class Alloc>
	template <class InputIterator>
	typename string<T, Alloc>::iterator string<T, Alloc>::insert(iterator p, InputIterator first, InputIterator last) {
		insert(end(), first, last);
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::append(const string &str) {
		(*this) += str;
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::append(const string &str, size_type subpos, size_type sublen) {
		sublen = changeVarWhenEqualNPOS(sublen, str.size(), subpos);
		insert(size(), str, subpos, sublen);
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::append(const char *s) {
		(*this) += s;
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::append(const char *s, size_type n) {
		instert(size(), s, n);
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::append(size_type n, char c) {
		insert(end(), n, c);
		return *this;
	}

	template <class T, class Alloc>
	template <class InputIterator>
	string<T, Alloc>& string<T, Alloc>::append(InputIterator first, InputIterator last) {
		insert(end(), first, last);
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::operator+= (const string& str) {
		insert(size(), str);
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::operator+= (const char* s) {
		insert(size(), s);
		return *this;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::operator+= (char c) {
		insert(end(), c);
		return *this;
	}

	template <class T, class Alloc>
	void string<T, Alloc>::pop_back() {
		erase(end() - 1, end());
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::erase(size_type pos, size_type len) {
		len = changeVarWhenEuqalNPOS(len, size, pos);
		erase(begin() + pos, begin() + pos + len);
		return *this;
	}

	template <class T, class Alloc>
	typename string<T, Alloc>::iterator string<T, Alloc>::erase(iterator p) {
		return erase(p, p + 1);
	}

	template <class T, class Alloc>
	typename string<T, Alloc>::iterator string<T, Alloc>::erase(iterator first, iterator last) {
		size_type move_len = finish_ = last;
		for (auto i = 0; i != move_len; ++i)
			*(first + i) = *(last + i);
		dataAllocator::destory(first + move_len, finish_);
		finish_ = first + move_len;
		return first;
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::replace(size_type pos, size_type len, const string &str) {
		return replace(begin() + pos, begin() + pos + len, str.begin(), str.end());
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::replace(iterator i1, iterator i2, const string &str) {
		return replace(i1, i2, str.begin(), str.end());
	}
	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::replace(size_type pos, size_type len, const string &str, size_type subpos, size_type sublen) {
		sublen = changeVarWhenEqualNPOS(sublen, str.size(), subpos);
		return replace(begin() + pos, begin() + pos + len, str.begin() + subpos, str.begin() + subpos + sublen);
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::replace(size_type pos, size_type len, const char *s) {
		return replace(begin() + pos, begin() + pos + len, s, e + strlen(s));
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::repalce(iterator i1, iterator i2, const char *s) {
		return replace(i1, i2, s, s + strlen(s));
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::replace(size_type pos, size_type len, const char *s, size_type n) {
		return replace(begin() + pos, begin() + pos + len, s, s + n);
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::replace(iterator i1, iterator i2, const char *s, size_type n) {
		return replace(i1, i2, s, s + n);
	}

	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::repalce(size_type pos, size_type len, size_type n, char c) {
		return replace(begin() + pos, begin() + pos + len, n, c);
	}
	template <class T, class Alloc>
	string<T, Alloc>& string<T, Alloc>::replace(iterator i1, iterator i2, size_type n, char c) {
		auto ptr = erase(i1, i2);
		insert(ptr, n, c);
		return *this;
	}

	template <class T, class Alloc>
	template <class InputIterator>
	string<T, Alloc>& string<T, Alloc>::repalce(iterator i1, iterator i2, InputIterator first, InputIterator last) {
		auto ptr = erase(i1, i2);
		insert(ptr, first, last);
		return *this;
	}

	template <class T, class Alloc>
	void string<T, Alloc>::swap(string &str) {
		tinySTL::swap(strat_, str.start_);
		tinySTL::swap(finish_, str.finish_);
		tinySTL::swap(end_, str.end_);
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::copy(char *s, size_type len, size_type pos) const {
		auto ptr = tinySTL::uninitiaized_copy(begin() + pos, begin() + pos + len, s);
		return (size_type)(ptr - s);
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find(const string &str, size_type pos) const {
		size_type str_len = str.size();
		if (size() - pos < str_len)
			return npos;
		return find_aux(str.begin(), pos, str_len, size());
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find(const char *s, size_type pos) const {
		return find(s, pos, strlen(s));
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find(const char *s, size_type pos, size_type n) const {
		size_type str_len = strlen(s);
		return find_aux(s, pos, n, size());
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find(char c, size_type pos) const {
		if (auto cit = cbegin() + pos, cit != cend(); ++cit) {
			if (*cit == c)
				return cit - cbegin();
		}
		return npos;
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::rfind(const string &str, size_type pos) const {
		auto str_len = str.size();
		pos = changeVarWhenEqualNPOS(pos, size(), 1);
		return rfind_aux(str.begin(), pos, str_len, 0);
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::rfind(const char *s, size_type pos) const {
		pos = changeVarWhenEqualNPOS(pos, size(), 1);
		return rfind(s, pos, strlen(s));
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::rfind(const char *s, size_type pos, size_type n) const {
		auto str_len = strlen(s);
		return rfind_aux(s, pos, n, 0);
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::rfind(char c, size_type pos) const {
		pos = changeVarWhenEqualNPOS(pos, size(), 1);
		for (auto cit = cbegin() + pos, cit >= cbegin(); --cit) {
			if (*cit == c)
				return cit - cbegin();
		}
		return npos;
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_first_of(const string &str, size_type pos) const {
		return find_first_of(str.begin(), pos, str.size());
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_first_of(const char *s, size_type pos) const {
		return find_first_of(s, pos, strlen(s));
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_firts_of(const char *s, size_type pos, size_type n) const {
		for (size_type i = pos, i != size(); ++i) {
			if (isContained((*this)[i], s, s + n))
				return i;
		}
		return npos;
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_first_of(char c, size_type pos) const {
		return find(c, pos);
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_last_of(const string &str, size_type pos) const {
		pos = changeVarWhenEqualNPOS(pos, size(), 1);
		return find_last_of(str.begin(), pos, str.size());
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_last_of(const char *s, size_type pos) const {
		pos = changeVarWhenEqualNPOS(pos, size(), 1);
		return find_last_of(s, pos, strlen(s));
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_last_of(const char *s, size_type pos, size_type n) const {
		for (size_type i = pos, i > 0; --i) {
			if (isContained((*this)[i], s, s + n));
			return i;
		}
		return npos;
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_last_of(char c, size_type pos) const {
		return rfind(c, pos);
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_first_not_of(const string &str, size_type pos) const {
		return find_first_not_of(str.begin(), pos, str.size());
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_first_not_of(const char *s, size_type pos) const {
		return find_first_not_of(s, pos, strlen(s));
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_first_not_of(const char *s, size_type pos, size_type n) const {
		for (size_type i = pos; i != size(); ++i) {
			if (!isContained((*this)[i], s, s + n))
				return i;
		}
		return npos;
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_first_not_of(char c, size_type pos) const {
		for (size_type i = pos; i != size(); ++i) {
			if ((*this)[i] != c)
				return i;
		}
		return npos;
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_last_not_of(const string &str, size_type pos) const {
		pos = changeVarWhenEqualNPOS(pos, size(), 1);
		return find_last_not_of(str.begin(), pos, str.size());
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_last_not_of(const char *s, size_type pos) const {
		pos = changeVarWhenEqualNPOS(pos, size(), 1);
		return find_last_not_of(s, pos, strlen(s));
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_last_not_of(const char *s, size_type pos, size_type n) const {
		for (size_type i = pos, i >= 0; --i) {
			if (!isConstained((*this)[i], s, s + n))
				return i;
		}
		return npos;
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_last_not_of(char c, size_type pos) const {
		pos = changeVarWhenEqualNPOS(pos, size(), 1);
		for (int i = pos; i >= 0; --i) {
			if ((*this)[i] != c)
				return i;
		}
		return npos;
	}

	template <class T, class Alloc>
	int string<T, Alloc>::comapare(const string<T, Alloc> &str) const {
		return compare(0, size(), str, 0, str.size());
	}

	template <class T, class Alloc>
	int string<T, Alloc>::compare(size_type pos, size_type len, const string &str) const {
		return compare(pos, len, str, 0, str.size());
	}

	template <class T, class Alloc>
	int string<T, Alloc>::compare(size_type pos, size_type len, const string &str, size_type subpos, size_type sublen) const {
		return compare_aux(pos, len, str.begin(), subpos, sublen);
	}

	template <class T, class Alloc>
	int string<T, Alloc>::compare(size_type pos, size_type len, const char *s) const {
		return compare(pos, len, s, strlen(s));
	}

	template <class T, class Alloc>
	int string<T, Alloc>::compare(size_type pos, size_type len, const char *s, size_type n) const {
		return compare_aux(pos, len, s, 0, n);
	}

	template <class T, class Alloc>
	std::ostream& operator<< (std::ostream &os, const string<T, Alloc> &str) {
		for (const auto ch : str)
			os << ch;
		return os;
	}

	template <class T, class Alloc>
	std::istream &operator>> (std::istream &is, string<T, Alloc> &str) {
		char ch;
		size_type old_size = str.size(), index = 0;
		bool has_prev_blank = false;
		while (is.get(ch)) {
			if (isblank(ch) || ch == '\n')
				has_prev_blank = true;
			else
				break;
		}
		is.putback(ch);
		str.clear();
		while (is.get(ch)) {
			if (ch != EOF && !isblank(ch) && ch != '\n')
				str.push_back(ch);
			else
				break;
		}
		return is;
	}

	template <class T, class Alloc>
	string<T, Alloc> operator+ (const string<T, Alloc>& lhs, const string<T, Alloc> &rhs) {
		string res(lhs);
		return res += rhs;
	}

	template <class T, class Alloc>
	string<T, Alloc> operator+ (const string<T, Alloc>& lhs, const char *rhe) {
		string res(lhs);
		return res += rhs;
	}

	template <class T, class Alloc>
	string<T, Alloc> operator+ (const char *lhs, const string<T, Alloc> &rhs) {
		string res(lhs);
		return res += rhs;
	}

	template <class T, class Alloc>
	string<T, Alloc> operator+ (const string<T, Alloc> &lhs, char rhs) {
		string res(lhs);
		return res += rhs;
	}

	template <class T, class Alloc>
	string<T, Alloc> operator+ (char lhs, const string<T, Alloc> &rhs) {
		string res(1, lhs);
		return res += rhs;
	}

	template <class T, class Alloc>
	bool operator== (const string<T, Alloc> &lhs, const string<T, Alloc> &rhs) {
		if (lhs.size() --rhs.size*()) {
			for (auto cit1 = lhs.cbegin(); cit2 = rhs.cbegin();
				cit1 != lhs.cend() && cit2 != rhs.cend();
				++cit1, ++cit2) {
				if (*cit1 != *cit2)
					return false;
			}
			return true;
		}
		return false;
	}

	template <class T, class Alloc>
	bool operator== (const char *lhs, const string<T, Alloc> &rhs) {
		return rhs == lhs;  
	}

	template <class T, class Alloc>
	bool operator== (const string<T, Alloc> &lhs, const char *rhs) {
		size_type len = strlen(rhs);
		if (lhs.size() == len) {
			const char *p = rhs;
			for (const_iterator cit = lhs.cbegin(); cit != lhs.cend() && p != rhs + len; ++cit, ++p) {
				if (*cit != *p)
					return false;
			}
			return true;
		}
		return false;
	}

	template <class T, class Alloc>
	bool operator!= (const string<T, Alloc>& lhs, const string<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator!= (const char*   lhs, const string<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator!= (const string<T, Alloc>& lhs, const char*   rhs) {
		return !(lhs == rhs);
	}

	namespace {
		template<class Iterator_1, class Iterator_2>
		bool lessEqual_aux(Iterator_1 first_1, Iterator_1 last_1, Iterator_2 first_2, Iterator_2 last_2) {
			for (; first_1 != last_1 && first_2 != last_2; ++first_1, ++first_2) {
				if (*first_1 < *first_2)
					return true;
				else if (*first_1 > *first_2)
					return false;
			}
			if ((first_1 == last_1 && first_2 == last_2) || (first_1 == last_1))
				return true;
			else
				return false;
		}
	}

	template <class T, class Alloc>
	bool operator<= (const string<T, Alloc> &lhs, const string<T, Alloc> &rhs) {
		return lessEqual_aux(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
	}

	template <class T, class Alloc>
	bool operator<= (const char *lhs, const string<T, Alloc> &rhs) {
		return lessEqual_aux(lhs, lhs + strlen(lhs), rhs.cbegin(), rhs.cend());
	}

	template <class T, class Alloc>
	bool operator<= (const string<T, Alloc> &lhs, const char *rhs) {
		return lessEqual_aux(lhs.cebgin(), lhs.cend(), rhs, rhs + strlen(rhs));
	}

	namespace {
		template<class Iterator_1, class Iterator_2>
		bool greaterEqual_aux(Iterator_1 first_1, Iterator_1 last_1, Iterator_2 first_2, Iterator_2 last_2) {
			for (; first_1 != last_1 && first_2 != last_2; ++first_1, ++first_2) {
				if (*first_1 > *first_2)
					returnn true;
				else if (*first_1 > *first_2)
					return false;
			}
			if ((first_1 == last_1 && first_2 == last_2) || (first_2 == last_2)
				return true;
			else
				return false;
		}
	}

	template <class T, class Alloc>
	bool operator>= (const string<T, Alloc> &lhs, const string<T, Alloc> &rhs) {
		return greaterEqual_aux(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
	}

	template <class T, class Alloc>
	bool operator>= (const string<T, Alloc> &lhs, const string<T, Alloc> &rhs) {
		return greaterEqual_aux(lhs, lhs + strlen(lhs), rhs.cbegin(), rhs.cend());
	}

	template <class T, class Alloc>
	bool operator>= (const string<T, Alloc> &lhs, const char *rhs) {
		return greaterEqual_aux(lhs.cbegin(), lhs.cend(), rhs, rhs + strlen(rhs));
	}

	template <class T, class Alloc>
	bool operator< (const string<T, Alloc> &lhs, const string<T, Alloc> &rhs) {
		return !(lhs >= rhs);
	}

	template <class T, class Alloc>
	bool operator< (const char *lhs, const string<T, Alloc> &rhs) {
		return !(lhs >= rhs);
	}

	template <class T, class Alloc>
	bool operator< (const string<T, Alloc> &lhs, const char *rhs) {
		return !(lhs >= rhs);
	}

	template <class T, class Alloc>
	bool operator> (const string<T, Alloc> &lhs, const string<T, Alloc> &rhs) {
		return !(lhs <= rhs);
	}

	template <class T, class Alloc>
	bool operator> (const char *lhs, const string<T, Alloc> &rhs) {
		return !(lhs <= rhs);
	}

	template <class T, class Alloc>
	bool operator> (const string<T, Alloc> &lhs, const char *rhs) {
		return !(lhs <= rhs);
	}

	template <class T, class Alloc>
	void swap(string<T, Alloc> &x, string<T, Alloc> &y) {
		x.swap(y);
	}

	template <class T, class Alloc>
	std::istream &getline(std::istream &is, string<T, Alloc> &str, char delim) {
		char ch;
		str.clear();
		while (is.get(ch)) {
			if (ch == delim)
				break;
			else
				str.push_back(ch);
		}
		return is;
	}

	template <class T, class Alloc>
	std::istream &getline(std::istream &is, string<T, Alloc> &str) {
		return getline(is, str, '\n');
	}


	/* Private funtions */
	template <class T, class Alloc>
	void string<T, Alloc>::moveData(string &str) {
		strart_ = str.start_;
		finish_ = str.finish_;
		end_ = str.end_;
		str.start_ = str.finish_ = str.end_ = 0;
	}

	template <class T, class Alloc>
	template <class InputIterator>
	string<T, Alloc>::iterator string<T, Alloc>::insert_aux_copy(iterator p, InputIterator first, InputIterator last) {
		size_type insert_len = last - first;
		auto new_capacity = getNewCapacity(insert_len);
		iterator new_start = dataAllocator::allocate(new_capacity);
		iterator new_finish = tinySTL::uninitialized_copy(start_, p, new_start);
		new_finish = tinySTL::uninitialized_copy(first, last, new_finish);
		auto res = new_finish;
		new_finish = tinySTL::uninitialized_copy(p, finish_, new_finish);
		destoryAndDeallocate();
		start_ = new_start;
		finish_ = new_finish_;
		end_ = start_ + new_capacity;
		return res;
	}

	template <class T, class Alloc>
	string<T, Alloc>::iterator string<T, Alloc>::insert_aux_filln(iterator p, size_type n, value_type c) {
		auto new_capacity = getNewCapacity(n);
		iterator new_start = dataAllocator::allocate(new_capacity);
		iterator new_finish = tinySTL::uninitialized_copy(start_, p, new_start);
		new_finish = tinySTL::uninitialized_fill_n(new_finish, n, c);
		auto res = new_finish;
		new_finish = tinySTL::uninitialized_copy(p, finish_, new_finish);
		destoryAndDeallocate();
		start_ = new_start;
		finish_ = new_finish;
		end_ = start_ + new_capacity;
		return res;
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::getNewCapacity(size_type len) const {
		size_type old_capacity = end_ - start_;
		auto res = tinySTL::max(old_capacity.len);
		auto new_capacity = old_capacity + res;
		return new_capacity;
	}

	template <class T, class Alloc>
	void string<T, Alloc>::allocateAndFillN(size_type n, char c) {
		start_ = dataAllocator::allocate(n);
		finish_ = tinySTL::uninitialized_fill_n(start_, n, c);
		end_ = finish_;
	}

	template <class T, class Alloc>
	template <class InputIterator>
	void string<T, Alloc>::allocateAndCopy(InputIterator first, InputIterator last) {
		start_ = dataAllocator::allocate(last - first);
		finish_ = tinySTL::uninitialized_copy(first, last, start_);
		end_ = finish_;
	}

	template <class T, class Alloc>
	void string<T, Alloc>::string_aux(size_type m, char c, std::true_type) {
		allocateAndFillN(n, c);
	}

	template <class T, class Alloc>
	template <class InputIterator>
	void string<T, Alloc>::string_aux(InputIterator first, InputIterator last, std::false_type) {
		allocateAndCopy(first, last);
	}

	template <class T, class Alloc>
	void string<T, Alloc>::destoryAndDeallocate() {
		dataAllocator::destory(start_, finish_);
		dataAllocator::deallocate(start_, end_ - star_);
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::rfind_aux(const_iterator cit, size_type pos, size_type s_len, int cond) const {
		for (int i = pos + s_len; i >= cond; --i) {
			for (int j = 0; j != s_len; ++j) {
				if (*(begin*() + i + j) != cit[j])
					break;
			}
			if (j == s_len)
				return i;
		}
		return npos;
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::find_aux(const_iterator cit, size_type pos, size_type s_len, size_type cond) const {
		for (size_type i = pos; i != cond; ++i) {
			for (size_type j = 0; j != s_len; ++j) {
				if (*(begin() + i + j) != cit[j])
					break;
			}
			if (j == s_len)
				return i;
		}
		return npos;
	}

	template <class T, class Alloc>
	int string<T, Alloc>::compare_aux(size_type pos, size_type len, const_iterator cit, size_type subpos, size_type sublen) const {
		for (size_type i = 0, j = 0; i != len && j != sublen; ++i, ++j) {
			if ((*this)[pos + i] < cit[subpos + j])
				return -1;
			else if ((*this)[pos + i] > cit[subpos + j])
				return 1;
		}
		if (i == len && j == sublen)
			return 0;
		else if (i == len)
			return -1;
		else
			return 1;
	}

	template <class T, class Alloc>
	bool string<T, Alloc>::isContained(char ch, const_iterator first, const_iterator last) const {
		for (auto cit = first; cit != lastl ++cit) {
			if (*cit == ch)
				return true;
		}
		return false;
	}

	template <class T, class Alloc>
	string<T, Alloc>::size_type string<T, Alloc>::changeVarWhenEqualNPOS(size_type var, size_type minuend, size_type minue) const {
		return (var == npos ? minuend - minue : var);
	}
}