#pragma once

namespace mystl
{
	// construct 构造对象
	template <typename Ty>
	void construct(Ty* ptr)
	{
		::new(static_cast<void*>ptr) Ty();
	}


}