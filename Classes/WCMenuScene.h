//
//  WCMenuScene.h
//  MyGame
//
//  Created by Wito Chandra on 10/16/13.
//
//

#ifndef __MyGame__WCMenuScene__
#define __MyGame__WCMenuScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class WCMenu : public CCLayer {
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(WCMenu);
private:
    void menuItemPressed(CCMenuItem*);
};

#endif /* defined(__MyGame__WCMenuScene__) */
