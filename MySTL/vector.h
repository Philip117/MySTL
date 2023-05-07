#pragma once

#include "memory.h"

namespace mystl
{
	template <typename T>
	class vector
	{
		/*
		* static_assert(value, err) value 为 true 时输出 err
		* STL 中，vector<bool> a是存在的，但是存储时一个字节存储了 8 个 bool 型变量
		* 这导致 &a[1] 到 &a[7] 都无法获取到对应的 4/8 字节的地址
		*/
		static_assert(!std::is_same<bool, T>::value, "vector<bool> is abandoned in mystl");

		// 公有变量和别名
	public:
		typedef mystl::allocator<T> allocator_type;
		typedef mystl::allocator<T> data_allocator;

		// 因为编译时 allocator_type 尚未实例化，需加上 typename 以告知编译器 value_type 是一个类成员
		typedef typename allocator_type::value_type value_type;
		typedef typename allocator_type::size_type size_type;

		typedef value_type* iterator;

		// 私有变量
	private:
		iterator begin_;	// 目前使用空间的头部
		iterator end_;	// 目前使用空间的尾部
		iterator cap_;	// 目前存储空间的尾部？

	public:
		vector() noexcept
		{
			try_init();
		}

		/*
		* explicit 只能修饰只有一个参数的构造函数，表明该构造函数不允许隐式类型转换
		* 也不能用于复制初始化
		*/
		explicit vector(size_type n)
		{
			fill_init()
		}

	private:
		void try_init() noexcept;	// 默认初始化容量为 16 的 vector
		void init_space(size_type size, size_type cap);	// 初始化大小为 size、容量为 cap 的vector
		void fill_init(size_type n, const value_type& value);	// 初始化大小为 n 的 vector，填充默认值为 value
	};

	template <typename T>
	void vector<T>::try_init() noexcept
	{
		try
		{
			begin_ = data_allocator::allocate(16);	// 默认可存 16 个元素
			end_ = begin_;
			cap_ = begin_ + 16;
		}
		catch(...)	// ... 表示捕获所有类型的异常
		{
			begin_ = nullptr;
			end_ = nullptr;
			cap_ = nullptr;
		}
	}

	template <typename T>
	void vector<T>::init_space(size_type size, size_type cap)
	{
		try
		{
			begin_ = data_allocator::allocate(cap);
			end_ = begin_ + size;
			cap_ = begin_ + cap;
		}
		catch (...)
		{
			begin_ = nullptr;
			end_ = nullptr;
			cap_ = nullptr;
			throw;	// 抛出异常，后续语句不会执行，相当于return
		}
	}

	template<typename T>
	void vector<T>::fill_init(size_type n, const value_type& value)
	{
		const size_type init_size = mystl::max(static_cast<size_type>(16), n);	// 取默认长度和所给大小的最大值
		init_space(n, init_size);	// 初始化vector
		mystl::uninitialied_fill_n(begin_, n, value);	// 填充默认值
	}
}