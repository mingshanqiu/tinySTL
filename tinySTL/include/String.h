#pragma once

#include "Allocator.h"
#include "Iterator.h"

namespace tinySTL {
	template <class T, class Alloc = Allocator> 
	class string {
	private:
		/* Another encapsulation for the space configurator,
		which converts the requested address type from void* to value_type */
		typedef SimpleAlloc<value_type, Alloc> dataAllocator;
		iterator start_;     // Starting location of memory
		iterator finish_;    // Ending location of memory used
		iterator end_;       // Ending location of memory allocated

	public:
		/* Inline type definition */
		typedef char                                    value_type;
		typedef char*                                   iterator;
		typedef const char*                             const_iterator;
		typedef tinySTL::reverse_iterator<iterator>     reverse_iterator;
		typedef const reverse_iterator                  const_reverse_iterator;
		typedef char&                                   reference;
		typedef const char&                             const_reference;
		typedef std::size_t                             size_type;
		typedef std::ptrdiff_t                          difference_type;

		//npos is a static member constant value with the greatest possible value for an elemnet of type size_t.
		static const size_type npos = -1;

	public:
		/* Constructors and Destructor */
		string() : start_(nullptr), finish_(nullptr), end_(nullptr) {}
		string(const string &str);
		string(string &&str);
		string(const string &str, size_type pos, size_type len = npos);
		string(const char *s);
		string(const char *s, size_type n);
		string(size_type n, char c);
		template <class InputIterator>
		string(InputIterator first, InputIterator last);

		~string();

		/* Iterators */
		iterator begin() { return start_; }
		const_iterator begin() const { return start_; }
		const_iterator cbegin() const { return start_; }
		reverse_iterator rbegin() { return reverse_iterator(finish_); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(finish_); }
		const_reverse_iterator rcbegin() const { return const_reverse_iterator(finish_); }

		iterator end() { return finish_; }
		const_iterator end() const { return finish_; }
		const_iterator cend() const { return finish_; }
		reverse_iterator rend() { return reverse_iterator(start_); }
		const_reverse_iterator rend() const { return const_reverse_iterator(start_); }
		const_reverse_iterator rvend() const { return const_reverse_iterator(start_); }

		/* Capacity */
		size_type size() const { return finish_ - start_; }
		size_type length() const { return size(); }
		size_type capacity() const { return end_ - start_; }
		void clear(); 
		bool empty() const { return begin() == end(); }
		void resize(size_type n);
		void resize(size_type n, char c);
		void reverse(size_type n = 0);
		void shrink_to_fit();

		/* Overloaded operator */
		string &operator=(const string &str);
		string &operator=(string &&str);
		string &operator=(const char *s);
		string &operator=(char c);

		/* Element access */
		char& operator[] (size_type pos) { return *(start_ + pos); }
		const char &operator[] (size_type pos) const { return *(start_ + pos); }
		char &front() { return *(start_); }
		const char &front() const { return *(start_); }
		char &back() { return *(finish_ - 1); }
		const char &back() const { return *(finish_ - 1); }

		/* Modifiers */
		void push_back(char c);
		void pop_back();


		string &insert(size_type pos, const string &str);
		string &insert(size_type pos, const string &str, size_type subpos, size_type sublen = npos);
		string &insert(size_type pos, const char *s);
		string &insert(size_type pos, const char *s, size_type n);
		string &insert(size_type pos, size_type n, char c);
		iterator insert(iterator p, size_type n, char c);
		template <class InputIterator>
		iterator insert(iterator p, InputIterator first, InputIterator last);

		string &append(const string &str);
		string &append(const string &str, size_type subpos, size_type sublen = npos);
		string &append(const char *s);
		string &append(const char *s, size_type n);
		string &append(size_type n, char c);
		template <class InputIterator>
		string &append(InputIterator first, InputIterator last);

		string& operator+= (const string& str);
		string& operator+= (const char* s);
		string& operator+= (char c);

		string &erase(size_type pos = 0, size_type len = npos);
		iterator erase(iterator p);
		iterator erase(iterator first, iterator last);

		string &replace(size_type pos, size_type len, const string &str);
		string &replace(iterator i1, iterator i2, const string &str);
		string &replace(size_type pos, size_type len, const string &str, size_type subpos, size_type sublen = npos);
		string &replace(size_type pos, size_type len, const char *s);
		string &repalce(iterator i1, iterator i2, const char *s);
		string &replace(size_type pos, size_type len, const char *s, size_type n);
		string &replace(iterator i1, iterator i2, const char *s, size_type n);
		string &repalce(size_type pos, size_type len, size_type n, char c);
		string &replace(iterator i1, iterator i2, size_type n, char c);
		template <class InputIterator>
		string &repalce(iterator i1, iterator i2, InputIterator first, InputIterator last);

		void swap(string &str);

		/* String operations */
		size_type copy(char *s, size_type len, size_type pos = 0) const;

		size_type find(const string &str, size_type pos = 0) const;
		size_type find(const char *s, size_type pos = 0) const;
		size_type find(const char *s, size_type pos, size_type n) const;
		size_type find(char c, size_type pos = 0) const;

		size_type rfind(const string &str, size_type pos = npos) const;
		size_type rfind(const char *s, size_type pos = npos) const;
		size_type rfind(const char *s, size_type pos, size_type n) const;
		size_type rfind(char c, size_type pos = npos) const;

		size_type find_first_of(const string &str, size_type pos = 0) const;
		size_type find_first_of(const char *s, size_type pos = 0) const;
		size_type find_firts_of(const char *s, size_type pos, size_type n) const;
		size_type find_first_of(char c, size_type pos = 0) const;

		size_type find_last_of(const string &str, size_type pos = npos) const;
		size_type find_last_of(const char *s, size_type pos = npos) const;
		size_type find_last_of(const char *s, size_type pos, size_type n) const;
		size_type find_last_of(char c, size_type pos = npos) const;

		size_type find_first_not_of(const string &str, size_type pos = 0) const;
		size_type find_first_not_of(const char *s, size_type pos = 0) const;
		size_type find_first_not_of(const char *s, size_type pos, size_type n) const;
		size_type find_first_not_of(char c, size_type pos = 0) const;

		size_type find_last_not_of(const string &str, size_type pos = npos) const;
		size_type find_last_not_of(const char *s, size_type pos = npos) const;
		size_type find_last_not_of(const char *s, size_type pos, size_type n) const;
		size_type find_last_not_of(char c, size_type pos = npos) const;

		string substr(size_t pos = 0, size_t len = npos) const {
			len = changeVarWhenEuqalNPOS(len, size(), pos);
			return string(begin() + pos, begin() + pos + len);
		}

		int comapare(const string &str) const;
		int compare(size_type pos, size_type len, const string &str) const;
		int compare(size_type pos, size_type len, const string &str, size_type subpos, size_type sublen = npos) const;
		int compare(size_type pos, size_type len, const char *s) const;
		int compare(size_type pos, size_type len, const char *s, size_type n) const;

		/* Non-member function overloads */
		friend std::ostream &operator<< (std::ostream &os, const string &str);
		friend std::istream &operator>> (std::istream &is, string &str);

		friend string operator+ (const string& lhs, const string &rhs);
		friend string operator+ (const string& lhs, const char *rhe);
		friend string operator+ (const char *lhs, const string &rhs);
		friend string operator+ (const string &lhs, char rhs);
		friend string operator+ (char lhs, const string &rhs);

		friend bool operator== (const string &lhs, const string &rhs);
		friend bool operator== (const char *lhs, const string &rhs);
		friend bool operator== (const string &lhs, const char *rhs);

		friend bool operator!= (const string &lhs, const string &rhs);
		friend bool operator!= (const char *lhs, const string &rhs);
		friend bool operator!= (const string &lhs, const char *rhs);

		friend bool operator<= (const string &lhs, const string &rhs);
		friend bool operator<= (const char *lhs, const string &rhs);
		friend bool operator<= (const string &lhs, const char *rhs);

		friend bool operator>= (const string &lhs, const string &rhs);
		friend bool operator>= (const string &lhs, const string &rhs);
		friend bool operator>= (const string &lhs, const char *rhs);

		friend bool operator< (const string &lhs, const string &rhs);
		friend bool operator< (const char *lhs, const string &rhs);
		friend bool operator< (const string &lhs, const char *rhs);

		friend bool operator> (const string &lhs, const string &rhs);
		friend bool operator> (const char *lhs, const string &rhs);
		friend bool operator> (const string &lhs, const char *rhs);

		friend void swap(string &x, string &y);

		friend std::istream &getline(std::istream &is, string &str, char delim);
		friend std::istream &getline(std::istream &is, string &str);

	private:
		/* Private funtions */
		void moveData(string &str);

		template <class InputIterator>
		iterator insert_aux_copy(iterator p, InputIterator first, InputIterator last);

		iterator insert_aux_filln(iterator p, size_type n, value_type c);

		size_type getNewCapacity(size_type len) const;

		void allocateAndFillN(size_type n, char c);

		template <class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last);

		void string_aux(size_type m, char c, std::true_type);
		template <class InputIterator>
		void string_aux(InputIterator first, InputIterator last, std::false_type);

		void destoryAndDeallocate();

		size_type rfind_aux(const_iterator cit, size_type pos, size_type s_len, int cond) const;
		size_type find_aux(const_iterator cit, size_type pos, size_type s_len, size_type cond) const;

		int compare_aux(size_type pos, size_type len, const_iterator cit, size_type subpos, size_type sublen)const;

		bool isContained(char ch, const_iterator first, const_iterator last) const;

		size_type changeVarWhenEqualNPOS(size_type var, size_type minuend, size_type minue) const;
	};
}