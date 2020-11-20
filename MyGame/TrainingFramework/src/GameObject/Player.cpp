#include "Player.h"
Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_isInAir = false;
	m_isInSkyGround = false;
	m_xSpeed = 0;
	m_ySpeed = 0;
	m_isAlive = true;

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("myAnimation");
	m_prun = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_prun->SetSize(100, 100);

	texture = ResourceManagers::GetInstance()->GetTexture("jump_up");
	m_pjump_up = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 0.1f);
	m_pjump_up->SetSize(100, 100);

	texture = ResourceManagers::GetInstance()->GetTexture("jump_down");
	m_pjump_down = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 0.1f);
	m_pjump_down->SetSize(100, 100);

	texture = ResourceManagers::GetInstance()->GetTexture("chem2");
	m_pchem = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	m_pchem->SetSize(100, 100);

	m_pAnimation = m_prun;

	m_vPosition.x = 150;

	m_vPosition.y = screenHeight-180;
}



Player::~Player()
{
	m_pAnimation = NULL;
}


int keyPressed = 0;
void Player::HandleKeyEvents(GLbyte key, bool bIsPressed)
{

	if (bIsPressed && m_isAlive)
	{
		
		switch (key)
		{
		case KEY_SPACE:
			if (!m_isInAir) {
				m_isInAir = true;
				m_ySpeed = -350;

			}
		case KEY_UP:
			if (!m_isInSkyGround) {
				m_isInSkyGround = true;
				m_xSpeed = -500;
			}
		default:
			break;
			}
	}
}




void Player::CheckEnemy(std::shared_ptr<enemy>Enemy)
{
	Vector2 pos_enemy = Enemy->GetAnimation()->Get2DPosition();
	Vector2 pos_player = GetAnimation()->Get2DPosition();
	int pos_y = pos_player.x;
	int pos_yEnemy = pos_enemy.x;
	
			if (abs(pos_enemy.x - pos_player.x) < 45) {

				m_isAlive = false;

			}
			else {

				m_isAlive = false;

			
		}
	
}
void Player::CheckKillEnemy(std::shared_ptr<enemy>Enemy) {
	if (m_isInSkyGround) {
		Vector2 pos_enemy = Enemy->Get2DPosition();
		Vector2 pos_player = GetAnimation()->Get2DPosition();
		int pos_y = pos_player.y;
		int pos_yEnemy = pos_enemy.y;
		if (fabs(pos_y - pos_yEnemy) < 100) { 
			Enemy->Death();
		}
	}
}


void Player::CheckGold(std::shared_ptr<gold>Gold)
{
	Vector2 pos_coin = Gold->Get2DPosition();
	Vector2 pos_player = GetAnimation()->Get2DPosition();
	float distance;
	distance = (pos_coin.x - pos_player.x)*(pos_coin.x - pos_player.x) + (pos_coin.y - pos_player.y)*(pos_coin.y - pos_player.y);
	if (distance < 100&&Gold->CheckAlive()) {
		Gold->Death();
		score += 10;
	}
}


void Player::CheckGround() {
	int tmp = GetAnimation()->Get2DPosition().y;
	if (tmp >= screenHeight - 180) {
		m_isInAir = false;
	}
	else m_isInAir = true;
}
void Player::CheckSkyLeftGround(){
	int tmp = GetAnimation()->Get2DPosition().x;
	if (tmp >= 150) {
		m_isInSkyGround = false;
	}
	else m_isInSkyGround = true;
}
void Player::CheckSkyGround(std::shared_ptr<SkyGround>skyground)
{
	Vector2 pos = GetAnimation()->Get2DPosition();
	Vector2 pos_ground = skyground->Get2DPosition();
	Vector2 size_ground = skyground->GetSize();
	if (m_ySpeed>0) {
		if (pos_ground.x<250 && pos_ground.x>50 && (-pos.y - 50 + pos_ground.y)<=0)
		{
			m_isInAir = false;
			m_pAnimation = m_prun;
		}
	}
}



void Player::CheckTree(std::shared_ptr<tree> tree) {
	Vector2 pos_player = GetAnimation()->Get2DPosition();
	Vector2 pos_tree = tree->Get2DPosition();
	Vector2 tree_size = tree->GetSize();
	if (fabs(pos_player.y + 50 - pos_tree.y - tree_size.y / 2) < 5 && fabs(pos_player.x - pos_tree.x) < tree_size.x-10)
	{
		m_isAlive = false;
	}
	else m_isAlive = true;
}


void Player::Move(GLfloat deltatime)
{
	if (m_isAlive) {
		if (m_isInAir) {
			m_xSpeed = 0;
			m_ySpeed += gravity;
			if (m_ySpeed < 0) {
				m_pAnimation = m_pjump_up;
			}
			else {
				m_pAnimation = m_pjump_down;
			}
		
		}
		else {
			
			m_ySpeed = 0;
			if (m_isInSkyGround) {
				m_xSpeed += 30;
				m_pAnimation = m_pchem;
			}
			else {
				m_xSpeed = 0;
				m_pAnimation = m_prun;
			}
		}
	}

	else
	{
		m_ySpeed = 100;
		m_pAnimation = m_pHurt;
	}
	m_vPosition.y += m_ySpeed * deltatime;
	m_vPosition.x += m_xSpeed * deltatime;
}


void Player::Update(GLfloat deltatime)
{
	Move(deltatime);
	GetAnimation()->Update(deltatime);
	m_pAnimation->Set2DPosition(m_vPosition);
}


