#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

typedef int32_t int32;

template<class T>
class List
{
private:
	typedef T      Data;
	typedef size_t size_type;

	struct Node
	{
		Node* next;
		Node* prev;
		Data data;
	};

public:
	struct ConstIterator
	{
		ConstIterator() {}
		ConstIterator(Node* at_) : at(at_) {}
		const Data& operator*() const { return at->data; }
		bool operator !=(const ConstIterator& v) const { return at != v.at; }
		bool operator ==(const ConstIterator& v) const { return at == v.at; }
		ConstIterator operator++() { /*assert(at != tail);*/ at = at->next; return *this; } // prefix
		ConstIterator operator++(int32 unused_) { Iterator pitr = *this; ++(*this); return pitr; } // postfix
		ConstIterator operator--() { /*assert(at->prev != head);*/  at = at->prev; return *this; } // prefix
		ConstIterator operator--(int32 unused_) { Iterator pitr = *this; ++(*this); return pitr; } // postfix

		Node* at;
	};

	struct Iterator
	{
		Iterator() {}
		Iterator(Node* at_) : at(at_) {}
		Data& operator*() { return at->data; }
		bool operator !=(const Iterator& v) const { return at != v.at; }
		bool operator ==(const Iterator& v) const { return at == v.at; }
		Iterator operator++() { /*assert(at != tail);*/ at = at->next; return *this; } // prefix
		Iterator operator++(int32 unused_) { Iterator pitr = *this; ++(*this); return pitr; } // postfix
		Iterator operator--() { /*assert(at->prev != head);*/  at = at->prev; return *this; } // prefix
		Iterator operator--(int32 unused_) { Iterator pitr = *this; ++(*this); return pitr; } // postfix

		Node* at;
	};

	List() { init_list(); }
	~List() { clear(); if (head) free(head); }

	List(const List<T>& v) { init_list(); copy(v); }
	List<T>& operator=(const List<T>& v) { clear(); copy(v); return *this; }
	List(List<T>&& v)
		: size(v.size), head(v.head), tail(v.tail)
	{
		v.size = 0;
		v.head = nullptr;
		v.tail = nullptr;
	}

	List<T>& operator=(List<T>&& v)
	{
		clear();
		free(head);
		head = v.head;
		tail = v.tail;
		size = v.size;
		v.head = nullptr;
		v.tail = nullptr;
		v.size = 0;
		return *this;
	}

private:
	void copy(const List<T>& source)
	{
		List<T>::ConstIterator itr = --source.end();
		for (; itr != source.begin(); --itr)
		{
			push_front(*itr);
		}
		assert(itr == source.begin());
		push_front(*itr);
	}

	void init_list()
	{
		size_type node_bytes = sizeof(Node);
		head = alloc_memory(2 * node_bytes);
		tail = (Node*)((char*)head + node_bytes);
		head->next = head->prev = tail;
		tail->next = tail->prev = head;
		size = 0;
	}

	Node* alloc_memory(size_type size)
	{
		assert(size > 0);
		Node *result = (Node *)malloc(size);
		assert(result);
		memset(result, 0, size);
		return result;
	}

	Node* _insert(Iterator where)
	{
		Node* node = where.at;
		Node* result = alloc_memory((size_type)sizeof(Node));
		result->prev = node->prev;
		result->next = node;
		node->prev->next = result;
		node->prev = result;
		return result;
	}

public:
	void push_front(const Data& data) { insert(begin(), data); }
	void push_front(Data&& data) { insert(begin(), std::move(data)); }

	void push_back(const Data& data) { insert(end(), data); }
	void push_back(Data&& data) { insert(end(), std::move(data)); }


	Iterator insert(Iterator where, const Data& data)
	{
		Node* result = _insert(where);
		result->data = data;
		++size;
		return Iterator{result};
	}

	Iterator insert(Iterator where, Data&& data)
	{
		Node* result = _insert(where);
		result->data = std::move(data);
		++size;
		return Iterator{result};
	}

	Iterator erase(Iterator where)
	{
		assert(where != end());
		Node* erased_node = where.at;
		Iterator result{ erased_node->next };
		erased_node->next->prev = erased_node->prev;
		erased_node->prev->next = erased_node->next;
		free(erased_node);
		--size;
		return result;
	}

	Iterator erase(Iterator first, Iterator last) { Iterator itr = first; while (itr != last) { itr = erase(itr); }; return last; } 

	void pop_front() { assert(!empty()); erase(begin()); }
	void pop_back() { assert(!empty()); erase(--end()); }

	void clear() { while (!empty()) pop_front(); }

	Data& front() { return *begin(); }
	Data& back() { return *(--end()); }

	const Data& front() const { return *begin(); }
	const Data& back() const { return *(--end()); }

	size_type length() const { return size; }
	bool empty() const { return !length(); }

	Iterator begin() { return Iterator{ head->next }; }
	Iterator end() { return Iterator{ tail }; }

	ConstIterator begin() const { return ConstIterator{ head->next }; }
	ConstIterator end() const { return ConstIterator{ tail }; }

private:
	Node* head;
	Node* tail;
	size_type size;
};