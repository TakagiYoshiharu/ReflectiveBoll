#include "stdafx.h"
#include "Title.h"
#include"Game.h"
#include"Game2.h"
Title::Title()
{
    //�摜��ǂݍ��ށB
    m_spriteRender.Init("Assets/sprite/333.dds", 1920.0f, 1080.0f);
    g_soundEngine->ResistWaveFileBank(1, "Assets/sound/AS_1236246_���邭�u�₩�ȉ��y.wav");

    titleBGM = NewGO<SoundSource>(1);
    titleBGM->Init(1);
    titleBGM->Play(true);
}

Title::~Title()
{
    DeleteGO(titleBGM);
}

void Title::Update()
{
    if (g_pad[0]->IsTrigger(enButtonA))
    {
        NewGO<Game>(0);
        DeleteGO(this);
    }

    if (g_pad[0]->IsTrigger(enButtonB)) {
        NewGO<Game2>(0);
        DeleteGO(this);
    }
}

void Title::Render(RenderContext& rc)
{
    //�摜��`�悷��B
    m_spriteRender.Draw(rc);
}