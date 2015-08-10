/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "InfectorTraits.hpp"
#include "priv/InfectorAbstractContext.hpp"


namespace Infector {

/** A Context holds instances of shared objects of your application. (think it
	as a singleton for part or for whole your application, but this is not an
	antipattern because you can still TEST every part of your application). */
class Context{
public:

    /** Creates a new object each time is called. Dependencies are automatically
		resolved.	*/
    template< typename Contract>
    std::unique_ptr< Contract> build();

    /** Create a shared instance and register it within the Context.
		(If a instance already exists it will be returned instead)*/
    template< typename Contract>
    std::shared_ptr< Contract> buildSingle();

    /** Register a shared Instance for a Contract.*/
    template< typename Contract>
    void registerInstance( std::shared_ptr< Contract> inst);

	/** Register a shared instance for multiple Contracts. (Same as calling
		registerInstance multiple times, but shorter to write;) )*/
	template< typename Impl, typename Contract, typename... Contracts>
	void registerMultiInstance( std::shared_ptr< Impl> inst);

    /** If the instance you register is provided by another Context, why
		not asking it directly? (Remove need for hiearchies and make
		explicit an intent instead of having it implicit)*/
    template< typename Contract>
    void getInstanceFrom( std::shared_ptr< Context> & inst);

	/** Creates another context wich is an exact copy of this one.
		Instances registered BEFORE FORK will be AUTOMATICALLY SHARED
		in both contexts. */
	Context forkContext() const;


    /**=====================================================================
                              MOCKING:
    ------------------------------------------------------------------------
    Utility methods based on user feedback that make easy testing with 3rd
    party frameworks (CppUnitTest, GoogleMock etc.). Do not use these methods
    in production code, but only in your test suite.
    =======================================================================*/

    /** Like build, but returns concrete instance of given contract(interface).
        Usefull when you need to call methods on derived class for testing.*/
    template< typename Contract, typename Impl>
    std::unique_ptr< Impl> buildAs();


    /**========================================
                       DETAILS:
    ===========================================*/

	template< typename Impl>
	void registerMultiInstance( std::shared_ptr< Impl> inst) const;

    //Context(ContextPointer && context_impl);
    inline ~Context() = default;
	Context( priv::ContextPointer );

private:

	priv::ContextPointer          context;

};

inline Context::Context( priv::ContextPointer p)
	:context( p){

}

template< typename Contract>
std::unique_ptr< Contract> Context::build(){
	return std::unique_ptr< Contract>( static_cast< Contract*>(
			context->buildComponent( &typeid( Contract))
															)
			);
}

template< typename Contract>
std::shared_ptr< Contract> Context::buildSingle(){
	return std::static_pointer_cast< Contract>(
			context->instance( &typeid( Contract)));
}

template< typename Contract>
void Context::registerInstance( std::shared_ptr< Contract> inst){
	isWireable<Contract>();
	
    context->registerInstance( 	std::static_pointer_cast<void>( inst),
								&typeid( Contract));
}

template< typename Impl>
void Context::registerMultiInstance( std::shared_ptr< Impl> inst) const{
	isWireable<Impl>();
}

template< typename Impl, typename Contract, typename... Contracts>
void Context::registerMultiInstance( std::shared_ptr< Impl> inst){
	std::shared_ptr<Contract> ptr = inst;
	registerInstance (ptr);
	registerMultiInstance< Impl, Contracts...>( inst);
}

template< typename Contract>
void Context::getInstanceFrom( std::shared_ptr< Context> & other){
    auto inst = other->buildSingle< Contract>();
    registerInstance( inst);
}

inline Context  Context::forkContext() const{
	
	
	return Context( context->fork());
}

template< typename Contract, typename Impl>
std::unique_ptr< Impl> Context::buildAs(){
	
	isMultiBase< Impl, Contract>(); // not this is actually not a safe check
	
	return std::unique_ptr< Impl>( static_cast< Impl*>(
		context->buildComponentAs( &typeid(Contract))
														)
		);
}


} // namespace Infector
