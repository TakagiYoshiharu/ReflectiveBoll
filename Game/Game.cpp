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
   m_reflection->SetGame2Mode(false); // Game���[�h

   g_soundEngine->ResistWaveFileBank(0, "Assets/sound/AS_978947_�y�����C���[�W�̃V���Z�|�b�v�Q���[�v�d�l.wav");
   gameBGM = NewGO<SoundSource>(0);
   gameBGM->Init(0);
   gameBGM->Play(true);

	return true;
}

void Game::Update()
{
	m_modelRender.Update(); 

    // �e��T��
    auto bullet = FindGO<Bullet>("bullet"); 
    if (bullet && m_goal)
    {
        Vector3 diff = bullet->GetPosition() - m_goal->GetPosition();
        m_distance = diff.Length();

        if (m_distance < m_goal->GetRadius() + bullet->GetRadius() && bullet->IsStopped())
        {
            // �^�C�}�[���~�߂�
            if (m_timeUI)
                m_timeUI->StopTimer();

            // �S�[�����ɒ��i�e�Ȃ�Ő���-5����
            if (bullet->GetType() == Bullet::Type::Straight) {  // Bullet �N���X�� Type ��ǉ����Ĕ���
                if (m_reflection)
                    m_reflection->AddStroke(-5);  // AddStroke�ɕ��̒l��n����悤�ɂ���
            }

            // �N���A��ʐ���
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
        // �Ő��̕`��
            wchar_t buffer[64];
            swprintf(buffer, 64, L"�Ő�: %d", m_reflection->GetStrokes());
            m_fontRenderCount.SetText(buffer);  // �C�ӂ� FontRender ���g�p
            m_fontRenderCount.SetPosition({ -600.0f, 50.0f, 0.0f });
            m_fontRenderCount.SetColor({ 0,0,0,1 });
            m_fontRenderCount.Draw(rc);
}