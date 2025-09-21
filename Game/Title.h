#pragma once
class Title :public IGameObject
{
public:
    Title();
    ~Title();
    //描画関数。
    void Render(RenderContext& rc);
    //更新処理。
    void Update();
    //スプライトレンダ―。
    SpriteRender m_spriteRender;
    SoundSource* titleBGM;
};

