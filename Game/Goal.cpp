#include "stdafx.h"
#include "Goal.h"

bool Goal::Start() {
	m_modelRender.Init("Assets/modelData/goal.tkm");
	m_modelRender.SetScale(Vector3(50.0f, 0.1f, 50.0f));
	m_modelRender.SetPosition(m_position);
	return true;
}

void Goal::Update() {

}

void Goal::Render(RenderContext&rc) {
	m_modelRender.Draw(rc);
}