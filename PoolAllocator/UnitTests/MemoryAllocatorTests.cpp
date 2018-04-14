#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "MyClass.hpp"
#include "PoolAllocator.hpp"
#include "TestUtility.hpp"

TEST_CASE("Pool allocator initialize one object", "Verify object is initialized correctly and pointer is aligned.")
{
    size_t alignment = alignof(MyClass);
    size_t size = sizeof(MyClass);
    PoolAllocator::Init(3, size, alignment);
    char a = 'a';
    int x= 8;
    MyClass* obj1 = new MyClass(a, x);
    REQUIRE(TestUtility::IsAligned(obj1, alignof(MyClass)) == true);
    REQUIRE(obj1->GetA() == a);
    REQUIRE(obj1->GetX() == x);
    delete obj1;
    PoolAllocator::FreeAll();
}

TEST_CASE("Pool allocator initialize multiple objects", "Verify all objects are initilized correctly with correct pointer alignment.")
{
    size_t alignment = alignof(MyClass);
    size_t size = sizeof(MyClass);
    PoolAllocator::Init(2, size, alignment);
    char a = 'a';
    int x= 8;
    char b = 'b';
    int y = 9;
    MyClass* obj1 = new MyClass(a, x);
    MyClass* obj2 = new MyClass(b, y);
    REQUIRE(TestUtility::IsAligned(obj1, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(obj2, alignof(MyClass)) == true);
    REQUIRE(obj1->GetA() == a);
    REQUIRE(obj1->GetX() == x);
    REQUIRE(obj2->GetA() == b);
    REQUIRE(obj2->GetX() == y);
    delete obj1;
    delete obj2;
    PoolAllocator::FreeAll();
}

TEST_CASE("Pool allocator free firt allocated object and re-allocate", "Verify all objects are initilized correctly with correct pointer alignment.")
{
    size_t alignment = alignof(MyClass);
    size_t size = sizeof(MyClass);
    PoolAllocator::Init(3, size, alignment);
    char a = 'a';
    int x= 8;
    char b = 'b';
    int y = 9;
    char c = 'c';
    int z = 10;
    MyClass* obj1 = new MyClass(a, x);
    MyClass* obj2 = new MyClass(b, y);
    MyClass* obj3 = new MyClass(c, z);
    REQUIRE(TestUtility::IsAligned(obj1, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(obj2, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(obj3, alignof(MyClass)) == true);
    REQUIRE(obj1->GetA() == a);
    REQUIRE(obj1->GetX() == x);
    REQUIRE(obj2->GetA() == b);
    REQUIRE(obj2->GetX() == y);
    REQUIRE(obj3->GetA() == c);
    REQUIRE(obj3->GetX() == z);
    
    // Free first allocated object and re-allocate
    delete obj1;
    MyClass* obj4 = new MyClass(c, z);
    REQUIRE(TestUtility::IsAligned(obj4, alignof(MyClass)) == true);
    REQUIRE(obj4->GetA() == c);
    REQUIRE(obj4->GetX() == z);
    delete obj4;
    delete obj2;
    delete obj3;
    PoolAllocator::FreeAll();
}

TEST_CASE("Pool allocator free second allocated object and re-allocate", "Verify all objects are initilized correctly with correct pointer alignment.")
{
    size_t alignment = alignof(MyClass);
    size_t size = sizeof(MyClass);
    PoolAllocator::Init(3, size, alignment);
    char a = 'a';
    int x= 8;
    char b = 'b';
    int y = 9;
    char c = 'c';
    int z = 10;
    MyClass* obj1 = new MyClass(a, x);
    MyClass* obj2 = new MyClass(b, y);
    MyClass* obj3 = new MyClass(c, z);
    REQUIRE(TestUtility::IsAligned(obj1, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(obj2, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(obj3, alignof(MyClass)) == true);
    REQUIRE(obj1->GetA() == a);
    REQUIRE(obj1->GetX() == x);
    REQUIRE(obj2->GetA() == b);
    REQUIRE(obj2->GetX() == y);
    REQUIRE(obj3->GetA() == c);
    REQUIRE(obj3->GetX() == z);
    
    // Free second allocated object and re-allocate
    delete obj2;
    MyClass* obj4 = new MyClass(b, y);
    REQUIRE(TestUtility::IsAligned(obj4, alignof(MyClass)) == true);
    REQUIRE(obj4->GetA() == b);
    REQUIRE(obj4->GetX() == y);
    delete obj4;
    delete obj2;
    delete obj3;
    PoolAllocator::FreeAll();
}

TEST_CASE("Pool allocator free last allocated object and re-allocate", "Verify all objects are initilized correctly with correct pointer alignment.")
{
    size_t alignment = alignof(MyClass);
    size_t size = sizeof(MyClass);
    PoolAllocator::Init(3, size, alignment);
    char a = 'a';
    int x= 8;
    char b = 'b';
    int y = 9;
    char c = 'c';
    int z = 10;
    MyClass* obj1 = new MyClass(a, x);
    MyClass* obj2 = new MyClass(b, y);
    MyClass* obj3 = new MyClass(c, z);
    REQUIRE(TestUtility::IsAligned(obj1, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(obj2, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(obj3, alignof(MyClass)) == true);
    REQUIRE(obj1->GetA() == a);
    REQUIRE(obj1->GetX() == x);
    REQUIRE(obj2->GetA() == b);
    REQUIRE(obj2->GetX() == y);
    REQUIRE(obj3->GetA() == c);
    REQUIRE(obj3->GetX() == z);
    
    // Free last allocated object and re-allocate
    delete obj3;
    MyClass* obj4 = new MyClass(c, z);
    REQUIRE(TestUtility::IsAligned(obj4, alignof(MyClass)) == true);
    REQUIRE(obj4->GetA() == c);
    REQUIRE(obj4->GetX() == z);
    delete obj4;
    delete obj2;
    delete obj3;
    PoolAllocator::FreeAll();
}

TEST_CASE("Pool Allocator allocate when pool is full", "Expect excpetion" )
{
    size_t alignment = alignof(MyClass);
    size_t size = sizeof(MyClass);
    PoolAllocator::Init(1, size, alignment);
    char a = 'a';
    int x= 8;
    MyClass* obj1 = new MyClass(a, x);
    REQUIRE(TestUtility::IsAligned(obj1, alignof(MyClass)) == true);
    REQUIRE(obj1->GetA() == a);
    REQUIRE(obj1->GetX() == x);
    
    // Try to allocate a block when pool is full, expect a bad alloc exception
    REQUIRE_THROWS_AS(new MyClass(a, x), std::bad_alloc);
    delete obj1;
    PoolAllocator::FreeAll();
}
