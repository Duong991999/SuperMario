#pragma once
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "SpriteAnimation.h";
#include <math.h>

//#include "Opossum.h"
//#include "Item.h"
//#include "Home.h"
class enemy;
class coin;
class SkyGround;
class tree;
//class Opossum;
//class Item;
//class Home;

extern int xSpeed;
extern int gravity;
extern int screenHeight;
extern int score;

class enemy : public Sprite2D
{

public:
	enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,GLint x, GLint y);

	~enemy();
	void CheckTree(std::shared_ptr<tree> tree);
	void CheckGround();
	void CheckSkyLeftGround();
	void HandleKeyEvents(GLbyte key, bool bIsPressed);
	void CheckSkyGround(std::shared_ptr<SkyGround> skyground);
	void CheckEnemy(std::shared_ptr<enemy>Enemy);
	void CheckKillEnemy(std::shared_ptr<enemy>Enemy);
	void CheckCoin(std::shared_ptr<coin>Coin);
	void	Move(GLfloat deltatime);

	std::shared_ptr<SpriteAnimation> GetAnimation() {
		return m_pAnimation;
	}
	void Death() {
		m_isAlive = false;
	}

	void Update(GLfloat deltatime);

	int GetxSpeed() {
		return m_xSpeed;
	}




	bool GetInAir() {
		return m_isInAir;
	}


	bool CheckAlive() {
		return m_isAlive;
	}


private:
	float time;
	float m_timeToDraw;
	void(*m_pKeyPreesed)();

	bool m_isKeyPressed;

	bool m_isRight;

	bool m_isInAir;

	bool m_isAlive;

	int m_xSpeed;
	bool m_isInSkyGround;

	int m_ySpeed;

	Vector2 m_vPosition;

	std::shared_ptr<SpriteAnimation> m_pAnimation;

	std::shared_ptr<SpriteAnimation> m_pHurt;

	std::shared_ptr<SpriteAnimation> m_prun;

	std::shared_ptr<SpriteAnimation> m_pdeath;

	std::shared_ptr<SpriteAnimation> m_pjump_down;
	std::shared_ptr<SpriteAnimation> m_pchem;

	//std::shared_ptr<SpriteAnimation> m_pIdleLeft;

	//std::shared_ptr<SpriteAnimation> m_pJumpUp;

	//std::shared_ptr<SpriteAnimation> m_pJumpDown;

	//std::shared_ptr<SpriteAnimation> m_pJumpLeftUp;

	//std::shared_ptr<SpriteAnimation> m_pJumpLeftDown;
};


