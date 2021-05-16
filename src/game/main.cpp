#include "../core/Coordinator.h"

void RegisterComponents();
std::vector<std::shared_ptr<System> > RegisterSystems();
void RunGameLoop(std::vector<std::shared_ptr<System> > systems);

int main(){

    Coordinator::GetInstance().Init();

    RegisterComponents();
    auto systems = RegisterSystems();
    RunGameLoop(systems);

    return 0;
}
