#pragma once
#include <utility>

template <typename Key, typename Value>
struct Node {
	Node(const Key& ky, const Value& val, Node* nxt) : key(ky), value(val), next(nxt) {}
	Key key;
	Value value;
	Node* next;
};

namespace {

template <typename Key>
int GetHashIndex(const Key& key, int nrBuckets) {
	return std::hash<Key>()(key) % nrBuckets;
}

template <typename Key, typename Value>
Node<Key, Value>** CreateNewValue(const Key& key, const Value& val, Node<Key, Value>** buckets, int nrBuckets) {
	const auto newHashIndex = GetHashIndex(key, nrBuckets);
	buckets[newHashIndex] = new Node<Key, Value>(key, val, buckets[newHashIndex]);
	return buckets;
}

template<typename Key, typename Value>
bool IsKeyInList(const Key& key, const Node<Key, Value>& node) {
	auto nodePtr = &node;
	while(nodePtr != nullptr) {
		if(nodePtr->key == key) {
			return true;
		}
		nodePtr = nodePtr->next;
	}
	return false;
}


template<typename Key, typename Value>
Node<Key, Value>* EraseIfKeyInList(const Key& key, Node<Key, Value>* node) {
	if(node == nullptr) {
		return node;
	}
	if(node->key == key) {
		auto nodeToDel = node;
		node = node->next;
		delete nodeToDel;
		return node;
	}
	auto currNode = node;
	for(auto nextNode = currNode->next; nextNode != nullptr; nextNode = nextNode->next) {
		if(nextNode->key == key) {
			currNode->next = nextNode->next;
			delete nextNode;
			return node;
		}
		currNode = nextNode;
	}
	return node;
}

}  // namespace

template <typename Key, typename Value>
class HashTable {
public:
	HashTable() = default;
	void Insert(const Key& key, const Value& val);
	void Erase(const Key& key);
	bool Contains(const Key& key) const;
	double LoadFactor() const;
	bool Empty() const;
private:
	bool IsRehashRequired(int newSize) const;
	void Rehash(int newNrBuckets);
	void AddNewValue(const Key& key, const Value& val);
	int m_nrBuckets = 0;
	int m_size = 0;
	Node<Key, Value>** m_buckets = nullptr;
	int m_maxLoadFactor = 5;
};

template <typename Key, typename Value>
bool HashTable<Key, Value>::Empty() const {
	return m_size == 0;
}

template <typename Key, typename Value>
double HashTable<Key, Value>::LoadFactor() const {
	return m_size * 1.0 / m_nrBuckets;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::IsRehashRequired(int newSize) const {
	return newSize > m_maxLoadFactor * m_nrBuckets;
}


template <typename Key, typename Value>
void HashTable<Key, Value>::Rehash(int newNrBuckets) {
	Node<Key, Value>** newBuckets = new Node<Key, Value>*[newNrBuckets]({});
	for(auto b = 0; b < m_nrBuckets; ++b) {
		for(auto p = m_buckets[b]; p != nullptr; ) {
			newBuckets = CreateNewValue(p->key, p->value, newBuckets, newNrBuckets);
			auto currP = p;
			p = p->next;
			delete currP;
		}
	}
	delete [] m_buckets;
	m_buckets = newBuckets;
	m_nrBuckets = newNrBuckets;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::AddNewValue(const Key& key, const Value& val) {
	m_buckets = CreateNewValue(key, val, m_buckets, m_nrBuckets);
	++m_size;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::Insert(const Key& key, const Value& val) {
	while(IsRehashRequired(m_size + 1)) {
		if(m_size == 0) {
			Rehash(1);
		} else {
			Rehash(m_nrBuckets * 2);
		}
	}
	AddNewValue(key, val);
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::Contains(const Key& key) const {
	const auto bucket = GetHashIndex(key, m_nrBuckets);
	if(m_buckets[bucket] != nullptr) {
		return IsKeyInList(key, *m_buckets[bucket]);
	}
	return false;
}


template <typename Key, typename Value>
void HashTable<Key, Value>::Erase(const Key& key) {
	const auto bucket = GetHashIndex(key, m_nrBuckets);
	m_buckets[bucket] = EraseIfKeyInList(key, m_buckets[bucket]);
	--m_size;
}
