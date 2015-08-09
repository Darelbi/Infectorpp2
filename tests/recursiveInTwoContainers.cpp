/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include "TestHelper.hpp"

/**
	===== Container 1:
	
	~(Shotgun < Weapon)
	~(ShotgunBullet < Ammo)   //regular ammo. Ok
	+(ShotgunBullet)
	
	===== Container 1.1:
	
	+(Shotgun):Ammo			 
	
	===== Container 1.2:
	
	~(BulletShotgun < Ammo)  	// weapon as ammo
	+(Shotgun):Ammo
	+(BulletShotgun):Weapon 	// throw CircularDependencyEx
*/

ABSTRACT_CLASS ( Weapon)
ABSTRACT_CLASS ( Ammo)

CONCRETE_CLASS ( Shotgun, Weapon, std::unique_ptr<Ammo> )
CONCRETE_CLASS ( ShotgunBullet, Ammo, void)
CONCRETE_CLASS ( BulletShotgun, Ammo, std::unique_ptr<Weapon>)


int recursiveInTwoContainers( int argc, char** argv){

	using namespace Infector;
	
	Container c1;
	
	c1.bindAs< 	Shotgun, 		Weapon>();
	c1.bindAs< 	ShotgunBullet, 	Ammo>();
	c1.wire< 	ShotgunBullet>();
	
	auto c2 = c1.splitContainer();
	auto c3 = c1.splitContainer();
	
	c2.wire<Shotgun, Unique<Ammo> >();
	
	c3.bindAs< BulletShotgun, Ammo>();
	c3.wire<   Shotgun, Unique<Ammo> >();
	
	try{
		c3.wire<  BulletShotgun, Unique<Weapon> >();
		assert(false); //test failed
	}
	catch( const priv::CircularDependencyEx &ex){
		
	}
	catch(...){
		assert(false); //test failed
	}
	
	return 0;
}