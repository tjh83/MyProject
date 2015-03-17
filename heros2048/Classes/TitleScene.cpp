#include "TitleScene.h"
#include "IngameScene.h"

USING_NS_CC;

CCScene* Title::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Title *layer = Title::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Title::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 255)) )
    {
        return false;
    }

	int i;
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	CCSprite* pBG1 = CCSprite::create("bg1.png");
	pBG1->setAnchorPoint(ccp(0.0f, 1.0f));
	pBG1->setPosition(ccp(origin.x, origin.y+visibleSize.height));
	this->addChild(pBG1, 0);
	
	for(i=0; i<2; ++i)
	{
		pBG2[i] = CCSprite::create("bg2.png");
		pBG2[i]->setAnchorPoint(ccp(0.0f, 1.0f));
		pBG2[i]->setPosition(ccp(origin.x+i*396, origin.y+visibleSize.height-46));
		this->addChild(pBG2[i], 0);
	}
	
	for(i=0; i<6; ++i)
	{
		pBG3[i] = CCSprite::create("bg3.png");
		pBG3[i]->setAnchorPoint(ccp(0.0f, 1.0f));
		pBG3[i]->setPosition(ccp(origin.x+i*64, origin.y+visibleSize.height-BG_3_HEIGHT));
		this->addChild(pBG3[i], 0);
	}

	for(i=0; i<2; ++i)
	{
		nBGPos[i] = 0;
	}

	CCSprite* iHero = CCSprite::create("hero/1_knignt_move_1.png");
	iHero->setAnchorPoint(ccp(0.5f, 0.0f));
	iHero->setPosition(ccp(origin.x+134, origin.y+visibleSize.height-BG_3_HEIGHT));
	this->addChild(iHero, 0);

	CCAnimation* iHeroAni = CCAnimation::create();
	iHeroAni->setDelayPerUnit(0.1f);
	iHeroAni->addSpriteFrameWithFileName("hero/1_knignt_move_1.png");
	iHeroAni->addSpriteFrameWithFileName("hero/1_knignt_move_2.png");
	iHeroAni->addSpriteFrameWithFileName("hero/1_knignt_move_1.png");
	iHeroAni->addSpriteFrameWithFileName("hero/1_knignt_move_3.png");
	CCAnimate* iHeroAnimate = CCAnimate::create(iHeroAni);
	CCRepeatForever* repeat = CCRepeatForever::create(iHeroAnimate);
	iHero->runAction(repeat);

	CCSprite* iTitleName = CCSprite::create("title_name.png");
	iTitleName->setAnchorPoint(ccp(0.5f, 1.0f));
	iTitleName->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height-142));
	this->addChild(iTitleName, 0);

	CCSprite* iTouch = CCSprite::create("title_text_touch.png");
	iTouch->setAnchorPoint(ccp(0.5f, 1.0f));
	iTouch->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height-320));
	this->addChild(iTouch, 0);

	CCSprite* iCopyright = CCSprite::create("title_text_copyright.png");
	iCopyright->setAnchorPoint(ccp(0.5f, 1.0f));
	iCopyright->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height-456));
	this->addChild(iCopyright, 0);

	this->schedule(schedule_selector(Title::MoveTitle));

	this->setTouchEnabled(true);
    
    return true;
}

void Title::MoveTitle(float t)
{
	int i;

	for(i=0; i<2; ++i)
	{
		pBG2[i]->setPosition(ccp(origin.x+i*396+nBGPos[0], origin.y+visibleSize.height-46));
	}
	for(i=0; i<6; ++i)
	{
		pBG3[i]->setPosition(ccp(origin.x+i*64+nBGPos[1], origin.y+visibleSize.height-BG_3_HEIGHT));
	}
	nBGPos[0]--;
	if(nBGPos[0] <= -396)
	{
		nBGPos[0] = 0;
	}
	nBGPos[1] -= 2;
	if(nBGPos[1] <= -64)
	{
		nBGPos[1] = 0;
	}
}

void Title::ccTouchesEnded(CCSet *touches, CCEvent *event)
{
	nextScene();
}

void Title::nextScene()
{
	CCScene* pScene = CCTransitionSlideInR::create(0.5f, Ingame::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}
