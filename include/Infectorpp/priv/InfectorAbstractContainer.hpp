/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
*******************************************************************************/
#pragma once
#include <memory>


namespace Infector {
namespace priv {
	
	class Container;
	class DependencyDAG;
	using ContainerPointer = std::shared_ptr< Container>;

/** Dependency Injection container.. Do not user this class directly
	It can be cumbersome. Use instead the very convenient wrapper:
	InfectorContainer.hpp.
	*/
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
									UpcastSignature upcast,
									std::size_t size) = 0;
	
	/** Update dependency graph.*/
	virtual void wire( 	TypeInfoP type, 
						TypeInfoP * dependencies, 
						std::size_t size,
						BuildSignature func) = 0;
						
	/** Split the container. */
	virtual ContainerPointer split( ContainerPointer p) = 0;
	
	
	/** Obtain implementation from interface. */
	virtual TypeInfoP getConcreteFromInterface( TypeInfoP interface) = 0;

	
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
ContainerPointer INFECTORPP_API createContainer();

} // namespace priv
} // namespace Infector
