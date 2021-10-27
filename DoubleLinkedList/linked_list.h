#pragma once

template <typename T>
class node
{
public:
	int data;
	node<T>* next;
	node<T>* prev;
};

template <typename T>
class linked_list
{
private:

public:
	int m_node_count = 0;
	//sentinal nodes
	node<T>* m_start = nullptr;
	node<T>* m_end = nullptr;

	linked_list<T>()
	{
		//allocate memory
		m_start = new node<T>();
		m_end = new node<T>();
	}

	void push(node<T>** head_ref, int new_data)
	{
		//allocate node
		node<T>* new_node = new node<T>();
		//put in data
		new_node->data = new_data;
		//make next of new node as head and previous as NULL
		new_node->next = (*head_ref);
		new_node->prev = NULL;
		//change prev of head node to new node
		if ((*head_ref) != NULL)
		{
			(*head_ref)->prev = new_node;
		}
		//move the head to point to the new node
		(*head_ref) = new_node;
		m_node_count++;

	}
	void insert(node<T>* prev_node, int new_data)
	{
		//check if the given prev_node is NULL
		if (prev_node == NULL)
		{
			std::cout << "the given previous node cannot be NULL\n";
			return;
		}
		//allocate new node
		node<T>* new_node = new node<T>();
		// put in the data
		new_node->data = new_data;
		//make the next of new node as next of prev node
		new_node->next = prev_node->next;
		//make the next of prev_node as new node
		prev_node->next = new_node;
		//make prev_node as previous of new node
		new_node->prev = prev_node;
		// change orevious of new_node's next node
		if (new_node->next != NULL)
		{
			new_node->next->prev = new_node;
		}
		m_node_count++;
	}

	void append(node<T>** head_ref, int new_data)
	{
		//allocate node
		node<T>* new_node = new node<T>();
		node<T>* last = *head_ref;
		//put in the data
		new_node->data = new_data;
		//this new node is going to be the last node, so make next of it as NULL
		new_node->next = NULL;
		//if the linked list is empty, then make the new node as head
		if (*head_ref == NULL)
		{
			new_node->prev = NULL;
			*head_ref = new_node;
			return;
		}
		// else traverse till the last node
		while (last->next != NULL)
		{
			last = last->next;
		}
		//change the next of last node
		last->next = new_node;
		//make last node as previous of new node
		new_node->prev = last;
		m_node_count++;
		return;
	}

	void delete_node(node<T>** head_ref, node<T>* del)
	{
		//base case
		if (*head_ref == NULL || del == NULL)
		{
			return;
		}
		//if node to be deleted is head node
		if (*head_ref == del)
		{
			*head_ref = del->next;
		}
		//change next only if node to be deleted is not the last node
		if (del->next != NULL)
		{
			del->next->prev = del->prev;
		}
		//change prev only if node to be deleted is not the first node
		if (del->prev != NULL)
		{
			del->prev->next = del->next;
		}
		// free the memory occupied by del
		delete del;
		m_node_count--;
	}

	void delete_node_at_position(node<T>** head_ref, int n)
	{
		if (*head_ref == NULL || n <= 0)
		{
			return;
		}
		node<T>* current = *head_ref;

		for (int i = 1; current != NULL && i < n; i++)
		{
			current = current->next;
		}

		if (current == NULL)
		{
			return;
		}
		delete_node(head_ref, current);
		m_node_count--;
	}

	//function to delete all nodes from the double linked list divisble by k
	void delete_all_nodes(node<T>** head_ref, int K)
	{
		node<T>* ptr = *head_ref;
		node<T>* next;

		while (ptr != NULL)
		{
			next = ptr->next;
			//if true, delete node 'ptr'
			if (ptr->data % K == 0)
			{
				delete_node(head_ref, ptr);
				m_node_count--;
				ptr = next;
			}
		}
	}

	//delete first node
	node<T>* remove_first_node(node<T>* head)
	{
		if (head == NULL)
		{
			return NULL;
		}
		//move head pointer to next node
		node<T>* temp = head;
		head = head->next;

		delete temp;
		m_node_count--;
		return head;
	}

	// find if list is empty
	bool empty() const
	{
		if (m_start == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// check if head is empty
	bool is_empty(node<T>* head)
	{
		if (head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//takes head pointer of linked list and index as argument and return data at index
	int find_node(node<T>* head, int index)
	{
		node<T>* current = head;

		//the index of the node we're currently looking at
		int count = 0;
		while (current != NULL)
		{
			if (count == index)
			{
				return (current->data);
			}
			count++;
			current = current->next;
		}
	}

	// print all node data starting from node given in arg
	void print_all_node_data(node<T>* node)
	{
		std::cout << "Your list: ";
		while (node != NULL)
		{
			std::cout << node->data << ", ";
			node = node->next;
		}
		std::cout << std::endl;
	}

	// sort list 
	void sort(node<T>* head)
	{
		struct node<T>* current = NULL, * index = NULL;
		int temp;
		if (head == NULL)
		{
			return;
		}
		else
		{
			for (current = head; current->next != NULL; current = current->next)
			{
				for (index = current->next; index != NULL; index = index->next)
				{
					if (current->data > index->data)
					{
						temp = current->data;
						current->data = index->data;
						index->data = temp;
					}
				}
			}
		}

	}
};
