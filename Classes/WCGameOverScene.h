//
//  WCGameOverScene.h
//  MyGame
//
//  Created by Wito Chandra on 10/17/13.
//
//

#ifndef __MyGame__WCGameOverScene__
#define __MyGame__WCGameOverScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class WCGameOverDelegate;

class WCGameOver : public CCLayerColor {
public:
    static CCScene* scene(int);
    virtual bool init();
    CREATE_FUNC(WCGameOver);
    void setScore(int);
    WCGameOverDelegate *delegate;
private:
    CCLabelTTF *mScoreLabel;
    void menuItemSelected(CCMenuItem *);
};

class WCGameOverDelegate {
public:
    virtual void retryPressed(WCGameOver *) = 0;
};

#endif /* defined(__MyGame__WCGameOverScene__) */
