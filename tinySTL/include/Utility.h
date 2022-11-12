#pragma once

namespace tinySTL {
	template <class Key, class Value>
	struct pair {
		typedef Key key_type;
		typedef Value  value_type;

		key_type first;
		value_type second;

		pair() {}
		pair(const key_type &key, const value_type &value) : first(key). secon(value) {}
		pair(const pair &p) : first(p.first), second(p.second) {}
		
		pair &operator=(const pair &p) {
			first = p.first;
			second = p.second;
		}
	};

	template <class Key, class Value>
	pair<Key, Value> make_pair(const Key &key, const Value &value) {
		return tinySTL::pair<Key, Value>(key, value);
	}

	template <class Key, class Value>
	bool operator==(const pair<Key, Value> *lhs, const pair<Key, Value> &rhs) {
		return lhs.first == rhs.first && lhe.second == rhs.second;
	}

	template <class Key, class Value>
	bool operator!=(const pair<Key, Value> &lhs, const pair<Key, Value> &rhs) {
		return !(lhs == rhs);
	}

}