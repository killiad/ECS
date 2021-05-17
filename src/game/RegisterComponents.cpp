#include "../core/Coordinator.h"
#include "../core/Components.h"

void RegisterComponents(){
    //Render components
    Coordinator::GetInstance().RegisterComponent<Drawable>();
    Coordinator::GetInstance().RegisterComponent<Image>();
    Coordinator::GetInstance().RegisterComponent<Animation>();

    //Physics Components
    Coordinator::GetInstance().RegisterComponent<Transform>();
    Coordinator::GetInstance().RegisterComponent<RigidBody>();
    Coordinator::GetInstance().RegisterComponent<Gravity>();
}
