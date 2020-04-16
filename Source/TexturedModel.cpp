#include <TexturedModel.h>
using namespace glm;


TexturedModel::TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture, string name) :
	Model(position, rotation, scaling, color, texture, name)
{
	init();
}
TexturedModel::TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture) :
	Model(position, rotation, scaling, color, texture)
{
	init();
}
TexturedModel::TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color) :
	Model(position, rotation, scaling, color)
{
	init();
}
TexturedModel::TexturedModel(vec3 position, vec3 scaling, vec3 color) :
	Model(position, scaling, color)
{
	init();
}
TexturedModel::TexturedModel()
{
	init();
}
TexturedModel::~TexturedModel()
{
	glDeleteBuffers(1, &mEBO);
	glDeleteVertexArrays(1, &mVAO);
}

void TexturedModel::draw(Shader* shader, GLuint drawingPrimitive)
{
	shader->use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shader->setVec3("objectColor", color);

	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mEBO);

	mat4 worldMatrix = translate(mat4(1.0f), position);
	worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 0.0f, 1.0f));
	worldMatrix = worldMatrix * scale(mat4(1.0f), scaling);

	shader->setMat4("worldMatrix", worldMatrix);
	glDrawElements(drawingPrimitive, numOfVertices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void TexturedModel::init() {
	setupModelEBO("../Resources/Assets/Models/" + name + ".obj");
}
GLuint TexturedModel::setupModelVBO(std::string path, int& vertexCount) {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;

	//read the vertex data from the model's OBJ file
	OBJloader::loadOBJ(path.c_str(), vertices, normals, UVs);

	GLuint mVAO;
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO); //Becomes active mVAO
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).

	//Vertex VBO setup
	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Normals VBO setup
	GLuint normals_VBO;
	glGenBuffers(1, &normals_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	//UVs VBO setup
	GLuint uvs_VBO;
	glGenBuffers(1, &uvs_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, uvs_VBO);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	// Unbind mVAO (it's always a good thing to unbind any buffer/array to prevent strange bugs, as we are using multiple VAOs)
	vertexCount = vertices.size();
	return mVAO;
}
void TexturedModel::setupModelEBO(std::string path) {
	std::vector<int> vertexIndices;
	//The contiguous sets of three indices of vertices, normals and UVs, used to make a triangle
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;

	//read the vertices from the cube.obj file
	//We won't be needing the normals or UVs for this program
	OBJloaderV2::loadOBJ2(path.c_str(), vertexIndices, vertices, normals, UVs);
	// VAO setup
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO); //Becomes active mVAO
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).

	//Vertex VBO setup
	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Normals VBO setup
	GLuint normals_VBO;
	glGenBuffers(1, &normals_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	//UVs VBO setup
	GLuint uvs_VBO;
	glGenBuffers(1, &uvs_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, uvs_VBO);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);

	//mEBO setup
	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(int), &vertexIndices.front(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	// Unbind mVAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the mEBO, keep it bound to this mVAO
	numOfVertices = vertexIndices.size();
}