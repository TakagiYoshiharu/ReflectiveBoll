#include "stdafx.h"
#include "Bullet.h"
#include <cstdlib> // rand()
#include <ctime>   // time()

Bullet::Bullet() {

}

Bullet::~Bullet() {

}

bool Bullet::Start() {
    // �e�̃��f�������[�h
    m_modelRender.Init("Assets/modelData/bull2.tkm");

    // ���f���̏����ʒu��ݒ�
    m_modelRender.SetPosition(m_position);

    return true;
}

void Bullet::Update() {
    float dt = g_gameTime->GetFrameDeltaTime();

    //�����x�𔽉f�������x
    m_velocity += m_acceleration * dt;

    //�ړ�����
    m_position += m_velocity * dt;

    //�n�ʔ���
    if (m_position.y <= 5.0f) {
        m_position.y = 5.0f;
        m_velocity = Vector3::Zero;
        m_acceleration = Vector3::Zero;
        m_isStopped = true;
    }

    // ����������
    static bool s_randomSeeded = false;
    if (!s_randomSeeded) {
        srand((unsigned int)time(nullptr));
        s_randomSeeded = true;
    }

    // �ǂɓ��������犮�S�����_�������ɔ���
    auto RandomDirection = []() -> Vector3 {
        float x = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // -1.0 ~ 1.0
        float y = 0.0f; // Y�����͒n�ʔ���ŌŒ�
        float z = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        Vector3 dir(x, y, z);
        dir.Normalize(); // �P�ʃx�N�g���ɐ��K��
        return dir;
        };

    // X�����̕ǔ���
    if (m_position.x < wallMinX || m_position.x > wallMaxX) {
        if (m_position.x < wallMinX) m_position.x = wallMinX;
        if (m_position.x > wallMaxX) m_position.x = wallMaxX;

        float speed = m_velocity.Length();
        m_velocity = RandomDirection() * speed; // ���S�����_�������ɔ���
    }

    // Z�����̕ǔ���
    if (m_position.z < wallMinZ || m_position.z > wallMaxZ) {
        if (m_position.z < wallMinZ) m_position.z = wallMinZ;
        if (m_position.z > wallMaxZ) m_position.z = wallMaxZ;

        float speed = m_velocity.Length();
        m_velocity = RandomDirection() * speed; // ���S�����_�������ɔ���
    }



    // ���f���̈ʒu���X�V
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

bool Bullet::IsStopped() {
    return m_isStopped;
}

Vector3 Bullet::GetPosition() {
    return m_position;
}

void Bullet::Render(RenderContext& rc) {
    m_modelRender.Draw(rc);
}

