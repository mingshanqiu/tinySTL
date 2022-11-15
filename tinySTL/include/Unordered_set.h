#pragma once

#include "Hashtable.h"

namespace tinySTL {
	template <class Key, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>, class Alloc = Allocator>
	class unordered_set {
	public:
		typedef Key																					 key_type;
		typedef Key																					 value_type;
		typedef std::size_t																			 size_type;
		typedef std::ptrdiff_t																		 differnce_type;
		typedef Hash																				 hasher;
		typedef KeyEqual																			 key_equal;
		typedef Alloc																				 allocator_type;
		typedef value_type&																			 reference;
		typedef const value_type&																	 const_reference;
		typedef value_type*																			 pointer;
		typedef const value_type*																	 const_pointer;
		typedef HashTable<key_type, value_type, std::_Identity<value_type>, Hash, KeyEqual, Alloc>   container_type;
		typedef typename container_type::iterator                                                    iterator;
		typedef typename container_type::const_iterator												 const_iterator;
		typedef typename container_type::local_iterator												 local_iterator;
		typedef typename container_type::const_lcoal_iterator										 const_local_iterator;
		typedef unordered_set Self;

		enum {INT_BUCKET_SIZE = 128};
		container_type cont_;

	public:
		explicit unordered_set(size_type bucketCount = INIT_BUCKET_SIZE,
			const hasher& hash = hasher(),
			const key_equal& equal = key_equal())
			: cont_(bucketCount, hash, equal)
		{  }

		template <class InputIterator>
		unordered_set(InputIterator first, InputIterator last,
			size_type bucketCount = INIT_BUCKET_SIZE,
			const hasher& hash = hasher(),
			const key_equal& equal = key_equal())
			: cont_(bucketCount, hash, equal) {
			while (first != last)
				insert(*first++);
		}

		unordered_set(const Self &set) : cont_(set.cont_) {}
		unordered_set(Self &&set) : cont_(set.cont_) {}
		~unordered_set() {}

		Self& operator=(const Self &set);
		Self& operator=(Self &&set);

		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;

		local_iterator begin(size_type n);
		const_local_iterator begin(size_type n) const;
		const_local_iterator cbegin(size_type n) const;

		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;

		local_iterator end(size_type n);
		const_local_iterator end(size_type n) const;
		const_local_iterator cend(size_type n) const;

		bool empty() const noexcept;
		size_type size() const noexcept;
		size_type max_size() const noexcept;

		void clear();

		tinySTL::pair<iterator, bool> insert(const value_type &value);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);

		iterator erase(const_iterator pos);
		size_type erase(const key_type &key);

		void swap(Self &set);

		size_type count(const key_type &key);

		iterator find(const key_type &key);
		const_iterator find(const key_type &key) const;

		tinySTL::pair<iterator, iterator> equal_range(const key_type &key);
		tinySTL::pair<const_iterator, const_iterator> equal_range(const key_type &key) const;

		size_type bucket_count() const;
		size_type max_bucket_count() const;
		size_type bucket_size(size_type n) const;
		size_type bucket(const key_type &key) const;

		hasher hash_function() const;
		key_equal key_eq() const;
	};
}