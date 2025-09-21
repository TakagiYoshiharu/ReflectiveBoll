#include "stdafx.h"
#include "Bullet.h"
#include <cstdlib> // rand()
#include <ctime>   // time()

Bullet::Bullet() {

}

Bullet::~Bullet() {

}

bool Bullet::Start() {
    // 弾のモデルをロード
    m_modelRender.Init("Assets/modelData/bull2.tkm");

    // モデルの初期位置を設定
    m_modelRender.SetPosition(m_position);

    return true;
}

void Bullet::Update() {
    float dt = g_gameTime->GetFrameDeltaTime();

    //加速度を反映した速度
    m_velocity += m_acceleration * dt;

    //移動処理
    m_position += m_velocity * dt;

    //地面判定
    if (m_position.y <= 5.0f) {
        m_position.y = 5.0f;
        m_velocity = Vector3::Zero;
        m_acceleration = Vector3::Zero;
        m_isStopped = true;
    }

    // 乱数初期化
    static bool s_randomSeeded = false;
    if (!s_randomSeeded) {
        srand((unsigned int)time(nullptr));
        s_randomSeeded = true;
    }

    // 壁に当たったら完全ランダム方向に反射
    auto RandomDirection = []() -> Vector3 {
        float x = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // -1.0 ~ 1.0
        float y = 0.0f; // Y方向は地面判定で固定
        float z = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        Vector3 dir(x, y, z);
        dir.Normalize(); // 単位ベクトルに正規化
        return dir;
        };

    // X方向の壁判定
    if (m_position.x < wallMinX || m_position.x > wallMaxX) {
        if (m_position.x < wallMinX) m_position.x = wallMinX;
        if (m_position.x > wallMaxX) m_position.x = wallMaxX;

        float speed = m_velocity.Length();
        m_velocity = RandomDirection() * speed; // 完全ランダム方向に反射
    }

    // Z方向の壁判定
    if (m_position.z < wallMinZ || m_position.z > wallMaxZ) {
        if (m_position.z < wallMinZ) m_position.z = wallMinZ;
        if (m_position.z > wallMaxZ) m_position.z = wallMaxZ;

        float speed = m_velocity.Length();
        m_velocity = RandomDirection() * speed; // 完全ランダム方向に反射
    }



    // モデルの位置を更新
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

