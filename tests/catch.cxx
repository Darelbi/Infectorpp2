// This file is needed to compile/link Catch Framework
#define CATCH_CONFIG_MAIN
#include "Catch.hpp"
#include "TestHelpers.hpp"
#include <iostream>
#include <exception>

void infectorAssert( const char* code, const char* file, const int line){
	std::cerr<<"--------------------------------------------------"<<std::endl;
	std::cerr<<"\nAssertion Failed:"<<std::endl;
	std::cerr<<"CODE: "<<code<<std::endl;
	std::cerr<<"FILE: "<<file<<std::endl;
	std::cerr<<"LINE: "<<line<<std::endl;
	std::cerr<<"--------------------------------------------------"<<std::endl;
	throw std::runtime_error("Assertion failed");
}