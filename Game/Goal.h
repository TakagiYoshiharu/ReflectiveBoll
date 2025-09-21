#pragma once
class Goal:public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	Vector3 GetPosition()const { return m_position; }
	float GetRadius()const { return m_radius; }
	ModelRender m_modelRender;
	Vector3 m_position = { -18.0f, 0.1f, 0.0f };
	float m_radius = 72.0f;
};

