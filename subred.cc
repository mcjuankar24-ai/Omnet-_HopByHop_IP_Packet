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
 * Clase que simula el comportamiento de una subred
 */

class subred : public cSimpleModule
{
private:
  int indice;//Índice del vector de subredes
  int miPrefijo; //Prefijo de la rubred
  int numSubredes;//Número de subredes
  int prefijosSubredes[10];//Prefijos de las subredes ordenados por su índice

//Variables relativas a la generación de paquetes
  bool subredPreparada; //La subred puede comenzar a generar paquetes
  double tiempoMedioEntrePaquetes;
  int tamanoMinDatos;
  int tamanoMaxDatos;
  int tamanoCabecera;
  int traficoPrioritario;

  //Cola de almacenamiento de paquetes pendientes de enviar (no tiene límite de tamaño)
  cQueue cola;

  //Vectores y variables de resultados
   cOutVector retardoTotal[10];//Retardo total sufrido por el paquete, se calcula desde el origen
   cOutVector retardoTotalP[10];//Retardo total de paquetes prioritarios (tipo de servicio = 1)

  bool modoPrueba;
  bool modoTrafico;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();


    virtual int obtenerIndice(int prefijo);
    virtual const char* obtenerNombre(int indice);
    virtual const char* obtenerNombreP(int indice);

    virtual void enviarPaquete(paqueteIP *pk);
    virtual void enviarPaquetePrueba(int origen, int destino, int servicio);
    virtual void procesarAutomensajePuerto(cMessage *msg);
    virtual void procesarAutomensajeGeneradorPaquetes(cMessage *msg);

    virtual void obtenerResultados(paqueteIP *pk);
};


Define_Module(subred);



int subred::obtenerIndice(int prefijo)
{

    //Obtiene el índice del vector de subredes para el prefijo indicado

    int indice = 0;
    while (prefijosSubredes[indice]!= prefijo)
    {
        indice++;
    };
    return indice;


}
///////////////
const char* subred::obtenerNombre(int indice)

{
    const char* nombre;
    int prefijo = prefijosSubredes[indice];

    switch (prefijo){
         case 160:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred160Hasta160";
                     break;
             case 161: nombre = "RetardoDeSubred160Hasta161";
                      break;
             case 162: nombre = "RetardoDeSubred160Hasta162";
                      break;
             case 163: nombre = "RetardoDeSubred160Hasta163";
                      break;
             case 164: nombre = "RetardoDeSubred160Hasta164";
                      break;
             case 165: nombre = "RetardoDeSubred160Hasta165";
                       break;
             case 166: nombre = "RetardoDeSubred160Hasta166";
                       break;
              }
             break;
         case 161:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred161Hasta160";
                     break;
             case 161: nombre = "RetardoDeSubred161Hasta161";
                      break;
             case 162: nombre = "RetardoDeSubred161Hasta162";
                      break;
             case 163: nombre = "RetardoDeSubred161Hasta163";
                      break;
             case 164: nombre = "RetardoDeSubred161Hasta164";
                      break;
             case 165: nombre = "RetardoDeSubred161Hasta165";
                       break;
             case 166: nombre = "RetardoDeSubred161Hasta166";
                       break;
              }
             break;
         case 162:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred162Hasta160";
                        break;
             case 161: nombre = "RetardoDeSubred162Hasta161";
                        break;
             case 162: nombre = "RetardoDeSubred162Hasta162";
                        break;
             case 163: nombre = "RetardoDeSubred162Hasta163";
                        break;
             case 164: nombre = "RetardoDeSubred162Hasta164";
                        break;
             case 165: nombre = "RetardoDeSubred162Hasta165";
                        break;
             case 166: nombre = "RetardoDeSubred162Hasta166";
                       break;
                         }
             break;
         case 163:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred163Hasta160";
                       break;
             case 161: nombre = "RetardoDeSubred163Hasta161";
                       break;
             case 162: nombre = "RetardoDeSubred163Hasta162";
                       break;
             case 163: nombre = "RetardoDeSubred163Hasta163";
                       break;
             case 164: nombre = "RetardoDeSubred163Hasta164";
                       break;
             case 165: nombre = "RetardoDeSubred163Hasta165";
                       break;
             case 166: nombre = "RetardoDeSubred163Hasta166";
                       break;
                         }
             break;
         case 164:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred164Hasta160";
                     break;
             case 161: nombre = "RetardoDeSubred164Hasta161";
                      break;
             case 162: nombre = "RetardoDeSubred164Hasta162";
                      break;
             case 163: nombre = "RetardoDeSubred164Hasta163";
                      break;
             case 164: nombre = "RetardoDeSubred164Hasta164";
                      break;
             case 165: nombre = "RetardoDeSubred164Hasta165";
                       break;
             case 166: nombre = "RetardoDeSubred164Hasta166";
                       break;
              }
             break;
         case 165:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred165Hasta160";
                     break;
             case 161: nombre = "RetardoDeSubred165Hasta161";
                      break;
             case 162: nombre = "RetardoDeSubred165Hasta162";
                      break;
             case 163: nombre = "RetardoDeSubred165Hasta163";
                      break;
             case 164: nombre = "RetardoDeSubred165Hasta164";
                      break;
             case 165: nombre = "RetardoDeSubred165Hasta165";
                       break;
             case 166: nombre = "RetardoDeSubred165Hasta166";
                       break;
              }
             break;
          case 166:
                 switch (miPrefijo){
                 case 160: nombre = "RetardoDeSubred166Hasta160";
                         break;
                 case 161: nombre = "RetardoDeSubred166Hasta161";
                          break;
                 case 162: nombre = "RetardoDeSubred166asta162";
                          break;
                 case 163: nombre = "RetardoDeSubred166Hasta163";
                          break;
                 case 164: nombre = "RetardoDeSubred166Hasta164";
                          break;
                 case 165: nombre = "RetardoDeSubred166Hasta165";
                           break;
                 case 166: nombre = "RetardoDeSubred166Hasta166";
                           break;
                  }
             break;
     };
    return  nombre;


}
///////////////
const char* subred::obtenerNombreP(int indice)

{
    const char* nombre;
    int prefijo = prefijosSubredes[indice];

    switch (prefijo){
         case 160:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred160Hasta160P";
                     break;
             case 161: nombre = "RetardoDeSubred160Hasta161P";
                      break;
             case 162: nombre = "RetardoDeSubred160Hasta162P";
                      break;
             case 163: nombre = "RetardoDeSubred160Hasta163P";
                      break;
             case 164: nombre = "RetardoDeSubred160Hasta164P";
                      break;
             case 165: nombre = "RetardoDeSubred160Hasta165P";
                       break;
             case 166: nombre = "RetardoDeSubred160Hasta166P";
                       break;
              }
             break;
         case 161:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred161Hasta160P";
                     break;
             case 161: nombre = "RetardoDeSubred161Hasta161P";
                      break;
             case 162: nombre = "RetardoDeSubred161Hasta162P";
                      break;
             case 163: nombre = "RetardoDeSubred161Hasta163P";
                      break;
             case 164: nombre = "RetardoDeSubred161Hasta164P";
                      break;
             case 165: nombre = "RetardoDeSubred161Hasta165P";
                       break;
             case 166: nombre = "RetardoDeSubred161Hasta166P";
                       break;
              }
             break;
         case 162:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred162Hasta160P";
                        break;
             case 161: nombre = "RetardoDeSubred162Hasta161P";
                        break;
             case 162: nombre = "RetardoDeSubred162Hasta162P";
                        break;
             case 163: nombre = "RetardoDeSubred162Hasta163P";
                        break;
             case 164: nombre = "RetardoDeSubred162Hasta164P";
                        break;
             case 165: nombre = "RetardoDeSubred162Hasta165P";
                        break;
             case 166: nombre = "RetardoDeSubred162Hasta166P";
                       break;
                         }
             break;
         case 163:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred163Hasta160P";
                       break;
             case 161: nombre = "RetardoDeSubred163Hasta161P";
                       break;
             case 162: nombre = "RetardoDeSubred163Hasta162P";
                       break;
             case 163: nombre = "RetardoDeSubred163Hasta163P";
                       break;
             case 164: nombre = "RetardoDeSubred163Hasta164P";
                       break;
             case 165: nombre = "RetardoDeSubred163Hasta165P";
                       break;
             case 166: nombre = "RetardoDeSubred163Hasta166P";
                       break;
                         }
             break;
         case 164:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred164Hasta160P";
                     break;
             case 161: nombre = "RetardoDeSubred164Hasta161P";
                      break;
             case 162: nombre = "RetardoDeSubred164Hasta162P";
                      break;
             case 163: nombre = "RetardoDeSubred164Hasta163P";
                      break;
             case 164: nombre = "RetardoDeSubred164Hasta164P";
                      break;
             case 165: nombre = "RetardoDeSubred164Hasta165P";
                       break;
             case 166: nombre = "RetardoDeSubred164Hasta166P";
                       break;
              }
             break;
         case 165:
             switch (miPrefijo){
             case 160: nombre = "RetardoDeSubred165Hasta160P";
                     break;
             case 161: nombre = "RetardoDeSubred165Hasta161P";
                      break;
             case 162: nombre = "RetardoDeSubred165Hasta162P";
                      break;
             case 163: nombre = "RetardoDeSubred165Hasta163P";
                      break;
             case 164: nombre = "RetardoDeSubred165Hasta164P";
                      break;
             case 165: nombre = "RetardoDeSubred165Hasta165P";
                       break;
             case 166: nombre = "RetardoDeSubred165Hasta166P";
                       break;
              }
             break;
          case 166:
                 switch (miPrefijo){
                 case 160: nombre = "RetardoDeSubred166Hasta16P";
                         break;
                 case 161: nombre = "RetardoDeSubred166Hasta161P";
                          break;
                 case 162: nombre = "RetardoDeSubred166asta162P";
                          break;
                 case 163: nombre = "RetardoDeSubred166Hasta163P";
                          break;
                 case 164: nombre = "RetardoDeSubred166Hasta164P";
                          break;
                 case 165: nombre = "RetardoDeSubred166Hasta165P";
                           break;
                 case 166: nombre = "RetardoDeSubred166Hasta166P";
                           break;
                  }
             break;
     };
    return  nombre;


}
///////////////


/////////////////////////////////////////////
//Función para enviar un paquete por el puerto indicado
//Si el canal está ocupado, el paquete se deposita en una cola

void subred::enviarPaquete(paqueteIP *pk){

//Antes de enviar el paquete, comprueba si el canal está ocupado
cChannel *canal = gate("puerto$o")->getTransmissionChannel();
simtime_t termina = canal->getTransmissionFinishTime();
if (termina <= simTime()){//Canal libre
    //Enviar el paquete
    send(pk, "puerto$o");
   //ev << "Canal libre \n";

}else{//Canal ocupado
    //Depositar paquete en una cola
    //EV << "Canal ocupado \n";
    cola.insert(pk);
    EV << "Número de paquetes en cola " << cola.length()<< "\n";
    //Programar la lectura para el momento en que el canal quede libre (mediante un automensaje)
    cMessage *canalLibre = new cMessage("canalLibre");
    scheduleAt(termina, canalLibre);
}
};

//////////////////////
//Función para enviar un solo paquete en modo Prueba
void subred::enviarPaquetePrueba(int origen, int destino, int servicio){

     double retardo = 80; //Espera a que las tablas estén cumplimentadas

    //Creación del paquete base con su cabecera
        paqueteIP *pk = new paqueteIP("paqueteIP");
        pk ->setByteLength(tamanoCabecera);

    //Establecer la dirección origen del paquete
        pk ->setSrcAddr(origen);
    //Establecer la dirección destino del paquete
        pk ->setDestAddr(destino);
    //Indicar el tipo de paquete (DATOS)
        pk ->setTipoPaquete(0);

        //Añadir la marca temporal
        pk->setTiempo(simTime().dbl()+ retardo);

        //Indicar el tipo de servicio requerido

        pk->setTipoServicio(servicio);


       //Establecer el tamaño de la carga útil
       //Ttamaño medio
       int tamano = (tamanoMinDatos + tamanoMaxDatos)/2;
       tamano = tamano*8; //Paso de octetos a bits

       //Creación del cuerpo/carga útil del paquete
       cPacket *cuerpo = new cPacket("datos", 0, tamano);
       pk->encapsulate(cuerpo);
       tamano= pk->getByteLength();

      //Envía el paquete
       sendDelayed(pk, retardo, "puerto$o");

       EV << "Tamaño del paquete: " << tamano << " (octetos) \n";
       EV << "_________________________\n";
};

/////////////////////////////////////////////////////////////////////////////////
//Procesamiento de un automensaje indicando que el canal ha quedado libre
void subred::procesarAutomensajePuerto(cMessage *msg){
//Antes de enviar el paquete, comprueba si realmente está libre
     cChannel *canal = gate("puerto$o")->getTransmissionChannel();
     simtime_t termina = canal->getTransmissionFinishTime();
     if (termina <= simTime()){//Canal libre
     //Enviar el paquete
         cObject *obj = cola.pop();
        paqueteIP *pk = check_and_cast<paqueteIP *>(obj);
         send(pk, "puerto$o");
     }else{//Canal ocupado
     //Programar la lectura para el momento en que el canal quede libre (mediante un automensaje)
         cMessage *canalLibre = new cMessage("canalLibre");
         scheduleAt(termina, canalLibre);
     }
     //Una vez procesado, se borra el automensaje
     delete msg;
};

/////////////////////////////////////////////////////////////////////////
//Procesamiento de un automensaje para generar un nuevo paquete de datos
void subred::procesarAutomensajeGeneradorPaquetes(cMessage *msg)
{

    // Sólo se generan paquetes si la subred está preparada
    if (subredPreparada){
        //EV << "Paquete generado desde la subred "<< miPrefijo;
        //Debe reiniciarse el temporizador, para que se genere el próximo paquete
           simtime_t_cref tTemporizador = msg->getArrivalTime();
           double Tempo = tTemporizador.dbl(); // Conversion de tipos
           delete msg;
           cMessage *temporizador = new cMessage("generadorDatos");
           scheduleAt(Tempo + exponential (tiempoMedioEntrePaquetes, indice), temporizador);


        //Creación del paquete base con la cabecera
            paqueteIP *pk = new paqueteIP("paqueteIP");
            pk ->setByteLength(tamanoCabecera);

        //Establecer la dirección origen del paquete
            //Prefijo de red: el de la subred : miPrefijo
            //Estación: Variable aleatoria con distribución uniforme
            int estacion = uniform(1,255, indice + numSubredes);
            int estacionEmisora = estacion + miPrefijo*256;
            //Cumplimentar el campo de cabecera
            pk ->setSrcAddr(estacionEmisora);

        //Establecer la dirección destino del paquete
            //Prefijo de red variable aleatoria
            int indicePrefijo = uniform(1,numSubredes, indice + numSubredes*2);

    if ((prefijosSubredes[indicePrefijo] == miPrefijo) && (obtenerIndice(miPrefijo) != 0)){
                indicePrefijo = 0;
            };
            //Estación: variable aleatoria con distribución uniforme
            estacion = uniform(1,255, indice + numSubredes*3);
            int estacionDestino = estacion + prefijosSubredes[indicePrefijo]*256;
            pk ->setDestAddr(estacionDestino);

          //Indicar el tipo de paquete (DATOS)
          pk ->setTipoPaquete(0);

          //Añadir la marca temporal
          pk->setTiempo(simTime().dbl());

         //Indicar el tipo de servicio requerido
                   if (traficoPrioritario == 0) {//Solamente tráfico no prioritario
                       pk->setTipoServicio(0);
                   } else{
                   if (traficoPrioritario == 100) {//Solamente tráfico  prioritario
                       pk->setTipoServicio(1);
                   } else{ //Combinación de tipos de tráfico
                       int TS;
                       TS = uniform(0,100, indice + numSubredes*5);
                       if (TS < traficoPrioritario){
                           pk->setTipoServicio(1);
                       }
                       else{
                           pk->setTipoServicio(0);
                       };
                    };
                   };

         //Establecer el tamaño del cuerpo del paquete
         //Obtenido estadísticamente mediante una distribución uniforme (en octetos)
         int tamano = uniform(tamanoMinDatos, tamanoMaxDatos+1, indice + numSubredes*4);
         tamano = tamano*8; //Paso de octetos a bits
         //Creación del tamaño de la carga útil del paquete
         cPacket *cuerpo = new cPacket("datos", 0, tamano);
         pk->encapsulate(cuerpo);

         enviarPaquete(pk);
         EV << "Paquete enviado desde la subred "<< miPrefijo << " por "<< estacionEmisora/256 << " con destino a " << estacionDestino/256 << "\n";
         if ((miPrefijo == prefijosSubredes[0]) and ((estacionDestino/256) == miPrefijo)){
             EV << "_____________________________________\n";
             EV << "Paquete enviado desde la subred "<<miPrefijo/256 << " por "<< estacionEmisora/256 << " con destino a " << estacionDestino/256 << "\n";
         };

    }
};//Fin de procesar automensaje generador de paquete


//////////////////////////////////////////////////////////////////////////////////////////////////
///// Obtención del retardo extremo a extremo del paquete y registro en vector de resultados
void subred::obtenerResultados(paqueteIP *pk){
    double retardo = simTime().dbl()- pk->getTiempo();
    int origen = pk->getSrcAddr();
    int indice = obtenerIndice(origen/256);
    int tipo = pk->getTipoPaquete();
    int tipoServicio = pk->getTipoServicio();
    if ((tipo == 0) and (tipoServicio != 1)){//Solo se registran paquetes de datos
        //Paquetes de datos sin prioridad
        retardoTotal[indice].record(retardo*1000);//Retardo en milisegundos
    } else{
        //Paquetes de datos con prioridad
        if ((tipo == 0) and (tipoServicio == 1)){//Solo se registran paquetes de datos
               retardoTotalP[indice].record(retardo*1000);//Retardo en milisegundos
        };
    };
};



//////////////////////////////////////
////// Inicialización  ///////////////
void subred::initialize()
{

   indice = par("indice");
   miPrefijo = par("prefijo");
   numSubredes = getParentModule()-> par("numSubredes");
   subredPreparada = true;

   std::string prefijosSubredesStr;
   prefijosSubredesStr = getParentModule()-> par("prefijosSubredes").stdstringValue();
   std::string sstr;
   int elemento;

   for (int i=0; i<numSubredes; i++){
        sstr = prefijosSubredesStr.substr(i*4,3);
        elemento = atoi(sstr.c_str());//Conversión de String a entero
        prefijosSubredes[i] = elemento;
       };

   /*EV << "TABLA DE PREFIJOS DE SUBREDES \n";

    for (int i=0; i<numSubredes; i++){
        EV << "Subred con índice "<< i << ". Prefijo: " << prefijosSubredes[i] <<" \n";

    };
    EV << "\n";*/



  /// EV << "Nombres de vectores de resultados para la subred "<< miPrefijo << " \n";
   for (int i=0; i<numSubredes; i++){
       //Solo se da nombre si no es mi índice
       if (i!= indice){
           retardoTotal[i].setName(obtenerNombre(i));
           retardoTotalP[i].setName(obtenerNombreP(i));

       }

   };


   // tamanoPaquete.setName("TamanoPaquete");

   //Tamaños relativos a paquetes (en octetos)
   tamanoMaxDatos = getParentModule()-> par("tamanoMaxDatos");
   tamanoMinDatos = getParentModule()-> par("tamanoMinDatos");
   tamanoCabecera = getParentModule()-> par("tamanoCabecera");

   //Obtención del tiempo medio entre generación de paquetes

    tiempoMedioEntrePaquetes = par("tiempoMedioEntrePaquetes");

    //Obtención de los tipos de tráfico distintos que genera
    traficoPrioritario = par("traficoPrioritario");

    //Obtención del modo de operación
    modoPrueba = getParentModule() -> par("modoPrueba");
    modoTrafico = getParentModule() -> par("modoTrafico");

//MODO PRUEBA
    if (modoPrueba){
        EV << "Modo Prueba\n";
            std::string estacionEmisoraStr;
            estacionEmisoraStr = getParentModule()-> par("estacionEmisora").stdstringValue();

            std::string estacionDestinoStr;
            estacionDestinoStr = getParentModule()-> par("estacionDestino").stdstringValue();

            int servicio = getParentModule()-> par("tipoServicioPrueba");

            std::string sstr;
            sstr = estacionEmisoraStr.substr(0,3);
            int subredE = atoi(sstr.c_str());//Conversión de String a entero
            sstr = estacionEmisoraStr.substr(4,3);
            int equipo = atoi(sstr.c_str());//Conversión de String a entero
            int estacionEmisora = subredE * 256 + equipo;

             sstr = estacionDestinoStr.substr(0,3);
             int subredD = atoi(sstr.c_str());//Conversión de String a entero
             sstr = estacionDestinoStr.substr(4,3);
             equipo = atoi(sstr.c_str());//Conversión de String a entero
             int estacionDestino = subredD * 256 + equipo;

           //Si la estacion emisora pertenece a esta subred, envía un paquete de datos de prueba
        if (miPrefijo == subredE ){
           EV << "_________________________\n";
           EV << "Paquete enviado por " << estacionEmisoraStr<< " con destino a " << estacionDestinoStr << "\n";
           EV << "Tipo de servicio solicitado: " << servicio <<"\n";
           enviarPaquetePrueba(estacionEmisora, estacionDestino, servicio);
            }

    }//Fin de modo prueba
    else
// MODO TRÁFICO DE PAQUETES
    {
        if (modoTrafico){
            EV << "Modo Tráfico\n";

        //Crea el temporizador para generación del primer paquete
                cMessage *temporizador = new cMessage("generadorPaquetes");
        // Planifica la generación del primer paquete
                double retardo = 60;
                scheduleAt(simTime().dbl()+ retardo + exponential (tiempoMedioEntrePaquetes, indice), temporizador);
                 };
     };

   EV << "Subred " << miPrefijo << " inicializada\n";




};
//////////////////////////////////////////
///// Gestión de mensajes recibidos  /////
void subred::handleMessage(cMessage *msg)
{
//AUTOMENSAJES

        if (msg->isSelfMessage()){
            const char* nombreAM;
            nombreAM = msg->getName();

            const char* gp = "generadorPaquetes";
            const char* cl = "canalLibre";

            if (*nombreAM == *gp){
             //GENERACIÓN Y DEPÓSITO DE UNA NUEVO PAQUETE EN LA COLA DE SALIDA HACIA EL ROUTER
              procesarAutomensajeGeneradorPaquetes(msg);

            }else{

               if (*nombreAM == *cl){
               //Extraer y enviar el siguiente paquete de la cola
                   procesarAutomensajePuerto(msg);

               }//Fin de canal libre
              }
         }//Fin de automensaje

else{

    // PAQUETE RECICBIDO DESDE EL ROUTER

    // Procesamiento de paquete IP en función de la dirección de destino

    // Toma el mensaje recibido y examina sus direcciones origen y destino.

     paqueteIP *pk = check_and_cast< paqueteIP *>(msg);
     int destino;
     destino = pk->getDestAddr(); //Obtiene la dirección destino
     int origen;
     origen = pk->getSrcAddr(); //Obtiene la dirección origen
     int tipo = pk->getTipoPaquete();

    if (modoPrueba and (tipo == 0)) {
         int selector = 255;
         int dest = destino & selector;
         int org = origen & selector;
         EV << "Paquete recibido en la subred " << miPrefijo << " con destino a "<< dest << " \n";
         EV << "Subred origen: " << origen/256 << " y estacion origen "<< org << " \n";
         int tamano = pk ->getByteLength();
         double retardo = simTime().dbl()- pk->getTiempo();
         EV << "Tamaño del paquete: " << tamano << " (octetos)\n";
         EV << "Retardo total del paquete: " << retardo * 1000 << " (milisegundos)\n";
    };

     //////Obtención de resultados
     ///Medir retardo sufrido por el paquete
     obtenerResultados(pk);

     // Una vez procesado, el paquete se elimina
     delete(pk);


}
};//Fin de handleMessage

void subred::finish(){};








