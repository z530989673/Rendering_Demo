#pragma once
#include <iostream>
#include <sstream>
#include <string>

class Debug
{
private:
	static std::stringstream debug;
public:
	Debug();
	~Debug();

	template<typename T>
	void static Log(T value)
	{
		std::cout << value;
	}
};

