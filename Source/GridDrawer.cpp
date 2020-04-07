
#include <GridDrawer.h>

GridDrawer::GridDrawer() {
	lineModel = new LineModel();

}
void GridDrawer::drawGrid(Shader* shader) {
    //draw the z axis 100 lines
    mat4 groundWorldMatrix;
    for (int i = 1; i <= 100; i++)
    {
        float z = 1.0f * i;
        groundWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, z - 50.0f));
        lineModel->Draw(shader, groundWorldMatrix);
    }

    //draw the x axis100 lines
    for (int i = 1; i <= 100; i++)
    {
        float x = 1.0f * i;
        groundWorldMatrix = translate(mat4(1.0f), vec3(x - 50.0f, 0.0f, 0.0f)) * rotate(mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        lineModel->Draw(shader, groundWorldMatrix);
    }

}

void GridDrawer::draw(Shader* shader, mat4 worldRotationMatrix) {
    /* glBindTexture(GL_TEXTURE_2D, snowTextureID);
    textureShader->setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
    mat4 pillarWorldMatrix;
    snowManDrawer->drawSnow(textureShader);*/
    // Draw ground

    mat4 groundWorldMatrix;

    shader->use();
    shader->setVec3("objectColor", vec3(0.0f, 1.0f, 0.0f));
    shader->setMat4("globalRotationMatrix", worldRotationMatrix);

    drawGrid(shader);
    //drawing the axis
    //x is blue
    shader->setVec3("objectColor", vec3(0.0f, 0.0f, 1.0f));
    groundWorldMatrix = scale(mat4(1.0f), vec3(0.05f)) * translate(mat4(1.0f), vec3(50.0f, 0.01f, 0.0f));
    lineModel->Draw(shader, groundWorldMatrix);

    //z is red
    shader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
    groundWorldMatrix = scale(mat4(1.0f), vec3(0.05f)) * translate(mat4(1.0f), vec3(0.0f, 0.01f, 50.0f)) * rotate(mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    lineModel->Draw(shader, groundWorldMatrix);

    //y is white
    shader->setVec3("objectColor", vec3(1.0f, 1.0f, 1.0f));
    groundWorldMatrix = scale(mat4(1.0f), vec3(0.05f)) * translate(mat4(1.0f), vec3(0.0f, 50.01f, 0.0f)) * rotate(mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    lineModel->Draw(shader, groundWorldMatrix);
}