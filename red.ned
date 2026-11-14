//
// ETSI de Telecomunicaci�n. Universidad de M�laga
// Titulaci�n: Grado en Ingenier�a Telem�tica
// Asignatura: Redes y Servicios de Telecomunicaci�n 3
// Profesora: Mar�a Carmen Espa�a Boquera
// 
// Simulaci�n de una red MPLS. Definici�n de la topolog�a.
//
simple router
{
    parameters:
        int indice;//�ndice del vector de routers
        int prefijo;//Prefijo de direcci�n (la parte de equipo es 0)
        int numPuertos = 4;//N�mero de puertos en cada router
        bool tieneSubred; //Indica si tiene una subred conectada o es s�lo de tr�nsito
        int tamanoTabla; //Tama�o de la tabla de encaminamiento
        string tablaPrefijosStr; //Par�metros para cargar la tabla de encaminamiento desde el fichero de inicializaci�n
        string tablaPuertosStr;
        string tablaMascarasStr;


        @display("i=abstract/router");
    gates:
        inout puerto[numPuertos];

}

simple subred
{
    parameters:
        int indice;//�ndice del vector de subredes
        int prefijo;
        double tiempoMedioEntrePaquetes;
        int traficoPrioritario;

        @display("i=misc/cloud");
    gates:
        inout puerto;
}

simple nada
{
    parameters:
        int identificador;//�ndice del vector de nadas

        @display("i=old/x_noentry");
    gates:
        inout puerto;
}


network red
{
    parameters:
        int numRouters;
        int numSubredes;
        int numNadas;
        string prefijosSubredes; //Ordenados seg�n el �ndice

        //Par�metros relativos a tama�os de paquete	
        int tamanoMaxDatos;
        int tamanoMinDatos;
        int tamanoCabecera;

        //Tama�o m�ximo de la cola de paquetes en cada puerto de una router
        int tamanoMaxCola;


        //Par�metros para las pruebas de env�o selectivo de un paquete
        bool modoPrueba;
        string estacionEmisora; //Selecciona la estaci�n emisora del paquete de prueba
        string estacionDestino; //Selecciona la estaci�n destino
        int tipoServicioPrueba;
        string direccionEspecial; //Multicast a routers vecinos

        //Selecci�n de modo tr�fico
        bool modoTrafico;

        //Par�metros para ingenier�a del tr�fico
        bool modoIngenieriaTrafico;

        //Caminos y FEC para los LSP bajo demanda (modo Ingenier�a del Tr�fico)
        int numCaminos;
        string caminosStr;
        string serviciosStr;



    types:


//Canales entre routers

        channel C25 extends ned.DatarateChannel
        {
            datarate = 155520000bps;//155,52Mbits/s
            double longitud @unit(km);
            longitud = 25km;
            delay = this.longitud / 200000km * 1s;
        }

        channel C50 extends ned.DatarateChannel
        {
            datarate = 155520000bps;//155,52Mbits/s
            double longitud @unit(km);
            longitud = 50km;
            delay = this.longitud / 200000km * 1s;

        }
        channel C75 extends ned.DatarateChannel
        {
            datarate = 155520000bps;//155,52Mbits/s
            double longitud @unit(km);
            longitud = 75km;
            delay = this.longitud / 200000km * 1s;
        }


//Canal entre router y subred

        channel CRS extends ned.DatarateChannel
        {
            datarate = 1000000000bps;//1000Mbits/s
            double longitud @unit(km);
            longitud = 1km;
            delay = this.longitud / 200000km * 1s;

        }


    submodules:


        routers[numRouters]: router {
            parameters:
                indice = index;

        }


        subredes[numSubredes]: subred {
            parameters:
                indice = index;


        }

        nadas[numNadas]: nada {
            parameters:
                identificador = index;


        }

    connections:

        //Conexiones entre routers
        routers[0].puerto[3] <--> C50 <--> routers[1].puerto[1];
        routers[0].puerto[1] <--> C50 <--> routers[2].puerto[0];
        routers[0].puerto[2] <--> C25 <--> routers[3].puerto[1];
        routers[1].puerto[2] <--> C25 <--> routers[3].puerto[0];
        routers[1].puerto[3] <--> C50 <--> routers[4].puerto[0];
        routers[2].puerto[3] <--> C50 <--> routers[6].puerto[1];
        routers[3].puerto[2] <--> C50 <--> routers[6].puerto[0];
        routers[3].puerto[3] <--> C25 <--> routers[5].puerto[1];
        routers[6].puerto[3] <--> C50 <--> routers[5].puerto[2];
        routers[5].puerto[0] <--> C25 <--> routers[4].puerto[1];

        //Conexiones entre cada subred y su router (o entre un router y nada)
        routers[0].puerto[0] <--> CRS <--> subredes[0].puerto;
        routers[2].puerto[2] <--> CRS <--> subredes[1].puerto;
        routers[6].puerto[2] <--> CRS <--> subredes[3].puerto;
        routers[5].puerto[3] <--> CRS <--> subredes[4].puerto;
        routers[4].puerto[2] <--> CRS <--> subredes[2].puerto;

        //Puertos de router no conectados (conectados a nada)
        routers[1].puerto[0] <--> CRS <--> nadas[0].puerto;
        routers[2].puerto[1] <--> CRS <--> nadas[1].puerto;
        routers[4].puerto[3] <--> CRS <--> nadas[2].puerto;




}
