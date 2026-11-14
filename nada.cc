//
// ETSI de Telecomunicación. Universidad de Málaga
// Titulación: Grado en Ingeniería Telemática
// Asignatura: Redes y Servicios de Telecomunicación 3
// Profesora: María Carmen España Boquera
//
// Modelo de subred
//

#include <string.h>
#include <omnetpp.h>
#include "paqueteIP_m.h"

using namespace omnetpp;
/**
 * Clase para no dejar puertos de los routers sin conectar
 */

class nada : public cSimpleModule
{
private:


  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

};

Define_Module(nada);


void nada::initialize()
{


}

void nada::handleMessage(cMessage *msg)
{

delete msg;
}









