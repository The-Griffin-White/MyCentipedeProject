#ifndef _Constants
#define _Constants

#include "TEAL\CommonElements.h"
#include "TEALConstants.h"

	// General Game Constants 	
	static const float GameScale = (float)WindowScale / 2.0f;							// 1.5f
	static const float DoubleScale = GameScale * 2.0f;

	static const int CellSize = 8 * WindowScale;										// CellSize values in both int and float
	static const int CellSize_Half = CellSize / 2;										// Half of Cellsize is useful for getting the center of a cell
	static const float CellSizeF = 8.0f * (float)WindowScale;
	static const float CellSize_HalfF = CellSizeF / 2.0f;

	static const int PlayerMaxRow = 26;
	static const float PlayerSpaceHeight = CellSizeF * (float)PlayerMaxRow;										// 624.0f
	static const float PlayerSpaceBottom = (float)GameWindowHeight - ( CellSizeF * 2.0f );
	static const float PlayerSpaceLeft = CellSizeF;
	static const float PlayerSpaceRight = (float)GameWindowWidth - CellSizeF;

	// Player constants
	static const int MaxNumPlayerLives = 5;
	static const int PointsForBonus = 12000;

	// MushroomField Constants
	static const int MaxCell = 31;
	static const int MinCell = 0;
	static const float MinCellF = (float)MinCell;
	static const int Mushroom_MaxCell = MaxCell - 2;
	static const int MushroomField_Likelihood_of_Spawn = 18;
	static const int OuterDimensions = 34;															// Do I use this? Come back when its done
	static const int FieldDimensions = 32;
	static const int PlayerField = 5;
	static const int MaxMushroomsInEnemyRow = 2;
	static const int MaxMushroomsInPlayerRow = 1;
	static const int TopPlayerRow = 25;
	static const int BottomRow = FieldDimensions - 1;

	static const float MushroomRegen_Sound_Volume = 10.0f * MasterVolume;
	static const float MushroomRegen_Sound_Pitch = 1.0f * MasterVolume;

	// Ship Constants
	static const float Ship_Speed = 6.0f;															// Change to non-GameTime dependent value
	static const int Ship_Start_Row = 29;
	static const int Ship_Start_Col = 15;
	static const int ShipDrawOrder = 1000;

	// Player Explosion
	static const float Ship_Explosion_Sound_Pitch = 1.0f;
	static const float Ship_Explosion_Sound_Volume = 10.0f * MasterVolume;

	// Bullet Constants
	static const float Bullet_Speed = 16.0f;															// Change to non-GameTime dependent value
	static const float Bullet_Fire_Sound_Pitch = 1.0f;
	static const float Bullet_Fire_Sound_Volume = 10.0f * MasterVolume;
	static const float Bullet_Pos_Relative_to_Ship = 8.0f;												// Maybe re-implement the bullet on the player model?

	// Mushroom Constants
	static const int Mushroom_MaxHealth = 4;
	static const int Mushroom_Damage_From_Bullet = 1;

	// General Enemy Things
	static const float Kill_Sound_Pitch = 1.0f;
	static const float Kill_Sound_Volume = 10.0f * MasterVolume;

	// Flea Constants
	static const int Flea_MaxHealth = 2;
	static const int Flea_Damage_From_Bullet = 1;
	static const float Flea_Base_Speed = CellSizeF / 8.0f;
	static const float Flea_Hurt_Speed = CellSizeF / 4.0f;
	static const int Flea_Base_Cell_Turns = CellSize / (int)Flea_Base_Speed;	// Yes, seriously
	static const int Flea_Hurt_Cell_Turns = CellSize / (int)Flea_Hurt_Speed;	// Used by flea movement to keep track of our row
	static const int Flea_Mushroom_Likelihood = 20;
	static const float Flea_Move_Sound_Pitch = 1.0f;
	static const float Flea_Move_Sound_Volume = 5.0f * MasterVolume;
	static const int Flea_MaxCell = MaxCell - 2;
	static const int Flea_MinCell = MinCell;
	static const int Flea_Offscreen = MaxCell + 3;					// Far enough off screen that we can kill it
	static const int Default_Mushrooms_To_Spawn_Fleas = 1;

	// Scorpion Constants
	static const float Scorpion_Speed = CellSizeF / (CellSize_HalfF);		// Change to non-GameTime dependent value
	static const int Scorpion_Iterator_Cap = (int)(CellSizeF / Scorpion_Speed);
	static const float Scorpion_Space_Height = CellSizeF * 21.0f;
	static const float Scorpion_Move_Sound_Pitch = 1.0f;
	static const float Scorpion_Move_Sound_Volume = 3.0f * MasterVolume;

	// Centipede Constants
	static const int Centipede_Spawn_Row = -1;
	static const int Centipede_Spawn_Col = 16;
	static const float Centipede_Move_Sound_Pitch = 1.0f;
	static const float Centipede_Move_Sound_Volume = 5.0f * MasterVolume;
	static const int Default_Centipede_Segments = 11;
	//		Head Constants
	static const float Centipede_Vertical_Speed = CellSizeF / CellSize_HalfF; // This has to be a divisor of 8
	static const int Centipede_Iterator_Cap = CellSize_Half - 1;
	//			cos/sin angle calculations

	// Spider Constants
	static const float Spider_Speed = CellSizeF / (CellSizeF / 4);							// Change to non-GameTime dependent value
	static const int Spider_Iterator_Cap = (int)(CellSizeF / Spider_Speed);
	static const int Spider_Field_Iterator_Cap = 7 * Spider_Iterator_Cap;
	static const float Spider_Move_Sound_Pitch = 1.0f;
	static const float Spider_Move_Sound_Volume = 3.0f * MasterVolume;
	static const int SpiderScore_Display_Length = 30;

#endif