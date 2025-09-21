#include "stdafx.h"
#include "Title.h"
#include"Game.h"
#include"Game2.h"
Title::Title()
{
    //‰æ‘œ‚ğ“Ç‚İ‚ŞB
    m_spriteRender.Init("Assets/sprite/333.dds", 1920.0f, 1080.0f);
    g_soundEngine->ResistWaveFileBank(1, "Assets/sound/AS_1236246_–¾‚é‚­‘u‚â‚©‚È‰¹Šy.wav");

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
    //‰æ‘œ‚ğ•`‰æ‚·‚éB
    m_spriteRender.Draw(rc);
}