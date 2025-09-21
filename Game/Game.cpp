#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include"Camera.h"
#include"Player.h"
#include"Result.h"
#include"Bullet.h"
#include"Goal.h"
#include"TimeUI.h"
#include"Title.h"
#include"Reflection.h"
#include<sstream>
#include<iomanip>

Game::~Game() {
    DeleteGO(m_player);

    DeleteGO(m_gameCamera);

    DeleteGO(m_backGround);

    DeleteGO(m_skyCube);

    DeleteGO(m_goal);

    DeleteGO(m_timeUI);

    DeleteGO(m_reflection);

    DeleteGO(gameBGM);
}

bool Game::Start()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");

	m_player = NewGO<Player>(0, "player");

	m_backGround = NewGO<BackGround>(0);

	m_gameCamera = NewGO<GameCamera>(0);

	m_skyCube = NewGO<SkyCube>(0, "skycube");

   m_goal = NewGO<Goal>(0, "goal");

   m_timeUI = NewGO<TimeUI>(0, "timeUI");

   m_reflection = NewGO<Reflection>(0, "reflection");
   m_reflection->SetGame2Mode(false); // Gameモード

   g_soundEngine->ResistWaveFileBank(0, "Assets/sound/AS_978947_楽しいイメージのシンセポップ＿ループ仕様.wav");
   gameBGM = NewGO<SoundSource>(0);
   gameBGM->Init(0);
   gameBGM->Play(true);

	return true;
}

void Game::Update()
{
	m_modelRender.Update(); 

    // 弾を探す
    auto bullet = FindGO<Bullet>("bullet"); 
    if (bullet && m_goal)
    {
        Vector3 diff = bullet->GetPosition() - m_goal->GetPosition();
        m_distance = diff.Length();

        if (m_distance < m_goal->GetRadius() + bullet->GetRadius() && bullet->IsStopped())
        {
            // タイマーを止める
            if (m_timeUI)
                m_timeUI->StopTimer();

            // ゴール時に直進弾なら打数を-5する
            if (bullet->GetType() == Bullet::Type::Straight) {  // Bullet クラスに Type を追加して判定
                if (m_reflection)
                    m_reflection->AddStroke(-5);  // AddStrokeに負の値を渡せるようにする
            }

            // クリア画面生成
            m_result = NewGO<Result>(0, "result");
            if (m_result && m_timeUI)
                m_result->SetRemainingTime(m_timeUI->GetRemainingTime());

            if (m_result && m_reflection)
                m_result->SetStrokes(m_reflection->GetStrokes());

            DeleteGO(bullet);
            DeleteGO(this);
        }
    }
    if (g_pad[0]->IsTrigger(enButtonSelect)) {
        NewGO<Title>(0, "title");
        DeleteGO(bullet);
        DeleteGO(this);
    }
}

void Game::Render(RenderContext& rc)
{
        // 打数の描画
            wchar_t buffer[64];
            swprintf(buffer, 64, L"打数: %d", m_reflection->GetStrokes());
            m_fontRenderCount.SetText(buffer);  // 任意の FontRender を使用
            m_fontRenderCount.SetPosition({ -600.0f, 50.0f, 0.0f });
            m_fontRenderCount.SetColor({ 0,0,0,1 });
            m_fontRenderCount.Draw(rc);
}