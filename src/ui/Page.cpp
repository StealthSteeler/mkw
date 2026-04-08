#include "Page.hpp"
#include "ControlGroup.hpp"
#include "nw4r/ut/ut_RTTI.hpp"
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
    fetchStartFrame();
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
    mInputManager->activate();
    onActivate();
    mInputManager->vf28();
    
    MultiControlInputManager* mgr = nw4r::ut::DynamicCast<MultiControlInputManager*>(mInputManager);

if (mgr != NULL) {
    for (u32 player = 0; player < 5; player++) {
        mgr->setPerControl(player, FALSE);
    }
}
    
    mControlGroup.init();
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
        //s32 a = System::RKSystem::spInstance->mSceneMgr.getSt;
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
                inAnimationStart();
            } else if (mState == ACTIVE_ANIM) {
                inAnimationEnd();
            } else if (mState == ACTIVE) {
                outAnimationStart();
            } else if (mState == DEACTIVATE_ANIM) {
                outAnimationEnd();
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
    MultiControlInputManager *mgr = nw4r::ut::DynamicCast<MultiControlInputManager*>(mInputManager);
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



void Page::calcAnim(){
    SolveVisitor solve;
    solve.pageState = mState;
    float f2;
    float f1;
    if(mState == ACTIVE_ANIM){
        if (mAnimationDirection == 0) {
            f1 = 1.0;
            f2 = -1.0;
        } else if (mAnimationDirection == 1) {
            f1 = -1.0;
            f2 = 1.0;
        }
        
    } else {
        if (mState != DEACTIVATE_ANIM) {
            return;
        }
        if (mAnimationDirection == 0) {
            f1 = 1.0;
            f2 = 0.0;
        } else if (mAnimationDirection == 1) {
            f1 = -1.0;
            f2 = 0.0;
        }
    }
    if(mState == DEACTIVATE_ANIM) {
        
    }
};
void SolveVisitor::operator()(UIControl *control){ //sloppy copy from ghidra output, no idea what this does and asm doesnt match either
    float f;
    if(page_Id == 0){
        f = control->getAnimStartFrame();
    } else {
        f = startFrame - control->getAnimStartFrame();
    }
    if(f < b){
        if(f + 10.0 <= b) {
            control->solve(unk3 + startFrame);
        } else {
            control->solve(unk3 + unk2*(b-f));
            finished = FALSE;
            if((unk4 - 1.0) <= f) {
                control->onPageEvent(UIControl::EVENT_PAGE_CLOSE, page_Id);
            }
        }
        
    } else {
        control->solve(unk3);
        finished = FALSE;
    }
}
void Page::fetchStartFrame(){
    FetchStartFrameVisitor startframe;
    mControlGroup.visit(startframe);
    mAnimationStartFrame = startframe.frame;
}
void FetchStartFrameVisitor::operator()(UIControl* control) {
    f32 startFrame = control->getAnimStartFrame();
    if (startFrame > frame) {
        frame = startFrame;
    }
}
void SolveFrameVisitor::operator()(UIControl* control) {
    control->solve(frame);
}
void Page::inAnimationStart(){
    mState = ACTIVE_ANIM;
    mFrame = -1;
    beforeInAnim();
    SolveFrameVisitor solveFrame;
    if(mAnimationDirection == 0){
        solveFrame.frame = -1.0;
    } else {
        solveFrame.frame = 1.0;
    }
    mControlGroup.visit(solveFrame);
}
void Page::inAnimationEnd(){
    SolveFrameVisitor solveFrame;
    solveFrame.frame = 0.0;
    mControlGroup.visit(solveFrame);
    mState = ACTIVE;
    mFrame = -1;

    if (mInputManager != NULL){
        MultiControlInputManager *mgr = nw4r::ut::DynamicCast<MultiControlInputManager*>(mInputManager);
        for (s32 player = 0; player < 5; player++) {
            mgr->setPerControl(player, TRUE);
        }
    } 

    afterInAnim();
}
void Page::outAnimationStart(){

    if (mInputManager != NULL){
        MultiControlInputManager *mgr = nw4r::ut::DynamicCast<MultiControlInputManager*>(mInputManager);
        for (s32 player = 0; player < 5; player++) {
            mgr->setPerControl(player, FALSE);
        }
    } 
    
    mState = DEACTIVATE_ANIM;
    mFrame = -1;
    beforeOutAnim();
    SolveFrameVisitor solveFrame;
    solveFrame.frame = 0.0;
    mControlGroup.visit(solveFrame);
    switch (mAnimationDirection) {
    case(0):
        if(mNextAnimationSfxId != 0) {
            SceneSoundManager::unkPlaySfxPage(mNextAnimationSfxId, -1, this);
            return;
        }
    case(1):
        if(mPrevAnimationSfxId != 0) {
            SceneSoundManager::unkPlaySfxPage(mPrevAnimationSfxId, -1, this);
            return;
        }
    }        
}
void Page::outAnimationEnd(){
    SolveFrameVisitor solveFrame;
    
    if(mAnimationDirection == 0){
        solveFrame.frame = 1.0;
    } else {
        solveFrame.frame = -1.0;
    }
    mControlGroup.visit(solveFrame);
    
    mState = EXITED;
    mFrame = -1;
    afterOutAnim();
}
void Page::f2934(){
    vf5c();
}
void Page::playSfx(u32 soundNameID, u32 unused){
    SceneSoundManager::playSfx(soundNameID, unused, this);
}
void Page::unkplaySfx(u32 unk, u32 unk2) {
    SceneSoundManager::unkPlaySfxPage(unk, unk2, this);
}
void Page::setAnimSfxIds(u32 nextId, u32 prevId){
    mNextAnimationSfxId = nextId;
    mPrevAnimationSfxId = prevId;
}

}
