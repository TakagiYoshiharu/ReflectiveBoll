#include "stdafx.h"
#include "Player.h"
#include"Bullet.h"
#include"Reflection.h"
Player::Player()
{
    //�A�j���[�V�����N���b�v�����[�h����B
    animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
    animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
    animationClips[enAnimationClip_Walk].SetLoopFlag(true);
    animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
    animationClips[enAnimationClip_Jump].SetLoopFlag(false);
    animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
    animationClips[enAnimationClip_Run].SetLoopFlag(false);

    //���j�e�B�����̃��f����ǂݍ��ށB
    m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

    //�L�����R��������������B
    m_characterController.Init(25.0f, 75.0f, m_position);
}



Player::~Player()
{

}

bool Player::Start() {
    m_forward = Vector3(0.0f, 0.0f, 1.0f); // Z�������������l��
    m_hasBullet = true;

    bullet = NewGO<Bullet>(0, "bullet");
    //���˂̈ʒu
    m_spawnPos = m_position;
    m_spawnPos.y += 50.0f;

    bullet->SetPosition(m_spawnPos);

    // �e�̏����x�i�O�����ɔ�΂��j
    up_forward = m_forward;
    up_forward.Normalize();
    bullet->SetVelocity(up_forward * 1000.0f);

    //�����x
    m_accel = up_forward * 50.0f;
    m_accel.y = -9.8f;
    bullet->SetAcceleration(m_accel);

    //�łƂȂ��Ȃ�
    m_hasBullet = false;
    return true;
}

//�X�V�����B
void Player::Update()
{
    if (!m_hasBullet) {
        Rotation();
        Move();
    }
    else
    {
        Rotation2();
    }

    ManageState();

    PlayAnimation();

    if (m_hasBullet) {
        //���i�e
        if (g_pad[0]->IsTrigger(enButtonB)) {
            bullet = NewGO<Bullet>(0, "bullet");
            bullet->SetType(Bullet::Type::Straight);
            //���˂̈ʒu
            m_spawnPos = m_position + Vector3(0.0f, 50.0f, 0.0f) + m_forward * 100.0f;

            bullet->SetPosition(m_spawnPos);

            // �e�̏����x�i�O�����ɔ�΂��j
            up_forward = m_forward;
            up_forward.Normalize();
            bullet->SetVelocity(up_forward * 1000.0f);

            //�����x
            m_accel = up_forward * 100.0f;
            m_accel.y = -9.8f;
            bullet->SetAcceleration(m_accel);

            //�łƂȂ��Ȃ�
            m_hasBullet = false;

            // ?? �Ő����J�E���g
            auto reflection = FindGO<Reflection>("reflection");
            if (reflection) {
                reflection->AddStroke();
            }
        }

        // B�{�^���F�������e
            if (g_pad[0]->IsTrigger(enButtonA)) {
                bullet = NewGO<Bullet>(0, "bullet");
                bullet->SetType(Bullet::Type::Parabola);

                m_spawnPos = m_position + Vector3(0.0f, 50.0f, 0.0f) + m_forward * 100.0f;
                m_spawnPos.y += 50.0f;
                bullet->SetPosition(m_spawnPos);

                // �O�����ɉ����āA������ɂ����x�𑫂�
                up_forward = m_forward;
                up_forward.Normalize();
                m_randomSpeed = 30.0f + (rand() % 101);
                m_startVel = up_forward * m_randomSpeed;//�O�����X�s�[�h
                m_startVel.y += 300.0f; // ����������𑫂�
                bullet->SetVelocity(m_startVel);

                // �������p�̏d��
                bullet->SetAcceleration(Vector3(0.0f, -100.0f, 0.0f));

                m_hasBullet = false;

                // ?? �Ő����J�E���g
                auto reflection = FindGO<Reflection>("reflection");
                if (reflection) {
                    reflection->AddStroke();
                }
            }
    }

    bullet = FindGO<Bullet>("bullet");
    if (bullet && bullet->IsStopped()) {
        m_dist = (bullet->GetPosition() - m_position).Length();
        if (m_dist < 30.0f) {
            DeleteGO(bullet);
            m_hasBullet = true;
        }
    }

    //�G�`������̍X�V�����B
    m_modelRender.Update();
}

void Player::Move()
{
    m_moveSpeed = Vector3::Zero;

    m_moveSpeed.x = 0.0f;
    m_moveSpeed.z = 0.0f;

    //���X�e�B�b�N�̓��͗ʂ��擾�B
    Vector3 stickL;
    stickL.x = g_pad[0]->GetLStickXF();
    stickL.y = g_pad[0]->GetLStickYF();


    //�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
    Vector3 forward = g_camera3D->GetForward();
    Vector3 right = g_camera3D->GetRight();

    //y�����ɂ͈ړ������Ȃ��B
    forward.y = 0.0f;
    right.y = 0.0f;

    forward.Normalize();
    right.Normalize();

    m_moveSpeed += right * (stickL.x * 120.0f);
    m_moveSpeed += forward * (stickL.y * 120.0f);

    //�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
    m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

    m_horizontalSpeed = Vector3(m_moveSpeed.x, 0.0f, m_moveSpeed.z);

    // �L�����N�^�[�R���g���[���[�ňړ�
    m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

    // �����������x
    m_horizontalSpeed = Vector3(m_moveSpeed.x, 0.0f, m_moveSpeed.z);

    // �������ɒǉ�
    if (m_horizontalSpeed.Length() > 0.1f) {
        float targetYaw = atan2f(m_horizontalSpeed.x, m_horizontalSpeed.z);
        m_rotation.SetRotationY(targetYaw);
        m_modelRender.SetRotation(m_rotation);
    }

    // ���f���ɍ��W��n��
    m_modelRender.SetPosition(m_position);


    //�G�`������ɍ��W��������B
    m_modelRender.SetPosition(m_position);
}

void Player::Rotation() {
    Vector3 stickl;
    stickl.x = g_pad[0]->GetLStickXF();
    stickl.z = g_pad[0]->GetLStickYF();

    //x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
    if (fabsf(stickl.x) >= 0.001f || fabsf(stickl.z) >= 0.001f)
    {
        Vector3 dir = stickl;
        dir.Normalize();

        //�L�����N�^�[�̕�����ς���B
        m_rotation.SetRotationYFromDirectionXZ(dir);

        //�G�`������ɉ�]��������B
        m_modelRender.SetRotation(m_rotation);

        m_forward = dir;
    }
}

// �e�������Ă���Ƃ��̉�]�����i�ړ��͂��Ȃ��j
void Player::Rotation2()
{
    Vector3 stickl;
    stickl.x = g_pad[0]->GetLStickXF();  // ���E���́iA/D�j
    stickl.z = g_pad[0]->GetLStickYF();  // �O����́iW/S�j

    // �X�e�B�b�N���͂��������ꍇ�͖���
    if (fabsf(stickl.x) < 0.1f && fabsf(stickl.z) < 0.1f) {
        return;
    }

    // �J�����̑O�����ƉE����
    Vector3 camForward = g_camera3D->GetForward();
    camForward.y = 0.0f;
    camForward.Normalize();

    Vector3 camRight = g_camera3D->GetRight();
    camRight.y = 0.0f;
    camRight.Normalize();

    // �X�e�B�b�N���͂��J������ɕϊ�
    // W = �J�����O�AS = �J�������AA = �J�������AD = �J�����E
    Vector3 dir = camForward * stickl.z + camRight * stickl.x;

    if (dir.Length() < 0.001f) return;
    dir.Normalize();

    // �L�����N�^�[����]
    m_rotation.SetRotationYFromDirectionXZ(dir);
    m_modelRender.SetRotation(m_rotation);

    // �O�������X�V�i�e���������p�j
    m_forward = dir;
}


//�X�e�[�g�Ǘ��B
void Player::ManageState()
{
    //x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
    if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
    {
        //�X�e�[�g��2(����)�ɂ���B
        m_playerState = 2;
    }

    //x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
    else
    {
        //�X�e�[�g��0(�ҋ@)�ɂ���B
        m_playerState = 0;
    }
}

void Player::PlayAnimation() {
    //�e�������Ă���Ƃ� 
    if (m_hasBullet) {
        m_modelRender.PlayAnimation(enAnimationClip_Idle);
        return;
    }

    float speed = m_horizontalSpeed.Length();
    const float walkThreshold = 1.0f;
    // �e�������Ă��Ȃ��ꍇ�͈ړ����x�Ŕ���
    if (speed >= walkThreshold) {
        m_modelRender.PlayAnimation(enAnimationClip_Walk);
    }
    else {
        m_modelRender.PlayAnimation(enAnimationClip_Idle);
    }
}

//�`�揈���B
void Player::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);
}
