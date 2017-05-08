#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

// �^�C�g���V�[��
class AttentionScene : public cocos2d::Scene
{
private:

public:
	// create�֐��̐錾�ƒ�`
	static AttentionScene* create();

	bool init();

	void update(float delta) override;
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * pEvent);

	void onButtonTouch(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType eventType);

	cocos2d::ui::Button* button; //�{�^��

};