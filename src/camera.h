#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

class Camera {
public:
	glm::vec3 Pos;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	glm::vec3 Right;
	float Pitch;
	float Yaw;
	float MovementSpeed;
	float MouseSensitivity;
	float Fov;

	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : 
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV) {
		Pos = pos;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 getViewMatrix() {
		return glm::lookAt(Pos, Pos + Front, WorldUp);
	}

	void processKeyBroad(Camera_Movement direction, float deltaTime) {
		float Speed = deltaTime * MovementSpeed;
		if (direction == FORWARD)
			Pos += Front * Speed;
		if (direction == BACKWARD)
			Pos -= Front * Speed;
		if (direction == LEFT)
			Pos -= Right * Speed;
		if (direction == RIGHT)
			Pos += Right * Speed;
		//Pos.y = 0.0f;
	}
	
	void processMouseMovement(float xOffset, float yOffset) {
		xOffset *= MouseSensitivity;
		yOffset *= MouseSensitivity;

		Yaw += xOffset;
		Pitch += yOffset;

		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;

		updateCameraVectors();
	}

	void processMouseScroll(float yOffset) {
		Fov -= yOffset;
		if (Fov < 1.0f)
			Fov = 1.0f;
		if (Fov > 45.0f)
			Fov = 45.0f;
	}
private:
	void updateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up	  = glm::normalize(glm::cross(Right, Front));
	}
};

#endif