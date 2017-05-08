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

// 初期化
bool AttentionScene::init()
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	// 背景画像
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


	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(AttentionScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	button->addTouchEventListener(CC_CALLBACK_2(AttentionScene::onButtonTouch, this));

	// 毎フレーム更新を有効化
	scheduleUpdate();



	// 初期化が正常終了
	return true;
}



// 毎フレーム更新
void AttentionScene::update(float delta)
{
	
}

// タッチ開始時コールバック
bool AttentionScene::onTouchBegan(Touch* touch, Event* pEvent)
{
	//タッチ座標を取得
	Vec2 touch_pos = touch->getLocation();

	// 作成したパーティクルのプロパティリストを読み込み
	ParticleSystemQuad* particle = ParticleSystemQuad::create("tap.plist");
	//パーティクルのメモリーリーク回避（★重要）
	particle->setAutoRemoveOnFinish(true);
	// パーティクルを開始
	particle->resetSystem();
	// パーティクルを表示する場所の設定
	particle->setPosition(touch_pos);
	// パーティクルを配置
	this->addChild(particle);

	return true;

}

void AttentionScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		// 次のシーンを作成する
		Scene* nextScene = PlayScene::createScene();

		//フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}

}
