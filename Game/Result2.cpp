#include "stdafx.h"
#include "Result2.h"
#include"Title.h"
#include"TimeUI.h"

Result2::Result2() {
	m_spriteRender.Init("Assets/sprite/666.dds", 1920.0f, 1080.0f);
}

Result2::~Result2() {
	DeleteGO(m_result2BGM);
}

bool Result2::Start() {
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/AS_820394_ゲームのリザルト画面など用の曲.wav");
	m_result2BGM = NewGO<SoundSource>(2);
	m_result2BGM->Init(2);
	m_result2BGM->Play(true);
	return true;
}

void Result2::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void Result2::Render(RenderContext& rc) {

	m_spriteRender.Draw(rc);

	wchar_t buf2[64];
	swprintf(buf2, 64, L"ゴール中心までの距離: %.2f m", m_distance);
	m_fontRenderStrokes.SetText(buf2);
	m_fontRenderStrokes.SetPosition({ -250.0f, 0.0f, 0.0f });
	m_fontRenderStrokes.SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	m_fontRenderStrokes.Draw(rc);
}