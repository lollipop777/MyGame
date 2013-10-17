//
//  WCGameScene.cpp
//  MyGame
//
//  Created by Wito Chandra on 10/11/13.
//
//

#include "WCGameScene.h"
#include "WCGameOverScene.h"
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

CCScene *WCGame::scene() {
    CCScene *scene = CCScene::create();
    
    CCSprite *bg = CCSprite::create("bggame1.jpg");
    bg->setPosition(CCPoint(scene->getContentSize().width / 2, scene->getContentSize().height / 2));
    
    WCGame *layer = WCGame::create();
    
    scene->addChild(bg, 0);
    scene->addChild(layer, 1);
    
    return scene;
}

bool WCGame::init() {
    if(!CCLayer::init()) {
        return false;
    }
    float width = this->getContentSize().width;
    float height = this->getContentSize().height;
    
    this->setTouchEnabled(true);
    
    mSeeker = CCSprite::create("seeker.png");
    mSeeker->setPosition(CCPointMake(mSeeker->getContentSize().width / 2, height / 2));
    // seeker->setScale(2);
    
    mSeeker->setTag(0);
    
    mCurrentLife = 100;
    char buffer[32];
    sprintf(buffer, "Score : %6i", mScore);
    
    mScoreLabel = CCLabelTTF::create(buffer, "Marker Felt", 24, CCSize(width, 50), kCCTextAlignmentRight);
    mScoreLabel->setColor(ccc3(0x00, 0x00, 0x00));
    mScoreLabel->setAnchorPoint(CCPoint(1, 1));
    mScoreLabel->setPosition(CCPoint(width, height));
    
    sprintf(buffer, "Life : %6i", mCurrentLife);
    mLifeLabel = CCLabelTTF::create(buffer, "Marker Felt", 24, CCSize(width, 50), kCCTextAlignmentCenter);
    mLifeLabel->setColor(ccc3(0x00, 0x00, 0x00));
    mLifeLabel->setAnchorPoint(CCPoint(1, 1));
    mLifeLabel->setPosition(CCPoint(width, height));
    
    this->addChild(mSeeker, 100);
    this->addChild(mScoreLabel, 100);
    this->addChild(mLifeLabel, 100);
    
    this->scheduleUpdate();
    this->schedule(schedule_selector(WCGame::gameLogic), 0.04);
    return true;
}

void WCGame::ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent) {
    mLastTouch = (CCTouch *)pTouches->anyObject();
}

void WCGame::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
    mLastTouch = (CCTouch *)pTouches->anyObject();
}

void WCGame::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
    mLastTouch = NULL;
}

void WCGame::retryPressed(WCGameOver *gameOver) {
    mCurrentLife = 100;
    mScore = 0;
    gameOver->removeFromParent();
    list<CCSprite*> spriteBuffer;
    for(list<CCSprite*>::iterator it = mProjectiles.begin(); it != mProjectiles.end(); it ++) {
        spriteBuffer.push_back(*it);
    }
    for(list<CCSprite*>::iterator it = mTargets.begin(); it != mTargets.end(); it ++) {
        spriteBuffer.push_back(*it);
    }
    for(list<CCSprite*>::iterator it = spriteBuffer.begin(); it != spriteBuffer.end(); it ++) {
        removeNode(*it);
    }
    this->scheduleUpdate();
    this->schedule(schedule_selector(WCGame::gameLogic), .04);
}

void WCGame::update(float dt) {
    list<CCSprite*> spriteBuffer;
    for(list<CCSprite*>::iterator i = mProjectiles.begin(); i != mProjectiles.end(); i++) {
        CCSprite *projectile = *i;
        CCRect projectileRect = CCRect(projectile->getPositionX(), projectile->getPositionY(), projectile->getContentSize().width, projectile->getContentSize().height);
        for(list<CCSprite*>::iterator j = mTargets.begin(); j != mTargets.end(); j++) {
            CCSprite *target = *j;
            CCRect targetRect = CCRect(target->getPositionX(), target->getPositionY(), target->getContentSize().width, target->getContentSize().height);
            if(projectileRect.intersectsRect(targetRect)) {
                mCurrentLife ++;
                char buffer[32];
                if(mScore < mCurrentLife - 100) {
                    mScore = mCurrentLife - 100;
                    sprintf(buffer, "Score : %6i", mScore);
                    mScoreLabel->setString(buffer);
                }
                sprintf(buffer, "Life : %6i", mCurrentLife);
                mLifeLabel->setString(buffer);
                spriteBuffer.push_back(target);
                spriteBuffer.push_back(projectile);
                break;
            }
        }
    }
    spriteBuffer.unique();
    for(list<CCSprite*>::iterator i = spriteBuffer.begin(); i != spriteBuffer.end(); i++) {
        CCSprite *sprite = *i;
        if(sprite != NULL) removeNode(sprite);
    }
    if(mLastTouch != NULL && mShootCountDown <= 0) {
        this->shoot(mLastTouch);
        mShootCountDown = 5;
    } else if(mShootCountDown > 0) {
        mShootCountDown --;
    }
    
}

void WCGame::addTarget() {
    CCSprite *target = CCSprite::create("target.png");
    CCPoint position;
    position.x = this->getContentSize().width + (target->getContentSize().width / 2);
    position.y = (target->getContentSize().height / 2) + (rand() % (int)(this->getContentSize().height - target->getContentSize().height));
    target->setPosition(position);
    target->setTag(1);
    this->addChild(target);
    mTargets.push_back(target);
    CCFiniteTimeAction *actionMove = CCMoveTo::create(1 + ((rand() % 100) / 100.0), CCPoint(- target->getContentSize().width / 2, position.y));
    CCFiniteTimeAction *actionDone = CCCallFuncN::create(this, callfuncN_selector(WCGame::hit));
    target->runAction(CCSequence::create(actionMove, actionDone, NULL));
}

void WCGame::removeNode(CCNode *node) {
    if(node->getTag() == 1) {
        mTargets.remove((CCSprite *)node);
    } else if(node->getTag() == 2) {
        mProjectiles.remove((CCSprite *)node);
    }
    this->removeChild(node);
}

void WCGame::hit(CCNode *node) {
    mCurrentLife -= 2;
    if(mCurrentLife < 0) mCurrentLife = 0;
    char buffer[32];
    sprintf(buffer, "Life : %6i", mCurrentLife);
    mLifeLabel->setString(buffer);
    removeNode(node);
    
    if(mCurrentLife == 0) {
        this->unscheduleAllSelectors();
        this->getActionManager()->removeAllActions();
        
        WCGameOver *gameOver = WCGameOver::create();
        gameOver->setScore(mScore);
        gameOver->setAnchorPoint(CCPoint(0, 0));
        gameOver->setPositionY(this->getContentSize().height);
        gameOver->delegate = this;
        
        gameOver->setPositionY(this->getContentSize().height);
        this->getParent()->addChild(gameOver, 2);
        gameOver->runAction(CCMoveTo::create(0.5, CCPoint(0, 0)));
    }
}

void WCGame::gameLogic(float dt) {
    this->addTarget();
}

void WCGame::shoot(cocos2d::CCTouch * touch) {
    float rad = atan2(touch->getLocation().y - mSeeker->getPositionY(), touch->getLocation().x - mSeeker->getContentSize().width);
    CCSprite *projectile = CCSprite::create("projectile.png");
    projectile->setPosition(CCPoint(mSeeker->getContentSize().width, mSeeker->getPositionY()));
    projectile->setTag(2);
    this->addChild(projectile);
    mProjectiles.push_back(projectile);
    CCFiniteTimeAction *actionMove = CCMoveBy::create(1, CCPoint(480 * cos(rad), 480 * sin(rad)));
    CCFiniteTimeAction *actionDone = CCCallFuncN::create(this, callfuncN_selector(WCGame::removeNode));
    projectile->runAction(CCSequence::create(actionMove, actionDone, NULL));
}

