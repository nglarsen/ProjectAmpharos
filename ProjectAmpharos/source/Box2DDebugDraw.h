///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		Box2DDebugDraw.h
//
//Purpose:	Draw box around physics objects
//
////////////////////////////////////////

#ifndef BOX2DDEBUGDRAW_H
#define	BOX2DDEBUGDRAW_H

#include <Box2D.h>
#include "ThirdParty\SDL2_gfx-1.0.1\include\SDL2_gfxPrimitives.h"
#include "ResourceManager.h"

class Box2DDebugDraw : public b2Draw 
{
public:
	Box2DDebugDraw();
	~Box2DDebugDraw();
	bool Initialize(ResourceManager* devices);

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform &xf);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

private:
	ResourceManager * devices;
	int circleAccuracy;
};


#endif // !BOX2DDEBUGDRAW_H
