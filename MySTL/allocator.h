#pragma once



namespace mystl
{
	template <typename T>
	class allocator
	{
		// 公有别名
	public:
		typedef T value_type;	// 将变量类型 T 别名为value_type
		typedef T* pointer;
		typedef size_t size_type;

		// 公有函数
	public:
		static T* allocate();
		static T* allocate(size_type n);
	};

	template <typename T>
	T* allocator<T>::allocate()
	{
		// 操作符 new 分配一个对象，函数 operator new() 分配内存空间
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