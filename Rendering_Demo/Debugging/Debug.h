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
	inline void static Log(T value)
	{
#ifdef _DEBUG
		std::cout << value << std::endl;
#endif // DEBUG
	}
};

