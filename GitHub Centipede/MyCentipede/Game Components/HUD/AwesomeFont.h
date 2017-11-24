// AwesomeFont
// Andre Berthiaume, May 2013

#ifndef _AwesomeFont
#define _AwesomeFont

#include "SpriteSheet.h"

class AwesomeFont : public SpriteSheet
{
public:
	AwesomeFont();

	AwesomeFont(const AwesomeFont&) = delete;
	AwesomeFont& operator=(const AwesomeFont&) = delete;
	virtual ~AwesomeFont() = default;

	virtual int CharToIndex(char& c);

private:

};


#endif _AwesomeFont