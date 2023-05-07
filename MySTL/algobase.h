#pragma once

// ��ͷ�ļ����� mystl �Ļ����㷨

#include "util.h"
#include "iterator.h"

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

	/*
	* �����á��� fitst λ�ÿ�ʼ��� n ��ֵ
	*/
	template <typename OutputIter, typename Size, typename T>
	OutputIter unchecked_fill_n(OutputIter first, Size n, const T& value)
	{
		// ʡȥ�˶����±���
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
	* �����á��������ƶ����������� [first, last) ������Ԫ�ظ�ֵΪ value
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
	* �����á��������ȡ���������� [first, last) ������Ԫ�ظ�ֵΪ value
	*/
	template <typename RandomIter, typename T>
	void fill_cat(RandomIter first, RandomIter last, const T& value, mystl::random_access_iterator_tag)
	{
		fill_cat(first, last - first, value, iterator_category(first));
	}

	/*
	* �����á��������ƶ����������� [first, last) ������Ԫ�ظ�ֵΪ value��
	*/
	template <typename ForwardIter, typename T>
	void fill(ForwardIter first, ForwardIter last, const T& value, mystl::forward_iterator_tag)
	{
		fill_cat(first, last, value, iterator_category(first));
	}
}