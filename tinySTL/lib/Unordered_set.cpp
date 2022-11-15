#include "Unordered_set.h"

namespace tinySTL{
	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::Self& 
		unordered_set<Key, Hash, KeyEqual, Alloc>::operator=(const Self &set) {
		cont_ = set.cont_;
		return *this;
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::Self& 
		unordered_set<Key, Hash, KeyEqual, Alloc>::operator=(Self &&set) {
		cont_ = std::move(set.cont_);
		return *this;
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::begin() noexcept { 
		return cont_.begin();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::const_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::begin() const noexcept { 
		return cont_.begin();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::const_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::cbegin() const noexcept { 
		return cont_.cbegin();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::local_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::begin(size_type n) { 
		return cont_.begin(n);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::const_local_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::begin(size_type n) const { 
		return cont_.begin(n);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::const_local_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::cbegin(size_type n) const { 
		return cont_.cbegin(n); 
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::end() noexcept { 
		return cont_.end();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::const_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::end() const noexcept { 
		return cont_.end();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::const_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::cend() const noexcept { 
		return cont_.cend();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::local_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::end(size_type n) { 
		return cont_.end(n);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::const_local_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::end(size_type n) const { 
		return cont_.end(n);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::const_local_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::cend(size_type n) const { 
		return cont_.cend(n);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	bool unordered_set<Key, Hash, KeyEqual, Alloc>::empty() const noexcept { 
		return cont_.empty();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::size_type 
		unordered_set<Key, Hash, KeyEqual, Alloc>::size() const noexcept { 
		return cont_.size();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::size_type 
		unordered_set<Key, Hash, KeyEqual, Alloc>::max_size() const noexcept { 
		return cont_.max_size();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	void unordered_set<Key, Hash, KeyEqual, Alloc>::clear() { 
		cont_.clear();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	tinySTL::pair<typename unordered_set<Key, Hash, KeyEqual, Alloc>::iterator, bool> 
		unordered_set<Key, Hash, KeyEqual, Alloc>::insert(const value_type &value) {
		iterator it = cont_.insert(value);
		if (it == end())
			return tinySTL::make_pair(it, false);
		else
			return tinySTL::make_pair(it, true);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	template <class InputIterator>
	void unordered_set<Key, Hash, KeyEqual, Alloc>::insert(InputIterator first, InputIterator last) {
		while (first != last)
			insert(*first++);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::erase(const_iterator pos) {
		retrun cont_.erase(pos);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::size_type 
		unordered_set<Key, Hash, KeyEqual, Alloc>::erase(const key_type &key) {
		return cont_.erase(key);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	void unordered_set<Key, Hash, KeyEqual, Alloc>::swap(Self &set) {
		cont_.swap(set.cont_);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	void swap(const HashTable<Key, Hash, KeyEqual, Alloc>& lhs,
		const HashTable<Key, Hash, KeyEqual, Alloc>& rhs) {
		lhs.swap(rhs);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::size_type 
		unordered_set<Key, Hash, KeyEqual, Alloc>::count(const key_type &key) { 
		return cont_.count(key);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::find(const key_type &key) { 
		return cont_.find(key);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::const_iterator 
		unordered_set<Key, Hash, KeyEqual, Alloc>::find(const key_type &key) const { 
		return cont_.find(key);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	tinySTL::pair<typename unordered_set<Key, Hash, KeyEqual, Alloc>::iterator, 
		typename unordered_set<Key, Hash, KeyEqual, Alloc>::iterator> 
		unordered_set<Key, Hash, KeyEqual, Alloc>::equal_range(const key_type &key) { 
		return cont_.equal_range(key);
	}
	
	template <class Key, class Hash, class KeyEqual, class Alloc>
	tinySTL::pair<typename unordered_set<Key, Hash, KeyEqual, Alloc>::const_iterator,
				  typename unordered_set<Key, Hash, KeyEqual, Alloc>::const_iterator>
		unordered_set<Key, Hash, KeyEqual, Alloc>::equal_range(const key_type &key) const {
		return cont_.equal_range(key);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::size_type 
		unordered_set<Key, Hash, KeyEqual, Alloc>::bucket_count() const { 
		return cont_.bucket_count();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::size_type 
		unordered_set<Key, Hash, KeyEqual, Alloc>::max_bucket_count() const { 
		return cont_.max_bucket_count();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::size_type 
		unordered_set<Key, Hash, KeyEqual, Alloc>::bucket_size(size_type n) const { 
		return cont_.bucket_size(n);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::size_type 
		unordered_set<Key, Hash, KeyEqual, Alloc>::bucket(const key_type &key) const { 
		return cont_.bucket(key);
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::hasher 
		unordered_set<Key, Hash, KeyEqual, Alloc>::hash_function() const { 
		return cont_.hash_function();
	}

	template <class Key, class Hash, class KeyEqual, class Alloc>
	unordered_set<Key, Hash, KeyEqual, Alloc>::key_equal 
		unordered_set<Key, Hash, KeyEqual, Alloc>::key_eq() const { 
		return cont_.key_eq();
	}
}