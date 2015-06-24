/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
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

	void bind( Y something, TypeInfoP interface){		
		if( found(get(interface)))
			throwOrBreak< M>();
		
		bindings.insert( std::pair< std::type_index, Y>
                    ( std::type_index(*interface), something));
	}

	void remove( TypeInfoP interface){
		auto it = bindings.find( std::type_index(*interface) );
		if(it!=bindings.end())
			bindings.erase( it);
	}

	typename TypeMap::iterator get( TypeInfoP interface){
		return bindings.find( std::type_index(*interface));
	}
	
	bool found(typename TypeMap::iterator it){
		return it != bindings.end();
	}

	GenericBinding() = default;
	~GenericBinding() = default;
};

} // namespace priv
} // namespace Infector
