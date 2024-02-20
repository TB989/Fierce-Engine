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
		Node(K f_key, V f_value) {
			key = f_key;
			value = f_value;
			next = nullptr;
		}

		~Node() {
			next = nullptr;
		}

		K getKey() { return key; }
		V getValue() { return value; }
		Node* nextNode() { return next; }

		void setValue(V f_value) { value = f_value; }
		void setKey(K f_key) { key = f_key; }
		void chainNode(Node* f_node) { next=f_node; }

	private:
		K key;
		V value;

		Node* next;
	};

	class Iterator {
	public:
		Iterator(HashMap* m_hashmap) {
			hashmap = m_hashmap;
			currentBucket = -1;
			currentNode = nullptr;

			logger = new Logger("HASH");
		}

		~Iterator() { delete logger; }

		void reset() {
			currentBucket = -1;
			currentNode = nullptr;
		}

		Node* advance() {
			if (currentNode != nullptr) {
				currentNode = currentNode->nextNode();
			}

			if (currentNode != nullptr) {
				return currentNode;
			}

			currentBucket++;
			findNextBucket(currentBucket);
			return currentNode;
		}

		Node* get() {
			return currentNode;
		}

	private:
		HashMap* hashmap;
		int currentBucket;
		Node* currentNode;

		Logger* logger;

		void findNextBucket(int currentBuck) {
			for (int i = currentBuck; i < hashmap->m_numBuckets; i++) {
				if (hashmap->buckets[i] != nullptr) {
					currentBucket = i;
					currentNode = hashmap->buckets[i];
					return;
				}
			}
			currentBucket = -1;
			currentNode = nullptr;
		}
	};

public:
	HashMap(int numBuckets) {
		logger = new Logger("HASH");
		m_numBuckets = numBuckets;
		size = 0;
		buckets = new Node * [numBuckets];

		for (int i = 0;i<numBuckets; i++) {
			buckets[i] = nullptr;
		}

		iterator = new Iterator(this);
	}

	~HashMap(){
		for (unsigned int i = 0; i < m_numBuckets; i++) {
			Node* currentNode = buckets[i];

			while (currentNode != nullptr) {
				Node* toDelete = currentNode;
				currentNode = currentNode->nextNode();
				delete toDelete;
			}
		}
		delete[] buckets;
	}

	void print() {
		for (int i = 0;i<m_numBuckets;i++) {
			logger->info("%p",buckets[i]);
		}
	}

	void put(const K& key, const V& value) {
		uint32_t hash = hashCompute(key) % m_numBuckets;

		//Empty bucket, create first node
		if (buckets[hash] == nullptr) {
			buckets[hash] = new HashMap::Node(key, value);
			size++;
			return;
		}

		Node* currentNode = buckets[hash];
		int counter = 1;
		while (currentNode->nextNode() != nullptr) {
			//Entry already exists
			if (currentNode->getKey() == key) {
				currentNode->setValue(value);
				return;
			}
			currentNode = currentNode->nextNode();
			counter++;
		}
		//Create new entry at end of linked list
		currentNode->chainNode(new HashMap::Node(key, value));
		size++;
	}

	void remove(const K& key) {
		uint32_t hash = hashCompute(key) % m_numBuckets;

		//Empty bucket, return
		if (buckets[hash] == nullptr) {
			return;
		}

		Node* currentNode = buckets[hash];
		Node* nextNode = currentNode->nextNode();

		//First node
		if (currentNode->getKey() == key) {
			size--;
			delete currentNode;
			buckets[hash] = nextNode;
		}

		//Other nodes
		while (nextNode != nullptr) {
			if (currentNode->getKey() == key) {
				currentNode->chainNode(nextNode->nextNode());
				size--;
				delete nextNode;
				return;
			}
			currentNode = currentNode->nextNode();
			nextNode = nextNode->nextNode();
		}
	}

	Node* get(const K& key) {
		uint32_t hash = hashCompute(key) % m_numBuckets;
		Node* currentNode = buckets[hash];

		while (currentNode != nullptr) {
			if (currentNode->getKey() == key) {
				return currentNode;
			}
			currentNode = currentNode->nextNode();
		}

		return nullptr;
	}

	bool has(const K& key) {
		uint32_t hash = hashCompute(key) % m_numBuckets;
		Node* currentNode = buckets[hash];

		while (currentNode != nullptr) {
			if (currentNode->getKey() == key) {
				return true;
			}
			currentNode = currentNode->nextNode();
		}

		return false;
	}

	int getSize() { return size; }

	Iterator* getIterator() { 
		return iterator; 
	}

	friend class Iterator;

private:
	Node** buckets;
	int m_numBuckets;
	F hashCompute;
	int size;
	Iterator* iterator;

	Logger* logger;
};