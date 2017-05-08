#include "AttentionScene.h"
#include "Result.h"
#include "PlayScene.h"

USING_NS_CC;

AttentionScene* AttentionScene::create()
{
	AttentionScene *pRet = new(std::nothrow) AttentionScene();
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
bool AttentionScene::init()
{
	// ���N���X�̏�����
	if (!Scene::init())
	{
		// ���N���X�̏����������s�Ȃ�A�ُ�I��
		return false;
	}

	// �w�i�摜
	Sprite* back = Sprite::create("attention_back.jpg");
	back->setPosition(480, 320);
	this->addChild(back);

	ui::Button* button = ui::Button::create("yes.png");
	button->setPosition(Vec2(480, 100));
	button->setScale(1.5f);
	this->addChild(button);

	std::vector<std::string>filenames;
	filenames.push_back("7_1.png");
	filenames.push_back("7_2.png");

	auto attention = Sprite::create("7_1.png");

	attention->setPosition(Vec2(800, 190));

	attention->setScale(0.4f);

	this->addChild(attention);

	auto animation = Animation::create();

	for (auto filename : filenames)
	{
		animation->addSpriteFrameWithFile(filename);
	}

	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(400);

	auto action = Animate::create(animation);

	attention->runAction(action);

	Blink* action3 = Blink::create(90.0f, 100);
	RepeatForever* repeat2 = RepeatForever::create(action3);
	button->runAction(repeat2);


	// �^�b�`�C�x���g���X�i�[���쐬
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(AttentionScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	button->addTouchEventListener(CC_CALLBACK_2(AttentionScene::onButtonTouch, this));

	// ���t���[���X�V��L����
	scheduleUpdate();



	// ������������I��
	return true;
}



// ���t���[���X�V
void AttentionScene::update(float delta)
{
	
}

// �^�b�`�J�n���R�[���o�b�N
bool AttentionScene::onTouchBegan(Touch* touch, Event* pEvent)
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

void AttentionScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		// ���̃V�[�����쐬����
		Scene* nextScene = PlayScene::createScene();

		//�t�F�[�h�g�����W�V����
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// ���̃V�[���Ɉڍs
		_director->replaceScene(nextScene);
	}

}
