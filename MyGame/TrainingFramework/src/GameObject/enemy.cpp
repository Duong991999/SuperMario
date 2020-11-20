#include "enemy.h"


enemy::enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,GLint x, GLint y)
	: Sprite2D(model, shader, texture)
{
	m_isInAir = false;
	m_isInSkyGround = false;
	m_xSpeed = 300;
	m_ySpeed = 0;

	m_isAlive = true;
	m_timeToDraw = 0;

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("enemy");
	m_prun = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_prun->SetSize(100, 100);

	texture = ResourceManagers::GetInstance()->GetTexture("death_enemy");
	m_pdeath = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pdeath->SetSize(100, 100);

	m_pAnimation = m_prun;

	m_vPosition.x = x;

	m_vPosition.y = y;
}



enemy::~enemy()
{
	m_pAnimation = NULL;
}




void enemy::Move(GLfloat deltatime)
{


	GetAnimation()->Update(deltatime);
	if (m_isAlive) {
		time += deltatime;
		m_vPosition.x -= m_xSpeed * deltatime;
		//m_timeToDraw += deltatime;
		}
		else {

			time += deltatime;
			m_vPosition.x -= m_xSpeed * deltatime;
			m_timeToDraw += deltatime;
			m_pAnimation = m_pdeath;
	}


}


void enemy::Update(GLfloat deltatime)
{
	Move(deltatime);
	GetAnimation()->Update(deltatime);
	m_pAnimation->Set2DPosition(m_vPosition);
}


