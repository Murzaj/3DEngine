#include <glm/glm.hpp>
#include <unordered_map>


struct MouseButtons {
  bool left;
  bool right;
  bool middle;
};


class InputMap {
public:
  bool isKeyDown(unsigned char key) const;
  bool isKeyJustPressed(unsigned char key) const;
  glm::vec2 getMouseMotion() const;
  int getWheelDirection() const;

 // setters - for engine to handle 
  void setKeyDown(unsigned char key);
  void setKeyUp(unsigned char key);
  void setLeftClickDown();
  void setLeftClickUp();
  void setRightClickDown();
  void setRightClickUp();
  void setMouseMotion(float x, float y);
  void setWheelDirection(int direction);
  void resetTemporary();

protected: 
  std::unordered_map<unsigned char, bool> pressedKeys;
  std::unordered_map<unsigned char, bool> prevFrameKeys;
  MouseButtons buttons;
  glm::vec2 mouseMotion;
  int wheelDirection;
};
