#pragma once
#include <functional>
//バックアップ

template <typename T>
class Property
{
	static_assert(!std::is_pointer<T>::value,
		"I don't delete pointer. Recommend not use raw pointer./こっちでdeleteしないので、生ポインター非推奨っす。");
public:

	Property(std::function<T& (void)> _getter, std::function<void(const T&)> _setter)
		: getter(_getter)
		, setter(_setter)
	{
	}

	Property(const Property& other)
		: setter(other.setter)
		, getter(other.getter)
	{
	}

	Property& operator= (const Property& other)
	{
		setter = other.setter;
		getter = other.getter;

		return *this;
	}

	Property(Property&& other) noexcept
		: setter(std::move(other.setter))
		, getter(std::move(other.getter))
	{
	}

	~Property() = default;

	operator T() const
	{
		return Get();
	}

	T& Get() const
	{
		return getter();
	}

	void Set(const T& _value)
	{
		setter(_value);
	}

	Property& operator= (const T& _value)
	{
		Set(_value);
		return *this;
	}

private:

	std::function<void(const T&)> setter;
	std::function<T& (void)> getter;
};



template <typename T>
class PropertyReadOnly
{
	static_assert(!std::is_pointer<T>::value,
		"I don't delete pointer. Recommend not use raw pointer./こっちでdeleteしないので、生ポインター非推奨っす。");
public:

	PropertyReadOnly(std::function<T& (void)> _getter)
		: getter(_getter)
	{
	}

	PropertyReadOnly(const PropertyReadOnly& other)
		: getter(other.getter)
	{
	}

	PropertyReadOnly& operator= (const PropertyReadOnly& other)
	{
		getter = other.getter;

		return *this;
	}

	PropertyReadOnly(PropertyReadOnly&& other) noexcept
		: getter(std::move(other.getter))
	{
	}

	~PropertyReadOnly() = default;

	operator T() const
	{
		return Get();
	}

	T& Get() const
	{
		return getter();
	}

private:
	std::function<T& (void)> getter;
};
