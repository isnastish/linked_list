## Implementation of `std::list`

# Example usage code:

```cpp
#include "linked_list.h"

/*
* NOTE: Helper function to print the list.
*/
template<class T>
static void debug_out_list(const List<T>& list)
{
	// NOTE: Make sure that you have operator * (dereference) overloaded for the data.
	std::cout << "head -> ";
	typename List<T>::ConstIterator itr = list.begin();
	for (; itr != list.end(); 
		++itr)
	{
		std::cout << *itr << " -> ";
	}
	std::cout << "tail;" << std::endl;
}

int main(int args_count, char **argv)
{
	List<int32> list;
	list.push_front(3);
	list.push_front(5);
	list.push_front(7);
	std::cout << "Length: " << list.length() << std::endl;
	list.push_back(15);
	list.push_back(17);
	std::cout << "Length: " << list.length() << std::endl;
	if (!list.empty())
		std::cout << "List is not empty!" << std::endl;
	debug_out_list(list);
	std::cout << "Front: " << list.front() << std::endl;
	std::cout << "Back: " << list.back() << std::endl;
	list.pop_front();
	std::cout << "Length: " << list.length() << std::endl;
	debug_out_list(list);
	std::cout << "Pop from the back!" << std::endl;
	list.pop_back();
	std::cout << "Length: " << list.length() << std::endl;
	debug_out_list(list);
	std::cout << "Clear out the list!" << std::endl;
	list.clear();
	debug_out_list(list);
	std::cout << "Length: " << list.length() << std::endl;
	list.push_back(34);
	list.push_back(67);
	list.push_back(80);
	list.push_back(-12);
	std::cout << "Before erase.begin(): ";
	debug_out_list(list);
	list.erase(list.begin());
	std::cout << "After erase.begin(): ";
	debug_out_list(list);
	std::cout << "Length: " << list.length() << std::endl;
	list.push_back(121);
	list.push_back(999);
	list.push_back(4096);
	list.push_back(8192);
	debug_out_list(list);
	std::cout << "Erase range: list.begin(), ++list.begin(): ";
	list.erase(list.begin(), ++list.begin());
	debug_out_list(list);
	std::cout << "Length: " << list.length() << std::endl;
	std::cout << "Before inserting to list.begin(): " << std::endl;
	debug_out_list(list);
	list.insert(list.begin(), 9);
	std::cout << "After inserting to list.begin(): " << std::endl;
	debug_out_list(list);
	std::cout << "Length: " << list.length() << std::endl;

	List<int32>::Iterator itr0 = list.begin();
	++itr0;
	++itr0;
	++itr0;
	list.insert(itr0, 555);
	debug_out_list(list);
	std::cout << "Length: " << list.length() << std::endl;

	std::cout << "Before copy: " << std::endl;
	debug_out_list(list);
	List<int32> list0 = list;
	std::cout << "After copy: " << std::endl;
	debug_out_list(list0);
	std::cout << "Length: " << list.length() << std::endl;

	list.push_front(65536);
	std::cout << "List: ";
	debug_out_list(list);

	list0 = list;
	std::cout << "List0: ";
	debug_out_list(list0);

	List<int32> list1 = std::move(list0);
	std::cout << "After moving: " << std::endl;
	debug_out_list(list1);

	std::cout << "After move assignment: " << std::endl;
	list.push_back(99999999);
	list1 = std::move(list);
	debug_out_list(list1);
  std::cout << "Length: " << list1.length() << std::endl;

  return 0;
}
```
