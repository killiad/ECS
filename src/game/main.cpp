#include "../core/Coordinator.h"

void RegisterComponents();
void RunGameLoop();

int main(){

    Coordinator::GetInstance().Init();

    RegisterComponents();
    RunGameLoop();

    return 0;
}
