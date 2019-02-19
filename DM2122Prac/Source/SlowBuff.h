#ifndef SLOWBUFF_H
#define SLOWBUFF_H
#include "Buff.h"
class SlowBuff : public Buff
{
public:
	SlowBuff();
	~SlowBuff();

	static float timer;
	static bool activateYet;
};

#endif // !SLOWBUFF_H
