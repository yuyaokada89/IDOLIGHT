#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "EventListenerGesture.h"

enum judge
{
	PERFECT,
	GREAT,
	GOOD,
	MISS,

	judgeNum
};

class PlayScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	const static int SCORE_DIGIT = 6;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual bool init2();

	void AudioFinishCB(int, const std::string&);

	void onTap(cocos2d::Vec2 pos);
	void onSwipe(EventListenerGesture::SwipeDirection dir);

	void update(float delta);

	void fallNorts();

	void notesCreate();

	void notesExpel(cocos2d::Sprite * notes);

	void reflectScoreSprite();

	void addScore(judge judge_s);

	judge Notesjudge();

	cocos2d::Sprite* m_arrow[5];

	cocos2d::Sprite* m_Notes[5];

	cocos2d::Sprite* normal[4];

	cocos2d::Sprite* m_scoreSprite[SCORE_DIGIT];

	cocos2d::Sprite* m_lane;

	cocos2d::Sprite* m_sprite;

	cocos2d::Sprite* spr_note;

	cocos2d::Sprite* m_line;

	std::vector<cocos2d::Sprite*> notes_v;
	std::vector<int> notes_v_line;
	std::vector<EventListenerGesture::SwipeDirection> note_judge;
	

private:

	int id;

	int randam;

	int Notes_cnt;

	int notes_y;

	int Notes;

	int notes_cnt;

	int end_cnt;

	int max_time;

	int m_scorenum;

	float fall_time;

	bool notesflg;

	static cocos2d::Vec2 start_pos[4];

	static cocos2d::Vec2 line_pos[4];


	

    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
};

#endif // __HELLOWORLD_SCENE_H__
