//
//  WCGameScene.h
//  MyGame
//
//  Created by Wito Chandra on 10/11/13.
//
//

#ifndef __MyGame__WCGameScene__
#define __MyGame__WCGameScene__

#include <iostream>
#include "cocos2d.h"
#include "WCGameOverScene.h"

using namespace std;
USING_NS_CC;

class WCGame : public CCLayer, public WCGameOverDelegate {
public:
    static CCScene* scene();
    virtual bool init();
    virtual void ccTouchesBegan(CCSet*, CCEvent*);
    virtual void ccTouchesMoved(CCSet*, CCEvent*);
    virtual void ccTouchesEnded(CCSet*, CCEvent*);
    CREATE_FUNC(WCGame);
    
    void retryPressed(WCGameOver *);
private:
    CCSprite *mSeeker;
    CCLabelTTF *mScoreLabel;
    CCLabelTTF *mLifeLabel;
    CCTouch *mLastTouch;
    list<CCSprite *> mProjectiles;
    list<CCSprite *> mTargets;
    int mCurrentLife;
    int mShootCountDown;
    int mScore;
    
    void update(float);
    void addTarget();
    void removeNode(CCNode*);
    void hit(CCNode *);
    void gameLogic(float);
    void shoot(CCTouch*);
};

#endif /* defined(__MyGame__WCGameScene__) */
