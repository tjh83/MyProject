#include "IngameScene.h"
#include "TitleScene.h"
#include "Number.h"

USING_NS_CC;

CCScene* Ingame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Ingame *layer = Ingame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

CCSprite* pHero;
CCSprite* pMonster;
int nBlock[16];
bool bJoin[16];
cocos2d::CCSprite* pGameBoard;
cocos2d::CCSprite* pBlock[16];
int nAddCnt;
int nPlayerStats[4];
int nMonsterStats[4];
int nMonsterLv;
int nKillNum;
int nBestKillNum;
Number* pKillNum;
//cocos2d::CCSprite* pKillNum[5];
Number* pBestKillNum;
Number* pStatsNum[4];
int nFrm;
int nMoveFrm[2];
bool bEnd;


Ingame::Ingame() : m_nBlockMoveCount(5)
{
	const int heroStat[STAT_COUNT] = { 100, 100, 100, 100 };
	const int monsterStat[STAT_COUNT] = { 100, 110, 90 ,90 };

	for( int i = 0; i < STAT_COUNT; i++ )
	{
		m_nHeroBaseStat[i] = heroStat[i];
		m_nMonsterBaseStat[i] = monsterStat[i];
	}
}

Ingame::~Ingame()
{
}

// on "init" you need to initialize your instance
bool Ingame::init()
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
		pBG3[i] = CCSprite::create( "bg3.png" );
		pBG3[i]->setAnchorPoint( ccp( 0.0f, 1.0f ) );
		pBG3[i]->setPosition( ccp( origin.x + i * 64 , origin.y + visibleSize.height - BG_3_HEIGHT ) );
		this->addChild( pBG3[i], 0 );
	}

	for(i=0; i<2; ++i)
	{
		nBGPos[i] = 0;
	}

	pHero = CCSprite::create("hero/1_knignt_move_1.png");
	pHero->setAnchorPoint(ccp(0.5f, 0.0f));
	pHero->setPosition(ccp(origin.x+134, origin.y+visibleSize.height-BG_3_HEIGHT));
	this->addChild(pHero, 0);

	CCAnimation* iHeroAni = CCAnimation::create();
	iHeroAni->setDelayPerUnit(0.1f);
	iHeroAni->addSpriteFrameWithFileName("hero/1_knignt_move_1.png");
	iHeroAni->addSpriteFrameWithFileName("hero/1_knignt_move_2.png");
	iHeroAni->addSpriteFrameWithFileName("hero/1_knignt_move_1.png");
	iHeroAni->addSpriteFrameWithFileName("hero/1_knignt_move_3.png");
	CCAnimate* iHeroAnimate = CCAnimate::create(iHeroAni);
	CCRepeatForever* HeroRepeat = CCRepeatForever::create(iHeroAnimate);
	pHero->runAction(HeroRepeat);

	pMonster = CCSprite::create("enemy/boss_1_move_1.png");
	pMonster->setAnchorPoint(ccp(0.5f, 0.0f));
	pMonster->setPosition(ccp(origin.x+visibleSize.width, origin.y+visibleSize.height-BG_3_HEIGHT));
	this->addChild(pMonster, 0);

	CCMoveTo* pMonsterMove = CCMoveTo::create(2.0f, ccp(origin.x+206, origin.y+visibleSize.height-BG_3_HEIGHT));
	pMonster->runAction(pMonsterMove);

	CCAnimation* iMonsterAni = CCAnimation::create();
	iMonsterAni->setDelayPerUnit(0.1f);
	iMonsterAni->addSpriteFrameWithFileName("enemy/boss_1_move_1.png");
	iMonsterAni->addSpriteFrameWithFileName("enemy/boss_1_move_2.png");
	iMonsterAni->addSpriteFrameWithFileName("enemy/boss_1_move_1.png");
	iMonsterAni->addSpriteFrameWithFileName("enemy/boss_1_move_3.png");
	CCAnimate* iMonsterAnimate = CCAnimate::create(iMonsterAni);
	CCRepeatForever* MonsterRepeat = CCRepeatForever::create(iMonsterAnimate);
	pMonster->runAction(MonsterRepeat);
	
	CCSprite* pStats = CCSprite::create("ingame_stat.png");
	pStats->setAnchorPoint(ccp(0.0f, 1.0f));
	pStats->setPosition(ccp(origin.x+5, origin.y+visibleSize.height-6));
	this->addChild(pStats, 1);

	InitStats();
	/*
	CCSpriteBatchNode* pNum = CCSpriteBatchNode::create("num.png");
	pStats->addChild(pNum);
	
	for(i=0; i<5; ++i)
	{
		pKillNum[i] = CCSprite::createWithTexture(pNum->getTexture(), CCRect(0, 0, 6, 8));
		pKillNum[i]->setAnchorPoint(ccp(0.0f, 1.0f));
		pKillNum[i]->setPosition(ccp(37+i*6, pStats->getContentSize().height));
		pNum->addChild(pKillNum[i], 0);
	}
	*/
	pKillNum = Number::create("num.png", nKillNum, 0, 0);
	pKillNum->setAnchorPoint(ccp(0.0f, 1.0f));
	pKillNum->setPosition(ccp(37, pStats->getContentSize().height));
	pStats->addChild(pKillNum, 0);

	pBestKillNum = Number::create("num.png", nBestKillNum, 0, 0);
	pBestKillNum->setAnchorPoint(ccp(0.0f, 1.0f));
	pBestKillNum->setPosition(ccp(186, pStats->getContentSize().height));
	pStats->addChild(pBestKillNum, 0);
	CCUserDefault *shared = CCUserDefault::sharedUserDefault();
	nBestKillNum = shared->getIntegerForKey("bestKill");
	pBestKillNum->SetNum(nBestKillNum);

	for(i=0; i<4; ++i)
	{
		pStatsNum[i] = Number::create("num.png", nPlayerStats[i], 0, 0);
		pStatsNum[i]->setAnchorPoint(ccp(0.0f, 1.0f));
		pStatsNum[i]->setPosition( ccp( 41, pStats->getContentSize().height - 108 - i * 10 ) );
		pStats->addChild(pStatsNum[i], 0);
	}
	
	pGameBoard = CCSprite::create("ingame_bg.png");
	pGameBoard->setAnchorPoint(ccp(0.0f, 1.0f));
	pGameBoard->setPosition(ccp(origin.x+10, origin.y+visibleSize.height-159));
	this->addChild(pGameBoard, 0);

	CCSpriteBatchNode* pBlocks = CCSpriteBatchNode::create("ingame_block.png");
	pGameBoard->addChild(pBlocks);
	for(i=0; i<16; ++i)
	{
		//pBlock[i] = CCSprite::create("ingame_block.png");
		pBlock[i] = CCSprite::createWithTexture(pBlocks->getTexture(), CCRect(0, 0, 62, 62));
		pBlock[i]->setAnchorPoint(ccp(0.5f, 0.5f));
		//pBlock[i]->setTextureRect(CCRect(0, 0, 62, 62));
		pBlock[i]->setPosition( ccp( 42 + ( i % 4 ) * ( 62 + 10 ), pGameBoard->getContentSize().height - 42 - (int)( i / 4) * ( 62 + 10 ) ) );
		pBlock[i]->setVisible(false);
		pBlocks->addChild(pBlock[i], 0);
	}

	for(i=0; i<16; ++i)
	{
		nBlock[i] = -1;
		bJoin[i] = false;
	}
	CreateNewBlock();
	nAddCnt = 0;

	nFrm = 0;
	nMoveFrm[0] = MOVEFRAME;
	nMoveFrm[1] = MOVEFRAME;

	bEnd = false;

	this->schedule(schedule_selector(Ingame::MoveIngame));

	this->setTouchEnabled(true);

	InitDamageEffect();
	InitBlockMoveUI();
	UpdateBlockMoveCount();
	InitWarningImage();
    
    return true;
}

void Ingame::MoveIngame(float t)
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

	if(nPlayerStats[0] > 0)
	{
		nFrm++;
	}
	if(nFrm >= 60)
	{
		int dmg;
		nFrm = 0;
		nMoveFrm[0] -= nPlayerStats[3];
		// 아군이 적군 공격
		if(nMoveFrm[0] <= 0)
		{
			nMoveFrm[0] = MOVEFRAME;	// 초기화
			// 공격하는 액션
			CCMoveTo* atk = CCMoveTo::create(0.2f, ccp(origin.x+134+40, origin.y+visibleSize.height-BG_3_HEIGHT));
			CCMoveTo* reverse = CCMoveTo::create(0.5f, ccp(origin.x+134, origin.y+visibleSize.height-BG_3_HEIGHT));
			pHero->runAction(CCSequence::create(atk, reverse, NULL));

			SetDamageEffect( MONSTER );

			// 데미지 산출(아군 공격력 - 적군 방어력)
			dmg = nPlayerStats[1] - nMonsterStats[2];
			// 최소 데미지는 1
			if(dmg <= 1)
			{
				dmg = 1;
			}
			nMonsterStats[0] -= dmg;
			if(nMonsterStats[0] <= 0)
			{
				// 몬스터 사라지는 액션
				CCFadeOut* fadeOut = CCFadeOut::create(2.0f);
				CCCallFunc* regen = CCCallFunc::create(this, callfunc_selector(Ingame::RegenMonster));
				pMonster->runAction(CCSequence::create(fadeOut, regen, NULL));
				// 킬수 증가
				nKillNum++;
				pKillNum->SetNum(nKillNum);

				m_nBlockMoveCount += 3;
				UpdateBlockMoveCount();
			}
		}

		nMoveFrm[1] -= nMonsterStats[3];
		// 적군이 아군 공격
		if(nMoveFrm[1] <= 0)
		{
			nMoveFrm[1] = MOVEFRAME;
			MonsterAtk();
		}
	}

	UpdateWarning();
}

CCPoint touchPos;
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

void Ingame::ccTouchesBegan(CCSet *touches, CCEvent *event)
{
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	touchPos = touch->getLocation();
}

void Ingame::ccTouchesEnded(CCSet *touches, CCEvent *event)
{
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint tempPos = touch->getLocation();

	if(bEnd)
	{
		nextScene();
		return;
	}

	int absX = abs(touchPos.x-tempPos.x);
	int absY = abs(touchPos.y-tempPos.y);
	if(absX > 30 && absY > 30)
	{
		if(absX >= absY)
		{
			if(touchPos.x > tempPos.x)
			{
				MoveBlock(LEFT);
			}
			else
			{
				MoveBlock(RIGHT);
			}
		}
		else
		{
			if(touchPos.y < tempPos.y)
			{
				MoveBlock(UP);
			}
			else
			{
				MoveBlock(DOWN);
			}
		}
	}
	else
	{
		if(touchPos.x-tempPos.x > 30)
		{
			MoveBlock(LEFT);
		}
		else if(touchPos.x-tempPos.x < -30)
		{
			MoveBlock(RIGHT);
		}
		else if(touchPos.y-tempPos.y < -30)
		{
			MoveBlock(UP);
		}
		else if(touchPos.y-tempPos.y > 30)
		{
			MoveBlock(DOWN);
		}
		else
		{
			if(CheckBlock(tempPos))
			{
				nAddCnt++;
				if(nAddCnt >= 3)
				{
					nAddCnt = 0;
					MonsterAtk();
				}
			}
		}
	}
}

bool Ingame::CreateNewBlock()
{
	int i;
	int temp;
	int arr[16];

	for(i=0; i<16; ++i)
	{
		arr[i] = i;
	}
	srand(time(NULL));
	for(i=0; i<16; ++i)
	{
		int ran = rand()%16;
		temp = arr[i];
		arr[i] = arr[ran];
		arr[ran] = temp;
	}
	for(i=0; i<16; ++i)
	{
		if(nBlock[arr[i]] == -1)
		{
			nBlock[arr[i]] = 0;
			pBlock[arr[i]]->setTextureRect(CCRect(0, 0, 62, 62));
			pBlock[arr[i]]->setVisible(true);
			SetPushAnimation( pBlock[arr[i]] );
			return true;
		}
	}
	return false;
}

void Ingame::UpdateBlock()
{
	int i;

	for(i=0; i<16; ++i)
	{
		if(nBlock[i] != -1)
		{
			pBlock[i]->setTextureRect(CCRect(nBlock[i]*62, 0, 62, 62));
		}
		/*else if(nBlock[i] == -1 && pBlock[i]->isVisible())
		{
			pBlock[i]->setVisible(false);
		}*/
		bJoin[i] = false;
	}
}

void Ingame::MoveBlock(int dir)
{
	int i, j;
	bool bMove = false;

	if( m_nBlockMoveCount <= 0 )
	{
		return;
	}
	
	switch(dir)
	{
	case LEFT:
		for(i=0; i<16; ++i)
		{
			// 첫번째줄은 이동이나 합체할 필요가 없으므로 통과.
			if(i%4 == 0)
			{
				continue;
			}
			// 해당칸에 블럭이 있을 경우에만 체크.
			// 이동 - 자기 앞 칸이 비었으면 앞으로 한 칸 이동.
			if(nBlock[i] != -1)
			{
				for(j=i; j%4>0; --j)
				{
					if(nBlock[j-1] == -1)
					{
						nBlock[j-1] = nBlock[j];
						pBlock[j-1]->setVisible(true);
						nBlock[j] = -1;
						pBlock[j]->setVisible(false);
						bMove = true;
					}
				}
			}
		}
		for(i=0; i<16; ++i)
		{
			// 첫번째줄은 이동이나 합체할 필요가 없으므로 통과.
			if(i%4 == 0)
			{
				continue;
			}
			// 이동이 끝나면 다시 해당칸에 블럭이 있는지 체크.
			// 합체 - 바로 앞 블럭이 현재 블럭과 같고, 블럭 인덱스가 10(2048) 이하이고, 아직 한 번도 합쳐지지 않은 블럭이면 합체.
			if(nBlock[i] != -1)
			{
				if(nBlock[i-1] == nBlock[i] && nBlock[i-1] < 10 && !bJoin[i-1])
				{
					SetPushAnimation( pBlock[i-1] );
					nBlock[i-1]++;
					bJoin[i-1] = true;
					nBlock[i] = -1;
					pBlock[i]->setVisible(false);
					bMove = true;
					// 합체시 뒤에 붙은 애들 다시 한칸씩 당긴다.
					if(i%4 == 1 || i%4 == 2)
					{
						for(j=i; j<i+(3-i%4); ++j)
						{
							if(nBlock[j+1] != -1)
							{
								nBlock[j] = nBlock[j+1];
								pBlock[j]->setVisible(true);
								nBlock[j+1] = -1;
								pBlock[j+1]->setVisible(false);
							}
						}
					}
				}
			}
		}
		break;
	case RIGHT:
		for(i=15; i>=0; --i)
		{
			if(i%4 == 3)
			{
				continue;
			}
			if(nBlock[i] != -1)
			{
				for(j=i; j%4<3; ++j)
				{
					if(nBlock[j+1] == -1)
					{
						nBlock[j+1] = nBlock[j];
						pBlock[j+1]->setVisible(true);
						nBlock[j] = -1;
						pBlock[j]->setVisible(false);
						bMove = true;
					}
				}
			}
		}
		for(i=15; i>=0; --i)
		{
			if(i%4 == 3)
			{
				continue;
			}
			if(nBlock[i] != -1)
			{
				if(nBlock[i+1] == nBlock[i] && nBlock[i+1] < 10 && !bJoin[i+1])
				{
					SetPushAnimation( pBlock[i+1] );
					nBlock[i+1]++;
					bJoin[i+1] = true;
					nBlock[i] = -1;
					pBlock[i]->setVisible(false);
					bMove = true;
					// 합체시 뒤에 붙은 애들 다시 한칸씩 당긴다.
					if(i%4 == 1 || i%4 == 2)
					{
						for(j=i; j%4>0; --j)
						{
							if(nBlock[j-1] != -1)
							{
								nBlock[j] = nBlock[j-1];
								pBlock[j]->setVisible(true);
								nBlock[j-1] = -1;
								pBlock[j-1]->setVisible(false);
							}
						}
					}
				}
			}
		}
		break;
	case UP:
		for(i=0; i<16; ++i)
		{
			if(i/4 == 0)
			{
				continue;
			}
			if(nBlock[i] != -1)
			{
				for(j=i; j/4>0; j-=4)
				{
					if(nBlock[j-4] == -1)
					{
						nBlock[j-4] = nBlock[j];
						pBlock[j-4]->setVisible(true);
						nBlock[j] = -1;
						pBlock[j]->setVisible(false);
						bMove = true;
					}
				}
			}
		}
		for(i=0; i<16; ++i)
		{
			if(i/4 == 0)
			{
				continue;
			}
			if(nBlock[i] != -1)
			{
				if(nBlock[i-4] == nBlock[i] && nBlock[i-4] < 10 && !bJoin[i-4])
				{
					nBlock[i-4]++;
					bJoin[i-4] = true;
					pBlock[i-4]->setVisible(true);
					SetPushAnimation( pBlock[i-4] );
					nBlock[i] = -1;
					pBlock[i]->setVisible(false);
					bMove = true;
					// 합체시 뒤에 붙은 애들 다시 한칸씩 당긴다.
					if(i/4 == 1 || i/4 == 2)
					{
						for(j=i; j<i+(3-i/4); j+=4)
						{
							if(nBlock[j+4] != -1)
							{
								nBlock[j] = nBlock[j+4];
								pBlock[j]->setVisible(true);
								nBlock[j+4] = -1;
								pBlock[j+4]->setVisible(false);
							}
						}
					}
				}
			}
		}
		break;
	case DOWN:
		for(i=15; i>=0; --i)
		{
			if(i/4 == 3)
			{
				continue;
			}
			if(nBlock[i] != -1)
			{
				for(j=i; j/4<3; j+=4)
				{
					if(nBlock[j+4] == -1)
					{
						nBlock[j+4] = nBlock[j];
						pBlock[j+4]->setVisible(true);
						nBlock[j] = -1;
						pBlock[j]->setVisible(false);
						bMove = true;
					}
				}
			}
		}
		for(i=15; i>=0; --i)
		{
			if(i/4 == 3)
			{
				continue;
			}
			if(nBlock[i] != -1)
			{
				if(nBlock[i+4] == nBlock[i] && nBlock[i+4] < 10 && !bJoin[i+4])
				{
					nBlock[i+4]++;
					bJoin[i-4] = true;
					pBlock[i+4]->setVisible(true);
					SetPushAnimation( pBlock[i+4] );
					nBlock[i] = -1;
					pBlock[i]->setVisible(false);
					bMove = true;
					// 합체시 뒤에 붙은 애들 다시 한칸씩 당긴다.
					if(i/4 == 1 || i/4 == 2)
					{
						for(j=i; j/4>0; j-=4)
						{
							if(nBlock[j-4] != -1)
							{
								nBlock[j] = nBlock[j-4];
								pBlock[j]->setVisible(true);
								nBlock[j-4] = -1;
								pBlock[j-4]->setVisible(false);
							}
						}
					}
				}
			}
		}
		break;
	}
	if(bMove)
	{
		UpdateBlock();
		CreateNewBlock();
	}
}

void Ingame::InitStats()
{
	nPlayerStats[STAT_HP]		= m_nHeroBaseStat[STAT_HP];
	nPlayerStats[STAT_ATK]		= m_nHeroBaseStat[STAT_ATK];
	nPlayerStats[STAT_DEF]		= m_nHeroBaseStat[STAT_DEF];
	nPlayerStats[STAT_SPD]		= m_nHeroBaseStat[STAT_SPD];

	nMonsterLv = 0;

	nKillNum = 0;
	nBestKillNum = 0;
}

void Ingame::InitMonsterStat()
{
	nMonsterStats[STAT_HP]		= m_nMonsterBaseStat[STAT_HP];
	nMonsterStats[STAT_ATK]		= m_nMonsterBaseStat[STAT_ATK];
	nMonsterStats[STAT_DEF]		= m_nMonsterBaseStat[STAT_DEF];
	nMonsterStats[STAT_SPD]		= m_nMonsterBaseStat[STAT_SPD];
}

bool Ingame::CheckBlock(CCPoint pos)
{
	int i, j;
	int blockIdx;
	int k;
	//int nAddStats[11] = {1, 1, 1, 1, 10, 3, 5, 5, 30, 10, 15};
	int nAddStats[11] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };

	if(GetBlockCnt() <= 1)
	{
		return false;
	}

	if(origin.x+16 < pos.x && pos.x <= origin.x+16+290 && origin.y+visibleSize.height-165-290 < pos.y && pos.y <= origin.y+visibleSize.height-165)
	{
		i = int((pos.x-(origin.x+16))/72)%4;
		j = int(((origin.y+visibleSize.height-165)-pos.y)/72);
		CCLog("i = %d, j= %d", i, j);
		blockIdx = i+j*4;
		if(nBlock[blockIdx] != -1)
		{
			for(k=0; k<11; ++k)
			{
				if(nBlock[blockIdx] == k)
				{
					//hads
					const int stat[11] = { 3, 0, 1, 2, 3, 0, 1, 2, 0, 1, 2 };
					nBlock[blockIdx] = -1;
					pBlock[blockIdx]->setVisible(false);
					SetStats( stat[k], nPlayerStats[stat[k]]+nAddStats[k]);

					m_nBlockMoveCount--;
					UpdateBlockMoveCount();
				}
			}
			return true;
		}
	}
	return false;
}

int Ingame::GetBlockCnt()
{
	int cnt = 0;

	for(int i=0; i<16; ++i)
	{
		if(nBlock[i] != -1)
		{
			cnt++;
		}
	}

	return cnt;
}

void Ingame::SetStats(int idx, int status)
{
	nPlayerStats[idx] = status;
	pStatsNum[idx]->SetNum(status);
}

void Ingame::MonsterAtk()
{
	CCMoveTo* monsterAtk = CCMoveTo::create(0.2f, ccp(origin.x+206-40, origin.y+visibleSize.height-BG_3_HEIGHT));
	CCMoveTo* monsterReverse = CCMoveTo::create(0.5f, ccp(origin.x+206, origin.y+visibleSize.height-BG_3_HEIGHT));
	pMonster->runAction(CCSequence::create(monsterAtk, monsterReverse, NULL));
	SetDamageEffect( HERO );

	int dmg = nMonsterStats[1] - nPlayerStats[2];
	if(dmg <= 1)
	{
		dmg = 1;
	}
	SetStats(0, nPlayerStats[0]-dmg);
	if(nPlayerStats[0] <= 0)
	{
		pHero->runAction( CCSequence::create( CCFadeOut::create( 2.0f ), CCDelayTime::create( 1.0f ), CCCallFunc::create( this, callfunc_selector( Ingame::SetGameOver ) ), NULL ) );	
	}
}

void Ingame::SetGameOver()
{
	CCLayerColor* gameoverLayer = CCLayerColor::create(ccc4(0, 0, 0, 128));
	addChild(gameoverLayer, 10);
	CCSprite* pGameover = CCSprite::create("ingame_gameover.png");
	pGameover->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
	gameoverLayer->addChild(pGameover);
	if(nBestKillNum < nKillNum)
	{
		nBestKillNum = nKillNum;
		pBestKillNum->SetNum(nBestKillNum);

		CCUserDefault::sharedUserDefault()->setIntegerForKey("bestKill", nBestKillNum);
		CCUserDefault::sharedUserDefault()->flush();
	}
	bEnd = true;
}

void Ingame::RegenMonster()
{
	int AddArray[4] = { 100, 50, 50, 5 };
	int i;

	nMonsterLv++;
	InitMonsterStat();

	for(i=0; i<nMonsterLv; ++i)
	{
		for(int j=0; j<4; ++j)
		{
			nMonsterStats[j] += AddArray[j];
		}
	}
	nMoveFrm[1] = MOVEFRAME;
	
	removeChild(pMonster, true);

	char monsterName[3][256];
	if((nMonsterLv+1) == 4)
	{
		for(i=0; i<2; ++i)
		{
			sprintf(monsterName[i], "enemy/boss_%d_move_%d.png", nMonsterLv%8+1, i+1);
		}
	}
	else
	{
		for(i=0; i<3; ++i)
		{
			sprintf(monsterName[i], "enemy/boss_%d_move_%d.png", nMonsterLv%8+1, i+1);
		}
	}
	pMonster = CCSprite::create(monsterName[0]);
	pMonster->setAnchorPoint(ccp(0.5f, 0.0f));
	pMonster->setPosition(ccp(origin.x+visibleSize.width, origin.y+visibleSize.height-BG_3_HEIGHT));
	this->addChild(pMonster, 0);

	CCAnimation* iMonsterAni = CCAnimation::create();
	iMonsterAni->setDelayPerUnit(0.1f);
	if((nMonsterLv+1) == 4)
	{
		for(i=0; i<2; ++i)
		{
			iMonsterAni->addSpriteFrameWithFileName(monsterName[i]);
		}
	}
	else
	{
		iMonsterAni->addSpriteFrameWithFileName(monsterName[0]);
		iMonsterAni->addSpriteFrameWithFileName(monsterName[1]);
		iMonsterAni->addSpriteFrameWithFileName(monsterName[0]);
		iMonsterAni->addSpriteFrameWithFileName(monsterName[2]);
	}
	CCAnimate* iMonsterAnimate = CCAnimate::create(iMonsterAni);
	CCRepeatForever* MonsterRepeat = CCRepeatForever::create(iMonsterAnimate);
	pMonster->runAction(MonsterRepeat);
	pMonster->setOpacity(255);
	pMonster->setPosition(ccp(origin.x+visibleSize.width, origin.y+visibleSize.height-BG_3_HEIGHT));
	CCMoveTo* pMonsterMove = CCMoveTo::create(2.0f, ccp(origin.x+206, origin.y+visibleSize.height-BG_3_HEIGHT));
	pMonster->runAction(pMonsterMove);
}

void Ingame::nextScene()
{
	CCScene* pScene = CCTransitionFade::create(1.0f, Title::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void Ingame::InitWarningImage()
{
	m_pWarningImage = CCSprite::create( "warning.png" );
	m_pWarningImage->setAnchorPoint( CCPointZero );
	m_pWarningImage->setPosition( CCPointZero );
	m_pWarningImage->setVisible( false );
	this->addChild( m_pWarningImage );

	CCActionInterval* action = (CCActionInterval*)( CCSequence::create( CCFadeOut::create( 1.0f ), CCFadeIn::create( 1.0f ), NULL ) );
	CCRepeatForever* repeatAction = CCRepeatForever::create( action );
	m_pWarningImage->runAction( repeatAction );
}

void Ingame::UpdateWarning()
{
	if( nPlayerStats[STAT_HP] <= m_nHeroBaseStat[STAT_HP] / 10 )
	{
		ShowWarningImage( true );
	}
	else
	{
		ShowWarningImage( false );
	}
}

void Ingame::ShowWarningImage( bool isShow )
{
	m_pWarningImage->setVisible( isShow );
}

void Ingame::InitBlockMoveUI()
{
	CCSprite* pSprite = CCSprite::create( "ingame_bg_2.png" );
	pSprite->setAnchorPoint( ccp( 0.0f, 1.0f ) );
	pSprite->setPosition( ccp( 209, origin.y + visibleSize.height - 129 ) );
	this->addChild( pSprite );

	m_pBlockMoveCount = CCLabelAtlas::create( "", "num_1.png", 6, 8, '0' );
	m_pBlockMoveCount->setAnchorPoint( ccp( 0.5f, 0.5f ) );
	m_pBlockMoveCount->setPosition( ccp( 32, 13 ) );
	pSprite->addChild( m_pBlockMoveCount );

	m_pLockImage = CCSprite::create( "lock.png" );
	m_pLockImage->setAnchorPoint( ccp( 0.0f, 1.0f ) );
	m_pLockImage->setPosition( ccp( origin.x + 10, origin.y + visibleSize.height - 159 ) );
	m_pLockImage->setVisible( false );
	this->addChild( m_pLockImage );
}

void Ingame::UpdateBlockMoveCount()
{
	char buf[32];
	sprintf( buf, "%d", m_nBlockMoveCount );
	m_pBlockMoveCount->setString( buf );

	if( m_nBlockMoveCount <= 0 )
	{
		m_pLockImage->setVisible( true );
	}
	else
	{
		m_pLockImage->setVisible( false );
	}
}

void Ingame::InitDamageEffect()
{
    m_DamageAni = CCAnimationCache::sharedAnimationCache()->animationByName( "DamageAni" );
    
    if( m_DamageAni == NULL )
    {
        int select_size = 250;
        
        m_DamageAni = CCAnimation::createWithSpriteFrames( NULL, 0.5f );
		m_DamageAni->addSpriteFrameWithFileName( "damage_effect1.png" );
		m_DamageAni->addSpriteFrameWithFileName( "damage_effect2.png" );
        
        CCAnimationCache::sharedAnimationCache()->addAnimation( m_DamageAni, "DamageAni" );
    }
}

void Ingame::SetDamageEffect( int target )
{
	int posX[2] = {
		pHero->getPosition().x, pMonster->getPosition().x
	};

	int posY[2] = {
		pHero->getPosition().y - ( pHero->getContentSize().height / 2 ),
		pHero->getPosition().y - ( pMonster->getContentSize().height / 2 )
	};

    CCSprite* pSprite = CCSprite::create( "damage_effect1.png" );
    pSprite->setAnchorPoint( ccp( 0.5f, 0.0f ) );
	pSprite->setPosition( ccp( posX[target], posY[target] ) );
    this->addChild( pSprite, 10 );
    
    CCAnimate* anim = CCAnimate::create( m_DamageAni );
    CCActionInterval* action = (CCActionInterval*)( CCSequence::create(
                                                                       CCShow::create(),
                                                                       anim,
                                                                       CCFadeOut::create( 0.5f ),
                                                                       NULL ) );
    pSprite->runAction( action );
}

void Ingame::SetPushAnimation( CCSprite* pSprite )
{
	pSprite->stopAllActions();
	pSprite->runAction( CCSequence::create( CCScaleTo::create( 0.1f, 0.8f ), CCScaleTo::create( 0.1f, 1.1f ), CCScaleTo::create( 0.1f, 1.0f ), NULL ) );
}