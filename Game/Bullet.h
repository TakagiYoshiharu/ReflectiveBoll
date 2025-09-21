#pragma once

class Bullet :public IGameObject
{
public:
	enum class Type { Straight, Parabola }; // �e�̎��
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
	float m_restitution = -1.0f;//����
	//�ʒu
	void SetPosition(const Vector3& pos) { m_position = pos; }
	float GetRadius() const { return m_radius; }             // ���a�擾
	//���x
	void SetVelocity(const Vector3& vel) { m_velocity = vel; }
	//�����x
	void SetAcceleration(const Vector3& acc) { m_acceleration = acc; }
	bool IsStopped();
	bool m_isStopped = false; // �n�ʂŎ~�܂������ǂ���
	Vector3 GetPosition();
	//�ǂ̓����蔻��𔻒肷��͈�
	float wallMinX = -1000.0f;
	float wallMaxX = 1000.0f;
	float wallMinZ = -1000.0f;
	float wallMaxZ = 1000.0f;
	// ?? �e�̃^�C�v�ݒ�
	void SetType(Type t) { m_type = t; }
	Type GetType() const { return m_type; }
	Type m_type = Type::Straight; // �f�t�H���g�͒��i�e
	SoundSource* bulletBGM;
};

