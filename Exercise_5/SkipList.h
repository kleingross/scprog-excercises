#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_


#include <functional>
#include <utility>

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
    const_iterator              begin() const;
    iterator                    end();
    const_iterator              end() const;

	//content
	struct element
	{
		value_type content;
		element* next;
	};

	element* head;
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

	const element* iter;
};


#endif /*SKIP_LIST_H_*/