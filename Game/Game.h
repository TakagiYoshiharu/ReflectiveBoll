#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class Goal;
class GameClear;
class TimeUI;
class Result;
class Reflection;
class Game : public IGameObject
{
public:
		~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	ModelRender m_modelRender;
	Vector3 m_pos;
	Player* m_player; //�v���C���[�B
	GameCamera* m_gameCamera; //�Q�[���J�����B
	BackGround* m_backGround;  //�w�i�B
	SkyCube* m_skyCube;
	Goal* m_goal;
	TimeUI* m_timeUI;
	Result* m_result;
	Reflection* m_reflection;
	SpriteRender m_spriteRender;
	FontRender m_fontRenderCount;
	SoundSource* gameBGM;
	float m_distance;
	int m_strokes = 0;
	void AddStroke() { m_strokes++; }
	int GetStrokes() const { return m_strokes; }
};

