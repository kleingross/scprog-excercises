#include "SkipList.h"

#include <vector>
#include <assert.h>


struct TestKey
{
    int         value;
    
                TestKey(): value(0) {}
    explicit    TestKey( int n ): value(n) {}
};

struct TestKeyCompare
{
    typedef TestKey first_argument_type;
    typedef TestKey second_argument_type;
    typedef bool    result_type;
    
    bool operator() ( const TestKey& k1, const TestKey& k2 ) const { return k1.value < k2.value; }
};

struct TestData
{
    int                 value;
    std::vector<char>   buffer;
    
                        TestData(): value(0), buffer(10*1024*1024) {}
    explicit            TestData( int n ): value(n), buffer(10*1024*1024) {}
};

typedef std::pair<TestKey,TestData> TestPair;
typedef SkipList<TestKey,TestData,TestKeyCompare> TestSkipList;

static void
TestContents( const TestSkipList& s, const std::vector<int>& key, const std::vector<int>& data )
{
    size_t i = 0;
    for( TestSkipList::const_iterator it = s.begin(); it != s.end(); ++it )
    {
        assert( it->first.value     == key[i] );
        assert( (*it).first.value   == key[i] );
        assert( it->second.value    == data[i] );
        assert( (*it).second.value  == data[i] );
        ++i;
    }
    assert( i == key.size() );
}

int
main( int argc, char** argv )
{
    TestSkipList s1;
    assert( s1.begin() == s1.end() );
    assert( s1.insert(TestPair(TestKey(10),TestData(100))).second == true );
    assert( s1.insert(TestPair(TestKey(10),TestData(100))).second == false );
    assert( s1.insert(TestPair(TestKey(5),TestData(50))).first->first.value == 5 );
    s1.insert( TestPair(TestKey(7),TestData(70)) );
    s1.insert( TestPair(TestKey(2),TestData(20)) );
    s1.insert( TestPair(TestKey(3),TestData(30)) );
    TestContents( s1, {2, 3, 5, 7, 10}, {20, 30, 50, 70, 100} );
    
    TestSkipList s2(s1);
    s2.erase( TestKey(3) );
    s2.erase( TestKey(7) );
    assert( s2.find(TestKey(3)) == 0 );
    assert( s2.find(TestKey(7)) == 0 );
    TestContents( s2, {2, 5, 10}, {20, 50, 100} );
    s2 = s2;
    TestContents( s2, {2, 5, 10}, {20, 50, 100} );
    assert( s2.find(TestKey(5))->first.value == 5 );
    assert( s2.find(TestKey(5))->second.value == 50 );
    
    TestSkipList s3;
    s3.insert( TestPair(TestKey(1),TestData(10)) );
    assert( s3.find(TestKey(1))->first.value == 1 );
    assert( s3.find(TestKey(1))->second.value == 10 );
    s3 = s2;
    assert( s3.find(TestKey(1)) == 0 );
    TestContents( s3, {2, 5, 10}, {20, 50, 100} );
    s2.insert( TestPair(TestKey(4),TestData(40)) );
    TestContents( s2, {2, 4, 5, 10}, {20, 40, 50, 100} );
    TestContents( s3, {2, 5, 10}, {20, 50, 100} );
    
    for( int i = 0; i < 500; ++i )
    {
		std::cout << i << std::endl;
        TestSkipList s4;
        {
            TestSkipList s5;
            s5.insert( TestPair(TestKey(1),TestData(10)) );
            s5.insert( TestPair(TestKey(2),TestData(20)) );
            s5.insert( TestPair(TestKey(3),TestData(30)) );
            s5.insert( TestPair(TestKey(4),TestData(40)) );
            s5.insert( TestPair(TestKey(5),TestData(50)) );
            s5.erase( TestKey(1) );
            s5.erase( TestKey(2) );
            s4 = s5;
        }
        assert( s4.find(TestKey(1)) == 0 );
        assert( s4.find(TestKey(2)) == 0 );
        assert( s4.find(TestKey(3))->first.value == 3 );
        assert( s4.find(TestKey(3))->second.value == 30 );
    }
    
    return 0;
}
