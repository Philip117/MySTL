#pragma once

namespace mystl
{
	// construct �������
	template <typename Ty>
	void construct(Ty* ptr)
	{
		/*
		* new ���ݱ������Ĳ�ͬ�������ڶ��ϻ���ȫ�����������ڴ�ռ䣬::new ��ʾ����ȫ������
		* new������ȫ�����������ڴ�ռ䣬���ӱ������Ĳ���
		* 
		*/
		::new (static_cast<void*>(ptr)) Ty();
	}

	template <typename Ty1, typename Ty2>
	void construct(Ty1* ptr, const Ty2& value)
	{
		::new (static_cast<void*>(ptr)) Ty1(value);
	}

	template <typename Ty, typename... Args>
	void construct(Ty* ptr, Args&&... args)
	{
		::new (static_cast<void*>(ptr)) Ty(mystl::forward<Args>(args)...);
	}

	// ֻд���Ͳ�д������������Ԫ������һ��������ǰ���ݻ��������ص�ͬ������
	template <typename Ty>
	void destroy_one(Ty*, std::true_type) {}

	template <typename Ty>
	void destroy_one(Ty* pointer, std::false_type)
	{
		if (pointer != nullptr)
			pointer->~Ty();	// ���ö����������������
	}

	template <typename ForwardIterator>
	void destroy_cat(ForwardIterator, ForwardIterator, std::true_type) {}
	
	template <typename ForwardIterator>
	void destroy_cat(ForwardIterator first, ForwardIterator last, std::false_type)
	{
		for (; first != last; first++)
			/*
			* &*first �������൱�� first���������Ƚ��н����ã�*������ȡ��ַ��&��
			* ���Կ�ָ������Ѿ������ٵ�Ԫ�ؽ��е����Ľ����û�ȡ��ַ���������ᵼ��δ������
			* Ϊ���Ƚ��н����ã���ȡ��ַ�����ֶԽ����õĽ��ȡ��ַ�Ĳ���ȴ�ǰ�ȫ�ģ����ᵼ
			* ��δ��������
			* ��Ҫע����ǣ����ֲ�����������ָ��������ָ���������ٲ�������������������
			* Ҫ���п��ٲ���
			*/
			destroy(&*first);
	}

	template <typename Ty>
	void destroy(Ty* pointer)
	{
		/*
		* ��is_trivially_destructible �����жϸ����Ƿ�ʹ������ʽ�������������������������
		* ��Ϊ�麯��������ķǾ�̬��Ա���������Ƿ�Ϊ is_trivially_destructible ��������
		* �����Զ����������������������Ϊ�麯������õ� std::false��ƥ�䵽���� 
		* ��destroy_one(Ty* pointer, std::false_type)���ú������øñ����Զ��������������
		* �����ٷ���õ� std::true��ƥ�䵽���� destroy_one(Ty*, std::true_type)���ú�����
		* ���κβ����ñ������������������ʱ���е���Ĭ�ϵ�����������������
		* ��std::is_trivially_destructible<Ty>{} �� std::is_trivially_destructible<Ty>
		* �Ľ�������� std::true_type �� std::false_type��������Ҳ�����ͣ�����ֻ�ܴ�ֵ��
		* ���� {} ���Ǵ���һ�������Դ�ֵ
		*/
		destroy_one(pointer, std::is_trivially_destructible<Ty>{});
	}

	template <typename ForwardIterator>
	void destroy(ForwardIterator* first, ForwardIterator* last)
	{
		destroy_cat(first, last, std::is_trivially_destructible<
			typename iterator_traits<ForwardIterator>::value_type>{});
	}
}