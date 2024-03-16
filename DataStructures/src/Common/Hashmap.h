#pragma once

#include "Logger.h"

template <typename K>
struct HashCompute {
	uint32_t operator()(const K& key) const{
		return std::hash<K>() (key);
	}
};

template <typename K,typename V, class F = HashCompute<K>>
class HashMap {
public:
	class Node {
	public:
		Node(K key, V value) {
			m_key = key;
			m_value = value;
			m_next = nullptr;
		}

		~Node() {
			m_next = nullptr;
		}

		K getKey() { return m_key; }
		V getValue() { return m_value; }
		Node* nextNode() { return m_next; }

		void setValue(V value) { m_value = value; }
		void setKey(K key) { m_key = key; }
		void chainNode(Node* node) { m_next=node; }

	private:
		K m_key;
		V m_value;

		Node* m_next;
	};

	class Iterator {
	public:
		Iterator(HashMap* hashmap) {
			m_hashmap = hashmap;
			m_currentBucket = -1;
			m_currentNode = nullptr;

			m_logger = new Logger("HASH");
		}

		~Iterator() { delete m_logger; }

		void reset() {
			m_currentBucket = -1;
			m_currentNode = nullptr;
		}

		Node* advance() {
			if (m_currentNode != nullptr) {
				m_currentNode = m_currentNode->nextNode();
			}

			if (m_currentNode != nullptr) {
				return m_currentNode;
			}

			m_currentBucket++;
			findNextBucket(m_currentBucket);
			return m_currentNode;
		}

		Node* get() {
			return m_currentNode;
		}

	private:
		HashMap* m_hashmap;
		int m_currentBucket;
		Node* m_currentNode;

		Logger* m_logger;

		void findNextBucket(int currentBuck) {
			for (int i = currentBuck; i < m_hashmap->m_numBuckets; i++) {
				if (m_hashmap->m_buckets[i] != nullptr) {
					m_currentBucket = i;
					m_currentNode = m_hashmap->m_buckets[i];
					return;
				}
			}
			m_currentBucket = -1;
			m_currentNode = nullptr;
		}
	};

public:
	HashMap(int numBuckets) {
		m_logger = new Logger("HASH");
		m_numBuckets = numBuckets;
		m_size = 0;
		m_buckets = new Node * [numBuckets];

		for (int i = 0;i<numBuckets; i++) {
			m_buckets[i] = nullptr;
		}

		m_iterator = new Iterator(this);
	}

	~HashMap(){
		if (m_size!=0) {
			m_logger->warn("%d entries have not been removed.",m_size);
		}

		for (unsigned int i = 0; i < m_numBuckets; i++) {
			Node* currentNode = m_buckets[i];

			while (currentNode != nullptr) {
				Node* toDelete = currentNode;
				currentNode = currentNode->nextNode();
				delete toDelete;
			}
		}
		delete[] m_buckets;
		delete m_logger;
	}

	void print(const char* title) {
		m_logger->info("##### %s #####",title);
		for (int i = 0;i<m_numBuckets;i++) {
			m_logger->info("%p",m_buckets[i]);
		}
		m_logger->info("##########");
	}

	bool put(const K& key, const V& value) {
		uint32_t hash = m_hashCompute(key) % m_numBuckets;

		//Empty bucket, create first node
		if (m_buckets[hash] == nullptr) {
			m_buckets[hash] = new HashMap::Node(key, value);
			m_size++;
			return true;
		}

		//At least one node exists in bucket
		Node* currentNode = m_buckets[hash];
		while (currentNode->nextNode() != nullptr) {
			if (currentNode->getKey() == key) {
				currentNode->setValue(value);
				return false;
			}
			currentNode = currentNode->nextNode();
		}

		//Create new entry at end of linked list
		if (currentNode->getKey() == key) {
			currentNode->setValue(value);
			return false;
		}
		currentNode->chainNode(new HashMap::Node(key, value));
		m_size++;
		return true;
	}

	bool remove(const K& key) {
		uint32_t hash = m_hashCompute(key) % m_numBuckets;

		//Empty bucket, return
		if (m_buckets[hash] == nullptr) {
			return false;
		}

		Node* currentNode = m_buckets[hash];
		Node* nextNode = currentNode->nextNode();

		//First node
		if (currentNode->getKey() == key) {
			m_size--;
			delete currentNode;
			m_buckets[hash] = nextNode;
			return true;
		}

		//Other nodes
		while (nextNode != nullptr) {
			if (currentNode->getKey() == key) {
				currentNode->chainNode(nextNode->nextNode());
				m_size--;
				delete nextNode;
				return true;
			}
			currentNode = currentNode->nextNode();
			nextNode = nextNode->nextNode();
		}
		return false;
	}

	Node* get(const K& key) {
		uint32_t hash = m_hashCompute(key) % m_numBuckets;
		Node* currentNode = m_buckets[hash];

		while (currentNode != nullptr) {
			if (currentNode->getKey() == key) {
				return currentNode;
			}
			currentNode = currentNode->nextNode();
		}
		return nullptr;
	}

	bool has(const K& key) {
		uint32_t hash = m_hashCompute(key) % m_numBuckets;
		Node* currentNode = m_buckets[hash];

		while (currentNode != nullptr) {
			if (currentNode->getKey() == key) {
				return true;
			}
			currentNode = currentNode->nextNode();
		}

		return false;
	}

	int getSize() { 
		return m_size;
	}

	Iterator* getIterator() { 
		return m_iterator; 
	}

	friend class Iterator;

private:
	Node** m_buckets;
	int m_numBuckets;
	F m_hashCompute;
	int m_size;
	Iterator* m_iterator;

	Logger* m_logger;
};