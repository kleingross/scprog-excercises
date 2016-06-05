#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_


#include <functional>
#include <utility>
//#include <random>
#include <stdlib.h>
#include <iostream>

template < typename Key, typename T, typename Compare = std::less<Key> >
class SkipList
{
public:
	typedef std::pair<const Key, T> value_type;
    
    class iterator;
    class const_iterator;
    
                                SkipList();
                                SkipList( const SkipList& list );
                                ~SkipList();
    
    SkipList&                   operator = ( const SkipList& list );
    
    const value_type*           find( const Key& key ) const;
    value_type*                 find( const Key& key );
    
    std::pair<value_type*,bool> insert( const value_type& val );
    size_t                      erase( const Key& key );
    
    iterator                    begin();
	iterator					begin(int begin_at_level);
    const_iterator              begin() const;
	const_iterator				begin(int begin_at_level) const;
    iterator                    end();
    const_iterator              end() const;

private:

	friend class iterator;
	friend class const_iterator;

	//define levels
	static const int max_level_height = 10;
	int current_highest_level;
	int get_level_height();


	//content
	struct element
	{
		value_type content;
		element* next[max_level_height];
		int level_height;

		//constructor
		//element(const value_type& new_content, int level);
		element(const value_type& new_content, int level) : content(new_content), level_height(level), next{ nullptr } {};
	};

	element* head[max_level_height];
	size_t length;
};



template <typename Key, typename T, typename Compare>
class SkipList<Key,T,Compare>::iterator
{
public:
                iterator();
            
    value_type& operator * () const;
    value_type* operator -> () const;
    
    iterator&   operator ++ ();
    iterator    operator ++ ( int );
            
    bool        operator == ( const iterator& rhs ) const;
    bool        operator != ( const iterator& rhs ) const;

private:

	friend class SkipList;
	friend class const_iterator;

	int iter_level;
	element* iter;
};

template <typename Key, typename T, typename Compare>
class SkipList<Key,T,Compare>::const_iterator
{
public:
                        const_iterator();
            
    const value_type&   operator * () const;
    const value_type*   operator -> () const;
    
    const_iterator&     operator ++ ();
    const_iterator      operator ++ ( int );
            
    bool                operator == ( const const_iterator& rhs ) const;
    bool                operator != ( const const_iterator& rhs ) const;

private:

	friend class SkipList;
	friend class iterator;

	int iter_level;
	const element* iter;
};




//SkipList

template<typename Key, typename T, typename Compare>
SkipList<Key, T, Compare>::SkipList()
{
	for (int i = 0; i < max_level_height; ++i)
	{
		head[i] = nullptr;
	}
	length = 0;
	current_highest_level = 0;
}

template<typename Key, typename T, typename Compare>
SkipList<Key, T, Compare>::SkipList(const SkipList & list)
{
	for (int i = 0; i < max_level_height; ++i)
	{
		head[i] = nullptr;
	}
	length = 0;
	current_highest_level = 0;
	
	//inserts all elements which are in list. level height of elements can be different. 
	for (const_iterator it = list.begin(); it != list.end(); ++it)
	{
		this->insert(*it);
	}
}

template<typename Key, typename T, typename Compare>
SkipList<Key, T, Compare>::~SkipList()
{
	element* current_ptr = head[0];
	while (current_ptr != nullptr)
	{
		element* next_ptr = current_ptr->next[0];
		delete current_ptr;
		current_ptr = next_ptr;
	}

}

template<typename Key, typename T, typename Compare>
SkipList<Key, T, Compare> & SkipList<Key, T, Compare>::operator=(const SkipList & list)
{
	//new_list = copy of list
	SkipList new_list;
	for (const_iterator it = list.begin(0); it != list.end(); ++it)
	{
		new_list.insert(*it);
	}
	
	//empty *this
	//delete all objects in *this
	element* delete_element = head[0];
	element* next_element = delete_element;
	while (delete_element)
	{
		next_element = delete_element->next[0];
		delete delete_element;
		delete_element = next_element;
	}
	//set up new head for *this
	for (int i = 0; i < max_level_height; ++i)
	{
		head[i] = nullptr;
	}
	length = 0;
	current_highest_level = 0;
	
	//insert all objects of new_list into *this
	for (iterator it = new_list.begin(0); it != new_list.end(); ++it)
	{
		this->insert(*it);
	}

	return *this;
}

template<typename Key, typename T, typename Compare>
const typename SkipList<Key, T, Compare>::value_type* SkipList<Key, T, Compare>::find(const Key & key) const
{
	element** previous_ptr = head; //previous_ptr is pointer to array of next pointers (aka next[])

	for (int level = current_highest_level; level >= 0; --level)
	{
		//while previous ptr not nullptr //current ptr not nullptr  //find_key <= current key
		while (previous_ptr[level] && !Compare()(key, previous_ptr[level]->content.first))
		{
			//if object is reached return pointer to content
			if (!Compare()(previous_ptr[level]->content.first, key) && !Compare()(key, previous_ptr[level]->content.first))
			{
				return &(previous_ptr[level]->content);
			}
			//if not update previous_ptr and continue
			else
			{
				previous_ptr = previous_ptr[level]->next;
			}
		}
	}

	return nullptr; //if nothing was found: return nullptr
}

template<typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::value_type * SkipList<Key, T, Compare>::find(const Key & key)
{
	element** previous_ptr = head; //previous_ptr is pointer to array of next pointers (aka next[])

	for (int level = current_highest_level; level >= 0; --level)
	{
		//while previous ptr not nullptr //current ptr not nullptr  //find_key <= current key
		while (previous_ptr && previous_ptr[level] && !Compare()(key, previous_ptr[level]->content.first))
		{
			//if object is reached return pointer to content
			if (!Compare()(previous_ptr[level]->content.first, key) && !Compare()(key, previous_ptr[level]->content.first))
			{
				return &(previous_ptr[level]->content);
			}
			//if not update previous_ptr and continue
			else
			{
				previous_ptr = previous_ptr[level]->next;
			}
		}
	}

	return nullptr; //if nothing was found: return nullptr
}

template<typename Key, typename T, typename Compare>
std::pair<typename SkipList<Key, T, Compare>::value_type*, bool> SkipList<Key, T, Compare>::insert(const value_type & val)
{
	//set up return element
	std::pair<typename SkipList<Key, T, Compare>::value_type*, bool> result;
	result.second = false;


	if (this->find(val.first))		//if val already in list
	{
		result.first = this->find(val.first);
		return result;
	}
	else							//if val not already in list
	{
		//set up element to insert
		int insert_level = get_level_height();
		element* insert_element_ptr = new element(val, insert_level);

		//if insert level greater_current highest_level: modify head and current_highest_level
		if (insert_level > current_highest_level) current_highest_level = insert_level;

		element** previous_ptr = head; 
		
		for (int level = current_highest_level; level >= 0; --level)
		{
			//while previous ptr not nullptr //insert key < current key
			while (previous_ptr[level] && Compare()(previous_ptr[level]->content.first, val.first))
			{
				previous_ptr = previous_ptr[level]->next;
			}
			//change pointers in previous to insert and in insert to current
			(insert_element_ptr->next)[level] = previous_ptr[level];
			previous_ptr[level] = insert_element_ptr;			
		}

		//change result to success return
		result.first = &(insert_element_ptr->content);
		result.second = true;
		this->length = this->length + 1;
	}

	return result;
}

template<typename Key, typename T, typename Compare>
size_t SkipList<Key, T, Compare>::erase(const Key & key)
{
	
	if (this->find(key))		//if val already in list
	{
		//previous_ptr is pointer to array of next pointers 
		//previous_ptr[level] points to current element in level
		element** previous_ptr = head; 

		//decend through all levels
		for (int level = current_highest_level; level >= 0; --level)
		{
			//while previous_ptr and element it is pointing to (= current element) are not nullptr
			//while delete_key  >= current key
			while (previous_ptr[level] && !Compare()(key, previous_ptr[level]->content.first))
			{
				//if object is reached
				if (!Compare()(previous_ptr[level]->content.first, key) && !Compare()(key, previous_ptr[level]->content.first))
				{
					//delete from level, delete element if level = 0
					if (level == 0)
					{
						element* ptr_to_delete_element = previous_ptr[level];
						previous_ptr[level] = previous_ptr[level]->next[level];
						delete ptr_to_delete_element;
					}
					else
					{
						previous_ptr[level] = previous_ptr[level]->next[level];
					}
				}
				else 
				{
					previous_ptr = previous_ptr[level]->next;
				}
			}
		}

		//check if highest level empty
		while (current_highest_level > 0) //reduce current highest level 
		{
			if (this->begin() == this->end()) current_highest_level = current_highest_level - 1;
			else break;
		}
		//change result to success return
		this->length = this->length - 1;
	}

	return this->length;
}

template<typename Key, typename T, typename Compare>
typename SkipList < Key, T, Compare>::iterator SkipList<Key, T, Compare>::begin()
{
	iterator result;
	result.iter_level = 0;
	result.iter = head[0];
	return result;
}

template<typename Key, typename T, typename Compare>
typename SkipList < Key, T, Compare>::iterator SkipList<Key, T, Compare>::begin(int begin_at_level)
{
	iterator result;
	result.iter_level = begin_at_level;
	result.iter = head[result.iter_level];
	return result;
}

template<typename Key, typename T, typename Compare>
typename SkipList < Key, T, Compare>::const_iterator SkipList<Key, T, Compare>::begin() const
{
	const_iterator result;
	result.iter_level = 0;
	result.iter = head[0] ;
	return result;
}

template<typename Key, typename T, typename Compare>
typename SkipList < Key, T, Compare>::const_iterator SkipList<Key, T, Compare>::begin(int begin_at_level) const
{
	const_iterator result;
	result.iter_level = begin_at_level;
	result.iter = head[result.iter_level];
	return result;
}

template<typename Key, typename T, typename Compare>
typename SkipList < Key, T, Compare>::iterator SkipList<Key, T, Compare>::end()
{
	iterator result;
	result.iter = nullptr;
	return result;
}

template<typename Key, typename T, typename Compare>
typename SkipList < Key, T, Compare>::const_iterator SkipList<Key, T, Compare>::end() const
{
	const_iterator result;
	result.iter = nullptr;
	return result;
}

template<typename Key, typename T, typename Compare>
int SkipList<Key, T, Compare>::get_level_height()
{
	int level_height = 0;
	int random_number = 0;

	while (level_height < max_level_height)
	{
		random_number = std::rand() % 2; //can be 1 or 0, 50:50 chance
		if (random_number == 0)
		{
			level_height = level_height + 1;
		}
		else break;
	}
	return level_height;
}



//iterator

template <typename Key, typename T, typename Compare>
SkipList<Key, T, Compare>::iterator::iterator()
{
	iter_level = max_level_height;
	iter = nullptr;
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::value_type& SkipList<Key, T, Compare>::iterator::operator*() const
{
	return iter->content;
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::value_type * SkipList<Key, T, Compare>::iterator::operator->() const
{
	return &(iter->content);
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::iterator & SkipList<Key, T, Compare>::iterator::operator++()
{
	iter = iter->next[iter_level];
	return *this;
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::iterator SkipList<Key, T, Compare>::iterator::operator++(int)
{
	typename SkipList<Key, T, Compare>::iterator old_iter = iter;
	iter = iter->next[iter_level];
	return old_iter;
}

template <typename Key, typename T, typename Compare>
bool SkipList<Key, T, Compare>::iterator::operator==(const iterator & rhs) const
{
	if (this->iter == rhs.iter) return true; //sollte this->iter_level == rhs.iter_level erfüllt sein?
	else return false;
}

template <typename Key, typename T, typename Compare>
bool SkipList<Key, T, Compare>::iterator::operator!=(const iterator & rhs) const
{
	if (*this == rhs) return false;
	else return true;
}



//const_iterator

template <typename Key, typename T, typename Compare>
SkipList<Key, T, Compare>::const_iterator::const_iterator()
{
	iter_level = max_level_height;
	iter = nullptr;
}

template <typename Key, typename T, typename Compare>
const typename SkipList<Key, T, Compare>::value_type& SkipList<Key, T, Compare>::const_iterator::operator*() const
{
	return iter->content;
}

template <typename Key, typename T, typename Compare>
const typename SkipList<Key, T, Compare>::value_type * SkipList<Key, T, Compare>::const_iterator::operator->() const
{
	return &(iter->content) ;
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::const_iterator & SkipList<Key, T, Compare>::const_iterator::operator++()
{
	iter = iter->next[iter_level];
	return *this;
}

template <typename Key, typename T, typename Compare>
typename SkipList<Key, T, Compare>::const_iterator SkipList<Key, T, Compare>::const_iterator::operator++(int)
{
	typename SkipList<Key, T, Compare>::const_iterator old_iter = iter;
	iter = iter->next[iter_level];
	return old_iter;
}

template <typename Key, typename T, typename Compare>
bool SkipList<Key, T, Compare>::const_iterator::operator==(const const_iterator & rhs) const
{
	if (this->iter == rhs.iter) return true; //sollte this->iter_level == rhs.iter_level erfüllt sein?
	else return false;
}

template <typename Key, typename T, typename Compare>
bool SkipList<Key, T, Compare>::const_iterator::operator!=(const const_iterator & rhs) const
{
	if (*this == rhs) return false;
	else return true;
}



#endif /*SKIP_LIST_H_*/