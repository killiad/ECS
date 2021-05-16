#include "../core/Coordinator.h"
#include "../core/Components.h"

void RegisterComponents(){
    Coordinator::GetInstance().RegisterComponent<Transform>();
    Coordinator::GetInstance().RegisterComponent<RigidBody>();
    Coordinator::GetInstance().RegisterComponent<Gravity>();
    Coordinator::GetInstance().RegisterComponent<Drawable>();
}
