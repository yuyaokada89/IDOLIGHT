#include "PlayScene.h"
#include "Result.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include <vector>

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::experimental;

cocos2d::Vec2 PlayScene::start_pos[4] = 
{
	Vec2(230,650),
	Vec2(400,650),
	Vec2(562,650),
	Vec2(730,650)
};

cocos2d::Vec2 PlayScene::line_pos[4] =
{
	Vec2(232,146),
	Vec2(400,146),
	Vec2(564,146),
	Vec2(730,146)
};

std::string notesjudge[judge::judgeNum] =
{
	"perfect_sq.png",
	"great_sq.png",
	"good_sq.png",
	"miss_sq.png",
};

std::string judge_name[judge::judgeNum] =
{
	"Perfect!.png",
	"Great!.png",
	"Good!.png",
	"Miss.png",
};




int judge_score[judge::judgeNum]=
{
	1000,
	500,
	100,
	0,
};

Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
   
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	srand(static_cast<unsigned int>(time(nullptr)));
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	m_lane = Sprite::create("gameplay.jpg");
	m_lane->setPosition(Vec2(483, 320));
	this->addChild(m_lane);

	m_sprite = Sprite::create("bar.png");
	m_sprite->setPosition(Vec2(466, 150));
	this->addChild(m_sprite);

	m_line = Sprite::create("line.jpg");
	m_line->setPosition(480.0f, 283.0f);
	m_line->setScaleX(1.05f);
	this->addChild(m_line);

	for (int i = 0; i < 4; i++)
	{
		normal[i] = Sprite::create("normal.png");
		normal[i]->setScale(0.9f);
		this->addChild(normal[i]);
	}
	
	normal[0]->setPosition(Vec2(232, 146));
	normal[1]->setPosition(Vec2(400, 146));
	normal[2]->setPosition(Vec2(564, 146));
	normal[3]->setPosition(Vec2(730, 146));

	notes_y = normal[0]->getPosition().y - normal[0]->getTextureRect().size.height / 2.0f;

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		m_scoreSprite[i] = Sprite::create("number.png");
		m_scoreSprite[i]->setPosition(600 - i * 92 * 0.5f, 590);
		m_scoreSprite[i]->setScale(0.5f);
		this->addChild(m_scoreSprite[i]);
	}

	std::vector<std::string>filenames;
	filenames.push_back("1_01.png");
	filenames.push_back("1_02.png");
	filenames.push_back("1-03.png");
	filenames.push_back("1-04.png");

	std::vector<std::string>filenames2;
	filenames2.push_back("2-01.png");
	filenames2.push_back("2-02.png");
	filenames2.push_back("2-03.png");
	filenames2.push_back("2-04.png");

	std::vector<std::string>filenames3;
	filenames3.push_back("L_1_1.png");
	filenames3.push_back("L_1_2.png");

	std::vector<std::string>filenames4;
	filenames4.push_back("L_2_1.png");
	filenames4.push_back("L_2_2.png");

	std::vector<std::string>filenames5;
	filenames5.push_back("R_1_1.png");
	filenames5.push_back("R_1_2.png");

	std::vector<std::string>filenames6;
	filenames6.push_back("R_2_1.png");
	filenames6.push_back("R_2_2.png");

	std::vector<std::string>filenames7;
	filenames7.push_back("light_l1.png");
	filenames7.push_back("light_l2.png");
	filenames7.push_back("light_l3.png");
	filenames7.push_back("light_l4.png");

	std::vector<std::string>lightfilenames_L1;
	lightfilenames_L1.push_back("L_1.png");
	lightfilenames_L1.push_back("L_2.png");
	lightfilenames_L1.push_back("L_3.png");
	lightfilenames_L1.push_back("L_4.png");
	lightfilenames_L1.push_back("L_5.png");
	lightfilenames_L1.push_back("L_6.png");
	lightfilenames_L1.push_back("L_7.png");


	std::vector<std::string>lightfilenames_L2;
	lightfilenames_L2.push_back("L_2.png");
	lightfilenames_L2.push_back("L_3.png");
	lightfilenames_L2.push_back("L_4.png");
	lightfilenames_L2.push_back("L_5.png");
	lightfilenames_L2.push_back("L_6.png");
	lightfilenames_L2.push_back("L_7.png");
	lightfilenames_L2.push_back("L_1.png");


	std::vector<std::string>lightfilenames_L3;
	lightfilenames_L3.push_back("L_3.png");
	lightfilenames_L3.push_back("L_4.png");
	lightfilenames_L3.push_back("L_5.png");
	lightfilenames_L3.push_back("L_6.png");
	lightfilenames_L3.push_back("L_7.png");
	lightfilenames_L3.push_back("L_1.png");
	lightfilenames_L3.push_back("L_2.png");

	std::vector<std::string>lightfilenames_R1;
	lightfilenames_R1.push_back("R_1.png");
	lightfilenames_R1.push_back("R_2.png");
	lightfilenames_R1.push_back("R_3.png");
	lightfilenames_R1.push_back("R_4.png");
	lightfilenames_R1.push_back("R_5.png");
	lightfilenames_R1.push_back("R_6.png");
	lightfilenames_R1.push_back("R_7.png");

	std::vector<std::string>lightfilenames_R2;
	lightfilenames_R2.push_back("R_2.png");
	lightfilenames_R2.push_back("R_3.png");
	lightfilenames_R2.push_back("R_4.png");
	lightfilenames_R2.push_back("R_5.png");
	lightfilenames_R2.push_back("R_6.png");
	lightfilenames_R2.push_back("R_7.png");
	lightfilenames_R2.push_back("R_1.png");

	std::vector<std::string>lightfilenames_R3;
	lightfilenames_R3.push_back("R_3.png");
	lightfilenames_R3.push_back("R_4.png");
	lightfilenames_R3.push_back("R_5.png");
	lightfilenames_R3.push_back("R_6.png");
	lightfilenames_R3.push_back("R_7.png");
	lightfilenames_R3.push_back("R_1.png");
	lightfilenames_R3.push_back("R_2.png");
	
	auto neutral = Sprite::create("1_01.png");
	auto neutral2 = Sprite::create("2-01.png");

	auto light = Sprite::create("L_1_1.png");
	auto light2 = Sprite::create("L_2_1.png");

	auto light3 = Sprite::create("R_1_1.png");
	auto light4 = Sprite::create("R_2_1.png");

	auto light5 = Sprite::create("light_l1.png");
	auto light6 = Sprite::create("light_l1.png");

	auto light_L1 = Sprite::create("L_1.png");
	auto light_L2 = Sprite::create("L_2.png");
	auto light_L3 = Sprite::create("L_3.png");

	auto light_R1 = Sprite::create("R_1.png");
	auto light_R2 = Sprite::create("R_2.png");
	auto light_R3 = Sprite::create("R_3.png");

	light_L1->setPosition(Vec2(91.0f, 595.0f));
	light_L2->setPosition(Vec2(161.0f, 595.0f));
	light_L3->setPosition(Vec2(233.0f, 595.0f));

	light_R1->setPosition(Vec2(740.0f, 595.0f));
	light_R2->setPosition(Vec2(811.0f, 595.0f));
	light_R3->setPosition(Vec2(882.0f, 595.0f));


	neutral->setPosition(Vec2(73.0f, 420.0f));
	neutral2->setPosition(Vec2(890.0f, 420.0f));

	light->setPosition(Vec2(80, 190));
	light2->setPosition(Vec2(80, 130));

	light3->setPosition(Vec2(880, 190));
	light4->setPosition(Vec2(880, 130));

	light5->setPosition(Vec2(80, 150));
	light6->setPosition(Vec2(880, 150));
	neutral->setScale(0.2f);
	neutral2->setScale(0.2f);
	light->setScale(0.9f);
	light3->setScale(0.9f);
	this->addChild(neutral);
	this->addChild(neutral2);
	this->addChild(light);
	this->addChild(light2);
	this->addChild(light3);
	this->addChild(light4);
	this->addChild(light5);
	this->addChild(light6);

	this->addChild(light_L1);
	this->addChild(light_L2);
	this->addChild(light_L3);

	this->addChild(light_R1);
	this->addChild(light_R2);
	this->addChild(light_R3);


	auto animation = Animation::create();
	auto animation2 = Animation::create();
	auto animation3 = Animation::create();
	auto animation4 = Animation::create();
	auto animation5 = Animation::create();
	auto animation6 = Animation::create();
	auto animation7 = Animation::create();

	auto lightanimation_L1 = Animation::create();
	auto lightanimation_L2 = Animation::create();
	auto lightanimation_L3 = Animation::create();

	auto lightanimation_R1 = Animation::create();
	auto lightanimation_R2 = Animation::create();
	auto lightanimation_R3 = Animation::create();

	for (auto filename : filenames)
	{
		animation->addSpriteFrameWithFile(filename);
	}

	for (auto filename2 : filenames2)
	{
		animation2->addSpriteFrameWithFile(filename2);
	}

	for (auto filename3 : filenames3)
	{
		animation3->addSpriteFrameWithFile(filename3);
	}

	for (auto filename4 : filenames4)
	{
		animation4->addSpriteFrameWithFile(filename4);
	}

	for (auto filename5 : filenames5)
	{
		animation5->addSpriteFrameWithFile(filename5);
	}

	for (auto filename6 : filenames6)
	{
		animation6->addSpriteFrameWithFile(filename6);
	}

	for (auto filename7 : filenames7)
	{
		animation7->addSpriteFrameWithFile(filename7);
	}

	for (auto lightfilename_L1 : lightfilenames_L1)
	{
		lightanimation_L1->addSpriteFrameWithFile(lightfilename_L1);
	}

	for (auto lightfilename_L2 : lightfilenames_L2)
	{
		lightanimation_L2->addSpriteFrameWithFile(lightfilename_L2);
	}

	for (auto lightfilename_L3 : lightfilenames_L3)
	{
		lightanimation_L3->addSpriteFrameWithFile(lightfilename_L3);
	}

	for (auto lightfilename_R1 : lightfilenames_R1)
	{
		lightanimation_R1->addSpriteFrameWithFile(lightfilename_R1);
	}

	for (auto lightfilename_R2 : lightfilenames_R2)
	{
		lightanimation_R2->addSpriteFrameWithFile(lightfilename_R2);
	}

	for (auto lightfilename_R3 : lightfilenames_R3)
	{
		lightanimation_R3->addSpriteFrameWithFile(lightfilename_R3);
	}


	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(200);

	animation2->setDelayPerUnit(0.2f);
	animation2->setRestoreOriginalFrame(true);
	animation2->setLoops(200);

	animation3->setDelayPerUnit(0.2f);
	animation3->setRestoreOriginalFrame(true);
	animation3->setLoops(400);

	animation4->setDelayPerUnit(0.2f);
	animation4->setRestoreOriginalFrame(true);
	animation4->setLoops(400);

	animation5->setDelayPerUnit(0.2f);
	animation5->setRestoreOriginalFrame(true);
	animation5->setLoops(400);

	animation6->setDelayPerUnit(0.2f);
	animation6->setRestoreOriginalFrame(true);
	animation6->setLoops(400);

	animation7->setDelayPerUnit(0.2f);
	animation7->setRestoreOriginalFrame(true);
	animation7->setLoops(400);

	lightanimation_L1->setDelayPerUnit(0.2f);
	lightanimation_L1->setRestoreOriginalFrame(true);
	lightanimation_L1->setLoops(200);

	lightanimation_L2->setDelayPerUnit(0.2f);
	lightanimation_L2->setRestoreOriginalFrame(true);
	lightanimation_L2->setLoops(200);

	lightanimation_L3->setDelayPerUnit(0.2f);
	lightanimation_L3->setRestoreOriginalFrame(true);
	lightanimation_L3->setLoops(200);

	lightanimation_R1->setDelayPerUnit(0.2f);
	lightanimation_R1->setRestoreOriginalFrame(true);
	lightanimation_R1->setLoops(200);

	lightanimation_R2->setDelayPerUnit(0.2f);
	lightanimation_R2->setRestoreOriginalFrame(true);
	lightanimation_R2->setLoops(200);

	lightanimation_R3->setDelayPerUnit(0.2f);
	lightanimation_R3->setRestoreOriginalFrame(true);
	lightanimation_R3->setLoops(200);

	auto action = Animate::create(animation);
	auto action2 = Animate::create(animation2);
	auto action3 = Animate::create(animation3);
	auto action4 = Animate::create(animation4);
	auto action5 = Animate::create(animation5);
	auto action6 = Animate::create(animation6);
	auto action7 = Animate::create(animation7);
	auto action8 = Animate::create(animation7);

	auto action_L1 = Animate::create(lightanimation_L1);
	auto action_L2 = Animate::create(lightanimation_L2);
	auto action_L3 = Animate::create(lightanimation_L3);

	auto action_R1 = Animate::create(lightanimation_R1);
	auto action_R2 = Animate::create(lightanimation_R2);
	auto action_R3 = Animate::create(lightanimation_R3);

	neutral->runAction(action);
	neutral2->runAction(action2);
	light->runAction(action3);
	light2->runAction(action4);
	light3->runAction(action5);
	light4->runAction(action6);
	light5->runAction(action7);
	light6->runAction(action8);

	light_L1->runAction(action_L1);
	light_L2->runAction(action_L2);
	light_L3->runAction(action_L3);

	light_R1->runAction(action_R1);
	light_R2->runAction(action_R2);
	light_R3->runAction(action_R3);

	Notes_cnt = 0;

	notes_cnt = 0;

	fall_time = 0;

	end_cnt = 0;

	m_scorenum = 0;

	max_time = 130;

	notesflg = true;

	reflectScoreSprite();

	AudioEngine::preload("hoshiyume.mp3");

	scheduleOnce(CC_CALLBACK_0(PlayScene::init2, this), 2.0f, "init2");

		//void scheduleOnce(const std::function<void(float)>& callback, float delay, const std::string &key);

    return true;
}

bool PlayScene::init2()
{
	//イベントリスナーを作成する
	EventListenerGesture* listener = EventListenerGesture::create();

	//スワイプと判定する距離を判定
	listener->setSwipeThreshouldDistance(100.0f);
	listener->setLongTapThreshouldSeconds(0.5f);

	//各コールバック関数を設定
	listener->onTap = CC_CALLBACK_1(PlayScene::onTap, this);
	listener->onSwipe = CC_CALLBACK_1(PlayScene::onSwipe, this);


	//イベントリスナーにシステムを登録する
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	id = AudioEngine::play2d("hoshiyume.mp3");
	AudioEngine::setFinishCallback(id, CC_CALLBACK_2(PlayScene::AudioFinishCB,this));
	


	return false;
}

void PlayScene::AudioFinishCB(int, const std::string&)
{
	end_cnt = 0;
	max_time = 0;
}

void PlayScene::update(float delta)
{
	fall_time += delta;

	log("xxxxxxxx update(%f)", delta / (1.0f/60.0f) * 100.0f);

	if (end_cnt >= 60)
	{
		max_time--;
		end_cnt = 0;
	}

	end_cnt++;

	if (notesflg == true)
	{
		fallNorts();
	}

	if (max_time <= 0)
	{
		log("xxxxxxxx ResultScene Create");
		// 次のシーンを作成する
		Scene* nextScene = ResultScene::create(m_scorenum);

		// 次のシーンに移行
		_director->replaceScene(nextScene);
	}

}

//ノーツを配列から追い出す関数
void PlayScene::notesExpel(Sprite * notes)
{
	for (int i = 0; i < notes_v.size(); i++)
	{
		if (notes_v[i] == notes)
		{
			// 要素の削除
			//ベクターから追い出す
			notes_v.erase(notes_v.begin() + i);
			notes_v_line.erase(notes_v_line.begin() + i);
			note_judge.erase(note_judge.begin() + i);
			i--;
		}
	}
}

void PlayScene::reflectScoreSprite()
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

		Rect rect(0, 0, 92.0f, 95.0f);

		rect.origin.x = 92 * (digit_number % 5);

		if (digit_number >= 5)
		{
			rect.origin.y = 95.0f;
		}

		m_scoreSprite[i]->setTextureRect(rect);

		scorenum /= 10;

	}
}

void PlayScene::addScore(judge judge_s)
{

	m_scorenum += judge_score[judge_s];

	reflectScoreSprite();

}

//ノーツを降らせる関数
void PlayScene::fallNorts()
{

	for (int i = 0; i < notes_v.size(); i++)
	{

			//if (spr_note == nullptr) continue;

			Notes = 0;
			Notes = rand() % 5;
			//ノーツのポジションが初期位置であり、ノーツ間隔は10フレーム以上であるか
			if (notes_v[i]->getPosition().y <= notes_y)
			{

				//スプライトの削除
				//notes_v[i]->removeFromParent();


				// 要素の削除
				//ベクターから追い出す
				notes_v.erase(notes_v.begin() + i);
				notes_v_line.erase(notes_v_line.begin() + i);
				note_judge.erase(note_judge.begin() + i);
				i--;

				//ノーツカウントを初期化する
				Notes_cnt = 0;
			}

			//ノーツカウントを足す
			Notes_cnt++;
		}
	
	if (fall_time >= 1.0f)
	{
		notesCreate();
		fall_time -= 1.0f;
		notes_cnt++;
		end_cnt++;
	}

		if (notes_cnt >= 120)
		{
			notesflg = false;
			
		}
}

void PlayScene::notesCreate()
{
	
	EventListenerGesture::SwipeDirection notes =(EventListenerGesture::SwipeDirection)(rand() % 5);

		switch (notes)
		{
		case EventListenerGesture::SwipeDirection::LEFT:
			spr_note = Sprite::create("notes.png");
			spr_note->setScale(0.6f);
			break;
		case  EventListenerGesture::SwipeDirection::UP:
			spr_note = Sprite::create("notes.png");
			spr_note->setRotation(90.0f);
			spr_note->setScale(0.6f);
			break;
		case EventListenerGesture::SwipeDirection::RIGHT:
			spr_note = Sprite::create("notes.png");
			spr_note->setRotation(180.0f);
			spr_note->setScale(0.6f);
			break;
		case EventListenerGesture::SwipeDirection::DOWN:
			spr_note = Sprite::create("notes.png");
			spr_note->setRotation(270.0f);
			spr_note->setScale(0.6f);
			break;
		case EventListenerGesture::SwipeDirection::NONE:
			spr_note = Sprite::create("notes_2.png");
			spr_note->setScale(0.6f);
			break;
		}

		this->addChild(spr_note);

		int Line_number = 0;

		Line_number = rand() % 4;

		Vec2 s_pos = start_pos[Line_number];
		Vec2 e_pos = start_pos[Line_number] + Vec2(0, -720);

		//初期位置
		spr_note->setPosition(s_pos);

		//アクションの作成
		MoveTo* action = MoveTo::create(1.0f, e_pos);
		CallFunc* action1 = CallFunc::create(CC_CALLBACK_0(PlayScene::notesExpel, this, spr_note));
		RemoveSelf* action2 = RemoveSelf::create(true);
		Sequence* action3 = Sequence::create(action, action1,action2, nullptr);


		spr_note->runAction(action3);
		//spr_note->runAction(action);

		// 要素の追加
		notes_v.push_back(spr_note);

		notes_v_line.push_back(Line_number);

		note_judge.push_back(notes);

}

//ノーツ判定
judge PlayScene::Notesjudge()
{
	judge result =judge::MISS;

	if (notes_v[0]->getPosition().y > normal[0]->getPosition().y + normal[0]->getTextureRect().size.height / 2.0f && notes_v[0]->getPosition().y <= 640.0f)
	{
		result = judge::GOOD;
	}

	if (notes_v[0]->getPosition().y < normal[0]->getPosition().y + normal[0]->getTextureRect().size.height / 2.0f && notes_v[0]->getPosition().y > normal[0]->getPosition().y - normal[0]->getTextureRect().size.height / 2.0f)
	{
		if (notes_v[0]->getPosition().y <= normal[0]->getPosition().y+20.0f  && notes_v[0]->getPosition().y >= normal[0]->getPosition().y - 20.0f)
		{
			result = judge::PERFECT;
		}
		else
		{
			result = judge::GREAT;
		}
	}

	return  result;
}

//タップ開始時に呼ばれる関数	
void PlayScene::onTap(Vec2 pos)
{
	std::string filename;

	judge judes;

	if (note_judge.size() == 0)
	{
		return;
	}
		if (EventListenerGesture::SwipeDirection::NONE == note_judge[0])
		{
			judes = Notesjudge();

			notes_v[0]->setVisible(false);
			Sprite* judgement = Sprite::create(notesjudge[judes]);
			Sprite* judgename = Sprite::create(judge_name[judes]);
			judgement->setScale(0.9f);
			int line_number = notes_v_line[0];
			judgement->setPosition(line_pos[line_number]);
			judgename->setPosition(Vec2(500, 320));
			this->addChild(judgement);
			this->addChild(judgename);
			addScore(judes);

			FadeOut* fadeout = FadeOut::create(1.0f);
			RemoveSelf* removeself = RemoveSelf::create(true);
			Sequence* fade = Sequence::create(fadeout, removeself, nullptr);
			FadeOut* fadeout2 = FadeOut::create(1.0f);
			RemoveSelf* removeself2 = RemoveSelf::create(true);
			Sequence* fade2 = Sequence::create(fadeout2, removeself2, nullptr);
			judgement->runAction(fade);
			judgename->runAction(fade2);

			if (judes != MISS)
			{
				Sprite* effect = Sprite::create("kira.png");
				effect->setScale(2.0f);
				effect->setPosition(line_pos[line_number]);
				this->addChild(effect);
				if (judes == PERFECT)
				{
					effect->setScale(3.0f);
				}
				else if (judes == GREAT)
				{
					effect->setScale(1.5f);
				}
				else if (judes == GOOD)
				{
					effect->setScale(1.0f);
				}
				RemoveSelf* removeself3 = RemoveSelf::create(true);
				Sequence* fade3 = Sequence::create(fadeout, removeself, nullptr);
				effect->runAction(fade3);
			}

		}
	
}

//スワイプされたときに呼ばれる関数
void PlayScene::onSwipe(EventListenerGesture::SwipeDirection dir)
{
	std::string filename;

	judge judes;

	if (note_judge.size() == 0)
	{
		return;
	}

		if (dir == note_judge[0])
		{
			judes = Notesjudge();

			notes_v[0]->setVisible(false);
			Sprite* judgement = Sprite::create(notesjudge[judes]);
			Sprite* judgename = Sprite::create(judge_name[judes]);
			judgement->setScale(0.9f);
			int line_number = notes_v_line[0];
			judgement->setPosition(line_pos[line_number]);
			judgename->setPosition(Vec2(500, 320));
			this->addChild(judgement);
			this->addChild(judgename);
			addScore(judes);

			FadeOut* fadeout = FadeOut::create(1.0f);
			RemoveSelf* removeself = RemoveSelf::create(true);
			Sequence* fade = Sequence::create(fadeout, removeself, nullptr);
			FadeOut* fadeout2 = FadeOut::create(1.0f);
			RemoveSelf* removeself2 = RemoveSelf::create(true);
			Sequence* fade2 = Sequence::create(fadeout2, removeself2, nullptr);
			FadeOut* fadeout3 = FadeOut::create(1.0f);
			judgement->runAction(fade);
			judgename->runAction(fade2);

			if (judes != MISS)
			{
				Sprite* effect = Sprite::create("kira.png");
				effect->setScale(2.0f);
				effect->setPosition(line_pos[line_number]);
				this->addChild(effect);
				if (judes == PERFECT)
				{
					effect->setScale(3.0f);
				}
				else if (judes == GREAT)
				{
					effect->setScale(1.5f);
				}
				else if (judes == GOOD)
				{
					effect->setScale(1.0f);
				}
				RemoveSelf* removeself3 = RemoveSelf::create(true);
				Sequence* fade3 = Sequence::create(fadeout, removeself, nullptr);
				effect->runAction(fade3);
			}

		}
}


