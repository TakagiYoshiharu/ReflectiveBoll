#include "stdafx.h"
#include "Reflection.h"

bool Reflection::Start() {
   
    return true;
}

void Reflection::Update() {

}

// ?? 引数 delta 付きに変更
void Reflection::AddStroke(int delta ) {
    m_strokes += delta;
    if (m_strokes < 0) m_strokes = 0; // 打数が負にならないよう制御
}

void Reflection::Render(RenderContext& rc) {
  
}

// Game2用：残り打数表示
void Reflection::RenderRemaining(RenderContext& rc) {
   
}
