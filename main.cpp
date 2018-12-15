//https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/


/*
CRTP is a powerful, static alternative to virtual functions and traditional inheritance that can be
used to give types properties at compile time.It works by having a base class template which
takes, as one of its template parameters, the derived class.This permits it to legally perform a
static_cast of its this pointer to the derived class

https://riptutorial.com/cplusplus/example/2383/the-curiously-recurring-template-pattern--crtp-

*/

#include <iterator>
#include <memory>
#include <cassert>

template<typename Sub>
class Container
{
private:
	Sub& sel() { return *Static_cast<Sub*>(this); }
	Sub const& self() const { return *static_cast<Sub const*> (this); };
public:
	decltype(auto) front() { return *self().begin(); }

	decltype(auto) back() { return std::prev(self().begin()); }

	decltype(auto) size() const { return std::distance(self().begin(), self().end()); }

	decltype(auto) operator[](std::size_t i) { return *std::next(self().begin(), i); }
	
};

template <typename T>
class DynArray: public Container<DynArray <T>>
{
public:
	using Base = Container<DynArray<T>>;

	DynArray(std::size_t size) : size_{ size }, data_{ std::make_unique<T[]>(size_)}
	{}

	T* begin() { return data_.get(); }
	T* begin()  const { return data_.get(); }

	T* end() { return data_.get() + size_; }
	T* end() const { return data_.get() + size_; }

private:
	std::size_t size_;
	std::unique_ptr<T[]> data_;
};



int main(int argc, const char * argv[])
{
	DynArray<int> my_array(10);
	my_array.front() = 2;
	my_array[2] = 5;
	assert(my_array.size() == 10);

	return 0;
}
