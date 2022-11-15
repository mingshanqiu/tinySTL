#pragma once

#include <cstddef>
#include <functional>
#include "Iterator.h"
#include "Vector.h"
#include "List.h"
#include "Allocator.h"
#include "Utility.h"

/* HashTableIterator class */
namespace tinySTL {
	template<class T>
	class HashTableIterator {
	public:
		typedef forward_iterator_tag                             iterator_category;
		typedef T                                                value_type;
		typedef value_type&                                      reference;
		typedef const value_type&                                const_reference;
		typedef value_type*                                      pointer;
		typedef const value_type*                                const_pointer;
		typedef std::size_t                                      size_type;
		typedef std::ptrdiff_t                                   difference_type;
		typedef tinySTL::vector<tinySTL::list<value_type>>       bucket_type;
		typedef typename tinySTL::list<value_type>::iterator     local_iterator;
		typedef HashTableIterator  Self;

	public: 
		int bucketIdx;
		local_iterator listIt;
	
	private:	
		bucket_type &bucket;

	public:
		/* Constructs */
		HashTableIterator(int idx, const bucket_type &b) : bucketIdx(idx), bucket(const_cast<bucket_type&>(b));
		HashTableIterator(int idx, bucket_type &b, local_iterator it) : bucketIdx(idx), bucket(b), listIt(it) {}
		HashTableIterator(const Self *ht) : bucketIdx(hs.bucketIdx), listIt(hs.listIt), bucket(hs.bucket) {}

		/* Overloaded operator */
		Self &operator=(const Self &hs);
		reference operator*();
		const_reference operator*() const;
		pointer operator->();
		Self& operator++();
		Self operator++(int);
		bool operator==(const Self &hs);

		void swap(Self &hs);
 	};


	/* HashTable class */
	template <class Key,
			  class Value,
			  class KeyOfValue,
			  class Hash = std::hash<Key>,
			  class KeyEqual = std::equal_to<Key>,
			  class Alloc = Allocator>
	class HashTable {
	public:
		typedef Key                                              key_type;
		typedef Value                                            value_type;
		typedef std::size_t                                      size_type;
		typedef std::ptrdiff_t                                   difference_type;
		typedef Hash                                             hasher;
		typedef KeyEqual                                         key_equal;
		typedef value_type&                                      reference;
		typedef const value_type&                                const_reference;
		typedef value_type*                                      pointer;
		typedef const value_type*                                const_pointer;

		typedef HashTableIterator<value_type>                    iterator;
		typedef const iterator                                   const_iterator;
		typedef tinySTL::vector<tinySTL::list<value_type>>       bucket_type;
		typedef typename tinySTL::list<value_type>::iterator     local_iterator;
		typedef const local_iterator                             const_local_iterator;
		typedef HashTable                                        Self;

		enum { INT_BUCKET_SIZE = 128, INT_LOAD_FACTOR = 5 };
	
	protected:
		bucket_type bucket_;
		size_type bucketSize_;
		size_type dataSize_;
		float factor_;
		hasher hash_;
		key_equal equal_;
		size_type entryIdx_;

	public:
		/* Constructors and Destructor */
		explicit HashTable(size_type bucketSize = INT_BUCKET_SIZE, const hasher& hash = hasher(), const key_equal &equal = key_equal())
			   : bucket_(bucketSize),
			     bucketSize_(bucketSize),
			     dataSize_(0),
			     factor_(INT_LOAD_FACTOR),
			     hash_(hash),
			     equal_(equal),
			     entryIdx_(bucketSize) {}

		~HashTable() {}

		HashTable(Self &ht)
			 : bucket_(ht.bucket_),
			   bucketSize_(ht.bucketSize_),
			   factor_(ht.factor_),
			   hash_(ht.hash_),
			   equal_(ht.equal_),
			   entryIdx_(ht.entryIdx_) {}

		HashTable(Self &&ht)
			 : bucket_(std::move(ht.bucket_)),
			   bucketSize_(std::move(ht.bucketSize_)),
			   factor_(std::move(ht.factor_)),
			   hash_(std::move(hash_)),
			   equal_(std::move(ht.equal_)),
			   entryIdx_(std::move(ht.entryIdx_)) {}

		Self& operator=(const Self &ht);
		Self* operator=(Self &&ht);
		
		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;

		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;

		bool empty() const noexcept;
		size_type size() const noexcept;
		size_type max_size() const noexcept;

		void clear() { bucket_.clear(); }
		iterator insert(const value_type &value);
		iterator erase(const_iterator pos);
		iterator erase(const_iterator first, const_iterator last);
		size_type erase(const key_type &key);

		iterator find(const key_type &key);
		const_iterator find(const key_type &key) const;

		size_type count(const key_type &key) const;

		tinySTL::pair<iterator, iterator> equal_range(const key_type &key);

		void swap(Self &ht);

		local_iterator begin(size_type n);
		const_local_iterator begin(size_type n) const;
		const_local_iterator cbegin(size_type n) const;

		local_iterator end(size_type n);
		const_local_iterator end(size_type n) const;
		const_local_iterator cend(size_type n) const;

		size_type bucket_count() const;
		size_type max_bucket_count() const;
		size_type bucket_size(size_type n) const;
		size_type bucket(const key_type &key) const;

		float load_factor() const;
		float max_load_factor() const;
		void max_load_factor(float ml);

		void rehash(size_type count);
		void reserve(size_type count);

		hasher hash_function() const;
		key_equal key_eq() const;

	private:
		void updateEntryForInsert(size_type idx);
		void updateEntryForErase(size_type idx);
		void rehashIfNeed();
	};
}
