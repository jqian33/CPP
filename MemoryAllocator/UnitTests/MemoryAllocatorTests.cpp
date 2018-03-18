#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Allocator.hpp"
#include "Header.hpp"
#include "MyClass.hpp"

TEST_CASE("Initialize Allocator", "Verify Allocator is initialized with one free block.")
{
    int totalSize = 500;
    Allocator::Init(totalSize);
    REQUIRE(Allocator::TotalSize() == totalSize);
    REQUIRE(Allocator::SpacesUsed() == sizeof(Header));
    REQUIRE(Allocator::NumberOfBlocks() == 1);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 1);
    Allocator::FreeAll();
}

TEST_CASE("Allocate object, not enough left over to create new block", "Verify no extra block is created.")
{
    int totalSize = 45;
    Allocator::Init(totalSize);
    char a = 'a';
    int x = 1;
    MyClass* object1 = new MyClass(a, x);
    REQUIRE(object1->GetA() == a);
    REQUIRE(object1->GetX() == x);
    REQUIRE(Allocator::SpacesUsed() == sizeof(Header) + sizeof(MyClass));
    REQUIRE(Allocator::NumberOfBlocks() == 1);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 0);
    Allocator::FreeAll();
}

TEST_CASE("Allocate one object", "Verify one block is allocated.")
{
    int totalSize = 100;
    Allocator::Init(totalSize);
    char a = 'a';
    int x = 1;
    MyClass* object1 = new MyClass(a, x);
    REQUIRE(object1->GetA() == a);
    REQUIRE(object1->GetX() == x);
    REQUIRE(Allocator::SpacesUsed() == sizeof(Header) * 2 + sizeof(MyClass));
    REQUIRE(Allocator::NumberOfBlocks() == 2);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 1);
    Allocator::FreeAll();
}

TEST_CASE("Allocate two objects", "Verify two blocks are allocated.")
{
    int totalSize = 200;
    Allocator::Init(totalSize);
    char a = 'a';
    int x = 1;
    char b = 'b';
    int y = 2;
    MyClass* object1 = new MyClass(a, x);
    MyClass* object2 = new MyClass(b, y);
    REQUIRE(object1->GetA() == a);
    REQUIRE(object1->GetX() == x);
    REQUIRE(object2->GetA() == b);
    REQUIRE(object2->GetX() == y);
    REQUIRE(Allocator::SpacesUsed() == sizeof(Header) * 3 + sizeof(MyClass) * 2);
    REQUIRE(Allocator::NumberOfBlocks() == 3);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 1);
    Allocator::FreeAll();
}

TEST_CASE("Free one object", "Verify one block is de-allocated, and merge with next free block takes place.")
{
    int totalSize = 100;
    Allocator::Init(totalSize);
    char a = 'a';
    int x = 1;
    MyClass* object1 = new MyClass(a, x);
    delete object1;
    REQUIRE(Allocator::SpacesUsed() == sizeof(Header));
    REQUIRE(Allocator::NumberOfBlocks() == 1);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 1);
    Allocator::FreeAll();
}

TEST_CASE("Free one object causing a merge with both previous and next block", "Verify two merge takes place.")
{
    int totalSize = 500;
    Allocator::Init(totalSize);
    char a = 'a';
    int x = 1;
    char b = 'b';
    int y = 2;
    MyClass* object1 = new MyClass(a, x);
    MyClass* object2 = new MyClass(b, y);
    REQUIRE(object1->GetA() == a);
    REQUIRE(object1->GetX() == x);
    REQUIRE(object2->GetA() == b);
    REQUIRE(object2->GetX() == y);
    
    // Deleting the object1 will not cause merge because object2 occupies the next block
    delete object1;
    REQUIRE(Allocator::SpacesUsed() == sizeof(Header) * 2 + sizeof(MyClass));
    REQUIRE(Allocator::NumberOfFreeBlocks() == 2);
    REQUIRE(Allocator::NumberOfBlocks() == 3);
    
    // Deleting the object2 will cause merge with both previous block and next block
    delete object2;
    REQUIRE(Allocator::SpacesUsed() == sizeof(Header));
    REQUIRE(Allocator::NumberOfFreeBlocks() == 1);
    REQUIRE(Allocator::NumberOfBlocks() == 1);
    
    Allocator::FreeAll();
}

TEST_CASE("Free one object causing merge with only previous block", "Verify only one merge takes place.")
{
    int totalSize = 500;
    Allocator::Init(totalSize);
    char a = 'a';
    int x = 1;
    char b = 'b';
    int y = 2;
    char c = 'c';
    int z = '3';
    MyClass* object1 = new MyClass(a, x);
    MyClass* object2 = new MyClass(b, y);
    MyClass* object3 = new MyClass(c, z);
    REQUIRE(object1->GetA() == a);
    REQUIRE(object1->GetX() == x);
    REQUIRE(object2->GetA() == b);
    REQUIRE(object2->GetX() == y);
    REQUIRE(object3->GetA() == c);
    REQUIRE(object3->GetX() == z);
    
    // Deleting the object1 will not cause merge because object2 occupies the next block
    delete object1;
    REQUIRE(Allocator::SpacesUsed() == sizeof(Header) * 3 + sizeof(MyClass) * 2);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 2);
    REQUIRE(Allocator::NumberOfBlocks() == 4);
    
    // Deleting the object2 will cause merge with previous block, but not next block because object3 occupies it
    delete object2;
    REQUIRE(Allocator::SpacesUsed() == sizeof(Header) * 2 + sizeof(MyClass));
    REQUIRE(Allocator::NumberOfFreeBlocks() == 2);
    REQUIRE(Allocator::NumberOfBlocks() == 3);
    
    Allocator::FreeAll();
}

