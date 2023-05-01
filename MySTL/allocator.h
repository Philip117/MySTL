#pragma once



namespace mystl
{
	template <typename T>
	class allocator
	{
		// ���б���
	public:
		typedef T value_type;	// ���������� T ����Ϊvalue_type
		typedef T* pointer;
		typedef size_t size_type;

		// ���к���
	public:
		static T* allocate();
		static T* allocate(size_type n);
	};

	template <typename T>
	T* allocator<T>::allocate()
	{
		// ������ new ����һ�����󣬺��� operator new() �����ڴ�ռ�
		return static_cast<T*>(::operator new(sizeof(T)));
	}

	template <typename T>
	T* allocator<T>::allocate(size_type n)
	{
		if (n == 0)
			return nullptr;
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}
}