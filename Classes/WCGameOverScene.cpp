//
//  WCGameOverScene.cpp
//  MyGame
//
//  Created by Wito Chandra on 10/17/13.
//
//

#include "WCGameOverScene.h"
#include "WCMenuScene.h"

USING_NS_CC;

bool WCGameOver::init() {
    if(!CCLayerColor::initWithColor(ccc4(0x00, 0x00, 0x00, 0x7f))) {
        return false;
    }
    
    float width = this->getContentSize().width;
    float height = this->getContentSize().height;
    
    mScoreLabel = CCLabelTTF::create("", "Marker Felt", 32, CCSize(width, 50), kCCTextAlignmentCenter);
    mScoreLabel->setPosition(CCPoint(width / 2, height - (mScoreLabel->getDimensions().height)));
    mScoreLabel->setColor(ccc3(0xFF, 0xFF, 0xFF));
    
    
    CCMenuItemFont *menuItemRetry = CCMenuItemFont::create("Retry", this, menu_selector(WCGameOver::menuItemSelected));
    // menuItemRetry->setPosition(CCPoint(width / 2, mScoreLabel->getPositionY() - (2 * mScoreLabel->getDimensions().height)));
    menuItemRetry->setTag(0);
    
    CCMenuItemFont *menuItemBackToMenu = CCMenuItemFont::create("Back To Menu", this, menu_selector(WCGameOver::menuItemSelected));
    // menuItemBackToMenu->setPosition(CCPoint(width / 2, mScoreLabel->getPositionY() - (2 * menuItemRetry->getContentSize().height)));
    menuItemBackToMenu->setTag(1);
    
    CCMenu *menu = CCMenu::create(menuItemRetry, menuItemBackToMenu, NULL);
    menu->alignItemsVertically();
    
    this->addChild(mScoreLabel);
    this->addChild(menu);
    
    CCLog("%f", mScoreLabel->getDimensions().height);
    CCLog("%f %f", width, height);
    
    return true;
}

void WCGameOver::setScore(int score) {
    char buffer[32];
    sprintf(buffer, "Score = %i", score);
    mScoreLabel->setString(buffer);
}

void WCGameOver::menuItemSelected(cocos2d::CCMenuItem *menuItem) {
    if(menuItem->getTag() == 0) {
        delegate->retryPressed(this);
    } else if(menuItem->getTag() == 1) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(0.5, WCMenu::scene(), kCCTransitionOrientationLeftOver));
    }
}
