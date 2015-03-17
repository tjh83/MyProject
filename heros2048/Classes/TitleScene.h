#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

class Title : public cocos2d::CCLayerColor
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();

    CREATE_FUNC(Title);

	void MoveTitle(float t);

	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

	void nextScene();
protected:
	cocos2d::CCSize visibleSize;
	cocos2d::CCPoint origin;
	cocos2d::CCSprite* pBG2[2];
	cocos2d::CCSprite* pBG3[6];
	int nBGPos[2];
};

#endif // __TITLE_SCENE_H__
