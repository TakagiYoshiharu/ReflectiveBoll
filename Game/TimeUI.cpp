#include "stdafx.h"
#include "TimeUI.h"

bool TimeUI::Start() {
   m_fontRender.SetColor({0,0,0,1}); // 白色に設定
    m_fontRender.SetPosition({ -600.0f, 100.0f, 0.0f });
    return true;
}

void TimeUI::Update()
{
    if (!m_isStopped) {
        // タイマーを減らす
        m_timeLeft += m_deltaTime;
    }
    // 秒を文字列に変換
    wchar_t buf[32];
    swprintf(buf, 32, L"タイム: %.1f", m_timeLeft);

    // 表示文字列を更新
    m_fontRender.SetText(buf);
}

float TimeUI::GetRemainingTime() {
    return m_timeLeft;
}

void TimeUI::Render(RenderContext& rc)
{
    m_fontRender.Draw(rc);
}