//
//  WCMenuScene.cpp
//  MyGame
//
//  Created by Wito Chandra on 10/16/13.
//
//

#include "WCMenuScene.h"
#include "WCGameScene.h"
#include "cocos2d.h"

USING_NS_CC;

CCScene *WCMenu::scene() {
    CCScene *scene = CCScene::create();
    
    CCSprite *bg = CCSprite::create("bgmenu1.jpg");
    bg->setPosition(CCPoint(scene->getContentSize().width / 2, scene->getContentSize().height / 2));
    
    WCMenu *menuLayer = WCMenu::create();
    
    scene->addChild(bg, 0);
    scene->addChild(menuLayer, 1);
    
    return scene;
}

bool WCMenu::init() {
    if(!CCLayer::init()) {
        return false;
    }
    float width = this->getContentSize().width;
    float height = this->getContentSize().height;
    CCLog("%f %f", width, height);
    
    CCMenuItemFont *item1 = CCMenuItemFont::create("Tembak2", this, menu_selector(WCMenu::menuItemPressed));
    item1->setTag(0);
    CCMenuItem *item2 = CCMenuItemFont::create("Menu Item 2", this, menu_selector(WCMenu::menuItemPressed));
    item2->setTag(1);
    item2->setEnabled(false);
    CCMenuItem *item3 = CCMenuItemFont::create("Menu Item 3", this, menu_selector(WCMenu::menuItemPressed));
    item3->setTag(2);
    item3->setEnabled(false);
    CCMenuItem *item4 = CCMenuItemFont::create("Menu Item 4", this, menu_selector(WCMenu::menuItemPressed));
    item4->setTag(3);
    item4->setEnabled(false);
    CCMenuItem *item5 = CCMenuItemFont::create("Menu Item 5", this, menu_selector(WCMenu::menuItemPressed));
    item5->setTag(4);
    item5->setEnabled(false);
    
    CCMenu *menu = CCMenu::create(item1, item2, item3, item4, item5, NULL);
    menu->setColor(ccc3(0xFF, 0xFF, 0xFF));
    menu->alignItemsVertically();
    menu->setContentSize(CCSize(width / 2, height));
    menu->setPosition(width - (menu->getContentSize().width / 2), height / 2);
    this->addChild(menu);
    CCLog("%s", item1->fontName());
    
    return true;
}

void WCMenu::menuItemPressed(CCMenuItem *item) {
    CCLog("menuItemPressed %i", item->getTag());
    if(item->getTag() == 0) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(0.5, WCGame::scene(), kCCTransitionOrientationRightOver));
    } else if(item->getTag() == 1) {
    }
}

