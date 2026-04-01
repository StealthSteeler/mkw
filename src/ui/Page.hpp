#pragma once

#include <rk_types.h>

#include <decomp.h>

#include "ui/ControlGroup.hpp"

namespace UI {

class MenuInputManager {
  public:
    virtual void reinitSelf();
    virtual void vf20();
    virtual void calc();
};

class Page {
public:
  Page();
  virtual ~Page();

  virtual void getName();
  virtual void getReplacement();
  virtual void vf14();
  virtual void vf18();
  virtual void changeSection(u32 sectionId, s32 animationDirection, double delay);
  virtual void vf20();
  virtual void push();
  virtual void onInit();
  virtual void onDeinit();
  virtual void onActivate();
  virtual void onDeactivate();
  virtual void beforeInAnim();
  virtual void afterInAnim();
  virtual void beforeOutAnim();
  virtual void afterOutAnim();
  virtual void beforeCalc();
  virtual void afterCalc();
  virtual void vf50();
  virtual void onRefocus();
  virtual void vf58();
  virtual void vf5c();
  virtual void getTypeInfo();

  void init(u32 pageId);
  void deinit();
  void activate();
  void deactivate();
  void advanceFrame();
  void f18b0();
  void calcActivation();
  void f1b90();
  void f1d90();
  void calc();
  void f1f84();
  void draw(u32 pass);
  void f1fc4();
  void refocus();
  void f2074();
  void setAnimationDirection(s32 animationDirection);
  void initChildren(s32 capacity);
  void insert(s32 index, UIControl* control, u32 drawPass);
  void setInputManager(MenuInputManager* inputManager);
  void skipInAnimation(void);
  void startReplace(s32 animationDirection, f32 delay);
  void skipOutAnimation(void); 
  void calcAnim();
  void f22a8();
  void f2518();
  void f256c(UIControl *control);
  void f25ac();
  void f25bc();
  void f2640();
  void f2750();
  void f28ac();
  void f2934();
  void playSfx();
  void f2958();
  void setAnimSfxIds(u32 nextId, u32 prevId);

private:
  s32 mId;
  u32 mState;
  bool mNextStateRequested;
  u8 _0d[0x10 - 0x0d];
  s32 mAnimationDirection;
  f32 mAnimationStartFrame;
  f32 mAnimationDelay;
  s32 mFrame;
  u32 mUnknown;
  ControlGroup mControlGroup;
  MenuInputManager* mInputManager;
  u32 mNextAnimationSfxId;
  u32 mPrevAnimationSfxId;
};

enum State {
    UNLOADED,    
    DEACTIVATED,  
    ACTIVATING,
    ACTIVE_ANIM,
    ACTIVE,
    DEACTIVATE_ANIM,
    EXITED,
};

static_assert(sizeof(Page) == 0x44);

} // namespace UI
