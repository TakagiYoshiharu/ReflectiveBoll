#pragma once
class Player;
class GameCamera :public IGameObject
{
public:
	GameCamera();
	void Update();
	bool Start();
private:
	Player* m_player;
	Vector3 m_toCameraPos;
};

