#pragma once
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "Player.h"

class Player;
extern int xSpeed;
extern int screenWidth;

class gold :
	public Sprite2D
{
public:
	gold(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint x, GLint y, GLint width, GLint height)
		:Sprite2D(model, shader, texture) {
		m_isAlive = true;
		Set2DPosition(x, y);
		SetSize(width, height);
		int m_score = 10;
		m_Size.x = width;
		m_Size.y = height;

		m_isInScreen = false;
	};
	gold() = default;
bool  CheckAlive() {
		return m_isAlive;
	};

	~gold();

	Vector2	GetSize() {
		return m_Size;
	}
	void Death() {
		m_isAlive = false;
	};
	int GetScore() {
		return m_score;
	}
	void	Update(GLfloat deltatime);


	bool	GetIsInScreen() {
		return m_isInScreen;
	};
private:
	float time;
	Vector2 m_Size;
	bool m_isAlive ;
	bool	m_isInScreen;
	int m_score = 10;
};

