#pragma once

#include "cocos2d.h"
#include "PlayScene.h"
#include "ui/CocosGUI.h"

// リザルトシーン
class ResultScene : public cocos2d::Scene
{

public:

	const static int SCORE_DIGIT = 6;

	// create関数の宣言と定義
	//CREATE_FUNC(ResultScene);

	static ResultScene* create(int score);

	bool init(int score);

	void reflectScoreSprite();

	void update(float delta) override;

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);

	cocos2d::Sprite* m_sprscore;

	cocos2d::Sprite* m_scoreSprite[SCORE_DIGIT];

	cocos2d::Sprite* m_result;

	cocos2d::Sprite* title;

	cocos2d::Sprite* retry;

	cocos2d::ui::Button* retry2; //ボタン

	int m_scorenum;

};