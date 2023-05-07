#pragma once

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
		template <typename U> static two test(...);	// ����ֵ��СΪ���ַ�
		/*
		* ��������������� iterator_category������ test ����ƥ��ð汾
		* ����ֵ��СΪһ�ַ�
		*/
		template <typename U> static char test(typename U::iterator_category *= 0);
	public:
		/*
		* SFINAE����
		* ���������ı��������ǻ������͡������ͣ�������������� iterator_category��value Ϊ true
		* https://blog.csdn.net/zp126789zp/article/details/127887498
		*/
		const static bool value = sizeof(test<T>(0)) == sizeof(char);
	};

	template <typename Iterator, bool>
	struct iterator_traits_impl {};

	/*
	* struct iterator_traits_impl<Iterator, true>
	* �ṹƫ�ػ�ģ�壨ָֻ���˲��ֵ�ģ�������
	*/
	template <typename Iterator>
	struct iterator_traits_impl<Iterator, true>
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::difference_type		difference_type;
	};

	template <typename Iterator, bool>
	struct iterator_traits_helper {};

	/*
	* std::is_convertible<from, to> �����ж� from �Ƿ����ת��Ϊ to
	* ���������жϵ����� Iterator �������Ƿ�Ϊֻ�������� input_iterator_tag ��ֻд������ output_iterator_tag �Ļ��ࣨ������������ת����
	*/
	template <typename Iterator>
	struct iterator_traits_impl<Iterator, true>
		:public iterator_traits_impl
		< Iterator,
		std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
		std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value
		>
	{};

	/*
	* ��������ȡ����Ĭ�ϰ汾
	* has_iterator_cat<Iterator>::value �����жϱ��������Ƿ�Ϊ������
	*/
	template <typename Iterator>
	struct iterator_traits : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};

	/*
	* ��������ȡ�����ԭ��ָ���ƫ�ػ��汾
	* ԭ��ָ���޷�������Ƕ�ͱ𣬱������޷�ʶ��ԭ��ָ��Ϊģ���������Ҫ���ԭ��ָ�����ƫ�ػ��ĵ�������ȡ��
	* https://blog.csdn.net/HouszChina/article/details/78904252
	*/
	template <typename T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ptrdiff_t					difference_type;
	};

	// ͬ����Գ���ԭ��ָ�����ƫ�ػ��ĵ�������ȡ��
	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef ptrdiff_t					difference_type;
	};

}