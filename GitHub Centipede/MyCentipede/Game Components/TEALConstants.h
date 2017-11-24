#ifndef _TEALConstants
#define _TEALConstants

// Changes Window Size, any other TEAL settings I might have reason to change. 
// Keeping this separate from the Constants.h the same way we keep engine separate from game files
static const int WindowScale = 3;	// Works on 3, seems OK on 2 (havent really bugtested, centipede rotation gets messed up)			
static const int StandardHeight = 272;
static const int StandardWidth = 256;

static const int GameWindowHeight = WindowScale * StandardHeight;			// 816
static const int GameWindowWidth = WindowScale * StandardWidth;				// 768

static const float MasterVolume = 0.5f;

#endif