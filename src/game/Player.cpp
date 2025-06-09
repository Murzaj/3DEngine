#include "game/Player.hpp"
#include <glm/common.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <iostream>


#include "InputMap.hpp"     
#include "EngineManager.hpp" 
#include "Shape3D.hpp"       



Player::Player(Shape3D* playerModel, double size, glm::vec3 startpos)
    :size(size), playerModel(playerModel), pos(startpos) {
    if (auto transformableModel = dynamic_cast<TransformableObject*>(playerModel)) {
        transformableModel->scale(glm::vec3(size));
    }
    else {
        std::cerr << "Model gracza nie jest TransformableObject" << std::endl;
    }
}


void Player::draw(const glm::mat4& view) {
    auto positioned = glm::translate(view, pos);
    if (playerModel) {
        playerModel->draw(positioned); 
    }
}

void Player::update(float delta, const InputMap& input, EngineManager* manager) {
    if (!manager) return; 

    if (dead) {
        manager->stop();
        return;
    }
    glm::vec2 motion = input.getMouseDelta(); 
    pos.x += motion.x * delta / 200.0f; 
    pos.z += motion.y * delta / 200.0f; 

    std::cout << "Poz: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
    pos = glm::clamp(pos, glm::vec3(-5.0f), glm::vec3(5.0f));
   

}


double Player::getSize() const {
    return size;
}
glm::vec3 Player::getPos() const {
    return pos;
}

void Player::hit() {
    std::cout << "Trafiony!" << std::endl;
    dead = true;
}