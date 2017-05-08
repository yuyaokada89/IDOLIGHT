#include "TitleScene.h"
#include "Result.h"
#include "PlayScene.h"
#include "AttentionScene.h"

USING_NS_CC;

TitleScene* TitleScene::create()
{
	TitleScene *pRet = new(std::nothrow) TitleScene();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

// ������
bool TitleScene::init()
{
	// ���N���X�̏�����
	if (!Scene::init())
	{
		// ���N���X�̏����������s�Ȃ�A�ُ�I��
		return false;
	}

	// �w�i�摜
	Sprite* background = Sprite::create("title.png");
	background->setPosition(480, 320);
	this->addChild(background);

	ui::Button* button = ui::Button::create("start.png");
	button->setPosition(Vec2(480, 100));
	button->setScale(2.0f);
	this->addChild(button);

	effect = Sprite::create("title_effect.png");
	effect->setPosition(480.0f, 300.0f);
	effect->setScale(3.0f);
	effect->setOpacity(100.0f);
	this->addChild(effect);

	FadeIn* action = FadeIn::create(4.0f);
	FadeOut* action2 = FadeOut::create(4.0f);
	Sequence* fade = Sequence::create(action2, action, nullptr);
	RepeatForever* repeat = RepeatForever::create(fade);
	effect->runAction(repeat);

	Blink* action3 = Blink::create(90.0f, 100);
	RepeatForever* repeat2 = RepeatForever::create(action3);
	button->runAction(repeat2);


	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	button->addTouchEventListener(CC_CALLBACK_2(TitleScene::onButtonTouch, this));

	// ���t���[���X�V��L����
	scheduleUpdate();



	// ������������I��
	return true;
}



// ���t���[���X�V
void TitleScene::update(float delta)
{
	
}

// �^�b�`�J�n���R�[���o�b�N
bool TitleScene::onTouchBegan(Touch* touch, Event* pEvent)
{
	//�^�b�`���W���擾
	Vec2 touch_pos = touch->getLocation();

	// �쐬�����p�[�e�B�N���̃v���p�e�B���X�g��ǂݍ���
	ParticleSystemQuad* particle = ParticleSystemQuad::create("tap.plist");
	//�p�[�e�B�N���̃������[���[�N����i���d�v�j
	particle->setAutoRemoveOnFinish(true);
	// �p�[�e�B�N�����J�n
	particle->resetSystem();
	// �p�[�e�B�N����\������ꏊ�̐ݒ�
	particle->setPosition(touch_pos);
	// �p�[�e�B�N����z�u
	this->addChild(particle);

	return true;

}

void TitleScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		// ���̃V�[�����쐬����
		Scene* nextScene = AttentionScene::create();

		//�t�F�[�h�g�����W�V����
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);
	}

}
