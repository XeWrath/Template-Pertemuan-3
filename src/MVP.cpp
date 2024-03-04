#define GLM_FORCE_PURE

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <common/controls.hpp>
#include <common/shader.hpp>
#include <engine/scene.hpp>
#include <engine/object.hpp>

class MainScene : engine::Scene {
public:
    GLFWwindow* window;
    engine::Object *cube, *plane;

    glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;       

    MainScene (GLFWwindow* window): Scene(window) {
        this->window = window;

        glClearColor(1.f, 1.f, 0.4f, 1.f);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);

        // Accept fragment if it is closer to the camera than the former one
        glDepthFunc(GL_LESS); 

        // Cull triangles which normal is not towards the camera
        glEnable(GL_CULL_FACE);

        // Blending
        glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        start();
    }

    void start() override {
        GLuint shader = LoadShaders("res/shader/basic.vs", "res/shader/basic.fs");

        cube = new engine::Object("res/obj/box.obj", "res/bmp/box.bmp", shader);

        cube->transform = glm::translate(cube->transform, vec3(0, 0, 5));
        cube->transform = glm::scale(cube->transform, vec3(0.5, 0.5, 0.5));
        cube->transform = glm::rotate(cube->transform, glm::radians(45.f), vec3(0, 1, 0));

        shader = LoadShaders("res/shader/plane.vs", "res/shader/plane.fs");

        plane = new engine::Object("res/obj/plane.obj", "res/bmp/plane.bmp", shader);

        plane->transform = glm::translate(plane->transform, vec3(0, -1, 0));

        ProjectionMatrix = glm::perspective(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 1000.0f);

        auto up = vec3( 0, 1, 0);
        ViewMatrix = glm::lookAt(
								vec3(0, 2, 0),           // Camera postion
								vec3(0, 0, 5), // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
                        );

        plane->ViewMatrix = ViewMatrix;
        plane->ProjectionMatrix = ProjectionMatrix;

        cube->ViewMatrix = ViewMatrix;
        cube->ProjectionMatrix = ProjectionMatrix;
    }

    void update() override {
        Scene::update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        computeMatricesFromInputs(window);
        
        /* do every frame here*/
        plane->render();
        cube->render();
    }
};