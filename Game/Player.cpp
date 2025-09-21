#include "stdafx.h"
#include "Player.h"
#include"Bullet.h"
#include"Reflection.h"
Player::Player()
{
    //アニメーションクリップをロードする。
    animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
    animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
    animationClips[enAnimationClip_Walk].SetLoopFlag(true);
    animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
    animationClips[enAnimationClip_Jump].SetLoopFlag(false);
    animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
    animationClips[enAnimationClip_Run].SetLoopFlag(false);

    //ユニティちゃんのモデルを読み込む。
    m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

    //キャラコンを初期化する。
    m_characterController.Init(25.0f, 75.0f, m_position);
}



Player::~Player()
{

}

bool Player::Start() {
    m_forward = Vector3(0.0f, 0.0f, 1.0f); // Z正方向を初期値に
    m_hasBullet = true;

    bullet = NewGO<Bullet>(0, "bullet");
    //発射の位置
    m_spawnPos = m_position;
    m_spawnPos.y += 50.0f;

    bullet->SetPosition(m_spawnPos);

    // 弾の初速度（前方向に飛ばす）
    up_forward = m_forward;
    up_forward.Normalize();
    bullet->SetVelocity(up_forward * 1000.0f);

    //加速度
    m_accel = up_forward * 50.0f;
    m_accel.y = -9.8f;
    bullet->SetAcceleration(m_accel);

    //打つとなくなる
    m_hasBullet = false;
    return true;
}

//更新処理。
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
        //直進弾
        if (g_pad[0]->IsTrigger(enButtonB)) {
            bullet = NewGO<Bullet>(0, "bullet");
            bullet->SetType(Bullet::Type::Straight);
            //発射の位置
            m_spawnPos = m_position + Vector3(0.0f, 50.0f, 0.0f) + m_forward * 100.0f;

            bullet->SetPosition(m_spawnPos);

            // 弾の初速度（前方向に飛ばす）
            up_forward = m_forward;
            up_forward.Normalize();
            bullet->SetVelocity(up_forward * 1000.0f);

            //加速度
            m_accel = up_forward * 100.0f;
            m_accel.y = -9.8f;
            bullet->SetAcceleration(m_accel);

            //打つとなくなる
            m_hasBullet = false;

            // ?? 打数をカウント
            auto reflection = FindGO<Reflection>("reflection");
            if (reflection) {
                reflection->AddStroke();
            }
        }

        // Bボタン：放物線弾
            if (g_pad[0]->IsTrigger(enButtonA)) {
                bullet = NewGO<Bullet>(0, "bullet");
                bullet->SetType(Bullet::Type::Parabola);

                m_spawnPos = m_position + Vector3(0.0f, 50.0f, 0.0f) + m_forward * 100.0f;
                m_spawnPos.y += 50.0f;
                bullet->SetPosition(m_spawnPos);

                // 前方向に加えて、上方向にも速度を足す
                up_forward = m_forward;
                up_forward.Normalize();
                m_randomSpeed = 30.0f + (rand() % 101);
                m_startVel = up_forward * m_randomSpeed;//前方向スピード
                m_startVel.y += 300.0f; // 上方向成分を足す
                bullet->SetVelocity(m_startVel);

                // 放物線用の重力
                bullet->SetAcceleration(Vector3(0.0f, -100.0f, 0.0f));

                m_hasBullet = false;

                // ?? 打数をカウント
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

    //絵描きさんの更新処理。
    m_modelRender.Update();
}

void Player::Move()
{
    m_moveSpeed = Vector3::Zero;

    m_moveSpeed.x = 0.0f;
    m_moveSpeed.z = 0.0f;

    //左スティックの入力量を取得。
    Vector3 stickL;
    stickL.x = g_pad[0]->GetLStickXF();
    stickL.y = g_pad[0]->GetLStickYF();


    //カメラの前方向と右方向のベクトルを持ってくる。
    Vector3 forward = g_camera3D->GetForward();
    Vector3 right = g_camera3D->GetRight();

    //y方向には移動させない。
    forward.y = 0.0f;
    right.y = 0.0f;

    forward.Normalize();
    right.Normalize();

    m_moveSpeed += right * (stickL.x * 120.0f);
    m_moveSpeed += forward * (stickL.y * 120.0f);

    //キャラクターコントローラーを使って座標を移動させる。
    m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

    m_horizontalSpeed = Vector3(m_moveSpeed.x, 0.0f, m_moveSpeed.z);

    // キャラクターコントローラーで移動
    m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

    // 水平方向速度
    m_horizontalSpeed = Vector3(m_moveSpeed.x, 0.0f, m_moveSpeed.z);

    // ←ここに追加
    if (m_horizontalSpeed.Length() > 0.1f) {
        float targetYaw = atan2f(m_horizontalSpeed.x, m_horizontalSpeed.z);
        m_rotation.SetRotationY(targetYaw);
        m_modelRender.SetRotation(m_rotation);
    }

    // モデルに座標を渡す
    m_modelRender.SetPosition(m_position);


    //絵描きさんに座標を教える。
    m_modelRender.SetPosition(m_position);
}

void Player::Rotation() {
    Vector3 stickl;
    stickl.x = g_pad[0]->GetLStickXF();
    stickl.z = g_pad[0]->GetLStickYF();

    //xかzの移動速度があったら(スティックの入力があったら)。
    if (fabsf(stickl.x) >= 0.001f || fabsf(stickl.z) >= 0.001f)
    {
        Vector3 dir = stickl;
        dir.Normalize();

        //キャラクターの方向を変える。
        m_rotation.SetRotationYFromDirectionXZ(dir);

        //絵描きさんに回転を教える。
        m_modelRender.SetRotation(m_rotation);

        m_forward = dir;
    }
}

// 弾を持っているときの回転処理（移動はしない）
void Player::Rotation2()
{
    Vector3 stickl;
    stickl.x = g_pad[0]->GetLStickXF();  // 左右入力（A/D）
    stickl.z = g_pad[0]->GetLStickYF();  // 前後入力（W/S）

    // スティック入力が小さい場合は無視
    if (fabsf(stickl.x) < 0.1f && fabsf(stickl.z) < 0.1f) {
        return;
    }

    // カメラの前方向と右方向
    Vector3 camForward = g_camera3D->GetForward();
    camForward.y = 0.0f;
    camForward.Normalize();

    Vector3 camRight = g_camera3D->GetRight();
    camRight.y = 0.0f;
    camRight.Normalize();

    // スティック入力をカメラ基準に変換
    // W = カメラ前、S = カメラ後ろ、A = カメラ左、D = カメラ右
    Vector3 dir = camForward * stickl.z + camRight * stickl.x;

    if (dir.Length() < 0.001f) return;
    dir.Normalize();

    // キャラクターを回転
    m_rotation.SetRotationYFromDirectionXZ(dir);
    m_modelRender.SetRotation(m_rotation);

    // 前方向を更新（弾を撃つ向き用）
    m_forward = dir;
}


//ステート管理。
void Player::ManageState()
{
    //xかzの移動速度があったら(スティックの入力があったら)。
    if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
    {
        //ステートを2(歩き)にする。
        m_playerState = 2;
    }

    //xとzの移動速度が無かったら(スティックの入力が無かったら)。
    else
    {
        //ステートを0(待機)にする。
        m_playerState = 0;
    }
}

void Player::PlayAnimation() {
    //弾を持っているとき 
    if (m_hasBullet) {
        m_modelRender.PlayAnimation(enAnimationClip_Idle);
        return;
    }

    float speed = m_horizontalSpeed.Length();
    const float walkThreshold = 1.0f;
    // 弾を持っていない場合は移動速度で判定
    if (speed >= walkThreshold) {
        m_modelRender.PlayAnimation(enAnimationClip_Walk);
    }
    else {
        m_modelRender.PlayAnimation(enAnimationClip_Idle);
    }
}

//描画処理。
void Player::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);
}
