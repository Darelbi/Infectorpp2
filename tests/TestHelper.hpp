/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/

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
