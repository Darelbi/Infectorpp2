/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
*******************************************************************************/
#pragma once

namespace Infector {
namespace priv {

class Context;

class Container{

public:

    /** Bind a concrete type to multiple types. */
    virtual void bindSingleAs( 	TypeInfoP concrete,
								TypeInfoP * interfaces,
								UpcastSignature * upcasts,
								std::size_t size) = 0;
								
	/** Bind a component to its type registering metainfo. */
    virtual void bindComponent( 	TypeInfoP concrete,
									TypeInfoP interface,
									UpcastSignature * upcast,
									std::size_t size) = 0;

    /** Register a factory function for given type.*/
    virtual void wire( 	TypeInfoP type, 
						BuildSignature func) = 0;
	
	/** Update dependency graph.*/
	virtual void touch( TypeInfoP type, 
						TypeInfoP * dependencies, 
						std::size_t size) = 0;

    /** allows calling destructor of derived classes from interfaces pointers.*/
    virtual ~Container() = default;
};

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//				IMPORT/EXPORT stuff needed for windows users
//_____________________________________________________________________________

#if defined (INFECTORPP_EXPORT)|| defined(INFECTORPP_IMPORT)
    #ifdef INFECTORPP_EXPORT
        #define INFECTORPP_API __declspec(dllexport)
    #else
        #define INFECTORPP_API __declspec(dllimport)
    #endif
#else
    #define INFECTORPP_API
#endif

// Decouple user from most implementations details to reduce compile time
// and separate "typechecking" from library logic
Container * INFECTORPP_API createContainer();

void INFECTORPP_API destroyContainer( Container * c);

} // namespace priv
} // namespace Infector
