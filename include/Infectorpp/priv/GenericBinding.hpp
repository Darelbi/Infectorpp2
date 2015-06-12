/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#pragma once
#include "ExceptionHandling.hpp"

#include <unordered_map>


namespace Infector {
namespace priv {

template< typename M, typename Y >
class GenericBinding {

	using TypeMap = std::unordered_map< std::type_index, Y>;

	TypeMap bindings;

public:

	void bind( TypeInfoP something, Y interface){
		INFECTORPP_CONDITIONAL_THROW(
			if(get(interface)!=nullptr),
				std::invalid_argument,	M::message() )
		
		bindings.insert( std::pair< std::type_index, Y>
                    ( std::type_index(*interface), something));
	}

	void remove( Y interface){
		auto it = bindings.find( std::type_index(*interface) );
		if(it!=bindings.end())
			bindings.erase( it);
	}

	X get( Y interface){
		auto it = bindings.find( std::type_index(*interface));
		return it!=bindings.end()? it->second : nullptr;
	}

	GenericBinding() = default;
	~GenericBinding() = default;
};

} // namespace priv
} // namespace Infector
