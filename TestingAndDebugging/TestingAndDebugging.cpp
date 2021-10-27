#include "pch.h"
#include "CppUnitTest.h"
#include "linked_list.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingAndDebugging
{
	// Test for linked_list methods
	TEST_CLASS(TestingAndDebugging)
	{
	public:
		// Test push() 
		TEST_METHOD(TestPush)
		{
			// create linked list
			linked_list<int> test_list;
			node<int>* head = NULL;
			// list should be: 8
			test_list.push(&head, 8);
			// list should be: 3, 8
			test_list.push(&head, 3);
			// check if values are adding
			Assert::IsNotNull(head);
			Assert::IsNotNull(head->next);
			// check that values are in correct place
			Assert::AreEqual(head->data, 3);
			Assert::AreEqual(head->next->data, 8);
		}
		// Test insert()
		TEST_METHOD(TestInsert)
		{
			// create linked list
			linked_list<int> test_list;
			node<int>* head = NULL;
			// list should be: 6
			test_list.push(&head, 6);
			// list should be: 6, 11
			test_list.insert(head, 11);
			// list should be: 6, 10, 11
			test_list.insert(head, 10);
			// check if values are adding
			Assert::IsNotNull(&head->next);
			Assert::IsNotNull(&head->next->next);
			// check that values are in correct place
			Assert::AreEqual(head->data, 6);
			Assert::AreEqual(head->next->data, 10);
			Assert::AreEqual(head->next->next->data, 11);
		}
		TEST_METHOD(TestDelete)
		{
			// create linked list
			linked_list<int> test_list;
			node<int>* head = NULL;
			// list should be: 90		
			test_list.append(&head, 90);
			// list should be: 90, 130
			test_list.append(&head, 130);
			// list should be: 90, 130, 598
			test_list.append(&head, 598);
			// list after delete should be: 90, 598
			test_list.delete_node_at_position(&head, 2);
			// test values in place
			Assert::AreEqual(head->data, 90);
			Assert::AreEqual(head->next->data, 598);
		}
		TEST_METHOD(TestSortLowToHigh)
		{
			// create linked list
			linked_list<int> test_list;
			node<int>* head = NULL;
			// fill list with values
			test_list.append(&head, 213);
			test_list.append(&head, 1234);
			test_list.append(&head, 538912);
			test_list.append(&head, 4389);
			// sort
			test_list.sort(head);
			// list after sort should be: 213, 1234, 4389, 538912
			Assert::AreEqual(head->data, 213);
			Assert::AreEqual(head->next->data, 1234);
			Assert::AreEqual(head->next->next->data, 4389);
			Assert::AreEqual(head->next->next->next->data, 538912);
		}
	};
}
