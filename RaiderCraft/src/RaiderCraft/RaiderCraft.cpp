#include <Raider.h>

#include "Player.h"
#include "world/World.h"
#include "world/WorldGenerator.h"
#include "render/WorldRenderer.h"
#include "render/ChunkMeshBuilder.h"

class RaiderCraftApp : public Raider::Application
{
public:
	RaiderCraftApp() : debugTimer("RaiderCraft")
	{
		Raider::EventSystem::getInstance()->addListener<Raider::EventMouseMove>(RD_SUBSCRIBE_EVENT(&RaiderCraftApp::onMouseMove));
		Raider::EventSystem::getInstance()->addListener<Raider::EventWindowResize>(RD_SUBSCRIBE_EVENT(&RaiderCraftApp::onWindowResize));
	}

	~RaiderCraftApp()
	{

	}

	void update() override
	{
		if (!firstCall)
		{
			firstCall = true;

			worldRenderer.setWorldRenderCam(&player.getPlayerCamera());

			debugTimer.startSection("worldGen");
			worldGenerator.generateWorld(&world);
			Raider::RaiderDebugTimer::RaiderDebugSection section = debugTimer.endSection();
			RD_INFO("World generation took: {} ms", section.lastTimeTaken);

			for (int x = 0; x < 16; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					for (int z = 0; z < 16; z++)
					{
						debugTimer.startSection("chunkGen");
						chunkMeshBuilder.buildChunk(&world, x, y, z);
						section = debugTimer.endSection();
					}
				}
			}

			RD_INFO("Avg Chunk Gen Time: {} ms", section.avgTimeTaken);

			worldRenderer.initRenderer();

			getWindow().disableCursor();
		}
	}

	void render() override
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updateCamera();
		worldRenderer.render(&world);

		//RD_INFO("X: {} - Y: {} - Z: {}", player.getX(), player.getY(), player.getZ());
	}

	void onWindowResize(Raider::EventWindowResize& event)
	{
		RD_INFO("Event called! X: {} - Y: {}", event.windowData().width, event.windowData().height);
	}

	void onMouseMove(Raider::EventMouseMove& event)
	{
		player.handleRotationInput(event.deltaX(), event.deltaY());
	}

	void updateCamera()
	{
		RaiderCraft::PlayerMovement playerMovement{};

		playerMovement.moveForwardPressed = getWindow().isKeyPressed(GLFW_KEY_W);
		playerMovement.moveBackPressed = getWindow().isKeyPressed(GLFW_KEY_S);
		playerMovement.moveLeftPressed = getWindow().isKeyPressed(GLFW_KEY_A);
		playerMovement.moveRightPressed = getWindow().isKeyPressed(GLFW_KEY_D);
		playerMovement.moveUpPressed = getWindow().isKeyPressed(GLFW_KEY_Q);
		playerMovement.moveDownPressed = getWindow().isKeyPressed(GLFW_KEY_Z);

		player.handleMovementInput(playerMovement);
	}

	RaiderCraft::World world;
	RaiderCraft::Player player;
	RaiderCraft::WorldRenderer worldRenderer;
	RaiderCraft::ChunkMeshBuilder chunkMeshBuilder;
	RaiderCraft::WorldGenerator worldGenerator;
	Raider::RaiderDebugTimer debugTimer;

	bool firstCall = false;
};

Raider::Application* Raider::createApplication()
{
	return new RaiderCraftApp();
}