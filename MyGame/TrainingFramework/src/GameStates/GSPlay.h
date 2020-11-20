#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "SkyGround.h"
#include "tree.h"
#include "gold.h"
#include "enemy.h"
class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;
class Player;
class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void	SetMap(std::shared_ptr<Models> model, std::shared_ptr<Shaders>);
	void	SetGold(std::shared_ptr<Models> model, std::shared_ptr<Shaders>);

	void SetGround(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader);
	
	void SetNewPostionForBullet();
	
private:
	std::shared_ptr<Player> m_Player;
	float time,TIME;
	float vantoc = 300;
	std::shared_ptr<Sprite2D> BackGround_1;
	std::shared_ptr<Sprite2D> BackGround_2;
	std::shared_ptr<SkyGround> m_Ground;
	std::shared_ptr<tree> tree1;
	std::vector<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_score;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	std::vector < std::shared_ptr<coin>> m_listSpriteAnimations;
	std::list<std::shared_ptr<tree>> m_listTree;
	std::list<std::shared_ptr<gold>> m_listGold;
	std::list<std::shared_ptr<enemy>> m_listEnemy;
	std::list<std::shared_ptr<SkyGround>> m_listGround;


};

