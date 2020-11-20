#include "SkyGround.h"

SkyGround::~SkyGround()
{
}


void SkyGround::Update(GLfloat deltatime)
{
	time += deltatime;
	Vector2 pos = Get2DPosition();
	pos.x = pos.x-300*deltatime;
	Set2DPosition(pos);

}
