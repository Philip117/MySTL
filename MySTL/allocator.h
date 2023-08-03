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
		// new 操作符做两件事：分配内存和调用构造函数初始化
		// 函数 operator new() 则负责分配内存空间，返回未初始化的内存
		// :: 可以用作：①命名空间作用域符号；②全局作用域符号；③（类）作用域符号
		// 此处是②全局作用域符号
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