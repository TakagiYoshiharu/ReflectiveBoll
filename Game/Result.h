#pragma once
class TimeUI;
class Result:public IGameObject
{
public:
	Result();
	~Result();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	float m_remainingTime = 0.0f;
	// ゴール時のタイムを設定する
	void SetRemainingTime(float time) { m_remainingTime = time; }
	SpriteRender m_spriteRender;
	FontRender m_fontRenderTime;
	FontRender m_fontRenderStrokes;
	SoundSource* m_resultBGM;
	int m_strokes = 0;
	void SetStrokes(int strokes) { m_strokes = strokes; }   // 🔹打数をセットする関数
};

