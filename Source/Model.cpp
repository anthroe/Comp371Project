<<<<<<< Updated upstream
#include "Model.h"

Model::Model() {

}

Model::Model(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture, string name)
{
	this->position = position;
	this->rotation = rotation;
	this->scaling = scaling;
	this->color = color;
	this->texture = texture;
	this->name = name;
}
Model::Model(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture) {
	this->position = position;
	this->rotation = rotation;
	this->scaling = scaling;
	this->color = color;
	this->texture = texture;
}
Model::Model(vec3 position, vec3 rotation, vec3 scaling, vec3 color) {
	this->position = position;
	this->rotation = rotation;
	this->scaling = scaling;
	this->color = color;
}
Model::Model(vec3 position, vec3 scaling, vec3 color) {
	this->position = position;
	this->scaling = scaling;
	this->color = color;
}
Model::~Model() {

}
void Model::draw(Shader* shader, GLuint drawingPrimitive)
{
}
void Model::draw(Shader* shader, glm::mat4 WorldMatrix) {

}
void Model::draw(Shader* shader) {

}
void Model::init() {

}
=======
#include "Model.h"

Model::Model() {

}
Model::Model(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture, string name) {
	this->position = position;
	this->rotation = rotation;
	this->scaling = scaling;
	this->color = color;
	this->texture = texture;
	this->name = name;
}
Model::Model(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture) {
	this->position = position;
	this->rotation = rotation;
	this->scaling = scaling;
	this->color = color;
	this->texture = texture;
}
Model::Model(vec3 position, vec3 rotation, vec3 scaling, vec3 color) {
	this->position = position;
	this->rotation = rotation;
	this->scaling = scaling;
	this->color = color;
}
Model::Model(vec3 position, vec3 scaling, vec3 color) {
	this->position = position;
	this->scaling = scaling;
	this->color = color;
}
Model::~Model() {

}
void Model::draw(Shader* shader, glm::mat4 WorldMatrix, GLuint drawingPrimitive)
{
}
void Model::draw(Shader* shader, glm::mat4 WorldMatrix) {

}
void Model::draw(Shader* shader, GLuint drawingPrimitive)
{

}

void Model::draw(Shader* shader) {

}
void Model::init() {

}

>>>>>>> Stashed changes
