/*

#include "SkipList.h"


//SkipList

template<typename Key, typename T, typename Compare>
SkipList<Key, T, Compare>::SkipList()
{
	head = nullptr;
	length = 0;
}

template<typename Key, typename T, typename Compare>
SkipList<Key, T, Compare> & SkipList<Key, T, Compare>::operator=(const SkipList & list)
{
	for (SkipList<Key, T, Compare>::iterator it = list.begin(); it != list.end(); ++it)
	{
		this->insert(*it)
	}
	return *this;
}

template<typename Key, typename T, typename Compare>
typename const SkipList<Key, T, Compare>::value_type* SkipList<Key, T, Compare>::find(const Key & key) const
{
	value_type* result = nullptr;
	for (SkipList<Key, T, Compare>::iterator it = *this.begin(); it != *this.end(); ++it)
	{
		if (it->first == key) 
		{
			result = it;
			break;
		}
	}
	const value_type* const_result = result;
	return result;
}

template<typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::value_type * SkipList<Key, T, Compare>::find(const Key & key)
{
	value_type* result = nullptr;
	for (SkipList<Key, T, Compare>::iterator it = *this.begin(); it != *this.end(); ++it)
	{
		if (it->first == key)
		{
			result = it;
			break;
		}
	}
	return result;
}

template<typename Key, typename T, typename Compare>
std::pair<typename SkipList<Key, T, Compare>::value_type*, bool> SkipList<Key, T, Compare>::insert(const value_type & val)
{
	//create object to insert
	SkipList<Key, T, Compare>::element insert_element;
	insert_element.content = val;

	//set up return item
	std::pair<typename SkipList<Key, T, Compare> value_type*, bool> result;
	result.second = false;
	if (*this.find(const val.first)) //find is nullptr if key already in list
	{
		SkipList<Key, T, Compare>::iterator old_iter;
		for (SkipList<Key, T, Compare>::iterator it = *this.begin(); it != *this.end(); ++it)
		{
			if (Compare(val.first, it->content.first))
			{
				old_it->next = *insert_element;
				insert_element.next = it->next;
				result.first = *insert_element.content;
				result.second = true;
				*this.length = *this.length + 1;
				return result;
			}
			else
			{
				old_it = it;
			}
		}
	}
	else
	{
		result.first = *this.find(const val.first);
		return result;
	}
}

template<typename Key, typename T, typename Compare>
size_t SkipList<Key, T, Compare>::erase(const Key & key)
{
	if (*this.find(key))
	{


		SkipList<Key, T, Compare>::iterator old_iter;
		for (SkipList<Key, T, Compare>::iterator it = *this.begin(); it != *this.end(); ++it)
		{
			if (Compare(key, it->content.first))
			{
				old_it = it;
			}
			else
			{
				old_it.iter->next = it.iter->next;
				*this.length = *this.length - 1;
				return *this.length;
			}
		}
	}
}

template<typename Key, typename T, typename Compare>
typename SkipList < Key, T, Compare>::iterator SkipList<Key, T, Compare>::begin()
{
	iterator result;
	result.iter = head;
	return result;
}

template<typename Key, typename T, typename Compare>
typename SkipList < Key, T, Compare>::const_iterator SkipList<Key, T, Compare>::begin() const
{
	iterator result;
	result.iter = head;
	const_iterator const_result = result;
	return const_result;
}

template<typename Key, typename T, typename Compare>
typename SkipList < Key, T, Compare>::iterator SkipList<Key, T, Compare>::end()
{
	iterator result = *this.begin();
	for(size_t i = 0; i < *this.length; i++)
	{
		++result;
	}
	return result;
}

template<typename Key, typename T, typename Compare>
typename SkipList < Key, T, Compare>::const_iterator SkipList<Key, T, Compare>::end() const
{
	iterator result;
	for (iterator it = *this.begin(); it.iter != nullptr; ++it)
	{
		result.iter = it.iter;
	}
	const_iterator const_result = result;
	return const_result;
}



//iterator

template <typename Key, typename T, typename Compare>
SkipList<Key, T, Compare>::iterator::iterator()
{
	iter = head;
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::value_type& SkipList<Key, T, Compare>::iterator::operator*() const
{
	return iter->content;
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::value_type * SkipList<Key, T, Compare>::iterator::operator->() const
{
	return *(iter->content);
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::iterator & SkipList<Key, T, Compare>::iterator::operator++()
{
	iter = iter->next;
	return iter;
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::iterator SkipList<Key, T, Compare>::iterator::operator++(int)
{
	typename SkipList<Key, T, Compare>::iterator old_iter = iter;
	iter = iter->next;
	return old_iter;
}

template <typename Key, typename T, typename Compare>
bool SkipList<Key, T, Compare>::iterator::operator==(const iterator & rhs) const
{
	if (!Compare(iter->content.first, rhs.iter->content.first)() && !Compare()(rhs.iter->content.first, iter->content.first))
		return true;
	else return false;
}

template <typename Key, typename T, typename Compare>
bool SkipList<Key, T, Compare>::iterator::operator!=(const iterator & rhs) const
{
	if (iter == rhs) return false;
	else return true;
}



//const_iterator

template <typename Key, typename T, typename Compare>
SkipList<Key, T, Compare>::const_iterator::const_iterator()
{
	iter = head;
}

template <typename Key, typename T, typename Compare>
typename const SkipList<Key, T, Compare>::value_type& SkipList<Key, T, Compare>::const_iterator::operator*() const
{
	return iter->content;
}

template <typename Key, typename T, typename Compare>
typename const SkipList<Key, T, Compare>::value_type * SkipList<Key, T, Compare>::const_iterator::operator->() const
{
	return *(iter->content);
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::const_iterator & SkipList<Key, T, Compare>::const_iterator::operator++()
{
	iter = iter->next;
	return iter;
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::const_iterator SkipList<Key, T, Compare>::const_iterator::operator++(int)
{
	typename SkipList<Key, T, Compare>::iterator old_iter = iter;
	iter = iter->next;
	return old_iter;
}

template <typename Key, typename T, typename Compare>
bool SkipList<Key, T, Compare>::const_iterator::operator==(const const_iterator & rhs) const
{
	if (!Compare(iter->content.first, rhs.iter->content.first)() && !Compare()(rhs.iter->content.first, iter->content.first))
		return true;
	else return false;
}

template <typename Key, typename T, typename Compare>
bool SkipList<Key, T, Compare>::const_iterator::operator!=(const const_iterator & rhs) const
{
	if (iter == rhs) return false;
	else return true;
}

*/