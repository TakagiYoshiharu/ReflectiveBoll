#pragma once

class Bullet :public IGameObject
{
public:
	enum class Type { Straight, Parabola }; // 弾の種類
	Bullet();
	~Bullet();
	void Update();
	bool Start();
	void Render(RenderContext& rc);
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_velocity;
	Vector3 m_acceleration;
	RigidBody m_ghost;
	float m_radius = 5.0f;
	float m_restitution = -1.0f;//減速
	//位置
	void SetPosition(const Vector3& pos) { m_position = pos; }
	float GetRadius() const { return m_radius; }             // 半径取得
	//速度
	void SetVelocity(const Vector3& vel) { m_velocity = vel; }
	//加速度
	void SetAcceleration(const Vector3& acc) { m_acceleration = acc; }
	bool IsStopped();
	bool m_isStopped = false; // 地面で止まったかどうか
	Vector3 GetPosition();
	//壁の当たり判定を判定する範囲
	float wallMinX = -1000.0f;
	float wallMaxX = 1000.0f;
	float wallMinZ = -1000.0f;
	float wallMaxZ = 1000.0f;
	// ?? 弾のタイプ設定
	void SetType(Type t) { m_type = t; }
	Type GetType() const { return m_type; }
	Type m_type = Type::Straight; // デフォルトは直進弾
	SoundSource* bulletBGM;
};

