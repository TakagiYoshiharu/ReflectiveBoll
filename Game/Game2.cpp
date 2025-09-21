#include "stdafx.h"
#include "Game2.h"
#include "BackGround.h"
#include"Camera.h"
#include"Player.h"
#include"Result2.h"
#include"Bullet.h"
#include"Goal.h"
#include"TimeUI.h"
#include"Title.h"
#include"Reflection.h"
#include<sstream>
#include<iomanip>

Game2::~Game2() {
    DeleteGO(m_player);

    DeleteGO(m_gameCamera);

    DeleteGO(m_backGround);

    DeleteGO(m_skyCube);

    DeleteGO(m_goal);

    DeleteGO(m_timeUI);

    DeleteGO(m_reflection);

    DeleteGO(game2BGM);
}

bool Game2::Start()
{
    m_modelRender.Init("Assets/modelData/unityChan.tkm");

    m_player = NewGO<Player>(0, "player");

    m_backGround = NewGO<BackGround>(0);

    m_gameCamera = NewGO<GameCamera>(0);

    m_skyCube = NewGO<SkyCube>(0, "skycube");

    m_goal = NewGO<Goal>(0, "goal");

    m_timeUI = NewGO<TimeUI>(0, "timeUI");

        m_reflection = NewGO<Reflection>(0, "reflection");
        m_reflection->SetMaxStrokes(3); // 最大打数設定

        g_soundEngine->ResistWaveFileBank(0, "Assets/sound/AS_978947_楽しいイメージのシンセポップ＿ループ仕様.wav");
        game2BGM = NewGO<SoundSource>(0);
        game2BGM->Init(0);
        game2BGM->Play(true);

    return true;
}

void Game2::Update()
{
    m_modelRender.Update();

    auto bullet = FindGO<Bullet>("bullet");

    // 現在距離を常に更新
    if (bullet && m_goal)
    {
        Vector3 diff = bullet->GetPosition() - m_goal->GetPosition();

        diff.y = 0.0f;

        m_distance = diff.Length();
    }

    // 打ち切ったかつボールが存在している場合
    if (m_reflection->GetStrokes() >= m_reflection->GetMaxStrokes() && bullet && m_goal)
    {
        // ボールが地面に着いて止まったとき
        if (bullet->IsStopped())
        {
            // ゴールの中心とボールの位置の距離を計算
            Vector3 diff = bullet->GetPosition() - m_goal->GetPosition();
            m_distance = diff.Length();

            // リザルトへ
            auto result2 = NewGO<Result2>(0, "result2");
            if (result2) {
                result2->SetStrokes(m_reflection->GetStrokes()); // 打数
                result2->SetDistance(m_distance);                // 最終距離
            }

            DeleteGO(bullet);
            DeleteGO(this);
        }
    }

    // セレクトボタンでタイトルへ戻る
    if (g_pad[0]->IsTrigger(enButtonSelect))
    {
        NewGO<Title>(0, "title");
        DeleteGO(bullet);
        DeleteGO(this);
    }
}

void Game2::Render(RenderContext& rc)
{
    // ゴールまでの距離
    wchar_t bufDist[64];
    swprintf(bufDist, 64, L"中心までの距離: %.2f", m_distance);
    m_fontRenderDistance.SetText(bufDist);
    m_fontRenderDistance.SetPosition({ 100.0f, 200.0f, 0.0f });
    m_fontRenderDistance.SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });
    m_fontRenderDistance.Draw(rc);

        int remaining = m_reflection->GetMaxStrokes() - m_reflection->GetStrokes();
        wchar_t buffer[64];
        swprintf(buffer, 64, L"残り打数: %d", remaining);
        m_fontRenderRemaining.SetText(buffer);
        m_fontRenderRemaining.SetPosition({ -600.0f, 50.0f, 0.0f });
        m_fontRenderRemaining.SetColor({ 1,0,0,1 }); 
        m_fontRenderRemaining.Draw(rc);
}