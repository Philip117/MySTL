#pragma once

//#include <cstring>
#include "util.h"

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
}