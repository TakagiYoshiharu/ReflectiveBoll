#pragma once
class Reflection:public IGameObject
{
public:
	bool Start();
	void Update();
	void  Render(RenderContext& rc);
	FontRender m_fontRenderCount;
	FontRender m_fontRenderRemaining;
	// �Ő��Ǘ�
	int GetStrokes() const { return m_strokes; }  // ���݂̑Ő�
	int GetMaxStrokes() const { return m_maxStrokes; } // �ő�Ő���Ԃ�
	void SetMaxStrokes(int maxStrokes) { m_maxStrokes = maxStrokes; } // �ݒ�
	void RenderRemaining(RenderContext& rc);  // �c��Ő��\���p
	// �\���؂�ւ��p�t���O
	void SetGame2Mode(bool flag) { m_isGame2 = flag; }
	int m_strokes = 0;
	int  m_maxStrokes = 3;
	bool m_isGame2 = false;
	 // ?? �Ő��Ǘ��idelta ������ǉ��j
	void AddStroke(int delta = 1);
};

