/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
void infectorAssert( const char* code, const char* file, const int line);

#define ASSERT(x)do{if(!(x))infectorAssert(#x,__FILE__,__LINE__);}while(false)

#define ABSTRACT_CLASS( x)  	\
								\
class x {						\
public:							\
	virtual ~x(){}				\
	virtual int method() = 0;	\
};							

#define CONCRETE_CLASS( y, x ,k)	\
									\
class y: public x{					\
public:								\
	virtual ~y(){}					\
	y( k ){}						\
									\
	virtual int method() 			\
	override	{ return 0;}		\
};
