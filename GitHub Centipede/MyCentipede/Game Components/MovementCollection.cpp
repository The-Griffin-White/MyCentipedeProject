#include "MovementCollection.h"
#include <math.h>

const OffsetArray MovementCollection::OffsetsStraightRight[12] =		{ OffsetArray(2.0f, 0.0f), OffsetArray(2.0f, 0.0f), OffsetArray(2.0f, 0.0f), OffsetArray(2.0f, 0.0f), 
																			OffsetArray(2.0f, 0.0f), OffsetArray(2.0f, 0.0f), OffsetArray(2.0f, 0.0f), OffsetArray(2.0f, 0.0f), 
																			OffsetArray(2.0f, 0.0f), OffsetArray(2.0f, 0.0f), OffsetArray(2.0f, 0.0f), OffsetArray(2.0f, 0.0f) };

const OffsetArray MovementCollection::OffsetsTurnUpEndRight[12] =		{ OffsetArray(0.0f, -2.0f), 
																			OffsetArray(0.0f, -2.0f), 
																			OffsetArray(0.0f, -2.0f), 
																			OffsetArray(0.0f, -2.0f),
																			OffsetArray(0.0f, -2.0f), 
																			OffsetArray(0.0f, -2.0f), 
																			OffsetArray(0.0f, -2.0f), 
																			OffsetArray(0.0f, -2.0f),
																			OffsetArray(0.0f, -2.0f), 
																			OffsetArray(0.0f, -2.0f), 
																			OffsetArray(0.0f, -2.0f), 
																			OffsetArray(0.0f, -2.0f) };

const OffsetArray MovementCollection::OffsetsTurnDownEndRight[12] =		{ OffsetArray(0.0f, 2.0f), 
																			OffsetArray(0.0f, 2.0f), 
																			OffsetArray(0.0f, 2.0f), 
																			OffsetArray(0.0f, 2.0f), 
																			OffsetArray(0.0f, 2.0f), 
																			OffsetArray(0.0f, 2.0f), 
																			OffsetArray(0.0f, 2.0f), 
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f), 
																			OffsetArray(0.0f, 2.0f), 
																			OffsetArray(0.0f, 2.0f), 
																			OffsetArray(0.0f, 2.0f) };

const OffsetArray MovementCollection::OffsetsStraightLeft[12] =			{ OffsetArray(-2.0f, 0.0f), OffsetArray(-2.0f, 0.0f), OffsetArray(-2.0f, 0.0f), OffsetArray(-2.0f, 0.0f), 
																			OffsetArray(-2.0f, 0.0f), OffsetArray(-2.0f, 0.0f), OffsetArray(-2.0f, 0.0f), OffsetArray(-2.0f, 0.0f), 
																			OffsetArray(-2.0f, 0.0f), OffsetArray(-2.0f, 0.0f), OffsetArray(-2.0f, 0.0f), OffsetArray(-2.0f, 0.0f) };

const OffsetArray MovementCollection::OffsetsTurnUpEndLeft[12] = { OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f),
																	OffsetArray(0.0f, -2.0f) };

const OffsetArray MovementCollection::OffsetsTurnDownEndLeft[12] = { OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f),
																		OffsetArray(0.0f, 2.0f) };

const OffsetArray MovementCollection::OffsetsPoisonTurnDownEndLeft[12] = { OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f) };

const OffsetArray MovementCollection::OffsetsPoisonTurnDownEndRight[12] = { OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f),
																			OffsetArray(0.0f, 2.0f) };

const float MovementCollection::RotationStraightLeft[12] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
const float MovementCollection::RotationStraightRight[12] = { 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f };
const float MovementCollection::RotationDownLeft[12] = { 195.0f, 210.0f, 225.0f, 240.0f, 255.0f, 270.0f, 285.0f, 300.0f, 315.0f, 330.0f, 345.0f, 360.0f };
const float MovementCollection::RotationDownRight[12] = { -15.0f, -30.0f, -45.0f, -60.0f, -75.0f, -90.0f, -105.0f, -120.0f, -135.0f, -150.0f, -165.0f, -180.0f };
const float MovementCollection::RotationUpLeft[12] = { 165.0f, 150.0f, 135.0f, 120.0f, 105.0f, 90.0f, 75.0f, 60.0f, 45.0f, 30.0f, 15.0f, 0.0f };
const float MovementCollection::RotationUpRight[12] = { 15.0f, 30.0f, 45.0f, 60.0f, 75.0f, 90.0f, 105.0f, 120.0f, 135.0f, 150.0f, 165.0f, 180.0f };
