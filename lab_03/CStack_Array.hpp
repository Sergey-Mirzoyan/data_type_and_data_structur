#ifndef __CSTACK_ARRAY_HPP_DEF__
#define __CSTACK_ARRAY_HPP_DEF__

#include <iostream>
#include <stdio.h>
#include <sstream>

template <class T>
class CStackArray
{
	private:
		const int multiply_coef = 4;

		T* base = nullptr;
		T* next_item = nullptr;
		int base_size = 0;
		int stack_size = 0;

		void Memcpy(T*, T*, const int);
		void ReallocateMemory(const int);
		void ReserveMemory(const int);

	public:
		CStackArray(){};
		CStackArray(const CStackArray& stack)
		{
			if (this != &stack)
			{
				ReserveMemory(stack.stack_size);
				Memcpy(stack.base, this->base, stack.stack_size);
			}
		};
		~CStackArray()
		{
			delete [] base;

			base       = nullptr;
			next_item  = nullptr;
			base_size  =       0;
			stack_size =       0;
		}
		CStackArray& operator=(const CStackArray&);
		T& operator[](const int) const;

		template <class U>
		friend std::ostream& operator<<(std::ostream&, const CStackArray<U>&);

		template <class U>
		friend std::istream& operator>>(std::istream&, CStackArray<U>&);

		void Push(const T&);
		T Pop(bool);
		void TrackMemory(std::ostream&);

		int size() const;
		bool is_empty() const;
		T top() const;
};

template <class T>
void CStackArray<T>::Memcpy(T* from, T* to, const int count)
{
	T* fPtr = from;
	T* tPtr = to;

	for (int i = 0; i < count; ++i)
	{
		tPtr[i] = fPtr[i];
	}
}

template <class T>
void CStackArray<T>::ReallocateMemory(const int new_size)
{
	if (new_size < 0)
	{
		throw std::invalid_argument("INVALID ARGUMENT!!!");
	}

	T* new_base = new T[new_size];
	int size_to_copy = stack_size < new_size ? stack_size : new_size;

	Memcpy(base, new_base, size_to_copy);

	delete [] base;
	base = new_base;
	base_size = new_size;
}

template <class T>
void CStackArray<T>::ReserveMemory(const int size)
{
	int diff = base_size - size;

	if (diff <= 0)
	{
		ReallocateMemory(size * multiply_coef);
		next_item = base + size;
	} else
	{
		next_item += size - stack_size;
	}

	stack_size = size;
}

template <class T>
CStackArray<T>& CStackArray<T>::operator=(const CStackArray<T>& stack)
{
	if (this != &stack)
	{
		ReserveMemory(stack.stack_size);
		Memcpy(stack.base, this->base, stack.stack_size);
	}

	return *this;
}

template <class T>
T& CStackArray<T>::operator[](const int index) const
{
	return base[index];
}

template <class T>
std::ostream& operator<<(std::ostream& out, const CStackArray<T>& stack)
{
	for (int i = 0; i < stack.stack_size; ++i)
	{
		out << stack.base[i] << ' ';
	}

	return out;
}

template <class T>
std::istream& operator>>(std::istream& in, CStackArray<T>& stack)
{
	T item;
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
	}

	return in;
}

// Public methods
template <class T>
void CStackArray<T>::Push(const T& item)
{
	ReserveMemory(stack_size + 1);
	*(next_item - 1) = item;
}

template <class T>
T CStackArray<T>::Pop(bool flag)
{
	if (flag)
	{
		printf("s");
	}
	if (is_empty())
	{
		T result;
		printf("EMPTY STACK!!!");
		return result;
		//throw std::range_error("EMPTY STACK!!!");
	}

	T result = *(next_item - 1);
	ReserveMemory(stack_size - 1);

	return result;
}

template <class T>
void CStackArray<T>::TrackMemory(std::ostream& out)
{
	for (T* iter = base; iter != next_item; ++iter)
	{
		out << iter << ' ';
	}

	out << std::endl;
}

// Getters & setters
template <class T>
int CStackArray<T>::size() const
{
	return stack_size;
}

template <class T>
bool CStackArray<T>::is_empty() const
{
	return stack_size == 0;
}

template <class T>
T CStackArray<T>::top() const
{
	return *(next_item - 1);
}

#endif // __CSTACK_ARRAY_HPP_DEF__
