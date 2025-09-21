#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class Goal;
class GameClear;
class TimeUI;
class Result2;
class Reflection;
class Game2 : public IGameObject
{
public:
	~Game2();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	ModelRender m_modelRender;
	Vector3 m_pos;
	Player* m_player; //プレイヤー。
	GameCamera* m_gameCamera; //ゲームカメラ。
	BackGround* m_backGround;  //背景。
	SkyCube* m_skyCube;
	Goal* m_goal;
	TimeUI* m_timeUI;
	Result2* m_result2;
	Reflection* m_reflection;
	SpriteRender m_spriteRender;
	FontRender m_fontRenderDistance;
	FontRender m_fontRenderRemaining;
	SoundSource* game2BGM;
	int m_maxStrokes = 3;
	float m_distance=0.0f;
	int m_strokes = 0;
	void AddStroke() { m_strokes++; }
	int GetStrokes() const { return m_strokes; }
};

