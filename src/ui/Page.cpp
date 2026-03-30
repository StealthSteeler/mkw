#include "Page.hpp"
#include "ControlGroup.hpp"
#include "rk_types.h"
#include <cstddef>

namespace UI {

Page::Page(){
   mId = -1;
   mState = UNLOADED;
   mNextStateRequested = FALSE;
   mAnimationStartFrame = 0.0;
   mAnimationDelay = 0.0;
   mFrame = -1;
   mUnknown = -1;
   mInputManager = NULL;
   mNextAnimationSfxId = 0;
   mPrevAnimationSfxId = 6;
   mAnimationDirection = 0;
}
Page::~Page() {
}
void Page::init(u32 pageId){
    mId = pageId;
    onInit();
    mControlGroup.init();
    //mControlGroup.transform(); I don't know how to implement this because I don't know what it is
    mState = DEACTIVATED;
}
void Page::onInit(){}
void Page::deinit(){
    onDeinit();
}
void Page::activate(){
    mState = ACTIVATING;
    mNextStateRequested = TRUE;
    mFrame = -1;
    mUnknown = -1;
}
void Page::deactivate(){
    onDeactivate();
    mState = DEACTIVATED;
}
void Page::advanceFrame(){
    mFrame += 1;
    mUnknown += 1;
}
void Page::f18b0(){}
void Page::calcActivation(){}
void Page::f1b90(){}
void Page::f1d90(){}
void Page::calc(){
    if (mState == ACTIVE_ANIM || mState == ACTIVE || mState == DEACTIVATE_ANIM){
        beforeCalc();
        mControlGroup.calc();
        afterCalc();
        calcAnim();
    }
}
void Page::f1f84(){
    if (mState == ACTIVE_ANIM || mState == ACTIVE || mState == DEACTIVATE_ANIM) {
        vf50();
    }
}
void Page::draw(u32 pass) {
    if (mState == ACTIVE_ANIM || mState == ACTIVE || mState == DEACTIVATE_ANIM) {
        mControlGroup.draw(pass);
    }
}
void Page::f1fc4(){}
void Page::refocus(){}
void Page::f2074(){
    if(mState == ACTIVE_ANIM || mState == ACTIVE || mState == DEACTIVATE_ANIM) {
        vf58();
    }
}
void Page::setAnimationDirection(s32 animationDirection) {
    if (animationDirection == -1) {
        return;
    }

    mAnimationDirection = animationDirection;
}
void Page::initChildren(s32 capacity) {
    mControlGroup.create(this, capacity);
}
void Page::insert(s32 index, UIControl* control, u32 drawPass) {
    mControlGroup.insert(index, control, drawPass);
}
void Page::setInputManager(MenuInputManager* inputManager) {
    mInputManager = inputManager;
}
void Page::skipInAnimation(void) {
    mNextStateRequested = true;
}
void Page::startReplace(s32 animationDirection, f32 delay) {
  setAnimationDirection(animationDirection);
  mAnimationDelay = delay;
  mNextStateRequested = true;
}
void Page::skipOutAnimation(void) {
    mNextStateRequested = true;
}
void Page::changeSection(u32 sectionId, s32 animationDirection, double delay){}
}
