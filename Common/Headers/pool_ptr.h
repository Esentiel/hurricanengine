#pragma once

template <typename T>
class pool_ptr
{
public:
	pool_ptr() : p(nullptr)
	{}

	pool_ptr(T* p_) : p(&p_)
	{
	}

	pool_ptr(pool_ptr& pp_) : p(pp_)
	{
	}

	const pool_ptr& operator=(const pool_ptr& pp_)
	{
		*p = *(pp_->p);
		return this;
	}

	//T* operator()
	//{
	//	return *p;
	//}

	const T* get() const noexcept
	{
		return *p;
	}

	void reset(T* p_ = nullptr)
	{
		delete *p;
		*p = p_;
	}

	~pool_ptr() = default;

private:
	T** p;
};