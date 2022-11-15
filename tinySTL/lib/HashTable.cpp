#include "HashTable.h"

namespace tinySTL {
	/* HashTableIterator class */
	template<class T>
	HashTableIterator<T>::HashTableIterator(int idx, const bucket_type &b) : bucketIdx(idx), bucket(const_cast<bucket_type&>(b)) {
		if (idx >= bucket.size()) {
			idx = bucket.size();
			listIt = local_iterator();
		}
		else
			listIt = bucket[idx].begin();
	}

	template<class T>
	HashTableIterator<T>::Self& HashTableIterator<T>::operator=(const Self &hs) {
		Self tmp(hs);
		this->swap(tmp);
		return *this;
	}

	template<class T>
	void HashTableIterator<T>::swap(Self &hs) {
		tinySTL::swap(bucketId, hs.bucketIdx);
		tinySTL::swap(listIt, hs.listIt);
		tinySTL::swap(bucket, hs.bucket);
	}

	template<class T>
	HashTableIterator<T>::reference HashTableIterator<T>::operator*() {
		return *listIt;
	}

	template<class T>
	HashTableIterator<T>::const_reference HashTableIterator<T>::operator*() const {
		return *listIt;
	}

	template<class T>
	HashTableIterator<T>::pointer HashTableIterator<T>::operator->() {
		return &(*listIt);
	}

	template<class T>
	HashTableIterator<T>::Self& HashTableIterator<T>::operator++() {
		local_iterator tmp(listIt);
		if (listIt == bucket[bucketIdx].end() || (++tmp) == bucket[bucketIdx].end()) {
			++bucketIdx;
			while (bucketIdx < bucket.size() && bucket[bucketIdx].empty())
				++bucketIdx;
			if (bucketIdx < bucket.size())
				listIt = bucket[bucketIdx].begin();
			else
				listIt = local_iterator(nullptr);
		}
		else
			++listIt;

		return *this;
	}

	template<class T>
	HashTableIterator<T>::Self HashTableIterator<T>::operator++(int) {
		Self tmp(*this);
		++(*this);
		return tmp;
	}

	template<class T>
	bool HashTableIterator<T>::operator==(const Self &hs) {
		return bucketIdx == hs.bucketIdx && listIt == hs.listIt && (&bucket == &hs.bucket);
	}


	/* HashTable class */
	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::Self& 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::operator=(const Self &ht) {
		Self tmp(ht);
		this->swap(tmp);
		return *this;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::Self* 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::operator=(Self &&ht) {
		Self tmp(std::move(ht));
		this->swap(tmp);
		return *this;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::begin() noexcept { 
		return iterator(entryIdx_, bucket_);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::const_iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::begin() const noexcept { 
		return const_iterator(entryIdx_, bucket_);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::const_iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::cbegin() const noexcept { 
		return const_iterator(entryIdx_, bucket_);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::end() noexcept { 
		return iterator{ bucketSize_, bucket_ };
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::const_iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::end() const noexcept { 
		return const_iterator(bucketSize_, bucket_);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::const_iterator HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::cend() const noexcept { 
		return const_iterator{ bucketSize_, bucket_ };
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	bool HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::empty() const noexcept { 
		return dataSize == 0;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size_type 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size() const noexcept { 
		return dataSize_;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size_type 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::max_size() const noexcept { 
		return static_cast<size_type>(-1);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	bool HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::empty() const noexcept { 
		return dataSize == 0;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size_type 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size() const noexcept { 
		return dataSize_;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size_type 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::max_size() const noexcept { 
		return static_cast<size_type>(-1);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	void HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::clear() { 
		bucket_.clear();
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	typename HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::iterator
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::insert(const value_type &value) {
		iterator it = find(KeyOfValue()(value));
		if (it == end()) {
			size_type idx = hash_(KeyOfValue()(value)) % bucketSize_;
			bucket_[idx].push_front(value);
			++dataSize;
			updateEntryForInsert(idx);
			rehashIfNeed();
			return find(KeyOfValue()(value));
		}
		else {
			return it;
		}
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	typename HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::iterator
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::erase(const_iterator pos) {
		size_type idx = pos.bucketIdx;
		if (idx < size()) {
			auto listIt = bucket_[idx].erase(pos.listIt);
			--dataSize_;
			updateEntryForErase(idx);
			if (listIt == bucket_[idx].end())
				return iterator(idx, bucket_, listIt)++;
			else
				return iterator(idx, bucket_, listIt);
		}
		return iterator(idx, bucket_, pos.listIt);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	typename HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::iterator
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::erase(const_iterator first, const_iterator last) {
		while (first != last)
			erase(*first++);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	typename HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size_type
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::erase(const key_type &key) {
		size_type cnt = 0;
		size_type idx = hash_(key) % bucketSize_;
		bucket_[idx].remove_if([&cnt, &key](const value_type &value) {
			bool isSame = KeyEqual()(key, KeyOfValue()(value));
			if (isSame)
				++cnt;
			return isSame;
			});
		dataSize_ -= cnt;
		updateEntryForErase(idx);
		return cnt;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	typename HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::iterator
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::find(const key_type &key) {
		size_type idx = hash_(key) % bucketSize_;
		auto it = tinySTL::find_if(bucket_[idx].begin(), bucket_[idx].end(), [*key](const value_type &value) {
			return KeyEqual()(key, KeyOfValue()(value));
		});
		if (!it != bucket_[idx].end())
			return iterator(idx, bucket_, it);
		else
			return end();
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	typename HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::const_iterator
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::find(const key_type &key) const {
		return const_cast<Self*>(this)->find(key);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	typename HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size_type
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::count(const key_type& key) const {
		size_type idx = hash_(key) % bucketSize_;
		return tinystl::count_if(bucket_[idx].begin(), bucket_[idx].end(),
			[&key](const value_type& value) {
				return KeyEqual()(key, KeyOfValue()(value));
			});
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	void HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::swap(Self &ht) {
		tinySTL::swap(bucket_, ht.bucket_);
		tinySTL::swap(bucketSize_, ht, bucketSize_);
		tinySTL::swap(factor_, ht.factor_);
		tinySTL::swap(entryIdx_, ht.entryIdx_);
		tinySTL::swap(dataSize, ht.dataSize);
		tinySTL::swap(hash_, ht.hash_);
		tinySTL::swap(equal_, ht.equal_);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	void swap(const HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>& lhs,
		const HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>& rhs) {
		lhs.swap(rhs);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::local_iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::begin(size_type n) { 
		return bucket_[n].begin();
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::const_local_iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::begin(size_type n) const { 
		return bucket_[n], begin();
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::const_local_iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::cbegin(size_type n) const { 
		return bucket_[n].begin();
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::local_iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::end(size_type n) { 
		return bucket_[n].end();
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::const_local_iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::end(size_type n) const { 
		return bucket_[n].end();
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::const_local_iterator 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::cend(size_type n) const { 
		return bucket_[n].end();
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size_type 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::bucket_count() const { 
		return bucketSize_;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size_type 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::max_bucket_count() const { 
		return static_cast<size_type>(-1);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size_type 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::bucket_size(size_type n) const { 
		return bucket_[n].size();
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::size_type 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::bucket(const key_type &key) const { 
		return hash_(key) % bucketSize_;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	float HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::load_factor() const { 
		return size() / static_cast<float>(bucket_count());
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	float HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::max_load_factor() const { 
		return factor_;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	void HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::max_load_factor(float ml) { 
		factor_ = ml;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	tinySTL::pair<typename HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::iterator,
		typename HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::iterator>
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::equal_range(const key_type &key) {
		iterator it = find(key);
		iterator first = it;
		iterator last = ++it;
		return tinySTL::make_pair(first, last);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	void HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::rehash(size_type count) {
		bucket_type newBucket(count);
		size_type newEntryIdx_ = count;
		for (iterator it = begin(); it != end(); ++it) {
			size_type idx = hash_(KeyOfValue()(*it)) % count;
			newBucket[idx].push_front(*it);
			newEntryIdx_ = std::min(newEntry_, idx);
		}
		tinySTL::swap(bucket_, newBucket);
		bucketSize_ = count;
		entryIdx_ = newEntryIdx_;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	void HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::reserve(size_type count) { 
		rehash(std::ceil(count / max_load_factor()));
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::hasher 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::hash_function() const { 
		return hash_;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::key_equal 
		HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::key_eq() const { 
		return equal_;
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	void HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::updateEntryForInsert(size_type idx) {
		entryIdx = tinySTL::min(entryIdx_, idx);
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	void HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::updateEntryForErase(size_type idx) {
		if (idx == entryIdx_) {
			while (entryIdx_ != bucketSize_ && bucket_[enrtyIdx_].empty())
				++entryIdx;
		}
	}

	template <class Key, class Value, class KeyOfValue, class Hash, class KeyEqual, class Alloc>
	void HashTable<Key, Value, KeyOfValue, Hash, KeyEqual, Alloc>::rehashIfNeed() {
		if (load_factor() >= max_load_factor())
			rehash(bucket_count() * 5);
	}
}