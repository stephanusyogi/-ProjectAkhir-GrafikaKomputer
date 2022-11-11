#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint shaderProgram, 
		VBO, VAO, EBO, texture, 
		VBO2, VAO2, EBO2, texture2, 
		VBO3, VAO3, EBO3, texture3,
		VBO4, VAO4, EBO4, texture4,
		VBO5, VAO5, EBO5, texture5
		;
	float angle = 10;
	float movement = 0;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	void BuildColoredKakiMeja1();
	void BuildColoredTengahMeja();
	void BuildColoredKakiMeja2();
	void BuildColoredKakiMeja3();
	void BuildColoredKakiMeja4();

	void BuildColoredTengahKursi();
	void BuildColoredKakiKursi1();
	void BuildColoredKakiKursi2();
	void BuildColoredKakiKursi3();
	void BuildColoredSanggahanTanganKakiKursi3();
	void BuildColoredSandaranKursi();
	void BuildColoredKakiKursi4();
	void BuildColoredSanggahanTanganKakiKursi4();
	
	void BuildColoredPlane();

	void DrawColoredKakiMeja1();
	void DrawColoredTengahMeja();
	void DrawColoredKakiMeja2();
	void DrawColoredKakiMeja3();
	void DrawColoredKakiMeja4();

	void DrawColoredKakiKursi1();
	void DrawColoredKakiKursi2();
	void DrawColoredTengahKursi();
	void DrawColoredSandaranKursi();
	void DrawColoredKakiKursi3();
	void DrawColoredSanggahanTanganKakiKursi3();
	void DrawColoredKakiKursi4();
	void DrawColoredSanggahanTanganKakiKursi4();
	
	void DrawColoredPlane();

	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};

