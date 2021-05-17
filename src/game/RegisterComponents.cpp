#include "../core/Coordinator.h"
#include "../core/Components.h"

void RegisterComponents(){
    //Render Components
    Coordinator::GetInstance().RegisterComponent<Drawable>();
    Coordinator::GetInstance().RegisterComponent<Image>();
    Coordinator::GetInstance().RegisterComponent<Animation>();

    //Physics Components
    Coordinator::GetInstance().RegisterComponent<Transform>();
    Coordinator::GetInstance().RegisterComponent<RigidBody>();
    Coordinator::GetInstance().RegisterComponent<Gravity>();

    //Input Components
    Coordinator::GetInstance().RegisterComponent<Input>();
    Coordinator::GetInstance().RegisterComponent<Movement>();
}
