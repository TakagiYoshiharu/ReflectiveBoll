#pragma once
class BackGround :public IGameObject
{
public:
    BackGround();
    ~BackGround();
    //�`��֐��B
    void Render(RenderContext& rc);
    //���f�������_�\�B        
    ModelRender m_modelRender;
    PhysicsStaticObject m_physicsStaticObject;
};

