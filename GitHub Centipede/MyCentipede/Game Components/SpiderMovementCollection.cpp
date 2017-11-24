#include "SpiderMovementCollection.h"

#include "Constants.h"

const SpiderOffsetArray SpiderMovementCollection::OffsetsLeftDownDiagonal = SpiderOffsetArray(-Spider_Speed, Spider_Speed);
const SpiderOffsetArray SpiderMovementCollection::OffsetsRightDownDiagonal = SpiderOffsetArray(Spider_Speed, Spider_Speed);
const SpiderOffsetArray SpiderMovementCollection::OffsetsLeftDown = SpiderOffsetArray(0, Spider_Speed);
const SpiderOffsetArray SpiderMovementCollection::OffsetsRightDown = SpiderOffsetArray(0, Spider_Speed);
const SpiderOffsetArray SpiderMovementCollection::OffsetsLeftUp = SpiderOffsetArray(0, -Spider_Speed);
const SpiderOffsetArray SpiderMovementCollection::OffsetsRightUp = SpiderOffsetArray(0, -Spider_Speed);
const SpiderOffsetArray SpiderMovementCollection::OffsetsLeftUpDiagonal = SpiderOffsetArray(-Spider_Speed, -Spider_Speed);
const SpiderOffsetArray SpiderMovementCollection::OffsetsRightUpDiagonal = SpiderOffsetArray(Spider_Speed, -Spider_Speed);