#pragma once

#include "resource.h"

enum ChkType 
{
	Chk_Start = 0,
	Chk_Info,
	Chk_Speed,
	Chk_MAC,
	Chk_Status,
	Chk_SignalS, //for XP
	Chk_SignalQ, //for Vista
	Chk_End
};

BOOL blGetNetworkCards(ChkType Type = Chk_Start);