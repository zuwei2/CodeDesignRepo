#include "EntityEditorApp.h"
#include <random>
#include <time.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include <iostream>

EntityEditorApp::EntityEditorApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) {

}

EntityEditorApp::~EntityEditorApp() {
	
}

bool EntityEditorApp::Startup() {

	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);

	int sizeOfData = sizeof(int) + m_entityCount * sizeof(Entity);
	m_fileHandle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		nullptr,
		PAGE_READWRITE,
		0, sizeof(sizeOfData),
		L"MySharedMemory");
	if (m_fileHandle == nullptr)
	{
		std::cout << "shared memory not allocated\n";
	}
	else
	{
		std::cout << "shared memory allocated\n";
	}
	srand(time(nullptr));
	for (auto& entity : m_entities) {
		entity.x = rand() % m_screenWidth;
		entity.y = rand() % m_screenHeight;
		entity.size = 10;
		entity.speed = rand() % 100;
		entity.rotation = rand() % 360;
		entity.r = rand() % 255;
		entity.g = rand() % 255;
		entity.b = rand() % 255;
	}

	return true;
}

void EntityEditorApp::Shutdown() {

	CloseHandle(m_fileHandle);
	CloseWindow();        // Close window and OpenGL context
}

void EntityEditorApp::Update(float deltaTime) {


	// select an entity to edit
	static int selection = 0;
	static bool selectionEditMode = false;
	static bool xEditMode = false;
	static bool yEditMode = false;
	static bool rotationEditMode = false;
	static bool sizeEditMode = false;
	static bool speedEditMode = false;
	static Color colorPickerValue = WHITE;


	if (GuiSpinner(Rectangle{ 90, 25, 125, 25 }, "Entity", &selection, 0, ENTITY_COUNT - 1, selectionEditMode)) selectionEditMode = !selectionEditMode;
	if (selection < 0)
	{
		selection = 0;
	}
	if (selection >= m_entityCount)
	{
		selection = m_entityCount -1;
	}
	int intX = (int)m_entities[selection].x;
	int intY = (int)m_entities[selection].y;
	int intRotation = (int)m_entities[selection].rotation;
	int intSize = (int)m_entities[selection].size;
	int intSpeed = (int)m_entities[selection].speed;


	// display editable stats within a GUI	
	GuiGroupBox(Rectangle{ 25, 70, 480, 220 }, "Entity Properties");

	if (GuiValueBox(Rectangle{ 90, 90, 125, 25 }, "x", &intX, 0, m_screenWidth, xEditMode)) xEditMode = !xEditMode;
	m_entities[selection].x = intX;

	if (GuiValueBox(Rectangle{ 90, 120, 125, 25 }, "y", &intY, 0, m_screenHeight, yEditMode)) yEditMode = !yEditMode;
	m_entities[selection].y = intY;

	m_entities[selection].rotation = GuiSlider(Rectangle{ 90, 150, 125, 25 }, "rotation", TextFormat("%2.2f", m_entities[selection].rotation), m_entities[selection].rotation, 0, 360);
	m_entities[selection].size = GuiSlider(Rectangle{ 90, 180, 125, 25 }, "size", TextFormat("%2.2f", m_entities[selection].size), m_entities[selection].size, 0, 100);
	m_entities[selection].speed = GuiSlider(Rectangle{ 90, 210, 125, 25 }, "speed", TextFormat("%2.2f", m_entities[selection].speed), m_entities[selection].speed, 0, 100);

	colorPickerValue = GuiColorPicker(Rectangle{ 260, 90, 156, 162 }, Color{ m_entities[selection].r, m_entities[selection].g, m_entities[selection].b });
	m_entities[selection].r = colorPickerValue.r;
	m_entities[selection].g = colorPickerValue.g;
	m_entities[selection].b = colorPickerValue.b;


	// move entities

	for (int i = 0; i < ENTITY_COUNT; i++) {
		if (selection == i)
			continue;

		float s = sinf(m_entities[i].rotation) * m_entities[i].speed;
		float c = cosf(m_entities[i].rotation) * m_entities[i].speed;
		m_entities[i].x -= s * deltaTime;
		m_entities[i].y += c * deltaTime;

		// wrap position around the screen
		m_entities[i].x = fmod(m_entities[i].x, m_screenWidth);
		if (m_entities[i].x < 0)
			m_entities[i].x += m_screenWidth;
		m_entities[i].y = fmod(m_entities[i].y, m_screenHeight);
		if (m_entities[i].y < 0)
			m_entities[i].y += m_screenHeight;
	}

	int* data = (int*)MapViewOfFile(m_fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
	if (data)
	{
		*data = m_entityCount;
		Entity* entityPointer = (Entity*)(data + 1);
		for (int i = 0; i < m_entityCount; i++)
		{
			*entityPointer = m_entities[i];
			entityPointer++;
		}
	}
}

void EntityEditorApp::Draw() {
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// draw entities
	for (auto& entity : m_entities) {
		DrawRectanglePro(
			Rectangle{ entity.x, entity.y, entity.size, entity.size }, // rectangle
			Vector2{ entity.size / 2, entity.size / 2 }, // origin
			entity.rotation,
			Color{ entity.r, entity.g, entity.b, 255 });
	}

	// output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	EndDrawing();
}