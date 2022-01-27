#include "app.h"

#include "keyboard_movement_controller.h"
#include "simple_render_system.h"
#include "camera.h"

#include <stdexcept>
#include <array>
#include <chrono>
#include <iostream>

namespace Engine
{

    App::App()
    {
        loadGameObjects();
    }

    App::~App() {}

    void App::run()
    {
        SimpleRenderSystem simpleRenderSystem{device, renderer.getSwapChainRenderPass()};
        Camera camera{};

        //camera.setViewDirection(glm::vec3{0.0f}, glm::vec3(0.5f, 0.0f, 1.0f));
        camera.setViewTarget(glm::vec3(-50.0f, -2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 2.5f));

        auto viewerObject = GameObject::createGameObject();
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!window.shouldClose())
        {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();

            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            frameTime = glm::min(frameTime, MAX_FRAME_TIME);

            // std::cout << "Frame Time: " << frameTime << std::endl;

            cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = renderer.getAspectRatio();

            camera.setPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 100.0f);

            if (auto commandBuffer = renderer.beginFrame())
            {
                renderer.beginSwapChainRenderPass(commandBuffer);

                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);

                renderer.endSwapChainRenderPass(commandBuffer);

                renderer.endFrame();
            }
        }

        vkDeviceWaitIdle(device.device());
    }

    void App::loadGameObjects()
    {
        std::shared_ptr<Model> model = Model::createModelFromFile(device, "assets/player.obj");

        auto cube = GameObject::createGameObject();

        cube.model = model;
        cube.transform.translation = {0.0f, 0.0f, 2.5f};
        cube.transform.scale = {0.5f, 0.5f, 0.5f};
        cube.transform.rotation = {90.0f, 0.0f, 0.0f};

        gameObjects.push_back(std::move(cube));
    }
}