#pragma once
#include <functional>


template <typename T>
class PropertyReadOnly
{
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

protected:
	std::function<T& (void)> getter;
};

template <typename T>
class PropertyWriteOnly
{
public:

	PropertyWriteOnly(std::function<void(const T&)> _setter)
		: setter(_setter)
	{
	}

	PropertyWriteOnly(const PropertyWriteOnly& other)
		: setter(other.setter)
	{
	}

	PropertyWriteOnly& operator= (const PropertyWriteOnly& other)
	{
		setter = other.setter;

		return *this;
	}

	PropertyWriteOnly(PropertyWriteOnly&& other) noexcept
		: setter(std::move(other.setter))
	{
	}

	~PropertyWriteOnly() = default;

	void Set(const T& _value)
	{
		setter(_value);
	}

	PropertyWriteOnly& operator= (const T& _value)
	{
		Set(_value);
		return *this;
	}

protected:
	std::function<void(const T&)> setter;
};

template <typename T>
class Property : public PropertyReadOnly<T>, public PropertyWriteOnly<T>
{
public:
	Property(std::function<T& (void)> _getter, std::function<void(const T&)> _setter)
		: PropertyReadOnly<T>(_getter)
		, PropertyWriteOnly<T>(_setter)
	{
	}

	Property(const Property& other)
		: PropertyReadOnly<T>(other.getter)
		, PropertyWriteOnly<T>(other.setter)
	{
	}

	Property& operator= (const Property& other)
	{
		this.setter = other.setter;
		this.getter = other.getter;

		return *this;
	}

	Property(Property&& other) noexcept
		: PropertyWriteOnly<T>(std::move(other.setter))
		, PropertyReadOnly<T>(std::move(other.getter))
	{
	}

	~Property() = default;

	operator T() const
	{
		return Get();
	}

	T& Get() const
	{
		return this->getter();
	}

	void Set(const T& _value)
	{
		this->setter(_value);
	}

	Property& operator= (const T& _value)
	{
		Set(_value);
		return *this;
	}
};