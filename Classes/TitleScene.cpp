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

// 初期化
bool TitleScene::init()
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	// 背景画像
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


	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	button->addTouchEventListener(CC_CALLBACK_2(TitleScene::onButtonTouch, this));

	// 毎フレーム更新を有効化
	scheduleUpdate();



	// 初期化が正常終了
	return true;
}



// 毎フレーム更新
void TitleScene::update(float delta)
{
	
}

// タッチ開始時コールバック
bool TitleScene::onTouchBegan(Touch* touch, Event* pEvent)
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

void TitleScene::onButtonTouch(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		// 次のシーンを作成する
		Scene* nextScene = AttentionScene::create();

		//フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}

}
