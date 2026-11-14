//
// ETSI de Telecomunicaci�n. Universidad de M�laga
// Titulaci�n: Grado en Ingenier�a Telem�tica
// Asignatura: Redes y Servicios de Telecomunicaci�n 3
// Profesora: Mar�a Carmen Espa�a Boquera
//
// Modelo de router
//

#include <string.h>
#include <omnetpp.h>
#include "paqueteIP_m.h"

using namespace omnetpp;

/**
 * Clase que simula el comportamiento de un router con encaminamiento de paquetes convencional
 */


class router : public cSimpleModule
{

private:

    int indice;//�ndice del vector de routers que contiene a este router
    int miDireccion; //Direcci�n propia del router
    int miPrefijo;//Prefijo de la direcci�n/subred del router
    int direccionEspecial;//Direcci�n espacial (grupo multicast de routers vecinos)

    //Tabla de encaminamiento
    int tablaPuertos[20];//Columna de puertos de salida de la tabla de encaminamiento
    int tablaPrefijos[20];//Columna de prefijos de direcci�n de la tabla de encaminamiento
    int tablaMascaras[20];//Columna de m�scaras de la tabla de encaminamiento
    int conversionMascara[9]; //Conversi�n de las m�scaras a n�meros enteros


     //Colas de almacenamiento de paquetes pendientes de enviar.
     //Dos colas por cada puerto: la cola normal (cola) y la cola de alta prioridad (colaP)
     cQueue cola[4];
     cQueue colaP[4];
     int tamanoMaxCola;//Tama�o m�xomo de una cola

      bool modoPrueba;

      //Vectores y variables de resultados para cada puerto
        cOutVector probabilidadDesbordamiento[4];//Probabilidad de que la cola se desborde en cada puerto
        double contadorDesbordamientoCola[4];
        double contadorIntentoEnvio[4];

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual const char* obtenerNombre(int puerto);

    //// FUNCIONES GENERALES PARA ENV�O DE PAQUETES ////

     //Si el canal est� ocupado, el paquete se deposita en una cola
     virtual void enviarPaquete(cPacket *pk, int puerto, int servicio);

     //Difusi�n de un paquete (se env�a hacia todos los puertos del router)
     virtual void difundePaquete(paqueteIP *pk);
     //Se aplica solamente a paquetes sin etiquetar

     //Procesamiento de un automensaje cuando un puerto ha quedado libre
     virtual void procesarAutomensajePuerto(cMessage *msg);


    ///  FUNCIONES PARA GESTION DE LA TABLA DE ENCAMINAMIENTO  ////
    virtual int buscaTablaEncaminamiento(int direccion);
    virtual  void cargaTabla();

    // Funci�n de encaminamiento de paquetes convencional
    virtual void encaminaPaquete(paqueteIP *pk);
    //Se aplica solamente a paquetes sin etiquetar

    virtual void finish();
};

Define_Module(router);
///////////////
const char* router::obtenerNombre(int puerto)
//Funci�n para asignar nombres a los vectores de resultados
{
    const char* nombre;
    switch (puerto){
         case 0:
             switch (miPrefijo){
             case 160: nombre = "R160ProbDesbordamientoPto0";
                     break;
             case 161: nombre = "R161ProbDesbordamientoPto0";
                      break;
             case 162: nombre = "R162ProbDesbordamientoPto0";
                      break;
             case 163: nombre = "R163ProbDesbordamientoPto0";
                      break;
             case 164: nombre = "R164ProbDesbordamientoPto0";
                      break;
             case 165: nombre = "R165ProbDesbordamientoPto0";
                       break;
             case 166: nombre = "R166ProbDesbordamientoPto0";
                       break;
             case 167: nombre = "R167ProbDesbordamientoPto0";
                       break;
              }
             break;
         case 1:
             switch (miPrefijo){
              case 160: nombre = "R160ProbDesbordamientoPto1";
                      break;
              case 161: nombre = "R161ProbDesbordamientoPto1";
                       break;
              case 162: nombre = "R162ProbDesbordamientoPto1";
                       break;
              case 163: nombre = "R163ProbDesbordamientoPto1";
                       break;
              case 164: nombre = "R164ProbDesbordamientoPto1";
                       break;
              case 165: nombre = "R165ProbDesbordamientoPto1";
                        break;
              case 166: nombre = "R166ProbDesbordamientoPto1";
                        break;
              case 167: nombre = "R167ProbDesbordamientoPto1";
                        break;
               }
              break;
         case 2:
             switch (miPrefijo){
              case 160: nombre = "R160ProbDesbordamientoPto2";
                      break;
              case 161: nombre = "R161ProbDesbordamientoPto2";
                       break;
              case 162: nombre = "R162ProbDesbordamientoPto2";
                       break;
              case 163: nombre = "R163ProbDesbordamientoPto2";
                       break;
              case 164: nombre = "R164ProbDesbordamientoPto2";
                       break;
              case 165: nombre = "R165ProbDesbordamientoPto2";
                        break;
              case 166: nombre = "R166ProbDesbordamientoPto2";
                        break;
              case 167: nombre = "R167ProbDesbordamientoPto2";
                        break;
               }
              break;
         case 3:
             switch (miPrefijo){
             case 160: nombre = "R160ProbDesbordamientoPto3";
                       break;
              case 161: nombre = "R161ProbDesbordamientoPto3";
                       break;
              case 162: nombre = "R162ProbDesbordamientoPto3";
                       break;
              case 163: nombre = "R163ProbDesbordamientoPto3";
                       break;
              case 164: nombre = "R164ProbDesbordamientoPto3";
                       break;
              case 165: nombre = "R165ProbDesbordamientoPto3";
                        break;
              case 166: nombre = "R166ProbDesbordamientoPto3";
                        break;
              case 167: nombre = "R167ProbDesbordamientoPto3";
                        break;
               }
             break;
      break;
     };
    return  nombre;


}
///////////////

///////////////////////////////////////////////
//Funci�n para enviar un paquete por el puerto indicado
//Si el canal est� ocupado, el paquete se deposita en una cola

void router::enviarPaquete(cPacket *pk, int puerto, int servicio){

contadorIntentoEnvio[puerto]=contadorIntentoEnvio[puerto]+1; //Para obtenci�n de de estad�sticas
bool colaPLlena = false;

 //Antes de enviar el paquete, comprueba si el canal est� ocupado
cChannel *canal = gate("puerto$o",puerto)->getTransmissionChannel();
simtime_t termina = canal->getTransmissionFinishTime();
if (termina <= simTime()){//Canal libre
    //EV << "Env�o inmediato sin cola \n";
    //Enviar el paquete
    send(pk, "puerto$o", puerto);

}else{//Canal ocupado
    if (servicio == 1){//Cola de alta prioridad
    //Depositar el paquete en cola, si la cola no est� llena
        int tamanoCola = colaP[puerto].length();
        if (tamanoCola <= tamanoMaxCola){
            colaP[puerto].insert(pk);
            //EV << "N�mero de paquetes en cola de alta prioridad " << colaP[puerto].length()<< "\n";
        } else colaPLlena = true;
    };//Fin de servicio 1
    if ((servicio == 0) or ((servicio ==1) and colaPLlena)){
        //Depositar el paquete en cola, si la cola no est� llena
                int tamanoCola = cola[puerto].length();

                if (tamanoCola <= tamanoMaxCola){
                    cola[puerto].insert(pk);
                    //EV << "N�mero de paquetes en cola normal " << cola[puerto].length()<< "\n";
                } else
                {
                    delete pk;
                    EV << "DESBORDAMIENTO DE LA COLA\n";
                    EV << "Router con prefijo: " << miPrefijo <<"; puerto: "<< puerto<< "\n";
                    contadorDesbordamientoCola[puerto]=contadorDesbordamientoCola[puerto]+1;
                };


    };  //Fin de servicio 0))
    const char* canal;
    //Programar la lectura para el momento en que el canal quede libre (mediante un automensaje)
    switch (puerto){
                     case 0: canal = "0";
                             break;
                     case 1: canal = "1";
                             break;
                     case 2: canal = "2";
                             break;
                     case 3: canal = "3";
                             break;
                      };

    cMessage *canalLibre = new cMessage(canal);
    scheduleAt(termina, canalLibre);
    }//Fin de canal ocupado


};//Fin de enviarPaquete


//////////// Funci�n para enviar un paquete por todos los puertos del router//////////////////////
void router::difundePaquete(paqueteIP *pk){
// Difusi�n del paquete a todos los puertos
    int numPuertos = par("numPuertos");
    int tipoServicio;
    tipoServicio = pk->getTipoServicio();
    for (int i=0; i<numPuertos; i++){
        paqueteIP *copia = pk->dup();
        enviarPaquete(copia, i, tipoServicio);
    };
    delete pk;
}

//Funci�n que procesa el automensaje generado cuando el canal queda libre

void router::procesarAutomensajePuerto(cMessage *msg)
{
       const char* cnl;
       cnl = msg->getName();
       const char* cl0 = "0";
       const char* cl1 = "1";
       const char* cl2 = "2";
       const char* cl3 = "3";

       int puerto;//N�mero de puerto que ha quedado libre


       if (*cnl == *cl0)
          {puerto = 0;}
       else{
           if ( *cnl == *cl1){ puerto = 1;}
           else{
               if ( *cnl == *cl2){ puerto = 2;}
               else{
                   if ( *cnl == *cl3){ puerto = 3;}
                   else{
                      EV << "Error en automensaje\n";
                   }
               }
           }
       };
      //EV << "Puerto libre " << puerto <<"\n";

     //Extraer y enviar el siguiente paquete de la cola

     //Antes de enviar el paquete, comprueba si realmente est� libre
       cChannel *canal = gate("puerto$o", puerto)->getTransmissionChannel();
       simtime_t termina = canal->getTransmissionFinishTime();
       if (termina <= simTime()){//Canal libre
            //Intenta sacar el paquete de la cola de alta prioridad
           int tamanoColaP = colaP[puerto].length();

           if (tamanoColaP > 0){
               cObject *obj = colaP[puerto].pop();
               cPacket *pk = check_and_cast<cPacket *>(obj);
               //Enviar el paquete
                send(pk, "puerto$o", puerto);
           } else //No hay paquetes en la cola de alta prioridad
           {
               int tamanoCola = cola[puerto].length();
               if (tamanoCola > 0){
                   cObject *obj = cola[puerto].pop();
                   cPacket *pk = check_and_cast<cPacket *>(obj);
                   //Enviar el paquete
                    send(pk, "puerto$o", puerto);
               }
           };

           //Si quedan paquetes en la cola, enviar un automensaje para seguir leyendo la cola
           if ( (cola[puerto].length()>0) or (colaP[puerto].length()>0)){
               //Programar la lectura para el momento en que el canal quede libre (mediante un automensaje)
               cChannel *canal = gate("puerto$o", puerto)->getTransmissionChannel();
               simtime_t termina = canal->getTransmissionFinishTime();
               cMessage *canalLibre = new cMessage();
                 canalLibre->setName(cnl);
                 scheduleAt(termina, canalLibre);

           };


         }//Fin de canal libre
       else{//Canal ocupado
       //Programar la lectura para el momento en que el canal quede libre (mediante un automensaje)
            cMessage *canalLibre = new cMessage();
            canalLibre->setName(cnl);
            scheduleAt(termina, canalLibre);
       }//Fin de canal ocupado

       //Despu�s de procesarlo, se borra el automensaje
       delete msg;

};




//FUNCIONES PARA GESTION DE LA TABLA DE ENCAMINAMIENTO

int router::buscaTablaEncaminamiento(int direccion)
{
    //Analiza toda la tabla comparando la direcci�n con prefijo/m�scara
    //Busca la mejor coincidencia (m�scara m�s larga)
    //Devuelve el puerto de salida

   int fila = -1;//Indice-fila de la tabla de encaminamiento
   int tamano = par("tamanoTabla");
   int puerto = -1; //Resultado de la b�squeda
    int mejorMascara = -1; // Guarda la longitud de la máscara más larga encontrada

    for (int i = 0; i < tamano; i++) 
    {
        int longitudMascara = tablaMascaras[i]; // Extraemos las máscaras de la tablaMascaras
        int mascaraBits = conversionMascara[longitudMascara]; // Obtenemos su valor en entero con la conversion
        int prefijoTabla = tablaPrefijos[i] * 256; // Obtenemos el valor entero del prefijo

        // Aplicamos la máscara tanto a la dirección destino como al prefijo de la tabla
        if ((direccion & mascaraBits) == (prefijoTabla & mascaraBits)) 
        {
            // Si coincide y la máscara es más larga que la mejor encontrada hasta ahora
            if (longitudMascara > mejorMascara) {
                mejorMascara = longitudMascara;
                puerto = tablaPuertos[i];
            }
        }
    }

    return puerto;
}

void router::cargaTabla(){

    //Carga la tabla de encaminamiento desde el fichero de inicializaci�n
    // y la presenta en pantalla

    //Variables auxiliares para cargar la tabla de encaminameinto desde el fichero de inicializaci�n
     std::string tablaPrefijosStr;
     std::string tablaPuertosStr;
     std::string tablaMascarasStr;

     tablaPrefijosStr = par("tablaPrefijosStr").stdstringValue();
     tablaPuertosStr = par("tablaPuertosStr").stdstringValue();
     tablaMascarasStr = par("tablaMascarasStr").stdstringValue();
     int tamano = par("tamanoTabla");

      //int tamano = sizeof(tablaPuertosStr);//Tama�o de la tabla
      std::string sstr;
      int elemento;

      for (int i=0; i<tamano; i++){
          sstr = tablaPuertosStr.substr(i*2,1);
          elemento = atoi(sstr.c_str());//Conversi�n de String a entero
          tablaPuertos[i] = elemento;
         };


      for (int i=0; i<tamano; i++){
           sstr = tablaPrefijosStr.substr(i*4,3);
           elemento = atoi(sstr.c_str());//Conversi�n de String a entero
           tablaPrefijos[i] = elemento;
          };

      for (int i=0; i<tamano; i++){
              sstr = tablaMascarasStr.substr(i*2,1);
              elemento = atoi(sstr.c_str());//Conversi�n de String a entero
              tablaMascaras[i] = elemento;
             };


        EV << "\n";

        EV << "TABLA DE ENCAMINAMIENTO DEL ROUTER " << miPrefijo << ".0\n";

       for (int i=0; i<tamano; i++){
   EV << "Puerto destino para el prefijo "<< tablaPrefijos[i] << ".0/" << tablaMascaras[i]<<" : " << tablaPuertos[i]<<" \n";

       };
       EV << "\n";


};

////////////////////////////////////////////
void router::initialize()
{

 //Obtiene los valores de los par�metros desde el fichero de inicializaci�n

  indice = par("indice");
  miPrefijo = par("prefijo");
  miDireccion = miPrefijo* 256;
  //Tama�o m�ximo de la cola
  tamanoMaxCola = getParentModule()-> par("tamanoMaxCola");

  conversionMascara[0] = 0;//Salida por defecto
  conversionMascara[1] = 32768;//10000000 00000000
  conversionMascara[2] = 49152;//11000000 00000000
  conversionMascara[3] = 57344;//11100000 00000000
  conversionMascara[4] = 61440;//11110000 00000000
  conversionMascara[5] = 63488;//11111000 00000000
  conversionMascara[6] = 64512;//11111100 00000000
  conversionMascara[7] = 65024;//11111110 00000000
  conversionMascara[8] = 65280;//11111111 00000000

 //Creaci�n de la tabla de encaminamiento para este router
 //Se lee desde el fichero de inicializaci�n

  cargaTabla();

  //Inicializaci�n de variables y  vectores de resultados
   int numP = par("numPuertos");
      for (int i=0; i< numP; i++){
          probabilidadDesbordamiento[i].setName(obtenerNombre(i));
          contadorDesbordamientoCola[i]=0;
          contadorIntentoEnvio[i]=0;
       };

  std::string direccionEspecialStr;
  direccionEspecialStr = getParentModule()-> par("direccionEspecial").stdstringValue();

   std::string sstr;
   sstr = direccionEspecialStr.substr(0,3);
   int subredE = atoi(sstr.c_str());//Conversi�n de String a entero
   sstr = direccionEspecialStr.substr(4,3);
   int equipo = atoi(sstr.c_str());//Conversi�n de String a entero
   direccionEspecial = subredE * 256 + equipo;

   modoPrueba = getParentModule() -> par("modoPrueba");
}


////////// Encaminamiento del paquete salto a salto convencional ///////////////////////
void router::encaminaPaquete(paqueteIP *pk)
{

// Procesamiento de paquete IP en funci�n de la direcci�n de destino

   // Toma el pauqete recibido y examina su direcci�n destino
  int destino;
  //COMPLETAR
  destino = pk->getDestAddr();

  int subredDestino = destino/256; //Prefijo de la subred destino
  //Dividir por 256 equivale a un desplazamiento en los bits de 8 posiciones a la derecha
  int equipoDestino = (destino & 255);
  //Con esta operaci�n l�gica nos quedamos con los 8 bits de menor peso

  if (modoPrueba){
      EV <<"Paquete recibido en el router: "<< miPrefijo << ".0 con destino a " << subredDestino <<"." << equipoDestino<< "\n";
      EV <<"Retardo acumulado por el paquete: "<< (simTime().dbl() - pk->getTiempo()) * 1000 << "(milisegundos)\n";
  };
  //Si la direcci�n es la propia o una direcci�n especial (ej.0), no debe encaminarlo (deber�a tratarse de un mensaje LDP que debe procesar

  if (destino == miDireccion){

      //Procesamiento de paquetes con destino al propio router

      // Luego examina el tipo de paquete

      int tipo;
      tipo = pk->getTipoPaquete();
      EV <<"Paquete de tipo "<< tipo << " destinado al router: "<< miPrefijo << ".0\n";
      delete pk;//Se elimina el paquete

  }//Fin de paquetes con direcci�n igual a la del router

  else
  {
       if (destino == direccionEspecial){
           //Procesamiento de una direcci�n especial
           int tipo;
           tipo = pk->getTipoPaquete();
           EV <<"Paquete de tipo "<< tipo << " con direcci�n especial recibido en el router: "<< miPrefijo << ".0\n";
           delete pk;//Se elimina el paquete
       }
       else //Procesamiento de un paquete que debe encaminarse
       {
               //Consulta la tabla de encaminamiento, para saber hacia qu� puerto de salida debe enviar el mensaje
               //COMPLETAR
               int puertoSalida;
               puertoSalida = buscaTablaEncaminamiento(destino);

                if (modoPrueba){
                    EV <<"Interfaz de salida "<< puertoSalida << "\n";
                };

                //Obtener el tipo de servicio requerido para el paquete
                //COMPLETAR
                int tipoServicio;
                tipoServicio = pk->getTipoServicio();

                //Env�a el paquete hacia ese puerto y con el tipo de srvicio reqquerido
                //COMPLETAR
                enviarPaquete(pk, puertoSalida,tipoServicio);


       }//Fin de procesamiento de paquetes que deben encaminarse

  }//Fin de paquetes con direcci�n distinta de la del router

};


////////////////////////////////////
void router::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()){
     //Automensaje indicando que un canal ha quedado libre
         procesarAutomensajePuerto(msg);

    }//Fin de automensaje


   else{//Paquete procedente de un puerto

     //Toma el mensaje recibido y lo convierte a paquete

      paqueteIP *pk = check_and_cast< paqueteIP *>(msg);

     //Encamina el paquete
     encaminaPaquete(pk);
   }
};//Fin de handleMessage

//////////////////////////////////////////77777

void router::finish(){

//// OBTENCI�N DE RESULTADOS
   double pDesbordamiento;
   int numP = par("numPuertos");
    for (int i=0; i< numP; i++){
        pDesbordamiento = 0;
        if (contadorIntentoEnvio[i] > 0){
            pDesbordamiento = contadorDesbordamientoCola[i] / contadorIntentoEnvio[i] * 100.0;
        }
        probabilidadDesbordamiento[i].record(pDesbordamiento);
    }


}











