#ifndef __INGAME_SCENE_H__
#define __INGAME_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

#define STAT_HP					0
#define STAT_ATK				1
#define STAT_DEF				2
#define STAT_SPD				3

#define STAT_COUNT				4

#define BG_3_HEIGHT				107

#define HERO					0
#define MONSTER					1

#define MOVEFRAME				1000

class Ingame : public cocos2d::CCLayerColor
{
private:
	CCSprite*		m_pWarningImage;
	CCSprite*		m_pLockImage;
	CCLabelAtlas*	m_pBlockMoveCount;

	CCSprite*       m_fireWorks[3];
	CCAnimation*    m_DamageAni;

	int				m_nHeroBaseStat[STAT_COUNT];
	int				m_nMonsterBaseStat[STAT_COUNT];
	int				m_nBlockMoveCount;
public:
	Ingame();
	~Ingame();

public:
    virtual bool init();  

    static cocos2d::CCScene* scene();

    CREATE_FUNC(Ingame);

	void MoveIngame(float t);
	
	void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

	void nextScene();
	bool CreateNewBlock();
	void UpdateBlock();
	void MoveBlock(int dir);
	void InitStats();
	void InitMonsterStat();
	bool CheckBlock(cocos2d::CCPoint pos);
	int GetBlockCnt();
	void SetStats(int idx, int status);
	void MonsterAtk();
	void SetGameOver();
	void RegenMonster();
protected:
	cocos2d::CCSize visibleSize;
	cocos2d::CCPoint origin;
	cocos2d::CCSprite* pBG2[2];
	cocos2d::CCSprite* pBG3[6];
	int nBGPos[2];

private:
	void InitWarningImage();
	void ShowWarningImage( bool isShow );
	void UpdateWarning();

	void InitBlockMoveUI();
	void UpdateBlockMoveCount();

	void InitDamageEffect();
	void SetDamageEffect( int target );

	void SetPushAnimation( CCSprite* pSprite );
};

#endif
