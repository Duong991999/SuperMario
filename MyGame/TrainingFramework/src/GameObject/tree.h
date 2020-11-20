#pragma once
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "Player.h"

class Player;
extern int xSpeed;
extern int screenWidth;

class tree :
	public Sprite2D
{
public:
	tree(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint x, GLint y, GLint width, GLint height)
		:Sprite2D(model, shader, texture) {

		Set2DPosition(x, y);
		SetSize(width, height);

		m_Size.x = width;
		m_Size.y = height;

		m_isInScreen = false;
	};
	tree() = default;

	~tree();

	Vector2	GetSize() {
		return m_Size;
	}

	void	Update(GLfloat deltatime);

	//void	CheckInScreen();

	bool	GetIsInScreen() {
		return m_isInScreen;
	};
private:
	float time;
	Vector2 m_Size;

	bool	m_isInScreen;
};

