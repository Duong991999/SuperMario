#pragma once
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "SpriteAnimation.h";
#include "Player.h"

class Player;
extern int xSpeed;
extern int screenWidth;

class coin :
	public Sprite2D
{
public:
	coin(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint x, GLint y);
	coin() = default;

	~coin();
	int GetScore()
	{
		return m_iScore;
	}

	std::shared_ptr<SpriteAnimation> GetAnimation() {
		return m_pAnimation;
	}
	void	Update(GLfloat deltatime);

	bool CheckAlive() {
		return m_isAlive;
	}
	float GetTimeToDraw()
	{
		return m_timeToDraw;
	}
	void Death() {
		m_isAlive = false;
	}
private:
	float time;
	std::shared_ptr<SpriteAnimation> m_pAnimation;
	std::shared_ptr<SpriteAnimation> m_pAlive;
	std::shared_ptr<SpriteAnimation> m_pDeath;
	int m_iScore;
	bool m_isAlive;
	float m_timeToDraw;
};

#pragma once
