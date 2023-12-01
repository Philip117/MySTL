#pragma once

namespace mystl
{
	// construct 构造对象
	template <typename Ty>
	void construct(Ty* ptr)
	{
		/*
		* new 根据编译器的不同，可以在堆上或者全局区上申请内存空间，::new 表示调用全局区的
		* new，即在全局区上申请内存空间，无视编译器的差异
		* 
		*/
		::new (static_cast<void*>(ptr)) Ty();
	}

	template <typename Ty1, typename Ty2>
	void construct(Ty1* ptr, const Ty2& value)
	{
		::new (static_cast<void*>(ptr)) Ty1(value);
	}

	template <typename Ty, typename... Args>
	void construct(Ty* ptr, Args&&... args)
	{
		::new (static_cast<void*>(ptr)) Ty(mystl::forward<Args>(args)...);
	}

	// 只写类型不写变量，属于哑元函数，一般用于向前兼容或区分重载的同名函数
	template <typename Ty>
	void destroy_one(Ty*, std::true_type) {}

	template <typename Ty>
	void destroy_one(Ty* pointer, std::false_type)
	{
		if (pointer != nullptr)
			pointer->~Ty();	// 调用对象自身的析构函数
	}

	template <typename ForwardIterator>
	void destroy_cat(ForwardIterator, ForwardIterator, std::true_type) {}
	
	template <typename ForwardIterator>
	void destroy_cat(ForwardIterator first, ForwardIterator last, std::false_type)
	{
		for (; first != last; first++)
			/*
			* &*first 表面上相当于 first，但它是先进行解引用（*），再取地址（&）
			* 若对空指针或者已经被销毁的元素进行单独的解引用或取地址操作，都会导致未定义行
			* 为而先进行解引用，再取地址，这种对解引用的结果取地址的操作却是安全的，不会导
			* 致未定义问题
			* 但要注意的是，这种操作仅适用于指针或迭代器指向对象的销毁操作，其它操作则仍需
			* 要先判空再操作
			*/
			destroy(&*first);
	}

	template <typename Ty>
	void destroy(Ty* pointer)
	{
		/*
		* ①is_trivially_destructible 用于判断该类是否使用了隐式定义的析构函数、析构函数是
		* 否为虚函数、基类的非静态成员变量自身是否为 is_trivially_destructible 的如果这个
		* 类有自定义的析构函数或析构函数为虚函数，则得到 std::false，匹配到函数 
		* ②destroy_one(Ty* pointer, std::false_type)，该函数调用该变量自定义的析构函数进
		* 行销毁否则得到 std::true，匹配到函数 destroy_one(Ty*, std::true_type)，该函数不
		* 做任何操作该变量会在其作用域结束时自行调用默认的析构函数进行销毁
		* ③std::is_trivially_destructible<Ty>{} 的 std::is_trivially_destructible<Ty>
		* 的结果是类型 std::true_type 或 std::false_type，这两个也是类型，函数只能传值，
		* 加上 {} 就是创建一个对象以传值
		*/
		destroy_one(pointer, std::is_trivially_destructible<Ty>{});
	}

	template <typename ForwardIterator>
	void destroy(ForwardIterator* first, ForwardIterator* last)
	{
		destroy_cat(first, last, std::is_trivially_destructible<
			typename iterator_traits<ForwardIterator>::value_type>{});
	}
}