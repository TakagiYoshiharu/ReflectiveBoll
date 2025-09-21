#include "stdafx.h"
#include "Result.h"
#include"Title.h"
#include"TimeUI.h"
#include"sound/SoundEngine.h"

Result::Result() {
	m_spriteRender.Init("Assets/sprite/666.dds", 1920.0f, 1080.0f);
}

Result::~Result() {
	DeleteGO(m_resultBGM);
}

bool Result::Start() {
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/AS_820394_ゲームのリザルト画面など用の曲.wav");
	m_resultBGM = NewGO<SoundSource>(2);
	m_resultBGM->Init(2);
	m_resultBGM->Play(true);
	return true;
}

void Result::Update() {
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void Result::Render(RenderContext& rc) {

	m_spriteRender.Draw(rc);

	// 残り時間を描画
		wchar_t buf[64];
		swprintf(buf, 64, L"クリアタイム: %.1f 秒", m_remainingTime);
		m_fontRenderTime.SetText(buf);
		m_fontRenderTime.SetPosition({ -200.0f, -100.0f, 0.0f });
		m_fontRenderTime.SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		m_fontRenderTime.Draw(rc);

		wchar_t buf2[64];
		switch (m_strokes) {
		case 0:
			swprintf(buf2, 64, L"スコア:ホールインワン");
			break;
		case 1:
			swprintf(buf2, 64, L"スコア:イーグル");
			break;
		case 2:
			swprintf(buf2, 64, L"スコア:バーディ");
			break;
		case 3:
			swprintf(buf2, 64, L"スコア:パー");
			break;
		case 4:
			swprintf(buf2, 64, L"スコア:ボギー");
			break;
		case 5:
			swprintf(buf2, 64, L"スコア:ダブルボギー");
			break;
		default:
			swprintf(buf2, 64, L"スコア:%d",m_strokes);
			break;
		}

		m_fontRenderStrokes.SetText(buf2);
		m_fontRenderStrokes.SetPosition({ -100.0f, 0.0f, 0.0f });
		m_fontRenderStrokes.SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		m_fontRenderStrokes.Draw(rc);
}