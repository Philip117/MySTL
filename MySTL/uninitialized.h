#pragma once

#include <type_traits>	// std::true_type��std::is_trivially_copy_assignable
#include "algobase.h"
#include "construct.h"

namespace mystl
{
	/* ������ӵ�и����������ֱ���ø�ֵ����������ڴ�ռ��ʼ��
	* first				[IN]:	������
	* n					[IN]:	��ʼ���ڴ����
	* value				[IN]:	���ڳ�ʼ����ֵ
	* std::true_type	[IN]:	��Ԫ����
	*/
	template <typename ForwardIter, typename Size, typename T>
	ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::true_type)
	{
		return mystl::fill_n(first, n, value);
	}

	/* ������û�и����������������Ҫ�и�ֵ��������ø�ֵ����������ڴ�ռ��ʼ������ǰֻ
	* �������ڴ�ռ䣬��δ��ʼ������
	* first				[IN]:	������
	* n					[IN]:	��ʼ���ڴ����
	* value				[IN]:	���ڳ�ʼ����ֵ
	* std::true_type	[IN]:	��Ԫ����
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
		* is_trivially_copy_assignable<T> �����ж� T �Ƿ���и��������
		* �еĻ���ƥ�䵽���� unchecked_uninit_fill_n(..., std::true_type)�����ս�ֱ����
		* = ���и��ƣ������ø��������
		* û�еĻ���ƥ�䵽���� unchecked_uninit_fill_n(..., std::false_type)�������ø�ֵ
		* �������ԭ��������ڴ�ռ���и�ֵ��������
		*/
		return mystl::unchecked_uninit_fill_n(first, n, value,
			std::is_trivially_copy_assignable<typename mystl::iterator_traits<ForwardIter>::value_type>{});
	}
}