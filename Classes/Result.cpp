#include "Result.h"
#include "TitleScene.h"
#include "PlayScene.h"

USING_NS_CC;

ResultScene* ResultScene::create(int score)
{
	ResultScene *pRet = new(std::nothrow) ResultScene();
	if (pRet && pRet->init(score))
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
bool ResultScene::init(int score)
{
	// 基底クラスの初期化
	if (!Scene::init())
	{
		// 基底クラスの初期化が失敗なら、異常終了
		return false;
	}

	m_scorenum = score;

	// 背景画像
	Sprite* background = Sprite::create("result2.jpg");
	background->setPosition(480, 320);
	this->addChild(background);

	/*retry = ui::Button::create("result_replay.png");
	retry->setPosition(Vec2(480, 100));
	retry->setScale(2.0f);
	this->addChild(retry);*/
	
	title = Sprite::create("result_title.png");
	title->setPosition(850, 100);
	title->setScale(2.0f);
	this->addChild(title);

	retry = Sprite::create("result_replay.png");
	retry->setPosition(620, 100);
	retry->setScale(2.0f);
	this->addChild(retry);

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		m_scoreSprite[i] = Sprite::create("number.png");
		m_scoreSprite[i]->setPosition(800 - i * 92 * 0.3f, 370);
		m_scoreSprite[i]->setScale(0.6f);
		this->addChild(m_scoreSprite[i]);
	}

	// 毎フレーム更新を有効化
	scheduleUpdate();

	reflectScoreSprite();

	// タッチイベントリスナーを作成
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ResultScene::onTouchBegan, this);
	_director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	log("xxxxxxxx ResultScene Init End");

	// 初期化が正常終了
	return true;
}

void ResultScene::reflectScoreSprite()
{
	//スコア数をコピー
	int scorenum = m_scorenum;

	//表示上限を計算
	int limit = pow(10, SCORE_DIGIT) - 1;

	if (scorenum > limit)
	{
		scorenum = limit;
	}

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		int digit_number = scorenum % 10;

		Rect rect(0, 0, 95.0f, 92.0f);

		rect.origin.x = 95 * (digit_number % 5);

		if (digit_number >= 5)
		{
			rect.origin.y = 92.0f;
		}

		m_scoreSprite[i]->setTextureRect(rect);

		scorenum /= 10;
	}
}



// 毎フレーム更新
void ResultScene::update(float delta)
{

}

// タッチ開始時コールバック
bool ResultScene::onTouchBegan(Touch* touch, Event* pEvent)
{
	Vec2 touch_pos = touch->getLocation();

	Rect rect_title = title->getBoundingBox();

	Rect rect_retry = retry->getBoundingBox();

	bool hit = rect_title.containsPoint(touch_pos);

	bool hit2 = rect_retry.containsPoint(touch_pos);

	if (hit)
	{
		// 次のシーンを作成する
		Scene* nextScene = TitleScene::create();

		//フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));

		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}
	else if(hit2)
	{
		 //次のシーンを作成する
		Scene* nextScene = PlayScene::createScene();
		
		//フェードトランジション
		nextScene = TransitionFade::create(1.0f, nextScene, Color3B(255, 255, 255));
		
		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}
		return true;
	
}


