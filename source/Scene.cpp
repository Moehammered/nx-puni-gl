#include "Scene.h"
#include <stdio.h>

puni::Scene::Scene() { }

void puni::Scene::cleanup() 
{ 
    printf("Cleaning up base Scene.\n\n");
}

puni::Scene::~Scene()
{
    cleanup();
}