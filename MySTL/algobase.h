#pragma once

// 该头文件包含 mystl 的基本算法

#include "util.h"
#include "iterator.h"

namespace mystl
{
	/*
	* 【作用】用三元运算符取二者中的较大值，相等时返回第一个参数
	*/
	template <typename T>
	const T& max(const T& lhs, const T& rhs)
	{
		return lhs < rhs ? rhs : lhs;
	}

	/*
	* 【作用】用函数comp代替三元运算符取二者中的较大值
	*/
	template <typename T, typename Compare>
	const T& max(const T& lhs, const T& rhs, Compare comp)
	{
		return comp(lhs, rhs) ? rhs : lhs;
	}

	/*
	* 【作用】用三元运算符取二者中的较小值，相等时返回第一个参数
	*/
	template <typename T>
	const T& min(const T& lhs, const T& rhs)
	{
		return rhs < lhs ? rhs : lhs;
	}

	/*
	* 【作用】用函数comp代替三元运算符取二者中的较小值
	*/
	template <typename T, typename Compare>
	const T& min(const T& lhs, const T& rhs, Compare comp)
	{
		return comp(rhs, lhs) ? rhs : lhs;
	}

	/*
	* 【作用】对调两个迭代器所指对象，可以是两个不同的迭代器
	* lhs 和 rhs 为地址
	*/
	template <typename FIter1, typename FIter2>
	void iter_swap(FIter1 lhs, FIter2 rhs)
	{
		mystl::swap(*lhs, *rhs);	// 交换指定元素
	}

	/*
	* 【作用】从 fitst 位置开始填充 n 个值
	*/
	template <typename OutputIter, typename Size, typename T>
	OutputIter unchecked_fill_n(OutputIter first, Size n, const T& value)
	{
		// 省去了定义新变量
		for (; n > 0; --n, first++)
		{
			*first = value;
		}

		return first;
	}

	template <typename OutputIter, typename Size, typename T>
	OutputIter fill_n(OutputIter first, Size n, const T& value)
	{
		return unchecked_fill_n(first, n, value);
	}

	/*
	* 【作用】将单向移动迭代器区间 [first, last) 的所有元素赋值为 value
	*/
	template <typename ForwardIter, typename T>
	void fill_cat(ForwardIter first, ForwardIter last, const T& value, mystl::forward_iterator_tag)
	{
		for (; first != last; first++)
		{
			*first = value;
		}
	}

	/*
	* 【作用】将随机读取迭代器区间 [first, last) 的所有元素赋值为 value
	*/
	template <typename RandomIter, typename T>
	void fill_cat(RandomIter first, RandomIter last, const T& value, mystl::random_access_iterator_tag)
	{
		fill_cat(first, last - first, value, iterator_category(first));
	}

	/*
	* 【作用】将单向移动迭代器区间 [first, last) 的所有元素赋值为 value？
	*/
	template <typename ForwardIter, typename T>
	void fill(ForwardIter first, ForwardIter last, const T& value, mystl::forward_iterator_tag)
	{
		fill_cat(first, last, value, iterator_category(first));
	}
}