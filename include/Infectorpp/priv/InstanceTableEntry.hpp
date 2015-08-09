/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "InfectorTypes.hpp"
#include <unordered_map>


namespace Infector{
namespace priv{
	
struct InstanceTableEntry{
	std::size_t				size = 0;
	
	BuildSignature			constructor = nullptr;
	UpcastSignature			toBaseConversion = nullptr;
	
	InstanceSignature		sharedConstructor = nullptr;
	SharedUpcastSignature	toSharedBaseConversion = nullptr;
	
	std::shared_ptr<void>	instance = nullptr;
};

using InstanceTable	 	=  std::unordered_map< std::type_index,
												InstanceTableEntry >;
	
} // namespace priv
} // namespace Infector