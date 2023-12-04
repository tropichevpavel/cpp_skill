
#include <concepts>
#include <string>

template <typename T>
concept ComplexConcept = !std::has_virtual_destructor<T>::value &&
	requires (T v)
	{
		{ v.hash() } -> std::convertible_to<long>;
		{ v.toString() } -> std::same_as<std::string>;
	};

template <ComplexConcept T>
void test(T t)
{
	t.hash();
}

struct Test
{
	// virtual ~Test();
	auto toString() -> std::string
	{
		return "";
	}
	auto hash() -> int
	{
		return 7890;
	}
};

int main()
{
	test(Test());
	return 0;
}
