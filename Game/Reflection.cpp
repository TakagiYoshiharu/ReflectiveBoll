#include "stdafx.h"
#include "Reflection.h"

bool Reflection::Start() {
   
    return true;
}

void Reflection::Update() {

}

// ?? ���� delta �t���ɕύX
void Reflection::AddStroke(int delta ) {
    m_strokes += delta;
    if (m_strokes < 0) m_strokes = 0; // �Ő������ɂȂ�Ȃ��悤����
}

void Reflection::Render(RenderContext& rc) {
  
}

// Game2�p�F�c��Ő��\��
void Reflection::RenderRemaining(RenderContext& rc) {
   
}
