#include <iostream>
#include "linked_list.h"

int main()
{
	linked_list<int> my_list;
	node<int>* head = NULL;
	my_list.print_all_node_data(head);
	std::cout << "Choose one of the following (a) to add to end, (de) to delete, (ap) to add at start" << std::endl;
	bool valid_input;
	std::string input;
	std::cin >> input;
	input == "a" || input == "de" || input == "ap" || input == "s" ? valid_input = true : valid_input = false;
	while (valid_input == true)
	{
		if (input == "a")
		{
			int num_to_add;
			std::cout << "Enter something to add to start: " << std::endl;
			std::cin >> num_to_add;
			my_list.push(&head, num_to_add);
		}
		else if (input == "de")
		{
			int index_to_delete;
			std::cout << "Enter an position to delete (starts at 1): " << std::endl;
			std::cin >> index_to_delete;
			my_list.delete_node_at_position(&head, index_to_delete);
		}
		else if (input == "ap")
		{
			int new_number;
			std::cout << "Enter a number to add to end: " << std::endl;
			std::cin >> new_number;
			my_list.append(&head, new_number);
		}
		else if (input == "s")
		{
			if (my_list.is_empty(head) == false)
			{
				my_list.sort(head);
				std::cout << "sucessfully sorted" << std::endl;
			}
			else
			{
				std::cout << "there is nothing in the list" << std::endl;
			}
		}
		else
		{
			std::cout << "Something went wrong." << std::endl;
			return 1;
		}
		my_list.print_all_node_data(head);
		std::cout << "Choose one of the following (a) to add to start, (de) to delete at position, (ap) to add at end, (s) to sort the list" << std::endl;
		std::cin >> input;
		input == "a" || input == "de" || input == "ap" || input == "s" ? valid_input = true : valid_input = false;
	}

	system("pause");
}