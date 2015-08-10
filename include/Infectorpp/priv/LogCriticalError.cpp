/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <iostream>
#include "ExceptionHandling.hpp"


namespace Infector{
namespace priv{
	
	void logCriticalError(const char * message){
		std::cout<<message<<std::endl;
		std::cerr<<message<<std::endl;
	}
	
}
}