#pragma once
class Reflection:public IGameObject
{
public:
	bool Start();
	void Update();
	void  Render(RenderContext& rc);
	FontRender m_fontRenderCount;
	FontRender m_fontRenderRemaining;
	// 打数管理
	int GetStrokes() const { return m_strokes; }  // 現在の打数
	int GetMaxStrokes() const { return m_maxStrokes; } // 最大打数を返す
	void SetMaxStrokes(int maxStrokes) { m_maxStrokes = maxStrokes; } // 設定
	void RenderRemaining(RenderContext& rc);  // 残り打数表示用
	// 表示切り替え用フラグ
	void SetGame2Mode(bool flag) { m_isGame2 = flag; }
	int m_strokes = 0;
	int  m_maxStrokes = 3;
	bool m_isGame2 = false;
	 // ?? 打数管理（delta 引数を追加）
	void AddStroke(int delta = 1);
};

