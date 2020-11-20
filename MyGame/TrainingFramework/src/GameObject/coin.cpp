#include "coin.h"

coin::~coin()
{
}
coin::coin(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint x, GLint y)
	: Sprite2D(model, shader, texture)
{
	m_isAlive = true;
	m_timeToDraw = 0;
	m_iScore = 20;
	time = 0;


	 shader = ResourceManagers::GetInstance()->GetShader("Animation");
	 texture = ResourceManagers::GetInstance()->GetTexture("coin1");
	m_pAlive = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pAlive->SetSize(54, 42);
	
	texture = ResourceManagers::GetInstance()->GetTexture("death_coin");
	m_pDeath = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pDeath->SetSize(54, 42);

	m_pAnimation = m_pAlive;
	m_pAnimation->Set2DPosition(x, y);
}


void coin::Update(GLfloat deltatime)
{

	if (m_isAlive) {
		time += deltatime;
		Vector2 pos = Get2DPosition();
		pos.x = pos.x - 300 * deltatime;
		Set2DPosition(pos);
	}
	else {
		time += deltatime;
		Vector2 pos = Get2DPosition();
		m_pAnimation = m_pDeath;
		pos.x = pos.x - 300 * deltatime;
		Set2DPosition(pos);
		m_timeToDraw += deltatime;
	}
	//Update(deltatime);
}
