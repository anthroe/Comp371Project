#include "Model.h"

Model::Model() {

}
Model::Model(vec3 translateVector, vec3 rotateVector, vec3 scaleVector, vec3 color) {
	this->translateVector = translateVector;
	this->rotateVector = rotateVector;
	this->scaleVector = scaleVector;
	this->color = color;
}
Model::Model(vec3 translateVector, vec3 scaleVector, vec3 color) {
	this->translateVector = translateVector;
	this->scaleVector = scaleVector;
	this->color = color;
}
Model::~Model() {

}
void Model::Draw(Shader* shader, glm::mat4 WorldMatrix) {

}
void Model::init() {

}