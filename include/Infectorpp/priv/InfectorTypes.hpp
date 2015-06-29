/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include <typeinfo>
#include <typeindex>
#include <memory>


namespace Infector {
namespace priv {

    using TypeInfoP = const std::type_info *;

    /** Convert from concrete class to abstract class. */
    template< typename Concrete, typename Interface> //Derived to Base
    void * upcast( void * concrete_ptr){
        Concrete * implem = static_cast<Concrete*>( concrete_ptr);
        Interface * interface = static_cast<Interface*>( implem); //trivial cast
        return static_cast<void *>( interface); //now to void*
    }
	
	template< typename Concrete, typename Interface> //Derived to Base
	std::shared_ptr<void> shared_upcast( std::shared_ptr<void> concrete){
		auto conc = std::static_pointer_cast<Concrete>( concrete);
		auto interface = std::static_pointer_cast<Interface>( conc);
		return std::static_pointer_cast<void>( interface);
	}
	
	class Context;

    /** Nicer to look at than "returnType(*)(Args)" function pointer */
    using UpcastSignature	= void*(*)(void*);
	using SharedUpcastSignature = std::shared_ptr<void> (*) (std::shared_ptr<void>);
	using BuildSignature	= void* (*)( priv::Context* ctx);
	using InstanceSignature = std::shared_ptr<void> (*)( priv::Context * ctx);

} // namespace priv
} // namespace Infector
