#pragma once

#include <type_traits>	// std::true_type¡¢std::is_trivially_copy_assignable
#include "algobase.h"

namespace mystl
{
	template <typename ForwardIter, typename Size, typename T>
	ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::true_type)
	{
		return mystl::fill_n(first, n, value);
	}

	template <typename ForwardIter, typename Size, typename T>
	ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::false_type)
	{
		auto cur = first;
		try
		{
			for (; n > 0; n--, cur++)
				mystl::cons
		}
		catch (...)
		{
			for (; first != cur; first++)
				mystl::
		}

		return cur;
	}

	template <typename ForwardIter, typename Size, typename T>
	ForwardIter uninitialied_fill_n(ForwardIter first, Size n, const T& value, std::false_type)
	{
		/*
		*
		*/
		return mystl::unchecked_uninit_fill_n(first, n, value,
			std::is_trivially_copy_assignable<typename mystl::iterator_traits<ForwardIter>::value_type>{});
	}
}