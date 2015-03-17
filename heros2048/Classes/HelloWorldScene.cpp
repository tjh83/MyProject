#include "HelloWorldScene.h"
#include "TitleScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 255)) )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite* pCI = CCSprite::create("ci.png");
	pCI->setAnchorPoint(ccp(0.5f, 0.5f));
	pCI->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
	this->addChild(pCI, 0);

	this->schedule(schedule_selector(HelloWorld::nextScene), 2.0f);
    
    return true;
}

void HelloWorld::nextScene(float t)
{
	CCScene* pScene = CCTransitionFade::create(1.0f, Title::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
