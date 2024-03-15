#define GLM_FORCE_PURE

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

enum class CAMERA_MODE{
    DEFAULT_PROJECTION,
    DEFAULT_ORTHOGRAPHIC,
    FREE_VIEW,
    PROJECTION_1,
    PROJECTION_2,
    PROJECTION_3
};

class MainScene : engine::Scene {
public:
    GLFWwindow* window;
    engine::Object *cube_1, *cube_2, *cube_3, *plane;
    CAMERA_MODE camera_mode = CAMERA_MODE::DEFAULT_PROJECTION;      

    MainScene (GLFWwindow* window): Scene(window) {
        this->window = window;

        glClearColor(1.f, 1.f, 0.4f, 1.f);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);

        // Accept fragment if it is closer to the camera than the former one
        glDepthFunc(GL_LEQUAL); 

        // Cull triangles which normal is not towards the camera
        // glEnable(GL_CULL_FACE);

        // Blending
        glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Associate the object instance with the GLFW window
        glfwSetWindowUserPointer(window, this);

        start();
    }

    void start() override {
        // ======================== PLANE ========================

        // LOAD PLANE SHADERS AND MODEL
        GLuint shader = LoadShaders("res/shader/Textured.vs", "res/shader/Textured.fs");
        plane = new engine::Object("../res/obj/plane.obj", "../res/bmp/plane_tugas.bmp", shader, this);

        // ======================== CUBES ========================

        // LOAD CUBE SHADERS AND MODEL I
        shader = LoadShaders("res/shader/Textured.vs", "res/shader/Textured.fs");
        cube_1 = new engine::Object("../res/obj/box.obj", "../res/bmp/box.bmp", shader, this);

        // TRANSFORM THE CUBE
        shader = LoadShaders("res/shader/Textured.vs", "res/shader/Textured.fs");
        cube_1 = new engine::Object("../res/obj/box.obj", "../res/bmp/box.bmp", shader, this);
        cube_1->transform = glm::translate(cube_1->transform, vec3(39, 5, -20));
        cube_1->transform = glm::rotate(cube_1->transform, glm::radians(45.f), vec3(0, 1, 0));
        cube_1->transform = glm::scale(cube_1->transform, vec3(19.5, 1, 9.7)); 

        // LOAD CUBE SHADERS AND MODEL II
        shader = LoadShaders("res/shader/Textured.vs", "res/shader/Textured.fs");
        cube_2 = new engine::Object("../res/obj/box.obj", "../res/bmp/box.bmp", shader, this);

        // TRANSFORM THE CUBE
        shader = LoadShaders("res/shader/Textured.vs", "res/shader/Textured.fs");
        cube_2 = new engine::Object("../res/obj/box.obj", "../res/bmp/box.bmp", shader, this);
        cube_2->transform = glm::translate(cube_2->transform, vec3(30, 2, 50));
        cube_2->transform = glm::rotate(cube_2->transform, glm::radians(360.f), vec3(0, 1, 0));
        cube_2->transform = glm::scale(cube_2->transform, vec3(10, 1, 10));  

        // LOAD CUBE SHADERS AND MODEL III
        shader = LoadShaders("res/shader/Textured.vs", "res/shader/Textured.fs");
        cube_3 = new engine::Object("../res/obj/box.obj", "../res/bmp/box.bmp", shader, this);

        // TRANSFORM THE CUBE
        shader = LoadShaders("res/shader/Textured.vs", "res/shader/Textured.fs");
        cube_3 = new engine::Object("../res/obj/box.obj", "../res/bmp/box.bmp", shader, this);
        cube_3->transform = glm::translate(cube_3->transform, vec3(-39, 2, 30));
        cube_3->transform = glm::rotate(cube_3->transform, glm::radians(360.f), vec3(0, 1, 0));
        cube_3->transform = glm::scale(cube_3->transform, vec3(19.5, 1, 9.7));
        // binding keys
        glfwSetKeyCallback(window, keyCallbackStatic);
    }

    void update() override {
        Scene::update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto up = vec3( 0, 1, 0);
        auto aspect_ratio = (float)window_width/window_height;
        switch (camera_mode) {
            case CAMERA_MODE::DEFAULT_ORTHOGRAPHIC:
                ViewMatrix = glm::lookAt(
                    vec3(0, 200, 1),
                    vec3(0, 0, 0),
                    up
                );
                ProjectionMatrix = glm::ortho<float>(-80*aspect_ratio, 80*aspect_ratio, -80, 80, -1000, 1000);
                break;
            case CAMERA_MODE::DEFAULT_PROJECTION:
                ViewMatrix = glm::lookAt(
                    vec3(0, 200, 1),
                    vec3(0, 0, 0),
                    up
                );
                ProjectionMatrix = glm::perspective<float>(glm::radians(45.f), aspect_ratio, 0.1f, 1000.0f);
                break;
            case CAMERA_MODE::PROJECTION_1:
                // TODO 4: CREATE PROJECTION FOR PROJECTION_1 (See module)
                ViewMatrix = glm::lookAt(
                glm::vec3(200, 0, 0),   
                glm::vec3(0, 0, 0),     
                up                      
                );
                ProjectionMatrix = glm::perspective<float>(glm::radians(45.f), aspect_ratio, 0.1f, 1000.0f); // Sudut pandang proyeksi kamera
                break;  
            case CAMERA_MODE::PROJECTION_2:
                // TODO 5: CREATE PROJECTION FOR PROJECTION_2 (See module)
                ViewMatrix = glm::lookAt(
                glm::vec3(200, 0, 0),   
                glm::vec3(0, 0, 0),     
                up                      
                );
                ProjectionMatrix = glm::perspective<float>(glm::radians(45.f), aspect_ratio, 0.1f, 1000.0f); // Sudut pandang proyeksi kamera
                break;
            case CAMERA_MODE::PROJECTION_3:
                // TODO 6: CREATE PROJECTION FOR PROJECTION_3 (See module)
                ViewMatrix = glm::lookAt(
                glm::vec3(200, 0, 0),   
                glm::vec3(0, 0, 0),     
                up                      
                );
                ProjectionMatrix = glm::perspective<float>(glm::radians(45.f), aspect_ratio, 0.1f, 1000.0f); // Sudut pandang proyeksi kamera
                break;
            case CAMERA_MODE::FREE_VIEW:
                // Don't touch
                computeMatricesFromInputs(window);
                ViewMatrix = getViewMatrix();
                ProjectionMatrix = getProjectionMatrix();
                break;
        }

        
        cube_1->render_with_projection();
        cube_2->render_with_projection();
        cube_3->render_with_projection();
        plane->render_with_projection();
    }

private:
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            std::cout << key << std::endl;
            switch (key) {
            case GLFW_KEY_1:
                camera_mode = CAMERA_MODE::DEFAULT_ORTHOGRAPHIC;
                break;
            case GLFW_KEY_2:
                camera_mode = CAMERA_MODE::DEFAULT_PROJECTION;
                break;
            case GLFW_KEY_3:
                camera_mode = CAMERA_MODE::PROJECTION_1;
                break;
            case GLFW_KEY_4:
                camera_mode = CAMERA_MODE::PROJECTION_2;
                break;
            case GLFW_KEY_5:
                camera_mode = CAMERA_MODE::PROJECTION_3;
                break;
            case GLFW_KEY_0:
                camera_mode = CAMERA_MODE::FREE_VIEW;
                break;
            }
        }
    }

    static void keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods) {
        MainScene* instance = static_cast<MainScene*>(glfwGetWindowUserPointer(window));
        instance->key_callback(window, key, scancode, action, mods);
    }
    

};