#include "CSmokePuff.h"

namespace galaxy {
  
CSmokePuff::CSmokePuff(CMap *pmap, const Uint32 x, const Uint32 y) :
CGalaxySpriteObject(pmap, 0, x, y)
{	
	setupGalaxyObjectOnMap(0x2E22, 0);
	xDirection = LEFT;
	performCollisions();
}

void CSmokePuff::process()
{
	if(!processActionRoutine())
		exists = false;

	if(!getActionStatus(0))
		return;
}
    
};