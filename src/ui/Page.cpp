#include "Page.hpp"
#include "ControlGroup.hpp"
#include "host_system/RKSystem.hpp"
#include "rk_types.h"
#include <cstddef>
#include "ControlGroup.hpp"
#include "ui/UIControl.hpp"

namespace UI {

Page::Page() : 
mId(-1), 
mState(UNLOADED), 
mNextStateRequested(FALSE), 
mAnimationDirection(0), 
mAnimationStartFrame(0.0), 
mAnimationDelay(0.0), 
mFrame(-1), 
mUnknown(-1), 
mInputManager(NULL), 
mNextAnimationSfxId(0), 
mPrevAnimationSfxId(6) {}

Page::~Page() {}
void Page::init(u32 pageId){
    mId = pageId;
    onInit();
    mControlGroup.init();
    //mControlGroup.transform(ControlGroup::FunctionWrapper(&Page::f256c));
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
void Page::f18b0(){
    if (mState != ACTIVE && mState != EXITED) {
        mInputManager->vf20();
    }
    else if (mState == ACTIVE) {
        mInputManager->vf20();
        //s32 a = System::RKSystem::spInstance->mSceneMgr->getStatus();
        //if(-1 < ((1 - a) | a -1)) {
            mInputManager->calc();
        //}
        
    }
}
void Page::calcActivation(){
    if(mNextStateRequested){
        while(mNextStateRequested){
            mNextStateRequested = FALSE;
            if(mState == ACTIVATING) {
                mState = ACTIVE_ANIM;
                mFrame = -1;
                beforeInAnim();
                if(mAnimationDirection == 0){
                    
                }
            }
        }
    }
}
void Page::calc(){
    if (mState == ACTIVE_ANIM || mState == ACTIVE || mState == DEACTIVATE_ANIM) {
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
void Page::f1fc4(){
    mInputManager->reinitSelf();
}
void Page::refocus(){
    mInputManager->reinitSelf();
    if(mInputManager != NULL) {
        
    }
    onRefocus();
}
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

void Page::f256c(UIControl *control){
    
}

void Page::f2934(){
    vf5c();
}

void Page::setAnimSfxIds(u32 nextId, u32 prevId){
    mNextAnimationSfxId = nextId;
    mPrevAnimationSfxId = prevId;
}

}
