#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Allocator.hpp"
#include "MyClass.hpp"
#include "LargeClass.hpp"
#include "TestUtility.hpp"

using namespace std;

TEST_CASE("Initialize Allocator", "Verify Allocator is initialized with one free block.")
{
    int totalSize = 500;
    Allocator::Init(totalSize);
    REQUIRE(Allocator::TotalSize() == totalSize);
    REQUIRE(Allocator::NumberOfBlocks() == 1);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 1);
    Allocator::FreeAll();
}

TEST_CASE("Allocate object, not enough left over to create new block", "Verify no extra block is created.")
{
    int totalSize = 60;
    Allocator::Init(totalSize);
    char a = 'a';
    int x = 1;
    MyClass* object1 = new MyClass(a, x);
    REQUIRE(object1->GetA() == a);
    REQUIRE(object1->GetX() == x);
    REQUIRE(TestUtility::IsAligned(object1, alignof(MyClass)) == true);
    REQUIRE(Allocator::NumberOfBlocks() == 1);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 0);
    Allocator::FreeAll();
}

TEST_CASE("Allocate object, not enough space", "Expect excpetion")
{
    int totalSize = 42;
    Allocator::Init(totalSize);
    REQUIRE_THROWS_AS(new MyClass('a', 1), bad_alloc);
    REQUIRE(Allocator::NumberOfBlocks() == 1);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 1);
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
    REQUIRE(TestUtility::IsAligned(object1, alignof(MyClass)) == true);
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
    REQUIRE(TestUtility::IsAligned(object1, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(object2, alignof(MyClass)) == true);
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
    REQUIRE(Allocator::NumberOfBlocks() == 1);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 1);
    REQUIRE(TestUtility::IsAligned(object1, alignof(MyClass)) == true);
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
    REQUIRE(TestUtility::IsAligned(object1, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(object2, alignof(MyClass)) == true);

    // Deleting the object1 will not cause merge because object2 occupies the next block
    delete object1;
    REQUIRE(Allocator::NumberOfFreeBlocks() == 2);
    REQUIRE(Allocator::NumberOfBlocks() == 3);

    // Deleting the object2 will cause merge with both previous block and next block
    delete object2;
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
    REQUIRE(TestUtility::IsAligned(object1, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(object2, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(object3, alignof(MyClass)) == true);
    
    // Deleting the object1 will not cause merge because object2 occupies the next block
    delete object1;
    REQUIRE(Allocator::NumberOfFreeBlocks() == 2);
    REQUIRE(Allocator::NumberOfBlocks() == 4);

    // Deleting the object2 will cause merge with previous block, but not next block because object3 occupies it
    delete object2;
    REQUIRE(Allocator::NumberOfFreeBlocks() == 2);
    REQUIRE(Allocator::NumberOfBlocks() == 3);

    Allocator::FreeAll();
}

TEST_CASE("Free an object in the middle, and re-allocate", "Verify the object is allocated correctly.")
{
    // Set size so that no extra free block is created after allocating the third object
    int totalSize = 156;
    Allocator::Init(totalSize);
    char a = 'a';
    int x = 1;
    char b = 'b';
    int y = 2;
    char c = 'c';
    int z = '3';
    char d = 'd';
    int zz = 373;
    MyClass* object1 = new MyClass(a, x);
    MyClass* object2 = new MyClass(b, y);
    MyClass* object3 = new MyClass(c, z);
    REQUIRE(object1->GetA() == a);
    REQUIRE(object1->GetX() == x);
    REQUIRE(object2->GetA() == b);
    REQUIRE(object2->GetX() == y);
    REQUIRE(object3->GetA() == c);
    REQUIRE(object3->GetX() == z);
    REQUIRE(TestUtility::IsAligned(object1, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(object2, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(object3, alignof(MyClass)) == true);
    
    // Delete second object so the block will be returned to the free list,
    // this will be the only free block in the list at this point because we know
    // no extra free block was create after allocating the third object
    delete object2;
    
    MyClass* object4 = new MyClass(d, zz);
    REQUIRE(object4->GetA() == d);
    REQUIRE(object4->GetX() == zz);
    REQUIRE(TestUtility::IsAligned(object4, alignof(MyClass)) == true);
    
    Allocator::FreeAll();
}

TEST_CASE("Allocate and free objects of different size", "Verify objects are allocated correctly")
{
    int totalSize = 300;
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
    REQUIRE(TestUtility::IsAligned(object1, alignof(MyClass)) == true);
    REQUIRE(TestUtility::IsAligned(object2, alignof(MyClass)) == true);
    REQUIRE(Allocator::NumberOfFreeBlocks() == 1);
    
    // Verify there are two free blocks after deleting object1
    delete object1;
    REQUIRE(Allocator::NumberOfFreeBlocks() == 2);
    
    // One of the two free blocks should be large enough to hold largeObject,
    // Verify the allocation is done correctly
    string lineA = "And I disappear";
    string lineB = "A ghost amidst the combat";
    string lineC = "Preparing to strike";
    string lineD = "Your eyes deceive you";
    string lineE = "An illusion fools you all";
    string lineF = "I move for the kill";
    LargeClass* largeObject = new LargeClass(lineA, lineB, lineC, lineD, lineE, lineF);
    
    REQUIRE(largeObject->GetA() == lineA);
    REQUIRE(largeObject->GetB() == lineB);
    REQUIRE(largeObject->GetC() == lineC);
    REQUIRE(largeObject->GetD() == lineD);
    REQUIRE(largeObject->GetE() == lineE);
    REQUIRE(largeObject->GetF() == lineF);
    REQUIRE(TestUtility::IsAligned(largeObject, alignof(LargeClass)) == true);
}


