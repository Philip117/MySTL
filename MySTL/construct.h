#pragma once

namespace mystl
{
	// construct 构造对象
	template <typename Ty>
	void construct(Ty* ptr)
	{
		::new(static_cast<void*>ptr) Ty();
	}

	template <typename Ty1, typename Ty2>
	void construct(Ty1* ptr, const Ty2& value)
	{
		::new (static_cast<void*>ptr) Ty1(value);
	}

	template <typename Ty, typename... Args>
	void construct(Ty* ptr, Args&&... args)
	{
		::new (static_cast<void*>) Ty(mystl::forward)
	}
}