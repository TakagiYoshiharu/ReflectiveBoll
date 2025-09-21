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
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/AS_820394_�Q�[���̃��U���g��ʂȂǗp�̋�.wav");
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

	// �c�莞�Ԃ�`��
		wchar_t buf[64];
		swprintf(buf, 64, L"�N���A�^�C��: %.1f �b", m_remainingTime);
		m_fontRenderTime.SetText(buf);
		m_fontRenderTime.SetPosition({ -200.0f, -100.0f, 0.0f });
		m_fontRenderTime.SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		m_fontRenderTime.Draw(rc);

		wchar_t buf2[64];
		switch (m_strokes) {
		case 0:
			swprintf(buf2, 64, L"�X�R�A:�z�[���C������");
			break;
		case 1:
			swprintf(buf2, 64, L"�X�R�A:�C�[�O��");
			break;
		case 2:
			swprintf(buf2, 64, L"�X�R�A:�o�[�f�B");
			break;
		case 3:
			swprintf(buf2, 64, L"�X�R�A:�p�[");
			break;
		case 4:
			swprintf(buf2, 64, L"�X�R�A:�{�M�[");
			break;
		case 5:
			swprintf(buf2, 64, L"�X�R�A:�_�u���{�M�[");
			break;
		default:
			swprintf(buf2, 64, L"�X�R�A:%d",m_strokes);
			break;
		}

		m_fontRenderStrokes.SetText(buf2);
		m_fontRenderStrokes.SetPosition({ -100.0f, 0.0f, 0.0f });
		m_fontRenderStrokes.SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		m_fontRenderStrokes.Draw(rc);
}