#ifndef __NUMBER_H__
#define __NUMBER_H__

#include "cocos2d.h"

class Number : public cocos2d::CCSpriteBatchNode
{
public:
	static Number* create(const char* filename, int num, int cnt, int space, bool zero = false, bool dir = false);
	void SetNum(int num);

private:
	int mNumber;
	int mCnt;
	int mSpace;
	bool mZero;
	bool mDir;
	int mWidth;
	int mHeight;
};

#endif
