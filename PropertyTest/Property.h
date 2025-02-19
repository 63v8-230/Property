#pragma once
#include <functional>

template <typename T>
class Property
{
	static_assert(!std::is_pointer<T>::value,
		"No Raw pointers. Use smart pointers./生ポインター使うな。スマートポインター使え。");
public:
	Property()
		:value{}
	{
		setter = [](T _value) const T& { return _value; };
		getter = [](T _value) const T& { return _value; };
	}

	Property(std::function<const T& (const T&)> _getter, std::function<const T& (const T&)> _setter)
		: value{}
		, getter(_getter)
		, setter(_setter)
	{
	}

	Property(Property&& other) noexcept
		: value(std::move(other.value))
		, setter(std::move(other.setter))
		, getter(std::move(other.getter))
	{
	}

	~Property() = default;

	operator T() const
	{
		return Get();
	}

	void SetSetter(std::function<const T& (const T&)> _func)
	{
		if (!_func) throw std::invalid_argument("_func is null./_funcが空っす。");
		setter = _func;
	}

	void SetGetter(std::function<const T& (const T&)> _func)
	{
		if (!_func) throw std::invalid_argument("_func is null./_funcが空っす。");
		getter = _func;
	}

	const T& Get() const
	{
		return getter(value);
	}

	void Set(const T& _value)
	{
		value = setter(_value);
	}

	Property& operator= (const T& _value)
	{
		Set(_value);
		return *this;
	}

	Property& operator=(T&& _value)
	{
		Set(std::move(_value));
		return *this;
	}

private:

	T value{};

	std::function<const T& (const T&)> setter;
	std::function<const T& (const T&)> getter;
};
