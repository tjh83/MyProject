#include "Number.h"

USING_NS_CC;

Number* Number::create(const char* filename, int num, int cnt, int space, bool zero, bool dir)
{
	Number* batch = new Number();
	int tempNum = num;

	if(tempNum < 0)
		tempNum = 0;

	batch->mNumber = num;
	if(cnt == 0)
	{
		cnt = 0;
		while(true)
		{
			cnt++;
			tempNum = tempNum/10;
			if (tempNum<=0)
				break;
		}
	}
	batch->mCnt = cnt;
	batch->mSpace = space;
	batch->mZero = zero;
	batch->mDir = dir;
	batch->initWithFile(filename, cnt);
	batch->mWidth = batch->getTexture()->getContentSize().width/10;
	batch->mHeight = batch->getTexture()->getContentSize().height;
	batch->autorelease();
	tempNum = num;
	for(int i=cnt-1; i>=0; --i)
	{
		CCSprite* number = CCSprite::createWithTexture(batch->getTexture(), CCRect(tempNum%10*batch->mWidth, 0, batch->mWidth, batch->mHeight));
		number->setAnchorPoint(ccp(0, 1.0f));
		number->setPosition(ccp(i*(batch->mWidth+batch->mSpace), 0));
		batch->addChild(number, 1, i);
		tempNum /= 10;
	}

	return batch;
}

void Number::SetNum(int num)
{
	int tempNum = num;
	int cnt = 0;
	int i;
	
	if(tempNum < 0)
	{
		tempNum = 0;
	}

	while(true)
	{
		cnt++;
		tempNum = tempNum/10;
		if (tempNum<=0)
			break;
	}
	// 원래 숫자보다 자리수가 늘어나면 스프라이트 추가
	if(mCnt < cnt)
	{
		for(i=mCnt; i<cnt; ++i)
		{
			CCSprite* number = CCSprite::createWithTexture(this->getTexture(), CCRect(0, 0, mWidth, mHeight));
			number->setAnchorPoint(ccp(0, 1.0f));
			number->setPosition(ccp(i*(mWidth+mSpace), 0));
			addChild(number, 1, i);
		}
	}
	// 원래 숫자보다 자리수가 줄어들면 스프라이트 제거
	else if(mCnt > cnt)
	{
		for(i=mCnt-1; i>=cnt; --i)
		{
			removeChild(getChildByTag(i), true);
		}
	}
	mCnt = cnt;
	tempNum = num;
	for(i=cnt-1; i>=0; --i)
	{
		CCSprite* number = ((CCSprite*)getChildByTag(i));
		number->setTextureRect(CCRect(tempNum%10*mWidth, 0, mWidth, mHeight));
		tempNum /= 10;
	}
}