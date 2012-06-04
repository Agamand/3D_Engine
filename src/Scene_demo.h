#ifndef SCENEDEMO_H
#define SCENEDEMO_H

#include "Object\Object.h"
Object* bouteille(glm::vec3 pos = glm::vec3());
Object* bague(glm::vec3 pos = glm::vec3());
Object* BagueB(glm::vec3 pos = glm::vec3());
Object* chaise(glm::vec3 pos = glm::vec3());
Object* chaise2(glm::vec3 pos = glm::vec3());
Object* table(glm::vec3 pos = glm::vec3());
Object* enstabcha(glm::vec3 pos = glm::vec3());
Object* banquette(glm::vec3 pos = glm::vec3());
Object* ensbanqtab(glm::vec3 pos = glm::vec3());
Object* sol();
Object* mur();
Object* plafond();
Object* mur_porte();
Object* mur_fond();
Object* porte(glm::vec3 pos = glm::vec3());
Object* bar(glm::vec3 pos = glm::vec3());
Object* ampoule(glm::vec3 pos = glm::vec3());
Object* lustre(glm::vec3 pos = glm::vec3());
/*
Object* robinet();
Object* cigarette();

Object* futBiere();

Object* scene();



Object* ens_evier();
Object* verre1();
Object* verre2();
Object* verre3();
Object* verre4();
Object* batte_baseball();
Object* batte_cloute();
Object* clou();
Object* parpaing();
Object* tas_de_parpaing();
Object* baril();
Object* baril_cigarette();
Object* cendrier();
Object* cendrier_cigar();

*/
void scene();

#endif 