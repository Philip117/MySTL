#pragma once

namespace mystl
{
	// construct �������
	template <typename Ty>
	void construct(Ty* ptr)
	{
		::new(static_cast<void*>ptr) Ty();
	}


}