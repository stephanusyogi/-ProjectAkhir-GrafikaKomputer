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
	GLuint depthmapShader, shadowmapShader, cubeVBO, cubeVAO, cubeEBO, cube_texture, cube_texture2, cube_texture3, cube_texture4, cube_texture5, cube_texture6, cube_texture7, cube_texture8, cube_texture9, planeVBO, planeVAO, planeEBO, plane_texture, stexture, stexture2, depthMapFBO, depthMap;

	float angle = 0;
	float perosotan = 0.5f;
	float movement = 0;
	bool dir = true;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);

	//Build
	void BuildTexturedPlane();
	void BuildDepthMap();
	void BuildShaders();

    void BuildTextured();
    void BuildTextured2();
    void BuildTextured3();
    void BuildTextured4();
    void BuildTextured5();
    void BuildTextured6();
    void BuildTextured7();
    void BuildTextured8();


	//Draw

    void DrawColoredKakiMeja1(GLuint shader);
    void DrawColoredTengahMeja(GLuint shader);
    void DrawColoredKakiMeja2(GLuint shader);
    void DrawColoredKakiMeja3(GLuint shader);
    void DrawColoredKakiMeja4(GLuint shader);

    void DrawColoredKakiKursi1(GLuint shader);
    void DrawColoredKakiKursi2(GLuint shader);
    void DrawColoredTengahKursi(GLuint shader);
    void DrawColoredSandaranKursi(GLuint shader);
    void DrawColoredKakiKursi3(GLuint shader);
    void DrawColoredSanggahanTanganKakiKursi3(GLuint shader);
    void DrawColoredKakiKursi4(GLuint shader);
    void DrawColoredSanggahanTanganKakiKursi4(GLuint shader);

    void DrawColoredKursiKecilTengahA(GLuint shader);
    void DrawColoredKakiKursiKecilA1(GLuint shader);
    void DrawColoredKakiKursiKecilA2(GLuint shader);
    void DrawColoredKakiKursiKecilA3(GLuint shader);
    void DrawColoredKakiKursiKecilA4(GLuint shader);
    void DrawColoredSandaranKursiKecilA(GLuint shader);

    void DrawColoredKakiKasur1(GLuint shader);
    void DrawColoredKakiKasur2(GLuint shader);
    void DrawColoredKakiKasur3(GLuint shader);
    void DrawColoredKakiKasur4(GLuint shader);
    void DrawColoredSandaranKasur(GLuint shader);
    void DrawColoredSandaranPendek1(GLuint shader);
    void DrawColoredSandaranPendek2(GLuint shader);
    void DrawColoredSandaranPendek3(GLuint shader);
    void DrawColoredAlasKasur(GLuint shader);

    void DrawColoredMejaKecil(GLuint shader);
    void DrawColoredAlasKipas(GLuint shader);
    void DrawColoredTiangKipas(GLuint shader);
    void DrawColoredPorosKipas(GLuint shader);

    void DrawColoredTembokKanan(GLuint shader);
    void DrawColoredTembokBelakang(GLuint shader);
    void DrawColoredTembokKiri(GLuint shader);

    void DrawColoredJam(GLuint shader);
    void DrawColoredJarumJam1(GLuint shader);
    void DrawColoredJarumJam2(GLuint shader);

	void DrawTexturedPlane(GLuint shader);


	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void MoveVerCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};

