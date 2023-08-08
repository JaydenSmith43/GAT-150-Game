#pragma once
#include <string>
#include <memory>

namespace kiko
{
	class Resource //virtual like an abstract class
	{
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string filename, ...) = 0; //variatic argument, pass any # of extra parameters
	};

	template <typename T>
	using res_t = std::shared_ptr<T>;

	//using uint = unsigned int; //give an alias to a data type
	//typedef unsigned int uint; //uint_8 is a typedef
}
