#pragma once

//#include <cstring>
#include "util.h"

namespace mystl
{
	/*
	* �����á�����Ԫ�����ȡ�����еĽϴ�ֵ�����ʱ���ص�һ������
	*/
	template <typename T>
	const T& max(const T& lhs, const T& rhs)
	{
		return lhs < rhs ? rhs : lhs;
	}

	/*
	* �����á��ú���comp������Ԫ�����ȡ�����еĽϴ�ֵ
	*/
	template <typename T, typename Compare>
	const T& max(const T& lhs, const T& rhs, Compare comp)
	{
		return comp(lhs, rhs) ? rhs : lhs;
	}

	/*
	* �����á�����Ԫ�����ȡ�����еĽ�Сֵ�����ʱ���ص�һ������
	*/
	template <typename T>
	const T& min(const T& lhs, const T& rhs)
	{
		return rhs < lhs ? rhs : lhs;
	}

	/*
	* �����á��ú���comp������Ԫ�����ȡ�����еĽ�Сֵ
	*/
	template <typename T, typename Compare>
	const T& min(const T& lhs, const T& rhs, Compare comp)
	{
		return comp(rhs, lhs) ? rhs : lhs;
	}

	/*
	* �����á��Ե�������������ָ���󣬿�����������ͬ�ĵ�����
	* lhs �� rhs Ϊ��ַ
	*/
	template <typename FIter1, typename FIter2>
	void iter_swap(FIter1 lhs, FIter2 rhs)
	{
		mystl::swap(*lhs, *rhs);	// ����ָ��Ԫ��
	}
}