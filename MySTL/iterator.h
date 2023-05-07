#pragma once

namespace mystl
{
	// 五种迭代器（标记）
	struct input_iterator_tag {};	// 只读迭代器
	struct output_iterator_tag {};	// 只写迭代器
	struct forward_iterator_tag :public input_iterator_tag {};	// 单项移动迭代器
	struct bidirectional_iterator_tag :public forward_iterator_tag {};	// 双向移动迭代器
	struct random_access_iterator_tag :public bidirectional_iterator_tag {};	// 随机读取迭代器

	/*
	* 迭代器应该可以访问容器的内部细节，因此设计在外的话会暴露出很多接口，因此迭代器应该被设计在容器的内部（内部类）
	* 迭代器的操作形如指针（类似智能指针），因此需要重载指针常用的操作：例如++，+，*，–，-等操作
	* ptrdiff_t 用来保存两个指针减法操作的结果，通常为 long int 类型
	*/
	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;	// 迭代器类型
		typedef T			value_type;			// 变量类型
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Distance	difference_type;
	};

	// 迭代器萃取器
	template <typename T>
	struct has_iterator_cat
	{
	private:
		struct two { char a; char b };	// 定义一个两字符的结构体
		template <typename U> static two test(...);	// 返回值大小为两字符
		/*
		* 如果迭代器有属性 iterator_category，则函数 test 优先匹配该版本
		* 返回值大小为一字符
		*/
		template <typename U> static char test(typename U::iterator_category *= 0);
	public:
		/*
		* SFINAE技巧
		* 若迭代器的变量类型是基本类型、类类型，则迭代器有属性 iterator_category，value 为 true
		* https://blog.csdn.net/zp126789zp/article/details/127887498
		*/
		const static bool value = sizeof(test<T>(0)) == sizeof(char);
	};

	template <typename Iterator, bool>
	struct iterator_traits_impl {};

	/*
	* struct iterator_traits_impl<Iterator, true>
	* 结构偏特化模板（只指定了部分的模板参数）
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
	* std::is_convertible<from, to> 用于判断 from 是否可以转换为 to
	* 这里用于判断迭代器 Iterator 的类型是否为只读迭代器 input_iterator_tag 或只写迭代器 output_iterator_tag 的基类（子类可以向基类转换）
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
	* 迭代器萃取器的默认版本
	* has_iterator_cat<Iterator>::value 用来判断变量类型是否为类类型
	*/
	template <typename Iterator>
	struct iterator_traits : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};

	/*
	* 迭代器萃取器针对原生指针的偏特化版本
	* 原生指针无法定义内嵌型别，编译器无法识别原生指针为模板参数，需要针对原生指针设计偏特化的迭代器萃取器
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

	// 同理，针对常量原生指针设计偏特化的迭代器萃取器
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