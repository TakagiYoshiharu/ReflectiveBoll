#include "stdafx.h"
#include "Camera.h"
#include"Player.h"

GameCamera::GameCamera() {

}

bool GameCamera::Start() {
    m_toCameraPos.Set(0.0f, 100.0f, -300.0f);

    g_camera3D->SetNear(0.1f);

    g_camera3D->SetFar(10000.0f);

    m_player = FindGO<Player>("player");

    return true;
}

void GameCamera::Update()
{

    if (!m_player) return;

    // �v���C���[�ʒu�𒍎��_��
    Vector3 target = m_player->m_position;
    target.y += 100.0f;

    // ���͎擾
    float x = g_pad[0]->GetRStickXF();
    float y = g_pad[0]->GetRStickYF();

    // Y����]
    Quaternion qRot;
    qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
    qRot.Apply(m_toCameraPos);

    // X����]
    Vector3 axisX;
    axisX.Cross(Vector3::AxisY, m_toCameraPos);
    if (axisX.Length() > 0.001f) {
        axisX.Normalize();
        qRot.SetRotationDeg(axisX, 1.3f * y);
        qRot.Apply(m_toCameraPos);
    }

    // �J�����ʒu
    Vector3 pos = target + m_toCameraPos;

    g_camera3D->SetTarget(target);
    g_camera3D->SetPosition(pos);
    g_camera3D->Update();
}