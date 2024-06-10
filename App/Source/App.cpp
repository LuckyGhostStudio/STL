#include "SString.h"

#include <iostream>

void StringTest()
{
    STL::String s = "Lucky";

    std::cout << s.GetLength() << " " << s << std::endl;
    
    s = s + " ";
    std::cout << s.GetLength() << " " << s << std::endl;

    s += "Hello";
    std::cout << s.GetLength() << " " << s << std::endl;

    std::cout << s[3] << std::endl;
    std::cout << (s == "Lucky") << std::endl;
    std::cout << (s != "Lucky") << std::endl;
    std::cout << s.Copy() << std::endl;
}

int main()
{
    try {
        StringTest();
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}