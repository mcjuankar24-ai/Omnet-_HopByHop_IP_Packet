//
//
// ETSI de Telecomunicación. Universidad de Málaga
// Titulación: Grado en Ingeniería Telemática
// Asignatura: Redes y Servicios de Telecomunicación 3
// Profesora: María Carmen España Boquera
//
// Modelo de paquete IP
//



packet paqueteIP
{
    int srcAddr = 0;//Dirección origen
    int destAddr = 0;//Dirección destino
    int tipoServicio = 0; // Campo tipo de servicio
    
    int tipoPaquete = 0; 
    //Los paquetes pueden ser de cinco tipos:
    //DATOS(0), HELLO(1); MAPPING(2); PATH(3); RESV(4)
    
	//Campos específicos para mensajes MAPPING, PATH y RESV
	int FECprefijo = 0;
	int FECmascara = 0;
	int etiquetaElegida = 0;
	int camino[10];
	
	//Campo auxiliar para medir retardos
	double tiempo = 0;

}

