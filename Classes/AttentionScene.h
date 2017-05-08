#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

// タイトルシーン
class AttentionScene : public cocos2d::Scene
{
private:

public:
	// create関数の宣言と定義
	static AttentionScene* create();

	bool init();

	void update(float delta) override;
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);

	cocos2d::ui::Button* button; //ボタン

};