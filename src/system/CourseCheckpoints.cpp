#include "CourseCheckpoints.hpp"

#include "CourseMap.hpp"
#include "egg/math/eggVector.hpp"

// Symbol: checkSector__Q26System17MapdataCheckPointCFRCQ26System16LinkedCheckpointRCQ23EGG8Vector2fRCQ23EGG8Vector2f
namespace System {
bool MapdataCheckPoint::checkSector(const LinkedCheckpoint& next,
                                    const EGG::Vector2f& p0,
                                    const EGG::Vector2f& p1) const {
  if (-(next.p0diff.y) * p0.x + next.p0diff.x * p0.y < 0.0f)
    return false;

  if (next.p1diff.y * p1.x - next.p1diff.x * p1.y < 0.0f)
    return false;

  return true;
}

bool MapdataCheckPoint::checkDistanceRatio(const LinkedCheckpoint& next,
                                          const EGG::Vector2f& p0,
                                          const EGG::Vector2f& p1, 
                                          f32* distanceRatio) const {

  float dot = EGG::Vector2f::dot(this->mDir, p1);

  float dot2 = -EGG::Vector2f::dot(next.checkpoint->mDir, p0);

  *distanceRatio = dot / (dot + dot2);

  return ((*distanceRatio >= 0.0f) && (*distanceRatio <= 1.0f));
}

enum MapdataCheckPoint::Completion MapdataCheckPoint::checkSectorAndDistanceRatio_(const LinkedCheckpoint& next,
                                          const EGG::Vector2f& p0,
                                          const EGG::Vector2f& p1,
                                          f32* distanceRatio) const {
  if(!checkSector(next, p0, p1)){
    return Completion_1;
  };
  return checkDistanceRatio(next, p0, p1, distanceRatio) ? Completion_0 : Completion_2;
}
} // namespace System
