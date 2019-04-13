#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene() {
	camera = new GCamera();
	AddObject(camera);
	mainCamera = camera;

	camera->transform.position.z = -10.0f;

	cube = new GPolyhedron();
	cube->AddVertices({ {-1,-1,-1}, {-1,-1,1}, {-1,1,-1}, {-1,1,1}, {1,-1,-1}, {1,-1,1}, {1,1,-1}, {1,1,1} });
	cube->AddColors({ { 1,0,0,1 },{ 0,1,0,1 },{ 0,0,1,1 },{ 1,1,1,1 },{ 1,1,0,1 },{ 1,0,1,1 },{ 0,1,1,1 },{ 0,0,0,1 } });
	cube->AddIndices(
		{
			0,1,2,
			1,2,3,
			2,3,7,
			2,6,7,
			6,7,4,
			4,5,7,
			0,1,5,
			0,5,4,
			3,7,1,
			1,7,5,
			2,6,0,
			0,6,4,
		}
	);
	cube->SetVao();
	AddObject(cube);

	cube2 = new GPolyhedron();
	cube2->AddVertices({ { -1,-1,-1 },{ -1,-1,1 },{ -1,1,-1 },{ -1,1,1 },{ 1,-1,-1 },{ 1,-1,1 },{ 1,1,-1 },{ 1,1,1 } });
	cube2->AddColors({ { 1,0,0,1 },{ 0,1,0,1 },{ 0,0,1,1 },{ 1,1,1,1 },{ 1,1,0,1 },{ 1,0,1,1 },{ 0,1,1,1 },{ 0,0,0,1 } });
	cube2->AddIndices(
		{
			0,1,2,
			1,2,3,
			2,3,7,
			2,6,7,
			6,7,4,
			4,5,7,
			0,1,5,
			0,5,4,
			3,7,1,
			1,7,5,
			2,6,0,
			0,6,4,
		}
	);
	cube2->SetVao();
	cube2->transform.position.x += 2.0f;
	cube2->transform.scale = glm::vec3(0.5f);
	cube->AddChild(cube2);
}

void GameScene::Update(float deltaTime) {
	GScene::Update(deltaTime);
	cube->transform.rotation.x += 30.0f * deltaTime;
	cube->transform.rotation.y += 30.0f * deltaTime;
	cube2->transform.rotation.z += 90.0f * deltaTime;
}

void GameScene::Render() {
	GScene::Render();
	cube->Render();
	cube2->Render();
}