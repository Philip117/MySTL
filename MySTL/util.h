#pragma once

#include <cstddef>	// 包含 C 标准库标头 <stddef.h> 并将关联的名称添加到 std 命名空间。包含此标头可确保使用 C 标准库标头中的外部链接声明的名称已在 std 命名空间中声明。

namespace mystl
{
	/*
	* 【作用】消去引用，包括引用和常引用
	* typename 编译时 remove_reference<T> 尚未实例化，需加上 typename 以告知编译器 type 是一个类成员
	* remove_reference<T> 用于消去引用，若 T 为 int&，则消去后为 int
	* ::type 表示去除引用后的类型
	* T&& 万能引用，传右值引用 T&& 后还是右值引用 T&&，其它均被折叠为左值引用 T&
	* https://blog.csdn.net/CegghnnoR/article/details/127197501
	* noexcept 告知编译器该函数不会发出异常，可以在一定程度上减少函数编译后生成的目标代码
	* 若实际使用中报错，程序可能会奔溃
	* https://blog.csdn.net/weixin_42923076/article/details/124637003
	*/
	template <typename T>
	typename std::remove_reference<T>::type&& move(T&& arg) noexcept
	{
		/*
		* static_cast 强制类型转换，相当于 C 语言的强制类型转换
		*/
		return static_cast<typename std::remove_reference<T>::type&&>(arg);
	}

	/*
	* 【功能】交换两个元素
	*/
	template <typename T>
	void swap(T& lhs, T& rhs)
	{
		auto tmp(mystl::move(lhs));	// tmp() 的写法兼容了基本类型和类类型
		lhs = mystl::move(rhs);
		rhs = mystl::move(tmp);
	}
}