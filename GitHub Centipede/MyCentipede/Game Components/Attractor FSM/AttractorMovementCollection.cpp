#include "AttractorMovementCollection.h"
#include "../Constants.h"

const float AttractorMovementCollection::AttractorWindowHeightTop = CellSizeF * 27.0f;
const float AttractorMovementCollection::AttractorWindowHeightBot = CellSizeF * BottomRow - 1.0f;
const float AttractorMovementCollection::AttractorWindowWidthMax = CellSizeF * (FieldDimensions - 2);
const float AttractorMovementCollection::AttractorWindowWidthMin = CellSizeF * 2.0f;

const AttractorOffsetArray AttractorMovementCollection::OffsetsLeftDownDiagonal = AttractorOffsetArray(-Ship_Speed, Ship_Speed);
const AttractorOffsetArray AttractorMovementCollection::OffsetsRightDownDiagonal = AttractorOffsetArray(Ship_Speed, Ship_Speed);
const AttractorOffsetArray AttractorMovementCollection::OffsetsLeftDown = AttractorOffsetArray(0.0f, Ship_Speed);
const AttractorOffsetArray AttractorMovementCollection::OffsetsRightDown = AttractorOffsetArray(0.0f, Ship_Speed);
const AttractorOffsetArray AttractorMovementCollection::OffsetsLeftUp = AttractorOffsetArray(0.0f, -Ship_Speed);
const AttractorOffsetArray AttractorMovementCollection::OffsetsRightUp = AttractorOffsetArray(0.0f, -Ship_Speed);
const AttractorOffsetArray AttractorMovementCollection::OffsetsLeftUpDiagonal = AttractorOffsetArray(-Ship_Speed, -Ship_Speed);
const AttractorOffsetArray AttractorMovementCollection::OffsetsRightUpDiagonal = AttractorOffsetArray(Ship_Speed, -Ship_Speed);