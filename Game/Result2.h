#pragma once
class TimeUI;
class Result2 :public IGameObject
{
public:
	Result2();
	~Result2();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	SpriteRender m_spriteRender;
	FontRender m_fontRenderTime;
	FontRender m_fontRenderStrokes;
	int m_strokes = 0;
	float m_distance = 0.0f;
	void SetStrokes(int strokes) { m_strokes = strokes; }   // ??‘Å”‚ğƒZƒbƒg‚·‚éŠÖ”
	void SetDistance(float distance) { m_distance = distance; }
	SoundSource* m_result2BGM;
};

