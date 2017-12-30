#ifndef __CSTACK_LIST_HPP_DEF__
#define __CSTACK_LIST_HPP_DEF__

#include <iostream>
#include <sstream>

struct
{
	int* data_free[1024];
	int size_free = 0;
}free_el;

template <class T>
class CStackList
{
	private:
		struct Node
		{
			T data;

			Node* next;
			Node* prev;
		};

		Node* head = nullptr;
		Node* tail = nullptr;

		int stack_size = 0;

	public:
		CStackList(){};
		~CStackList()
		{
			Node* p = head;

			while (p != nullptr)
			{
				head = head->next;
				delete p;
				p = head;
			}

			head       = nullptr;
			tail       = nullptr;
			stack_size =       0;
		};

		CStackList& operator=(const CStackList&);
		T& operator[](const int) const;

		template <class U>
		friend std::ostream& operator<<(std::ostream&, const CStackList<U>&);

		template <class U>
		friend std::istream& operator>>(std::istream&, CStackList<U>&);

		void Push(const T&);
		T Pop(bool);
		void TrackMemory(std::ostream&);

		int size() const;
		bool is_empty() const;
		T top() const;
};

template <class T>
CStackList<T>& CStackList<T>::operator=(const CStackList<T>& stack)
{
	if (this != &stack)
	{
		Node* iter;
		for (iter = stack.head; iter; iter = iter->next)
		{
			this->Push(iter->data);
		}
	}

	return *this;
}

template <class T>
T& CStackList<T>::operator[](const int index) const
{
	Node* current = head;
	for (int i = 0; i < index; ++i)
	{
		current = current->next;
	}

	return current->data;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const CStackList<T>& stack)
{
	out << '\n';
	typename CStackList<T>::Node* iter;
	for (iter = stack.head; iter; iter = iter->next)
	{
		out << "Element: " << iter->data << '\n';
	
		//T *pa = &iter->data;
		//printf("Address: %p\n", pa);
		//out << "Адрес: " << pa << '\n';
	}
//	out << "All Address: " << size_free << '\n';
	for (iter = stack.head; iter; iter = iter->next)
	{
		out << ((int*)&(iter->data)) << '\n';
	}
	out << "Free Address: " << free_el.size_free << '\n';
	for (int i = 0; i < free_el.size_free; ++i)
	{
		out << free_el.data_free[i] << ' ';
	}
	out << '\n';
	return out;
}

template <class T>
std::istream& operator>>(std::istream& in, CStackList<T>& stack)
{
	T item;
	//printf("\nInput count elements: ");
	std::string input;
	while (std::getline(in, input) && !input.empty())
	{

		std::stringstream stream(input);
		while (!stream.eof())
		{
			stream >> item;

			if (!static_cast<T>(item))
			{
				throw std::invalid_argument("INVALID ARGUMENT TYPE!!!");
			}

			stack.Push(item);
		}

		if (std::is_same<T, char>::value)
		{
			stack.Pop(false);
		}
	}/*
	int count = 0;
	in >> count;
	//while (input != "\n")
	printf("Input Elements:\n");
	for (; count; --count)
	{
		in >> item;
		if (!static_cast<T>(item))
		{
			throw std::invalid_argument("INVALID ARGUMENT TYPE!!!");
		}
		stack.Push(item);
	}
*/
	return in;
}

template <class T>
void CStackList<T>::Push(const T& item)
{
	Node* node = new Node;;

	node->data = item;

	if (tail)
	{
		tail->next = node;
	}

	node->next = nullptr;
	node->prev = tail;
	tail = node;
	
	if (head == nullptr)
	{
		head = node;
	}
	
	for (int i = 0; i < free_el.size_free; ++i)
	{
		if (free_el.data_free[i] == (int*)&(node->data))
		{
			for (int j = i + 1; j < free_el.size_free - 1; ++j)
			{
				free_el.data_free[j-1] = free_el.data_free[j];
			}
			free_el.data_free[i] = 0;
			free_el.size_free--;
			break;
		}
	}
	++stack_size;
}

template <class T>
T CStackList<T>::Pop(bool flag)
{
	if (is_empty())
	{
		//T result = *(next_item);
		printf("EMPTY STACK!!!");
		T result;//= tail->data;
		return result;
		//throw std::range_error("EMPTY STACK!!!");
	}

	Node* temp = tail->prev;

	if (head != tail)
	{
		temp->next = nullptr;
	}
	if (flag)
	{
		//printf("\n\n\n\nCHECK\n");
		free_el.data_free[free_el.size_free] = (int*)&(tail->data);
		free_el.size_free++;
	}

	T result = tail->data;

	delete tail;

	if (head != tail)
	{
		tail = temp;
	}
	else
	{
		head = tail = nullptr;
	}

	--stack_size;

	return result;
}

template <class T>
void CStackList<T>::TrackMemory(std::ostream& out)
{
	for (struct Node* iter = head; iter; iter = iter->next)
	{
		out << iter << ' ';
	}

	out << std::endl;
}

template <class T>
int CStackList<T>::size() const
{
	return stack_size;
}

template <class T>
bool CStackList<T>::is_empty() const
{
	return stack_size == 0;
}

template <class T>
T CStackList<T>::top() const
{
	return tail->data;
}

#endif // __CSTACK_LIST_HPP_DEF__
