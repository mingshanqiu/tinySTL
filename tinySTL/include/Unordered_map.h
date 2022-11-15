#pragma once

#include "Hashtable.h"

namespace tinySTL {
	template <class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>, class Alloc = Allocator>
	class unordered_map {
	public:
		typedef Key																					 key_type;
		typedef T																					 mapped_type;
		typedef tinySTL::pair<const Key, T>															 value_type;
		typedef std::size_t																			 size_type;
		typedef std::ptrdiff_t																		 difference_type;
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
		typedef unordered_map																		 Self;

		enum { INT_BUCKET_SIZE = 128 };
	protected:
		container_type cont_;

	public:
		unordered_map() {}
		explicit unordered_map(size_type bucketCount. const hasher &hash = hasher(), const key_equal &equal = key_equal())
			: cont_(bucketCount, hash, equal) 
		{ }
		
		template <class InputIterator>
		unordered_map(InputIterator first, InputIterator last, size_type bucketCount = INT_BUCKET_SIZE, const hasher &hash = hasher(), const key_equal &equal = key_equal()) : cont_(bucketCount, hash, equal) {
			while (first != last)
				insert(*first++);
		}

		~unpordered_map() {}
		unordered_map(const Self &map) : cont_(map.cont_) {}
		unordered_map(const Self &map) : cont_(map.cont_) {}
		unordered_map(Self &&map) : cont_(std::move(map.cont_)) {}

		Self& operator=(const Self &map);
		Self& operator=(Self &&map);

		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;

		local_iterator begin(size_type n) { return cont_.begin(n); }
		const_local_iterator begin(size_type n) const { return cont_.begin(n); }
		const_local_iterator cbegin(size_type n) const { return cont_.cbegin(n); }

		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;

		local_iterator end(size_type n) { return cont_.end(n); }
		const_local_iterator end(size_type n) const { return cont_.end(n); }
		const_local_iterator cend(size_type n) const { return cont_.cend(n); }

		bool empty() const noexcept;
		size_type size() const noexcept;
		size_type max_size() const noexcept;

		void clear() { cont_.clear(); }

		tinySTL::pair<iterator, bool> insert(const value_type &value);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);

		iterator erase(const_iterator pos);
		size_type erase(const key_type &key);

		void swap(Self &map);

		mapped_type& operator[](const key_type &key);
		mapped_type& at(const key_type &key);
		const mapped_type& at(const key_type &key) const;

		size_type count(const key_type &key);
		iterator find(const key_type &key);
		const_iterator find(const key_type &key) const;

		tinySTL::pair<iterator, iterator> equal_range(const key_type &key);
		tinySTL::pair<const_iterator, const_iterator> equal_range(const key_type &key) const;

		size_type bucket_count() const { return cont_.bucket_count(); }
		size_type max_bucket_count() const { return cont_.max_buckte_count(); }
		size_type bucket_size(size_type n) const { return cont_.bucket_size(n); }
		size_type bucket(const key_type &key) const { return cont_.bucket(key); }

		float load_factor() const { return cont_.load_factor(); }
		float max_load_factor() const { return cont_.max_load_factor(); }
		void max_load_factor(float ml) { cont_.max_load_factor(ml); }

		void rehash(size_type count) { cont_.rehash(count); }
		void reserve(size_type count) { cont_.rehash(count); }

		hasher hash_function() const { return cont_.hash_function(); }
		key_equal key_eq() const { return cont_.key_eq(); }

	};
}