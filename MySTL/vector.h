#pragma once

#include "memory.h"

namespace mystl
{
	template <typename T>
	class vector
	{
		/*
		* static_assert(value, err) value Ϊ true ʱ��� err
		* STL �У�vector<bool> a�Ǵ��ڵģ����Ǵ洢ʱһ���ֽڴ洢�� 8 �� bool �ͱ���
		* �⵼�� &a[1] �� &a[7] ���޷���ȡ����Ӧ�� 4/8 �ֽڵĵ�ַ
		*/
		static_assert(!std::is_same<bool, T>::value, "vector<bool> is abandoned in mystl");

		// ���б����ͱ���
	public:
		typedef mystl::allocator<T> allocator_type;
		typedef mystl::allocator<T> data_allocator;

		// ��Ϊ����ʱ allocator_type ��δʵ����������� typename �Ը�֪������ value_type ��һ�����Ա
		typedef typename allocator_type::value_type value_type;
		typedef typename allocator_type::size_type size_type;

		typedef value_type* iterator;

		// ˽�б���
	private:
		iterator begin_;	// Ŀǰʹ�ÿռ��ͷ��
		iterator end_;	// Ŀǰʹ�ÿռ��β��
		iterator cap_;	// Ŀǰ�洢�ռ��β����

	public:
		vector() noexcept
		{
			try_init();
		}

		/*
		* explicit ֻ������ֻ��һ�������Ĺ��캯���������ù��캯����������ʽ����ת��
		* Ҳ�������ڸ��Ƴ�ʼ��
		*/
		explicit vector(size_type n)
		{
			fill_init()
		}

	private:
		void try_init() noexcept;	// Ĭ�ϳ�ʼ������Ϊ 16 �� vector
		void init_space(size_type size, size_type cap);	// ��ʼ����СΪ size������Ϊ cap ��vector
		void fill_init(size_type n, const value_type& value);	// ��ʼ����СΪ n �� vector�����Ĭ��ֵΪ value
	};

	template <typename T>
	void vector<T>::try_init() noexcept
	{
		try
		{
			begin_ = data_allocator::allocate(16);	// Ĭ�Ͽɴ� 16 ��Ԫ��
			end_ = begin_;
			cap_ = begin_ + 16;
		}
		catch(...)	// ... ��ʾ�����������͵��쳣
		{
			begin_ = nullptr;
			end_ = nullptr;
			cap_ = nullptr;
		}
	}

	template <typename T>
	void vector<T>::init_space(size_type size, size_type cap)
	{
		try
		{
			begin_ = data_allocator::allocate(cap);
			end_ = begin_ + size;
			cap_ = begin_ + cap;
		}
		catch (...)
		{
			begin_ = nullptr;
			end_ = nullptr;
			cap_ = nullptr;
			throw;	// �׳��쳣��������䲻��ִ�У��൱��return
		}
	}

	template<typename T>
	void vector<T>::fill_init(size_type n, const value_type& value)
	{
		const size_type init_size = mystl::max(static_cast<size_type>(16), n);	// ȡĬ�ϳ��Ⱥ�������С�����ֵ
		init_space(n, init_size);	// ��ʼ��vector
		mystl::uninitialied_fill_n(begin_, n, value);	// ���Ĭ��ֵ
	}
}