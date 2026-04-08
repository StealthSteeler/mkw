#pragma once

#include <rk_types.h>

#include <decomp.h>

#include "nw4r/ut/ut_RTTI.hpp"
#include "ui/ControlGroup.hpp"
#include "ui/Page.hpp"
#include "ui/UIControl.hpp"

namespace UI {



class MenuInputManager {
  public:
    virtual nw4r::ut::detail::RuntimeTypeInfo *GetRuntimeTypeInfo();
    virtual void reinitSelf();
    virtual void vf20();
    virtual void calc();
    virtual void vf28();
    void activate();
};

class SceneSoundManager {
  public:
  static void playSfx(u32 soundNameID, u32 unused, void *origin);
  static void unkPlaySfxPage(u32 unk, u32 unk2, Page *page);
};

class MultiControlInputManager : public MenuInputManager{
  public:
    static nw4r::ut::detail::RuntimeTypeInfo typeInfo;
    void setPerControl(u32 playerId, BOOL perControl);
};

struct FetchStartFrameVisitor : ControlGroup::Visitor {
    FetchStartFrameVisitor() : frame(0.0f) {}
    virtual void operator()(UIControl* control) override; 
    f32 frame;
};

struct SolveFrameVisitor : ControlGroup::Visitor {
    SolveFrameVisitor() : frame(0.0f) {}
    virtual void operator()(UIControl* control) override;
    f32 frame;
};

struct SolveVisitor : ControlGroup::Visitor {
    virtual void operator()(UIControl* control) override;
    u32 page_Id;
    u32 pageState;
    f32 startFrame;
    f32 unk2;
    f32 unk3;
    u32 unk4;
    f32 b;
    BOOL finished;
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
  void fetchStartFrame();
  void inAnimationStart();
  void inAnimationEnd();
  void outAnimationStart();
  void outAnimationEnd();
  void f2934();
  void playSfx(u32 soundNameID, u32 unused);
  void unkplaySfx(u32 unk, u32 unk2);
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
