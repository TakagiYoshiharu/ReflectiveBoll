#pragma once
class TimeUI:public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	// �ǉ�: �^�C�}�[��~�p
	void StopTimer() { m_isStopped = true; }
	FontRender m_fontRender; // �t�H���g�`��p
	float m_timeLeft = 00.0f; // �c�莞�ԁi�b�j
	float m_deltaTime=0.015f;
	float GetRemainingTime();
	bool m_isStopped = false;
};

