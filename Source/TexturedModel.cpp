
#include <TexturedModel.h>
using namespace glm;
TexturedModel::TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture, GLenum drawingPrimitive) :
	Model(position, rotation, scaling, color, texture, drawingPrimitive)
{

}
TexturedModel::TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture) :
	Model(position, rotation, scaling, color, texture)
{

}
TexturedModel::TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color) :
	Model(position, rotation, scaling, color)
{

}
TexturedModel::TexturedModel(vec3 position, vec3 scaling, vec3 color) :
	Model(position, scaling, color)
{

}
TexturedModel::TexturedModel()
{
}
TexturedModel::~TexturedModel()
{
	glDeleteVertexArrays(1, &mVAO);
}

void TexturedModel::draw(Shader* shader)
{
	shader->use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shader->setVec3("objectColor", color);

	glBindVertexArray(mVAO);

	mat4 worldMatrix = translate(mat4(1.0f), position);
	worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	worldMatrix = worldMatrix * rotate(mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	worldMatrix = worldMatrix * scale(mat4(1.0f), scaling);

	shader->setMat4("worldMatrix", worldMatrix);
	glDrawElements(drawingPrimitive, numOfVertices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void TexturedModel::setVAO(GLuint VAO, int verticesCount) {
	mVAO = VAO;
	numOfVertices = verticesCount;
}