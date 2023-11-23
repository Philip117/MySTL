#pragma once

#include "type_traits.h"

namespace mystl
{
	// ���ֵ���������ǣ�
	struct input_iterator_tag {};	// ֻ��������
	struct output_iterator_tag {};	// ֻд������
	struct forward_iterator_tag :public input_iterator_tag {};	// �����ƶ�������
	struct bidirectional_iterator_tag :public forward_iterator_tag {};	// ˫���ƶ�������
	struct random_access_iterator_tag :public bidirectional_iterator_tag {};	// �����ȡ������

	/*
	* ������Ӧ�ÿ��Է����������ڲ�ϸ�ڣ�����������Ļ��ᱩ¶���ܶ�ӿڣ���˵�����Ӧ�ñ�������������ڲ����ڲ��ࣩ
	* �������Ĳ�������ָ�루��������ָ�룩�������Ҫ����ָ�볣�õĲ���������++��+��*���C��-�Ȳ���
	* ptrdiff_t ������������ָ����������Ľ����ͨ��Ϊ long int ����
	*/
	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, class Reference = T&>
	struct iterator
	{
		// �������ͱ���
		typedef Category	iterator_category;	// ����������
		typedef T			value_type;			// ��������
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Distance	difference_type;
	};

	// ��������ȡ��
	template <typename T>
	struct has_iterator_cat
	{
	private:
		struct two { char a; char b };	// ����һ�����ַ��Ľṹ��
		
		template <typename U>
		static two test(...);	// ����ֵ��СΪ���ַ�

		/*
		* ��������������� iterator_category������ test ����ƥ��ð汾
		* ����ֵ��СΪһ�ַ�
		*/
		template <typename U>
		static char test(typename U::iterator_category *= 0);

	public:
		/*
		* SFINAE����
		* ���������ı��������ǻ������͡������ͣ�������������� iterator_category��value Ϊ true
		* https://blog.csdn.net/zp126789zp/article/details/127887498
		*/
		const static bool value = sizeof(test<T>(0)) == sizeof(char);
	};

	/*
	* impl ��Ĭ�ϰ汾
	*/
	template <typename Iterator, bool>
	struct iterator_traits_impl {};

	/*
	* struct iterator_traits_impl<Iterator, true>
	* �ṹƫ�ػ�ģ�壨ָֻ���˲��ֵ�ģ�������
	*/
	template <typename Iterator>
	struct iterator_traits_impl<Iterator, true>
	{
		// ��ȡ������������
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::difference_type		difference_type;
	};

	/*
	* helper ��Ĭ�ϰ汾
	*/
	template <typename Iterator, bool>
	struct iterator_traits_helper {};


	/*
	* �ṹƫ�ػ��汾
	* std::is_convertible<from, to> �����ж� from �Ƿ����ת��Ϊ to
	* ���������жϵ����� Iterator �������Ƿ�Ϊֻ�������� input_iterator_tag ��ֻд������ output_iterator_tag �Ļ��ࣨ���������������������������ת����
	*/
	template <typename Iterator>
	struct iterator_traits_helper<Iterator, true>
		:public iterator_traits_impl
		< Iterator,
		std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
		std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value
		>
	{};

	/*
	* ��ȡ��������Ĭ�ϰ汾
	* has_iterator_cat<Iterator>::value �����жϱ��������Ƿ�Ϊ������
	* ��ȡ��Ҫ��ȡ iterator ��ǰ������� iterator �� iterator_category ������ԣ���Ӧ������������
	* has_iterator_cat<Iterator>::value
	* �Ҹ� iterator_category ����ת���� input_iterator_tag �� output_iterator_tag����Ӧ������������
	* public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value>
	*/
	template <typename Iterator>
	struct iterator_traits : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};

	/*
	* ��ȡ���������ԭ��ָ���ƫ�ػ��汾
	* ԭ��ָ���޷�������Ƕ�ͱ𣬱������޷�ʶ��ԭ��ָ��Ϊģ���������Ҫ���ԭ��ָ�����ƫ�ػ��ĵ�������ȡ��
	* https://blog.csdn.net/HouszChina/article/details/78904252
	*/
	template <typename T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef ptrdiff_t					difference_type;
	};

	// ͬ����Գ���ԭ��ָ�����ƫ�ػ��ĵ�������ȡ��
	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef ptrdiff_t					difference_type;
	};


	/*
	* �����жϵ������Ƿ��г�Ա iterator_category�������ԭ�������� int �Ⱦ�û��
	* ������ T �������Ƿ���ת��Ϊ U ���ͣ��ǵĻ� has_iterator_cat_of ���̳� m_true_type
	*/
	template <typename T, typename U, bool = has_iterator_cat<iterator_traits<T>>::value>
	struct has_iterator_cat_of
		: public m_bool_constant<
			std::is_convertible<typename iterator_traits<T>::iterator_category, U>::value>
	{};

	template <typename T, typename U>
	struct has_iterator_cat_of<T, U, false> : public m_false_type {};

	template <typename Iter>
	struct is_input_iterator :public has_iterator_cat_of<Iter, input_iterator_tag> {};

	template <typename Iter>
	struct is_output_iterator :public has_iterator_cat_of<Iter, output_iterator_tag> {};

	template <typename Iter>
	struct is_forward_iterator :public has_iterator_cat_of<Iter, forward_iterator_tag> {};

	template <typename Iter>
	struct is_bidirectional_iterator :public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

	template <typename Iter>
	struct is_random_access_iterator :public has_iterator_cat_of<Iter, random_access_iterator_tag> {};

	template <typename Iterator>
	struct is_iterator :
		public m_bool_constant < is_input_iterator<Iterator>::value ||
		is_output_iterator<Iterator>::value>
	{};

	/*
	* ����ֵ�������ǵ�������ȡ���������ͱ�ǣ��� input_iterator_tag �ȵĶ���
	* �������û�г�Ա
	*/
	template <typename Iterator>
	typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator&)
	{
		typedef typename iterator_traits<Iterator>::iterator_category Category;
		return Category();
	}

	template <typename Iterator>
	typename iterator_traits<Iterator>::difference_type*
		distance_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	template <typename Iterator>
	typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	/*
	* �����������Խ���ڴ����
	*/
	template <typename InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			first++;
			n++;
		}

		return n;
	}

	/*
	* ��Ϊ�����ȡ���������ڴ�ռ�һ���������ģ�����ֱ�ӷ��� last - first
	*/
	template <typename RandomIterator>
	typename iterator_traits<RandomIterator>::difference_type
		distance_dispatch(RandomIterator first, RandomIterator last, random_access_iterator_tag)
	{
		return last - first;
	}

}