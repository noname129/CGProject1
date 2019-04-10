#include "stdafx.h"

namespace Glory {

class GObject {
private:
std:vector<GObject> childs;  
  
public:
  GObject *parent;
  GScene &scene;
  GTransform transform;
  
  GObject(GScene scene);
  ~GObject();
  
  void AddChild(const GObject* obj);
};

}