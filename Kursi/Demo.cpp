#include "Demo.h"



Demo::Demo() {

}


Demo::~Demo() {
}



void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);

	BuildColoredTengahMeja();
	BuildColoredKakiMeja2();
	BuildColoredPlane();
	BuildColoredKakiMeja3();
	BuildColoredKakiMeja4();
	BuildColoredKakiMeja1();

	BuildColoredTengahKursi();
	BuildColoredKakiKursi1();
	BuildColoredKakiKursi2();
	BuildColoredSandaranKursi();
	BuildColoredKakiKursi3();
	BuildColoredSanggahanTanganKakiKursi3();
	BuildColoredKakiKursi4();
	BuildColoredSanggahanTanganKakiKursi4();

	InitCamera();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);

	glDeleteVertexArrays(1, &VAO3);
	glDeleteBuffers(1, &VBO3);
	glDeleteBuffers(1, &EBO3);

	glDeleteVertexArrays(1, &VAO4);
	glDeleteBuffers(1, &VBO4);
	glDeleteBuffers(1, &EBO4);


}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth/2;
	double midY = screenHeight/2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);



}

void Demo::Update(double deltaTime) {
	angle += (float) ((deltaTime * 1.5f) / 100);
	movement += (float)((3.0f * deltaTime ) / 1000);
}

void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(15, 6, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	
	DrawColoredKakiMeja1();
	DrawColoredTengahMeja();
	DrawColoredKakiMeja2();
	DrawColoredPlane();
	DrawColoredKakiMeja3();
	DrawColoredKakiMeja4();

	DrawColoredTengahKursi();
	DrawColoredKakiKursi1();
	DrawColoredKakiKursi2();
	DrawColoredSandaranKursi();
	DrawColoredKakiKursi3();
	DrawColoredSanggahanTanganKakiKursi3();
	DrawColoredKakiKursi4();
	DrawColoredSanggahanTanganKakiKursi4();
	

	glDisable(GL_DEPTH_TEST);
}

void Demo::BuildColoredKakiMeja1() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredTengahMeja() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredKakiMeja2() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("marble.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 256);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, -0.5, -50.0,  0,  0,
		 50.0, -0.5, -50.0, 50,  0,
		 50.0, -0.5,  50.0, 50, 50,
		-50.0, -0.5,  50.0,  0, 50,


	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::BuildColoredKakiMeja3() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredKakiMeja4() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::BuildColoredTengahKursi() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredKakiKursi1() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredKakiKursi2() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredSandaranKursi() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredKakiKursi3() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredSanggahanTanganKakiKursi3() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredKakiKursi4() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::BuildColoredSanggahanTanganKakiKursi4() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

//Kaki Meja 1
void Demo::DrawColoredKakiMeja1()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-2.5, 0, 1.4));

	//model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(1, 4, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//Tengah Meja
void Demo::DrawColoredTengahMeja()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 2.4, 0));

//	model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(6.2, 1, 4));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//Kaki Meja 2
void Demo::DrawColoredKakiMeja2()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-2.5, 0, -1.1));

	//model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(1, 4, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//Lantai
void Demo::DrawColoredPlane()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//kaki Meja 3
void Demo::DrawColoredKakiMeja3()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(2.5, 0, 1.4));

	//model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(1, 4, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//kaki Meja 4
void Demo::DrawColoredKakiMeja4()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(2.5, 0, -1.4));

	//model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(1, 4, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}


//Tengah Kursi
void Demo::DrawColoredTengahKursi()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 2.4, 6));

	//	model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(15, 1, 4));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//Kaki Kursi 1
void Demo::DrawColoredKakiKursi1()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-6.5, 0, 7.5));

	//model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(1, 14, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//Kaki Kursi 2
void Demo::DrawColoredKakiKursi2()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(6.5, 0, 7.5));

	//model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(1, 14, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//Sandaran Kursi
void Demo::DrawColoredSandaranKursi()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 5, 7.5));

	//	model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(15, 5, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//Kaki Kursi 3
void Demo::DrawColoredKakiKursi3()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(6.5, 0, 5));

	//model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(1, 10, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//Sanggahan Tangan Kursi 3
void Demo::DrawColoredSanggahanTanganKakiKursi3()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(6.5, 4.5, 6));

	//	model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(1, 1, 4));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//Kaki Kursi 4
void Demo::DrawColoredKakiKursi4()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-6.5, 0, 5));

	//model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(1, 10, 1));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//Sanggahan Tangan Kursi 4
void Demo::DrawColoredSanggahanTanganKakiKursi4()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-6.5, 4.5, 6));

	//	model = glm::rotate(model, angle, glm::vec3(0, 0, 0));

	model = glm::scale(model, glm::vec3(1, 1, 4));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}


void Demo::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 1.0f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}
void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}
void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}


int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Transformation: Transform Cube", 800, 600, false, false);
}