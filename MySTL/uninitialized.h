#pragma once

#include <type_traits>	// std::true_type、std::is_trivially_copy_assignable
#include "algobase.h"
#include "construct.h"

namespace mystl
{
	/* 迭代器拥有复制运算符，直接用赋值运算符进行内存空间初始化
	* first				[IN]:	迭代器
	* n					[IN]:	初始化内存个数
	* value				[IN]:	用于初始化的值
	* std::true_type	[IN]:	哑元罢了
	*/
	template <typename ForwardIter, typename Size, typename T>
	ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::true_type)
	{
		return mystl::fill_n(first, n, value);
	}

	/* 迭代器没有复制运算符，但必须要有赋值运算符，用赋值运算符进行内存空间初始化，先前只
	* 申请了内存空间，并未初始化，妙
	* first				[IN]:	迭代器
	* n					[IN]:	初始化内存个数
	* value				[IN]:	用于初始化的值
	* std::true_type	[IN]:	哑元罢了
	*/
	template <typename ForwardIter, typename Size, typename T>
	ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::false_type)
	{
		auto cur = first;
		try
		{
			for (; n > 0; n--, cur++)
				mystl::construct(&*cur, *first);
		}
		catch (...)
		{
			for (; first != cur; first++)
				mystl::destroy(&*cur);
		}

		return cur;
	}

	/*
	*
	*/
	template <typename ForwardIter, typename Size, typename T>
	ForwardIter uninitialied_fill_n(ForwardIter first, Size n, const T& value)
	{
		/*
		* is_trivially_copy_assignable<T> 用于判断 T 是否具有复制运算符
		* 有的话，匹配到函数 unchecked_uninit_fill_n(..., std::true_type)，最终将直接用
		* = 进行复制，即调用复制运算符
		* 没有的话，匹配到函数 unchecked_uninit_fill_n(..., std::false_type)，最终用赋值
		* 运算符对原先申请的内存空间进行赋值，很巧妙
		*/
		return mystl::unchecked_uninit_fill_n(first, n, value,
			std::is_trivially_copy_assignable<typename mystl::iterator_traits<ForwardIter>::value_type>{});
	}
}