#pragma once
class TimeUI:public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	// 追加: タイマー停止用
	void StopTimer() { m_isStopped = true; }
	FontRender m_fontRender; // フォント描画用
	float m_timeLeft = 00.0f; // 残り時間（秒）
	float m_deltaTime=0.015f;
	float GetRemainingTime();
	bool m_isStopped = false;
};

