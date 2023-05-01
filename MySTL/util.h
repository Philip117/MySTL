#pragma once

#include <cstddef>	// ���� C ��׼���ͷ <stddef.h> ����������������ӵ� std �����ռ䡣�����˱�ͷ��ȷ��ʹ�� C ��׼���ͷ�е��ⲿ������������������ std �����ռ���������

namespace mystl
{
	/*
	* �����á���ȥ���ã��������úͳ�����
	* typename ����ʱ remove_reference<T> ��δʵ����������� typename �Ը�֪������ type ��һ�����Ա
	* remove_reference<T> ������ȥ���ã��� T Ϊ int&������ȥ��Ϊ int
	* ::type ��ʾȥ�����ú������
	* T&& �������ã�����ֵ���� T&& ������ֵ���� T&&�����������۵�Ϊ��ֵ���� T&
	* https://blog.csdn.net/CegghnnoR/article/details/127197501
	* noexcept ��֪�������ú������ᷢ���쳣��������һ���̶��ϼ��ٺ�����������ɵ�Ŀ�����
	* ��ʵ��ʹ���б���������ܻᱼ��
	* https://blog.csdn.net/weixin_42923076/article/details/124637003
	*/
	template <typename T>
	typename std::remove_reference<T>::type&& move(T&& arg) noexcept
	{
		/*
		* static_cast ǿ������ת�����൱�� C ���Ե�ǿ������ת��
		*/
		return static_cast<typename std::remove_reference<T>::type&&>(arg);
	}

	/*
	* �����ܡ���������Ԫ��
	*/
	template <typename T>
	void swap(T& lhs, T& rhs)
	{
		auto tmp(mystl::move(lhs));	// tmp() ��д�������˻������ͺ�������
		lhs = mystl::move(rhs);
		rhs = mystl::move(tmp);
	}
}