#pragma once
class Bullet;
class Player :public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void ManageState();
	void PlayAnimation();
	bool Start();
	void Rotation2();
	Vector3 GetPosition() const { return m_position; }
	Vector3 m_position;
	Vector3 m_forward;
	Vector3 camForward;
	Vector3 camRight;
	ModelRender m_modelRender;
	Vector3 m_horizontalSpeed;
	Vector3 up_forward;
	Vector3 m_startVel;
	Vector3 m_accel;
	Vector3 m_dir;
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
	CharacterController m_characterController;
	Vector3 m_moveSpeed;
	Quaternion m_rotation;
	Vector3 m_spawnPos;
	int m_playerState = 0;
	bool m_hasBullet = true;
	float m_dist;
	Bullet* bullet;
	float m_randomSpeed;
};

