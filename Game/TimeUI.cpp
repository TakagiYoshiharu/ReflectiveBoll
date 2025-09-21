#include "stdafx.h"
#include "TimeUI.h"

bool TimeUI::Start() {
   m_fontRender.SetColor({0,0,0,1}); // ���F�ɐݒ�
    m_fontRender.SetPosition({ -600.0f, 100.0f, 0.0f });
    return true;
}

void TimeUI::Update()
{
    if (!m_isStopped) {
        // �^�C�}�[�����炷
        m_timeLeft += m_deltaTime;
    }
    // �b�𕶎���ɕϊ�
    wchar_t buf[32];
    swprintf(buf, 32, L"�^�C��: %.1f", m_timeLeft);

    // �\����������X�V
    m_fontRender.SetText(buf);
}

float TimeUI::GetRemainingTime() {
    return m_timeLeft;
}

void TimeUI::Render(RenderContext& rc)
{
    m_fontRender.Draw(rc);
}