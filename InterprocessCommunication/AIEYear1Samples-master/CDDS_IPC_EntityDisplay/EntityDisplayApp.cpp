#include "EntityDisplayApp.h"
#include <iostream>

EntityDisplayApp::EntityDisplayApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) {

}

EntityDisplayApp::~EntityDisplayApp() {

}

bool EntityDisplayApp::Startup() {

	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);
	m_fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"MySharedMemory");
	if (m_fileHandle == nullptr)
	{
		std::cout << "shared memory not allocated\n";
		exit;
	}
	else
	{
		std::cout << "shared memory allocated\n";
	}


	return true;
}

void EntityDisplayApp::Shutdown() {

	CloseHandle(m_fileHandle);
	CloseWindow();        // Close window and OpenGL context
}

void EntityDisplayApp::Update(float deltaTime) {

}

void EntityDisplayApp::Draw() {
	BeginDrawing();

	ClearBackground(RAYWHITE);
	int* data = (int*)MapViewOfFile(m_fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
	if (data != nullptr)
	{
		m_entityCount = *data;
		m_entities = std::vector<Entity>();
		Entity* entityPointer = (Entity*)(data + 1);
		for (int i = 0; i < m_entityCount; i++)
		{
			m_entities.push_back(*entityPointer);
			entityPointer++;
		}
		// draw entities
		for (auto& entity : m_entities) {
			DrawRectanglePro(
				Rectangle{ entity.x, entity.y, entity.size, entity.size }, // rectangle
				Vector2{ entity.size / 2, entity.size / 2 }, // origin
				entity.rotation,
				Color{ entity.r, entity.g, entity.b, 255 });
		}


	}
	// output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	EndDrawing();
}