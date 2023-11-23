#pragma once

#include "type_traits.h"

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
		// 定义类型别名
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
		
		template <typename U>
		static two test(...);	// 返回值大小为两字符

		/*
		* 如果迭代器有属性 iterator_category，则函数 test 优先匹配该版本
		* 返回值大小为一字符
		*/
		template <typename U>
		static char test(typename U::iterator_category *= 0);

	public:
		/*
		* SFINAE技巧
		* 若迭代器的变量类型是基本类型、类类型，则迭代器有属性 iterator_category，value 为 true
		* https://blog.csdn.net/zp126789zp/article/details/127887498
		*/
		const static bool value = sizeof(test<T>(0)) == sizeof(char);
	};

	/*
	* impl 的默认版本
	*/
	template <typename Iterator, bool>
	struct iterator_traits_impl {};

	/*
	* struct iterator_traits_impl<Iterator, true>
	* 结构偏特化模板（只指定了部分的模板参数）
	*/
	template <typename Iterator>
	struct iterator_traits_impl<Iterator, true>
	{
		// 获取迭代器各类型
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::difference_type		difference_type;
	};

	/*
	* helper 的默认版本
	*/
	template <typename Iterator, bool>
	struct iterator_traits_helper {};


	/*
	* 结构偏特化版本
	* std::is_convertible<from, to> 用于判断 from 是否可以转换为 to
	* 这里用于判断迭代器 Iterator 的类型是否为只读迭代器 input_iterator_tag 或只写迭代器 output_iterator_tag 的基类（另外三个子类可以向这两个基类转换）
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
	* 萃取迭代器的默认版本
	* has_iterator_cat<Iterator>::value 用来判断变量类型是否为类类型
	* 萃取器要萃取 iterator 的前提是这个 iterator 有 iterator_category 这个属性，对应代码下述代码
	* has_iterator_cat<Iterator>::value
	* 且该 iterator_category 可以转换成 input_iterator_tag 或 output_iterator_tag，对应代码下述代码
	* public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value>
	*/
	template <typename Iterator>
	struct iterator_traits : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};

	/*
	* 萃取迭代器针对原生指针的偏特化版本
	* 原生指针无法定义内嵌型别，编译器无法识别原生指针为模板参数，需要针对原生指针设计偏特化的迭代器萃取器
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

	// 同理，针对常量原生指针设计偏特化的迭代器萃取器
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
	* 首先判断迭代器是否有成员 iterator_category，如果是原生类型如 int 等就没有
	* 迭代器 T 的类型是否能转换为 U 类型，是的话 has_iterator_cat_of 将继承 m_true_type
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
	* 返回值的类型是迭代器萃取出来的类型标记，即 input_iterator_tag 等的对象
	* 这个对象没有成员
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
	* 计算迭代器跨越的内存距离
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
	* 因为随机读取迭代器的内存空间一定是连续的，所以直接返回 last - first
	*/
	template <typename RandomIterator>
	typename iterator_traits<RandomIterator>::difference_type
		distance_dispatch(RandomIterator first, RandomIterator last, random_access_iterator_tag)
	{
		return last - first;
	}

}