#include <iostream>
#include <cstdlib>
#include <string> //tener mejor control sobre el string y más opciones
#include <sstream>
#include <time.h>
#include <fstream>
#include <conio.h>
/*define un tipo llamado stringstream que nos 
permite tratar un string como un stream, eso nos 
permite la inserción y la extracción 
desde y a strings de la misma manera que 
podríamos hacer con cin y cout.
*/

using namespace std;

// Definición de las estructuras de datos

struct DIRECCION
{
    string calle;
    string carrera;
    int numero;
    string diagonal;
    string transversal;
    string referencia;
};

struct FECHA_NACIMIENTO
{
    int anio;
    int mes;
    int dia;
};

struct DATOS_BASICOS
{
    string nombre;
    string apellido;
    string cedula;
    int edad;
    string correoElectronico;
    char sexo;
    float estatura;
    string telefono;
    DIRECCION direccion;
    FECHA_NACIMIENTO fechaNacimiento;
};

struct TIPO_DE_CUENTA
{
    string codigo;
    string descripcion;
    TIPO_DE_CUENTA(): codigo("-1"), descripcion("") {}
};

struct ESTADO_CUENTA
{
    char cod;
    string descripcion;
    ESTADO_CUENTA(): cod('I'), descripcion("Inactiva") {}
};

struct PLAZO
{
    int dia_plazo;
    int mes_plazo;
    int anio_plazo;	
};

struct FECHACREACION
{
    int dia_creacion_cuenta;
	int mes_creacion_cuenta;
	int anio_creacion_cuenta;	
};

struct CUENTA
{
    string codCuenta;
    string numeroCuenta;
    int cupo;
    int saldo;
    int disponible;
    ESTADO_CUENTA estado;
    PLAZO plazo;
    FECHACREACION fechaCreacion;
    CUENTA() : codCuenta("-1"), numeroCuenta(""),cupo(0), saldo(0), disponible(0) {}
};



struct PRODUCTO
{
    string cedula;
    string numeroCuenta;
    PRODUCTO() : cedula("-1"), numeroCuenta("-1") {}
};

struct CLIENTE
{
    DATOS_BASICOS datosBasicos;
    TIPO_DE_CUENTA tipoCuentas[7];
    CUENTA cuentas[100];
    PRODUCTO productos[100];
};

CLIENTE cliente;
CUENTA cuenta;
TIPO_DE_CUENTA tipo_de_cuenta;
PRODUCTO producto;

void guardarPersonas(CLIENTE* banco, int contador){
    ofstream archivo("personas.txt", ios::app);

    if (archivo.is_open()) {
        // El archivo se abrió correctamente
        // Realiza operaciones de escritura en el archivo
        for(int i=0; i < contador; i++){
            archivo << banco[i].datosBasicos.nombre;
            archivo << ";";
            archivo << banco[i].datosBasicos.apellido;
            archivo << ";";
            archivo << banco[i].datosBasicos.cedula;
            archivo << ";";
            archivo << banco[i].datosBasicos.edad;
            archivo << ";";
            archivo << banco[i].datosBasicos.sexo<<endl;
        }
        archivo.close(); // Cierra el archivo cuando hayas terminado
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }

}

void guardarCuentas(CLIENTE* banco, int contador){
    ofstream archivoCuentas("cuentas.txt", ios::app);

    if (archivoCuentas.is_open()) {
        //for que recorre los clientes
        for(int i=0; i < contador; i++){
            int j = 0;
            // while que recorre las cuentas del cliente
            while(banco[i].cuentas[j].codCuenta != "-1")
            {
                archivoCuentas << banco[i].cuentas[j].codCuenta;
                archivoCuentas << ";";
                archivoCuentas << banco[i].cuentas[j].numeroCuenta;
                archivoCuentas << ";";
                archivoCuentas << banco[i].cuentas[j].saldo;
                archivoCuentas << ";";
                archivoCuentas << banco[i].cuentas[j].disponible;
                archivoCuentas << ";";
                archivoCuentas << banco[i].cuentas[j].estado.cod<<endl;
                j++;
            }
        }
        archivoCuentas.close(); // Cierra el archivo cuando hayas terminado
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }

}

void guardarProductos(CLIENTE* banco, int contador){
    ofstream archivoProductos("productos.txt", ios::app);

    if (archivoProductos.is_open()) {
        //for que recorre los clientes
        for(int i=0; i < contador; i++){
            int j = 0;
            // while que recorre los productos del cliente
            while(banco[i].productos[j].cedula != "-1")
            {
                archivoProductos << banco[i].productos[j].cedula;
                archivoProductos << ";";
                archivoProductos << banco[i].productos[j].numeroCuenta<<endl;
                j++;
            }
        }
        archivoProductos.close(); // Cierra el archivo cuando hayas terminado
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }

}

void verPersonasRegistradas(){
     ifstream archivo("personas.txt");

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            // Realiza operaciones de procesamiento en cada línea leída
            istringstream ss(linea);
            string token;
        
            while (getline(ss, token, ';')) {
                cout << token << " ";
            }

            cout << endl;
        }

        archivo.close(); // Cierra el archivo cuando hayas terminado de leer
    } else {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }

}

void guardarDatos(CLIENTE* banco, int contador){
    guardarPersonas(banco, contador);
    guardarCuentas(banco, contador);
    guardarProductos(banco, contador);
}

int contarTipoCuentasCliente(CLIENTE* banco, int posicionBanco){
    int numeroTipoCuentas = 0;
    while(banco[posicionBanco].tipoCuentas[numeroTipoCuentas].codigo != "-1"){
        numeroTipoCuentas++;
    }
    return numeroTipoCuentas;
}

bool buscarTipoCuentaCliente(CLIENTE* banco, int posicionBanco, string codigoCuenta){
    int numeroTipoCuentas = 0;
    while(banco[posicionBanco].tipoCuentas[numeroTipoCuentas].codigo != "-1"){
        if(banco[posicionBanco].tipoCuentas[numeroTipoCuentas].codigo == codigoCuenta){
            return true;
        }
        numeroTipoCuentas++;
    }
    return false;

}

int buscarCliente(CLIENTE* banco, int &contador, string cedula){
    int posicionBanco = -1;
    for(int i=0; i < contador; i++)
    {
        if(banco[i].datosBasicos.cedula == cedula){
            posicionBanco = i;
            break;
        }
    }
    return posicionBanco;
}

// Función para buscar un producto en el arreglo de productos de un cliente
int buscarProductoEnCliente(CLIENTE* banco, int contador, string numeroCuenta)
{
    for (int i = 0; i < contador; ++i) {
        for (int j = 0; j < 100; ++j) {  // Suponiendo un máximo de 100 productos por cliente
            if (banco[i].productos[j].numeroCuenta == numeroCuenta) {
                // El producto se encuentra en la posición j del arreglo del cliente i
                return j;
            }
        }
    }
    // Si no se encuentra el producto, devolver -1
    return -1;
}

// Función para crear un tipo de cuenta
void crearTipoCuenta(CLIENTE* banco, int contador){
   system("cls");  // Limpia la pantalla 
    int codigo;
    string cedulaPersona;
    int posicionBanco;
    cout << "\n==========================================" << endl;
    cout <<"Tipos de cuenta"<<endl;
    cout << "==========================================" << endl;
    cout << "101. Ahorros"<<endl;
    cout << "102. corriente"<<endl;
    cout << "103. Tarjeta de credito"<<endl;
    cout << "104. Prestamo"<<endl;
    cout << "105. Nequi"<<endl;
    cout << "106. Fiducuenta"<<endl;
    cout << "107. CDT"<<endl;
    cout <<"\nDigite el  tipo de cuenta que desea crear: ";
    cin >> codigo;
    cout << endl;

    cout <<"Digite la cedula de la persona: ";
    cin >> cedulaPersona;

    posicionBanco = buscarCliente(banco, contador, cedulaPersona);
    if(posicionBanco == -1){
        cout << "La persona no se encuentra registrada."<<endl;
        getch();
    }else {

        //creacion de los tipos de cuenta con un switch que asocia cada codigo a la descripcion del tipo de cuenta
        string codigoString = to_string(codigo);

        switch (codigo) {
            case 101:
                tipo_de_cuenta.codigo = codigoString;
                tipo_de_cuenta.descripcion = "Ahorros";
                break;
            case 102:
                tipo_de_cuenta.codigo = codigoString;
                tipo_de_cuenta.descripcion = "Corriente";
                break;
            case 103:
                tipo_de_cuenta.codigo = codigoString;
                tipo_de_cuenta.descripcion = "Tarjeta de credito";
                break;
            case 104:
                tipo_de_cuenta.codigo = codigoString;
                tipo_de_cuenta.descripcion = "Prestamo";
                break;
            case 105:
                tipo_de_cuenta.codigo = codigoString;
                tipo_de_cuenta.descripcion = "Nequi";
                break;
            case 106:
                tipo_de_cuenta.codigo = codigoString;
                tipo_de_cuenta.descripcion = "Fiducuenta";
                break;
            case 107:
                tipo_de_cuenta.codigo = codigoString;
                tipo_de_cuenta.descripcion = "CDT";
                break;
            default:
                break;
        }
        banco[posicionBanco].tipoCuentas[contarTipoCuentasCliente(banco, posicionBanco)]= tipo_de_cuenta;
    }
    getch();

}


// Función para crear datos básicos de una persona e ingresar
void crearPersona(CLIENTE* banco, int &contador){
   system("cls"); 
    cout << "\n==========================================" << endl;
    cout <<"Persona (datos basicos)"<<endl;
    cout << "==========================================" << endl;
    cout << "Digite el nombre: ";
    cin >> cliente.datosBasicos.nombre;
    cout << "Digite el apellido: ";
    cin >> cliente.datosBasicos.apellido;
    cout << "Digite la cedula: ";
    cin >> cliente.datosBasicos.cedula;
    cout << "Digite la fecha de nacimiento (DD MM AAAA): " <<endl;
    cin >> cliente.datosBasicos.fechaNacimiento.anio;
    cin >> cliente.datosBasicos.fechaNacimiento.mes;
    cin >> cliente.datosBasicos.fechaNacimiento.dia;
    cout << "Su fecha ha sido registrada como: " <<cliente.datosBasicos.fechaNacimiento.anio << "/" << cliente.datosBasicos.fechaNacimiento.mes << "/" << cliente.datosBasicos.fechaNacimiento.dia <<endl;
    cout << "Digite la edad: ";
    cin >> cliente.datosBasicos.edad;
    cout << "Digite el correo electronico: ";
    cin >> cliente.datosBasicos.correoElectronico;
    cout << "Digite el sexo (M para masculino, F para femenino): ";
    cin >> cliente.datosBasicos.sexo;
    cout << "Digite la estatura (Metros): ";
    cin >> cliente.datosBasicos.estatura;
    cout << "Digite el telefono: ";
    cin >> cliente.datosBasicos.telefono;
    banco[contador]=cliente;
    contador++;
    getch();
}


int contarCuentasCliente(CLIENTE* banco, int posicionBanco){
    int numeroCuentas = 0;
    while(banco[posicionBanco].cuentas[numeroCuentas].codCuenta != "-1"){
        numeroCuentas++;
    }
    return numeroCuentas;
}

//FUNCION QUE ANALIZA LA HORA EXACTA DE CREACION DE CUALQUIER TIPO DE CUENTA
bool fechaCreacionCuenta(FECHACREACION &fechaCreacion)
{ 
    // Obtener la fecha actual
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Asignar la fecha actual a la estructura FECHACREACION
    fechaCreacion.dia_creacion_cuenta = ltm->tm_mday;
    fechaCreacion.mes_creacion_cuenta = 1 + ltm->tm_mon;
    fechaCreacion.anio_creacion_cuenta = 1900 + ltm->tm_year;

    return true;

} 
//C   U   E   N   T   A
// Funcion para crear una cuenta
// Función para crear una cuenta
void crearCuenta(CLIENTE* banco, int &contador){
    string cedulaPersona;
    int posicionBanco;
    bool existeCuenta;
    system("cls");  
    cout << "\n==========================================" << endl;
    cout << "Creando cuenta"<<endl;
    cout << "==========================================" << endl;
    cout << "Digite la cedula de la persona para crear la cuenta: ";
    cin >> cedulaPersona;
    cout <<endl;
    posicionBanco = buscarCliente(banco, contador, cedulaPersona);
    if(posicionBanco == -1){
        cout << "La persona no se encuentra registrada."<<endl;
        getch();
    } else {
        cout << "Digite el codigo de tipo de codigo cuenta: ";
        cin >> cuenta.codCuenta;
        existeCuenta = buscarTipoCuentaCliente(banco, posicionBanco, cuenta.codCuenta);
        if(!existeCuenta){
            cout << "La persona no tiene registrado ese tipo de cuenta"<<endl;
            getch();
        }else {

            cout <<endl;
            cuenta.estado.cod = 'A';
            cuenta.estado.descripcion = "Activa";
            // Aplicar restricciones según el tipo de cuenta
            if (cuenta.codCuenta == "101" || // Cuenta de Ahorros
                cuenta.codCuenta == "105" || // Nequi
                cuenta.codCuenta == "106")   // Fiducuenta
            {

                cuenta.disponible = cuenta.saldo; // Saldo igual a disponible
            }

            if (cuenta.codCuenta == "102" || // Cuenta Corriente
                cuenta.codCuenta == "103") // Tarjeta de Crédito
            {
                // Cupo
                cout << "Digite el cupo para la cuenta: ";
                cin >> cuenta.cupo;
            }

            if (cuenta.codCuenta == "104" || // Préstamo
                cuenta.codCuenta == "107") // CDT
            {
                // Plazo
                cout << "Digite el plazo para la cuenta (DD MM AAAA): ";
                cin >> cuenta.plazo.dia_plazo;
                cin >> cuenta.plazo.mes_plazo; 
                cin >> cuenta.plazo.anio_plazo;
                cout << "La fecha de plazo queda registrada como: " << cuenta.plazo.dia_plazo << "/" << cuenta.plazo.mes_plazo << "/" << cuenta.plazo.anio_plazo<<endl;
            }
            //fecha de creacion de cuenta (para todos los tipos de cuenta)
            cout << "A continuacion, se pide la fecha de creacion para la cuenta (DD MM AAAA): ";
            cin >> cuenta.fechaCreacion.dia_creacion_cuenta;
            cin >> cuenta.fechaCreacion.mes_creacion_cuenta; 
            cin >> cuenta.fechaCreacion.anio_creacion_cuenta;
            cout << "La fecha de creacion fue exitosamente registrada como: " << cuenta.fechaCreacion.dia_creacion_cuenta << "/" << cuenta.fechaCreacion.mes_creacion_cuenta << "/" << cuenta.fechaCreacion.anio_creacion_cuenta<<endl;

            stringstream numeroCuentaStream;
            srand(time(NULL)); // Inicializar la semilla para obtener números realmente aleatorios
            int codigoTipoCuenta = stoi(cuenta.codCuenta); // Convertir el código de tipo de cuenta a entero
            long long  numeroAleatorio = rand() % 9000000 + 1000000; // Generar un número aleatorio de 10 dígitos
            string numeroCuentaStr = to_string(codigoTipoCuenta) + to_string(numeroAleatorio); // Concatenar el código de tipo de cuenta y el número aleatorio
            cuenta.numeroCuenta = numeroCuentaStr;

            cout << "\n El numero de cuenta generado es: " << cuenta.numeroCuenta << endl;
            banco[posicionBanco].cuentas[contarCuentasCliente(banco, posicionBanco)]=cuenta;
            getch();
        }


    }
}

// Función para gestionar el estado de la cuenta
void gestionarEstadoCuenta() {
    system("cls");  
    cout << "\n==========================================" << endl;
    cout << "Gestionar estado de cuenta" << endl;
    cout << "==========================================" << endl;
    cout << "1. Cambiar a estado inactivo" << endl;
    cout << "2. Cambiar a estado bloqueado" << endl;
    cout << "3. Embargar cuenta" << endl;
    cout << "4. Volver al menú principal" << endl;
    cout << "Digite la opción: ";
    int opcion;
    cin >> opcion;

    switch (opcion) {
        case 1: // Cambiar a estado inactivo
            if (tipo_de_cuenta.codigo == "101" || // Cuenta de Ahorros
                tipo_de_cuenta.codigo == "102" || // Cuenta Corriente
                tipo_de_cuenta.codigo == "105" || // Nequi
                tipo_de_cuenta.codigo == "106") { // Fiducuenta
                cuenta.estado.cod = 'I';
                cuenta.estado.descripcion = "Inactiva";
            }
            break;
        case 2: // Cambiar a estado bloqueado
            if (tipo_de_cuenta.codigo == "103" || // Tarjeta de Crédito
                tipo_de_cuenta.codigo == "104" || // Préstamo
                tipo_de_cuenta.codigo == "107") { // CDT
                cuenta.estado.cod = 'B';
                cuenta.estado.descripcion = "Bloqueada";
            }
            break;
        case 3: // Embargar cuenta
            if (tipo_de_cuenta.codigo != "104") { // No es Préstamo
                // Restricción: Solo la cuenta de Préstamo no puede ser embargada
                cuenta.estado.descripcion = "Embargada";
            }
            break;
        case 4: // Volver al menú principal
            break;
        default:
            break;
    }
}

bool verificarCuenta(CLIENTE* banco, int posicionBanco, string numeroCuenta){
    int numeroCuentas = 0;
    while(banco[posicionBanco].cuentas[numeroCuentas].codCuenta != "-1"){
        if(banco[posicionBanco].cuentas[numeroCuentas].numeroCuenta == numeroCuenta){
            return true;
        }
        numeroCuentas++;
    }
    return false;
}

int buscarCuenta(CLIENTE* banco, int posicionBanco, string numeroCuenta)
{
    int posicionCuenta = 0;
    while(banco[posicionBanco].cuentas[posicionCuenta].codCuenta != "-1"){
        if(banco[posicionBanco].cuentas[posicionCuenta].numeroCuenta == numeroCuenta)
        {
            return posicionCuenta;
        }
        posicionCuenta++;
    }
    return -1;
}

int contarProductos(CLIENTE* banco, int posicionBanco){
    int numeroProductos = 0;
    while(banco[posicionBanco].productos[numeroProductos].cedula != "-1"){
        numeroProductos++;
    }
    return numeroProductos;
}


// funcion para hacer la asociacion de cedula con numero de cuenta
void crearProducto(CLIENTE* banco, int posicionBanco, int &contador)
{
    string cedulaPersona;
    string numeroCuenta;
    system("cls");
     cout << "\n==========================================" << endl;
    cout << "Asociando producto"<<endl;
    cout << "==========================================" << endl;
    cout << "Digite la cedula de la persona: ";
    cin >> cedulaPersona;
    posicionBanco = buscarCliente(banco, contador, cedulaPersona);
    if(posicionBanco == -1){
        cout << "La persona no se encuentra registrada."<<endl;
        getch();
    }else
     {
        cout << "Digite el numero de la cuenta: ";
        cin >> numeroCuenta;
        if(!buscarCuenta(banco, posicionBanco, numeroCuenta)){
            cout << "El numero de la cuenta no existe.";
        getch();
        }else 
        {
        producto.cedula = cedulaPersona;
        producto.numeroCuenta = numeroCuenta;
        banco[posicionBanco].productos[contarProductos(banco, posicionBanco)]=producto;
        cout << "Para la cedula "<< cedulaPersona <<" esta asignado el producto "<< numeroCuenta <<endl;
        getch();
        }
    
    }
}

// Funcion para consultar saldo
void consultarSaldo(CLIENTE *banco,int posicionBanco, int posicionCuenta, int contador)
{
    system("cls");
    string numeroCuenta;
    string cedula;
    cout << "\n==========================================" << endl;
    cout << "Consultar Saldo" << endl;
    cout << "==========================================" << endl;
    cout << "Digite el número de cuenta: ";
    cin >> numeroCuenta;
    cout << "Digite la cedula: ";
    cin >> cedula;
    posicionBanco=buscarCliente(banco, contador, cedula);
    posicionCuenta=buscarCuenta(banco, posicionBanco, numeroCuenta);

            // Mostrar disponible según el tipo de cuenta
            if (banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "102") {
                // Cuenta corriente
                if (banco[posicionBanco].cuentas[posicionCuenta].saldo < 0) {
                    cout << "No tiene disponible." << endl;
                } else {
                    cout << "Disponible: $" << banco[posicionBanco].cuentas[posicionCuenta].saldo + banco[posicionBanco].cuentas[posicionCuenta].cupo << endl;
                }
            } else if (banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "103") {
                // Tarjeta de crédito
                cout << "Disponible: $" << banco[posicionBanco].cuentas[posicionCuenta].cupo - banco[posicionBanco].cuentas[posicionCuenta].saldo << endl;
            } else if (banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "101" || 
            banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "105" || 
            banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "106") {
                // Cuenta de Ahorros, Nequi, Fiducuenta
                cout << "No aplica para este tipo de cuenta." << endl;
            } else
             {
                // Otros tipos de cuenta
                cout << "Disponible: $" << banco[posicionBanco].cuentas[posicionCuenta].saldo << endl;
            }
    
    getch();   
}        

// Funcion para consultar disponible
void consultarDisponible(CLIENTE *banco,int posicionBanco, int posicionCuenta, int contador) 
{
    string numeroCuenta;
    string cedula;
    system("cls");
    cout << "\n==========================================" << endl;
    cout << "Consultar Disponible" << endl;
    cout << "==========================================" << endl;
    cout << "Digite el número de cuenta: ";
    cin >> numeroCuenta;
    cout << "Digite la cedula: ";
    cin >> cedula;
    posicionBanco=buscarCliente(banco, contador, cedula);
    posicionCuenta=buscarCuenta(banco, posicionBanco, numeroCuenta);



            // Mostrar disponible según el tipo de cuenta
            if (banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "102") {
                // Cuenta corriente
                if (banco[posicionBanco].cuentas[posicionCuenta].saldo < 0) {
                    cout << "No tiene disponible." << endl;
                } else {
                    cout << "Disponible: $" << banco[posicionBanco].cuentas[posicionCuenta].saldo + banco[posicionBanco].cuentas[posicionCuenta].cupo << endl;
                }
            } else if (banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "103") {
                // Tarjeta de crédito
                cout << "Disponible: $" << banco[posicionBanco].cuentas[posicionCuenta].cupo - banco[posicionBanco].cuentas[posicionCuenta].saldo << endl;
            } else {
                // Resto de tipos de cuenta
                cout << "No aplica para este tipo de cuenta." << endl;
            }
            
            getch();

 }

//BLOQUE DE FUNCIONES ENCARGADAS DE CONSIGNAR 
//funcion que controla las consignaciones de cuenta corriente
void consignarCuentaCorriente(CLIENTE *banco,int posicionBanco, int posicionCuenta, int contador) 
{
    float montoAbono;
    string cedula;
    string numeroCuenta;
    cout << "Ingrese la cedula de la persona: " <<endl;
    cin >> cedula;
    cout << "Ingrese el numero de la cuenta: " <<endl;
    cin >> numeroCuenta;
    cout << "Ingrese el monto a abonar: ";
    cin >> montoAbono;
    posicionBanco=buscarCliente(banco, contador, cedula);
    posicionCuenta=buscarCuenta(banco, posicionBanco, numeroCuenta);

    if (banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Activa" ||
        banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Inactiva" ||
        banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Embargada") 
    {
        if (banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "102")
        {
            // Cuenta Corriente
            if (montoAbono > 0) 
            {
                if (banco[posicionBanco].cuentas[posicionCuenta].saldo >= 0) 
                {
                    // Caso 1: Saldo positivo
                    banco[posicionBanco].cuentas[posicionCuenta].disponible += montoAbono;
                } 
                else 
                {
                    // Caso 2: Saldo negativo
                    if (montoAbono >= abs(banco[posicionBanco].cuentas[posicionCuenta].saldo))
                    {
                        // Actualizar saldo y disponible
                        banco[posicionBanco].cuentas[posicionCuenta].saldo += montoAbono;
                        banco[posicionBanco].cuentas[posicionCuenta].disponible += montoAbono;
                    } 
                    else 
                    {
                        // Actualizar solo el saldo
                        banco[posicionBanco].cuentas[posicionCuenta].saldo += montoAbono;
                    }
                }
                cout << "Abono exitoso. Nuevo disponible: $" << banco[posicionBanco].cuentas[posicionCuenta].disponible << endl;
            } 
            else 
            {
                cout << "El monto a abonar debe ser mayor que cero." << endl;
            }
        } 
        else 
        {
            cout << "Esta cuenta no permite abonos." << endl;
        }
    } 
    else if (banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Bloqueada" ||
              banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Eliminada") 
    {
        cout << "No puede abonar a una cuenta bloqueada o eliminada" << endl;
    }
    getch();
}


// funcion que controla la consignacion en tarjetas de credito
void consignarTarjetaDeCredito(CLIENTE *banco,int posicionBanco, int posicionCuenta, int contador)
{
    float montoAbono;
    string cedula;
    string numeroCuenta;
    cout << "Ingrese la cedula de la persona: " <<endl;
    cin >> cedula;
    cout << "Ingrese el numero de la cuenta: " <<endl;
    cin >> numeroCuenta;
    cout << "Ingrese el monto a abonar: ";
    cin >> montoAbono;
    posicionBanco=buscarCliente(banco, contador, cedula);
    posicionCuenta=buscarCuenta(banco, posicionBanco, numeroCuenta);

    // Verificar si la cuenta está bloqueada
    if (banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Bloqueada") 
    {
        cout << "No puede abonar a una cuenta bloqueada." << endl;
    } 
    else 
    {
        if (banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Activa" ||
            banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Inactiva" ||
            banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Embargada") 
        {
            // Verificar el tipo de cuenta 
            if (banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "103")
            {
                // El saldo se actualiza restando al saldo actual el valor consignado
                // y se aumenta el disponible más no el cupo. 
                banco[posicionBanco].cuentas[posicionCuenta].saldo -= montoAbono;
                banco[posicionBanco].cuentas[posicionCuenta].disponible += montoAbono;
                cout << "Consignación realizada con éxito." << endl;
                cout << "Saldo de tarjeta de credito actual: " << banco[posicionBanco].cuentas[posicionCuenta].saldo << endl;
                cout << "Disponible de tarjeta de credito actual: " << banco[posicionBanco].cuentas[posicionCuenta].disponible << endl;
            } 
            else 
            {
                cout << "No se puede realizar la consignación. Tipo de cuenta no válido." << endl;
            }
        }
    }
    getch();
}
//funcion para consignar prestamo
void consignarPrestamo(CLIENTE *banco,int posicionBanco, int posicionCuenta, int contador)
{
    float montoAbono;
    string cedula;
    string numeroCuenta;
    cout << "Ingrese la cedula de la persona: " <<endl;
    cin >> cedula;
    cout << "Ingrese el numero de la cuenta: " <<endl;
    cin >> numeroCuenta;
    cout << "Ingrese el monto a abonar: ";
    cin >> montoAbono;
    posicionBanco=buscarCliente(banco, contador, cedula);
    posicionCuenta=buscarCuenta(banco, posicionBanco, numeroCuenta);


        if (banco[posicionBanco].cuentas[posicionCuenta].estado.cod == 'A' ||
         banco[posicionBanco].cuentas[posicionCuenta].estado.cod == 'I' ||
         banco[posicionBanco].cuentas[posicionCuenta].estado.cod == 'E') 
        {
            if (banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "104")
            {
                banco[posicionBanco].cuentas[posicionCuenta].saldo -= montoAbono;
                cout << "Consignación realizada con éxito." << endl;
                cout << "Saldo del prestamo actual: " << banco[posicionBanco].cuentas[posicionCuenta].saldo << endl;
            }
        
        }
        getch();
}

void consignarCdt(CLIENTE *banco,int posicionBanco, int posicionCuenta, int contador) 
{
    string numeroCuenta;
    string cedula;
    int montoAbono;
    cout << "Ingrese su cedula: ";
    cin >> cedula;
    cout << "Ingrese su numero de cuenta: ";
    cin >> numeroCuenta;
    cout << "Ingrese el valor a consignar :" << endl;
    cin >> montoAbono;
    posicionBanco=buscarCliente(banco, contador, cedula);
    posicionCuenta=buscarCuenta(banco, posicionBanco, numeroCuenta);

   if (banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Activa" || 
      banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Inactiva" || 
      banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Embargada")
    {
        // CDT
        if (banco[posicionBanco].cuentas[posicionCuenta].plazo.dia_plazo > 0 && 
        banco[posicionBanco].cuentas[posicionCuenta].plazo.mes_plazo > 0 && 
        banco[posicionBanco].cuentas[posicionCuenta].plazo.anio_plazo > 0)
        {
            if (fechaCreacionCuenta(cuenta.fechaCreacion))
            {
                if (montoAbono > 0)
                {
                    // Calcula los intereses según el plazo
                    float intereses = 0.0;
                    if (banco[posicionBanco].cuentas[posicionCuenta].plazo.dia_plazo == 30) 
                    {
                        intereses = montoAbono * 0.03;
                    } 
                    else if (banco[posicionBanco].cuentas[posicionCuenta].plazo.dia_plazo == 60) 
                    {
                        intereses = montoAbono * 0.05;
                    } 
                    else if (banco[posicionBanco].cuentas[posicionCuenta].plazo.dia_plazo == 90)
                    {
                        intereses = montoAbono * 0.07;
                    } 
                    else if (banco[posicionBanco].cuentas[posicionCuenta].plazo.dia_plazo == 180) 
                    {
                        intereses = montoAbono * 0.09;
                    } 
                    else if (banco[posicionBanco].cuentas[posicionCuenta].plazo.dia_plazo == 365) 
                    {
                        intereses = montoAbono * 0.15;
                    }

                    // Actualiza el saldo con los intereses
                    banco[posicionBanco].cuentas[posicionCuenta].saldo += montoAbono + intereses;
                    cout << "Abono exitoso. Nuevo saldo: $" << banco[posicionBanco].cuentas[posicionCuenta].saldo << endl;
                }
                else
                {
                    cout << "El monto a abonar debe ser mayor que cero." << endl;
                }
            }
            else
            {
                cout << "No puede abonar a una cuenta con fecha de creación futura" << endl;
            }
        }
        else
        {
            cout << "El plazo debe ser mayor que cero." << endl;
        }
    } 
    else if (banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Bloqueada" ||
    banco[posicionBanco].cuentas[posicionCuenta].estado.descripcion == "Eliminada") 
    {
        cout << "No puede abonar a una cuenta bloqueada o eliminada" << endl;
    }
    getch();
}

//BLOQUE DE FUNCIONES DE RETIROS
void retiroCuentasTipoAhorro(CLIENTE *banco,int posicionBanco, int posicionCuenta) 
{   
    string numeroCuenta;
    string cedula;
    int valorRetiro;
    cout << "Ingrese su cedula: ";
    cin >> cedula;
    cout << "Ingrese su numero de cuenta: ";
    cin >> numeroCuenta;
    cout << "Ingrese el valor  a retirar :" << endl;
    cin >> valorRetiro;

    if ((banco[posicionBanco].cuentas[posicionCuenta].codCuenta == "101" || 
        banco[posicionBanco].cuentas[posicionCuenta].codCuenta== "106" || 
        banco[posicionBanco].cuentas[posicionCuenta].codCuenta== "105")) 
    {
        // Verificar que el valor a retirar no sea mayor que el saldo o disponible
         if (valorRetiro <= cuenta.saldo || valorRetiro <= cuenta.disponible) 
        {
            // Realizar el retiro
            banco[posicionBanco].cuentas[posicionCuenta].saldo -= valorRetiro;
            banco[posicionBanco].cuentas[posicionCuenta].disponible -= valorRetiro;

            cout << "Retiro exitoso. Nuevo saldo: " << banco[posicionBanco].cuentas[posicionCuenta].saldo << endl;
        } else 
        {
        cout << "Error: El monto a retirar es mayor que el saldo o disponible." << endl;
        }
    }
    getch();    
    
}

// Función para realizar retiro en cuenta corriente
void realizarRetiroCuentaCorriente(CLIENTE *banco,int posicionBanco, int posicionCuenta, int contador) 
{
    string numeroCuenta;
    string cedula;
    int valorRetiro;
    cout << "Ingrese su cedula: ";
    cin >> cedula;
    cout << "Ingrese su numero de cuenta: ";
    cin >> numeroCuenta;
    cout << "Ingrese el valor  a retirar :" << endl;
    cin >> valorRetiro;
    posicionBanco=buscarCliente(banco, contador, cedula);
    posicionCuenta=buscarCuenta(banco, posicionBanco, numeroCuenta);

    // 1. Si tiene saldo cero (0)
    if (cuenta.saldo == 0) 
    {
        banco[posicionBanco].cuentas[posicionCuenta].saldo -= valorRetiro;
        banco[posicionBanco].cuentas[posicionCuenta].disponible = banco[posicionBanco].cuentas[posicionCuenta].cupo - valorRetiro;
        cout << "Retiro exitoso. Nuevo saldo: " << banco[posicionBanco].cuentas[posicionCuenta].saldo << ", Nuevo disponible: " << banco[posicionBanco].cuentas[posicionCuenta].disponible << endl;
    } 
    // 2. Si tiene saldo > 0
    else if (banco[posicionBanco].cuentas[posicionCuenta].saldo > 0) 
    {
        // Caso 2.1: El valor a retirar es mayor que el saldo actual
        if (valorRetiro > banco[posicionBanco].cuentas[posicionCuenta].saldo) 
        {
            banco[posicionBanco].cuentas[posicionCuenta].saldo -= valorRetiro;
            banco[posicionBanco].cuentas[posicionCuenta].disponible = banco[posicionBanco].cuentas[posicionCuenta].cupo - valorRetiro;
            cout << "Retiro exitoso. Nuevo saldo: " << banco[posicionBanco].cuentas[posicionCuenta].saldo << ", Nuevo disponible: " << banco[posicionBanco].cuentas[posicionCuenta].disponible << endl;
        } 
        // Caso 2.2: El valor a retirar es menor que el saldo actual
        else 
        {
            banco[posicionBanco].cuentas[posicionCuenta].saldo -= valorRetiro;
            cout << "Retiro exitoso. Nuevo saldo: " << banco[posicionBanco].cuentas[posicionCuenta].saldo << ", Nuevo disponible: " << banco[posicionBanco].cuentas[posicionCuenta].disponible << endl;
        }
    } 
    // 3. Si tiene saldo < 0 (saldo negativo)
    else
     {
        banco[posicionBanco].cuentas[posicionCuenta].saldo -= valorRetiro;
        if (banco[posicionBanco].cuentas[posicionCuenta].saldo < -banco[posicionBanco].cuentas[posicionCuenta].cupo) 
        {
            cout << "Error: Saldo negativo excede el límite del cupo." << endl;
            // Revertir el cambio en el saldo
            banco[posicionBanco].cuentas[posicionCuenta].saldo += valorRetiro;
        } else 
        {
            banco[posicionBanco].cuentas[posicionCuenta].disponible = banco[posicionBanco].cuentas[posicionCuenta].cupo + banco[posicionBanco].cuentas[posicionCuenta].saldo;
            cout << "Retiro exitoso. Nuevo saldo: " << banco[posicionBanco].cuentas[posicionCuenta].saldo << ", Nuevo disponible: " << banco[posicionBanco].cuentas[posicionCuenta].disponible << endl;
        }
    }
    getch();
}

//Funcion para hacer retiro de tarjeta de credito
void retiroTarjetaDeCredito(CLIENTE *banco,int posicionBanco, int posicionCuenta, int contador) 
{
    string numeroCuenta;
    string cedula;
    int valorRetiro;
    cout << "Ingrese su cedula: ";
    cin >> cedula;
    cout << "Ingrese su numero de cuenta: ";
    cin >> numeroCuenta;
    cout << "Ingrese el valor  a retirar :" << endl;
    cin >> valorRetiro;
    posicionBanco=buscarCliente(banco, contador, cedula);
    posicionCuenta=buscarCuenta(banco, posicionBanco, numeroCuenta);

    // Verificar que el monto de retiro no sea mayor al disponible
    if (valorRetiro > banco[posicionBanco].cuentas[posicionCuenta].disponible) {
        cout << "Error: El monto de retiro supera el disponible de la cuenta." << endl;
    }

    // Actualizar el saldo y el disponible
    banco[posicionBanco].cuentas[posicionCuenta].saldo += valorRetiro;
    banco[posicionBanco].cuentas[posicionCuenta].disponible -= valorRetiro;

    // Mostrar información de la transacción
    cout << "Retiro exitoso." << endl;
    cout << "Nuevo saldo: " << banco[posicionBanco].cuentas[posicionCuenta].saldo << endl;
    cout << "Nuevo disponible: " << banco[posicionBanco].cuentas[posicionCuenta].disponible << endl;
    getch();
}

// Función para verificar el saldo de una cuenta
int verificarSaldo(CLIENTE* banco, int posicionBanco, string numeroCuenta, int contador) 
{
    for (int i = 0; i < contador; i++) {
        if (banco[posicionBanco].cuentas[i].numeroCuenta == numeroCuenta) {
            return i;  // Se encontró la cuenta, devolvemos el índice de la cuenta
        }
    }
    return -1;  // No se encontró la cuenta
}

// Función para realizar transferencias entre cuentas
void transferencia(CLIENTE* banco, int posicionBanco, string numeroCuentaOrigen, string numeroCuentaDestino, int contador) 
{
    int montoTransferencia;
    verificarSaldo(banco, posicionBanco, numeroCuentaOrigen, contador);
    verificarSaldo(banco, posicionBanco, numeroCuentaDestino, contador);
    // Buscar las cuentas de origen y destino
    int indiceCuentaOrigen = verificarSaldo(banco, posicionBanco, numeroCuentaOrigen, contador);
    int indiceCuentaDestino = verificarSaldo(banco, posicionBanco, numeroCuentaDestino, contador);

    if (indiceCuentaOrigen == -1 || indiceCuentaDestino == -1) {
        cout << "Error: Una o ambas cuentas no se encuentran registradas." << endl;
        return;
    }

    // Obtener información sobre las cuentas de origen y destino
    string tipoCuentaOrigen = banco[posicionBanco].tipoCuentas[contarTipoCuentasCliente(banco, posicionBanco)].descripcion;
    string tipoCuentaDestino = banco[posicionBanco].tipoCuentas[contarTipoCuentasCliente(banco, posicionBanco)].descripcion;

    // Solicitar el monto a transferir
    cout << "Ingrese el monto a transferir: ";
    cin >> montoTransferencia;

    // Verificar si la cuenta de origen es un préstamo o CDT
    if (tipoCuentaOrigen == "Prestamo" || tipoCuentaOrigen == "CDT") {
        cout << "Error: No se puede transferir desde un préstamo ni de un CDT." << endl;
        return;
    }

    // Verificar si la cuenta de destino es un préstamo o CDT
    if (tipoCuentaDestino == "Prestamo" || tipoCuentaDestino == "CDT") {
        cout << "Error: No se puede transferir a un préstamo ni a un CDT." << endl;
        return;
    }

    // Realizar la transferencia
    // Verificar que el monto de transferencia no sea mayor que el saldo o disponible de la cuenta de origen
    if (montoTransferencia > banco[posicionBanco].cuentas[indiceCuentaOrigen].saldo ||
        montoTransferencia > banco[posicionBanco].cuentas[indiceCuentaOrigen].disponible) {
        cout << "Error: El monto a transferir es mayor que el saldo o disponible de la cuenta de origen." << endl;
    } else {
        // Realizar la transferencia
        banco[posicionBanco].cuentas[indiceCuentaOrigen].saldo -= montoTransferencia;
        banco[posicionBanco].cuentas[indiceCuentaDestino].saldo += montoTransferencia;

        // Mostrar información de la transacción
        cout << "Transferencia exitosa." << endl;
        cout << "Nuevo saldo de la cuenta de origen: " << banco[posicionBanco].cuentas[indiceCuentaOrigen].saldo << endl;
        cout << "Nuevo saldo de la cuenta de destino: " << banco[posicionBanco].cuentas[indiceCuentaDestino].saldo << endl;
    }
}
//BLOQUE DE FUNCIONES PARA CANCELAR CUENTA
// Función para verificar el saldo de una cuenta
// Funcion verificarSaldo();
// Función para realizar un retiro de una cuenta
void realizarRetiro(CLIENTE* banco, int posicionBanco, int indiceCuenta) {
    int tipoCuentaCodigo;
    cout << "Ingrese el código de tipo de cuenta (101-107): ";
    cin >> tipoCuentaCodigo;
    // Verificar que la cuenta es de tipo Ahorros, CDT, Fiducuenta o Nequi
    if (tipoCuentaCodigo == 101 || tipoCuentaCodigo == 106 || tipoCuentaCodigo == 107 || tipoCuentaCodigo == 105) {
        int saldo = banco[posicionBanco].cuentas[indiceCuenta].saldo;
        banco[posicionBanco].cuentas[indiceCuenta].saldo = 0;  // Retirar el saldo
        cout << "Se realizó un retiro de $" << saldo << " por la cancelación de la cuenta." << endl;
    } else {
        cout << "La operación de retiro solo es válida para cuentas de tipo Ahorros, CDT, Fiducuenta o Nequi." << endl;
    }
}
// Función para realizar una consignación en una cuenta
void realizarConsignacion(CLIENTE* banco, int posicionBanco, int indiceCuenta) 
{
    int saldo = banco[posicionBanco].cuentas[indiceCuenta].saldo;
    banco[posicionBanco].cuentas[indiceCuenta].saldo = 0;  // Dejar el saldo en cero
    cout << "Se realizó una consignación de $" << saldo << " por la cancelación de la cuenta corriente." << endl;
}

// Función para pagar el saldo y cancelar productos asociados a la cuenta
void pagarSaldoYCancelarProductos(CLIENTE* banco, int posicionBanco, int indiceCuenta) 
{
    int saldo = banco[posicionBanco].cuentas[indiceCuenta].saldo;

    // Pagar (consignar) el saldo
    banco[posicionBanco].cuentas[indiceCuenta].saldo = 0;
    cout << "Se realizó el pago (consignación) de $" << saldo << " por la cancelación de la cuenta." << endl;

    // Cancelar productos asociados a la cuenta
    for (int i = 0; i < 100; i++)
     {
        if (banco[posicionBanco].productos[i].numeroCuenta == banco[posicionBanco].cuentas[indiceCuenta].numeroCuenta)
        {
            banco[posicionBanco].productos[i] = PRODUCTO();  // Limpiar el producto
        }
    }

    cout << "Los productos asociados a la cuenta han sido cancelados." << endl;
}

// Función para emitir un paz y salvo al cliente
void emitirPazYSalvo(CLIENTE* banco, int posicionBanco) 
{
    system("cls");  // Limpia la pantalla

    cout << "\n==============================" << endl;
    cout << "       Paz y Salvo" << endl;
    cout << "==============================" << endl;

    cout << "Cliente: " << banco[posicionBanco].datosBasicos.nombre << " " << banco[posicionBanco].datosBasicos.apellido << endl;
    cout << "Cedula: " << banco[posicionBanco].datosBasicos.cedula << endl;

    // Puedes agregar más información según tus necesidades

    cout << "\nEstado de cuentas:" << endl;
    for (int i = 0; i < 100; i++) {
        if (banco[posicionBanco].cuentas[i].estado.cod != 'I') 
        {
            cout << "Cuenta: " << banco[posicionBanco].cuentas[i].numeroCuenta << " - Estado: " << banco[posicionBanco].cuentas[i].estado.descripcion << endl;
        }
    }

    cout << "\nProductos cancelados:" << endl;
    for (int i = 0; i < 100; i++) {
        if (banco[posicionBanco].productos[i].cedula != "-1") {
            cout << "Producto: " << banco[posicionBanco].productos[i].numeroCuenta << " - Cancelado" << endl;
        }
    }

    cout << "\n==============================" << endl;

    cout << "\nSe ha emitido un paz y salvo al cliente." << endl;
    getch();  // Espera a que el usuario presione una tecla antes de continuar
}

// Función para cancelar una cuenta
void cancelarCuenta(CLIENTE* banco, int posicionBanco, string numeroCuenta, int contador) 
{
    int indiceCuenta = verificarSaldo(banco, posicionBanco, numeroCuenta, contador);

    if (indiceCuenta != -1) {
        // Verificar el tipo de cuenta
        string tipoCuenta = banco[posicionBanco].tipoCuentas[contarTipoCuentasCliente(banco, posicionBanco)].descripcion;

        if (tipoCuenta == "Tarjeta de credito" || tipoCuenta == "Prestamo") 
        {
            pagarSaldoYCancelarProductos(banco, posicionBanco, indiceCuenta);
    
        } else if (tipoCuenta == "Cuenta corriente") 
        {
            if (banco[posicionBanco].cuentas[indiceCuenta].saldo > 0) 
            {
                realizarRetiro(banco, posicionBanco, indiceCuenta);
            } else if (banco[posicionBanco].cuentas[indiceCuenta].saldo < 0) 
            {
                realizarConsignacion(banco, posicionBanco, indiceCuenta);
            }
        }

        // Cambiar el estado a 'C' (Cancelado)
        banco[posicionBanco].cuentas[indiceCuenta].estado.cod = 'C';
        banco[posicionBanco].cuentas[indiceCuenta].estado.descripcion = "Cancelada";

        cout << "La cuenta ha sido cancelada." << endl;

        // Emitir un paz y salvo
        emitirPazYSalvo(banco, posicionBanco);
    } else {
        cout << "La cuenta no se encuentra registrada." << endl;
    }
}

//MENU DE FUNCIONES DE CONSIGNACION/RETIRO/TRANSFERENCIA/CANCELAR
void menuTransacciones() 
{
    CLIENTE *banco;
    int contador;
    int opcionPrincipal = -3;
    string tipoCuentaOrigen, tipoCuentaDestino; 
    CUENTA cuentaOrigen;
    CUENTA cuentaDestino;
    int posicionBanco;
    int posicionCuenta;
    string numeroCuentaOrigen;
    string numeroCuentaDestino;
    string numeroCuenta;

    do {
        system("cls");
        cout << "Transacciones" << endl;
        cout << "\n==========================================" << endl;
        cout << "1. Abono" << endl;
        cout << "2. Retiro" << endl;
        cout << "3. Transferencia " << endl;
        cout << "4. Cancelar " << endl;
        cout << "5. Salir " << endl;
        cout << "Digite una de las opciones" << endl;
        cin >> opcionPrincipal;

        switch (opcionPrincipal) {
            case 1: {
                int opcionSub = -3;

                do {
                    system("cls");
                    cout << "ABONO A LA CUENTA" << endl;
                    cout << "A continuación se presentan los tipos de cuenta: " << endl;
                    cout << "\n==========================================" << endl;
                    cout << "101. Ahorros" << endl;
                    cout << "102. Corriente" << endl;
                    cout << "103. Tarjeta de crédito" << endl;
                    cout << "104. Préstamo" << endl;
                    cout << "105. Nequi" << endl;
                    cout << "106. Fiducuenta" << endl;
                    cout << "107. CDT" << endl;
                    cout << "108. Salir" << endl;
                    cout << "Digite una de las opciones" << endl;
                    cin >> opcionSub;

                    switch (opcionSub) {
                        case 101:
                            cout << "Para este tipo de cuenta no puede consignar.";
                            break;

                        case 102:
                            consignarCuentaCorriente(banco, posicionBanco, posicionCuenta ,contador);
                            break;

                        case 103:
                            consignarTarjetaDeCredito(banco, posicionBanco, posicionCuenta ,contador);
                            break;

                        case 104:
                            consignarPrestamo(banco, posicionBanco, posicionCuenta ,contador);
                            break;

                        case 105:
                            cout << "Para este tipo de cuenta no puede consignar.";
                            break;

                        case 106:
                            cout << "Para este tipo de cuenta no puede consignar.";
                            break;

                        case 107:
                            consignarCdt(banco, posicionBanco, posicionCuenta ,contador);
                            break;

                        case 108:
                            opcionSub = 0;
                            break;

                        default:
                            break;
                    }
                } while (opcionSub != 0);

                break;
            }

            case 2: {
                int opcionSub = -3;

                do {
                    system("cls");
                    cout << "RETIRO A LA CUENTA" << endl;
                    cout << "A continuación se presentan los tipos de cuenta: " << endl;
                    cout << "\n==========================================" << endl;
                    cout << "101. Ahorros" << endl;
                    cout << "102. Corriente" << endl;
                    cout << "103. Tarjeta de crédito" << endl;
                    cout << "104. Préstamo" << endl;
                    cout << "105. Nequi" << endl;
                    cout << "106. Fiducuenta" << endl;
                    cout << "107. CDT" << endl;
                    cout << "108. Salir" << endl;
                    cout << "Digite una de las opciones" << endl;
                    cin >> opcionSub;

                    switch (opcionSub) 
                    {
                        case 101:
                            retiroCuentasTipoAhorro(banco, posicionBanco, posicionCuenta);
                            break;

                        case 102:
                             realizarRetiroCuentaCorriente(banco, posicionBanco, posicionCuenta ,contador);
                            break;

                        case 103:
                             retiroTarjetaDeCredito(banco, posicionBanco, posicionCuenta ,contador);
                            break;

                        case 104:
                            cout << "No se puede retirar de este tipo de cuenta. ";
                            break;

                        case 105:
                            retiroCuentasTipoAhorro(banco, posicionBanco, posicionCuenta);
                            break;

                        case 106:
                            retiroCuentasTipoAhorro(banco, posicionBanco, posicionCuenta);
                            break;

                        case 107:
                            cout << "No se puede retirar de este tipo de cuenta. ";
                            break;

                        case 108:
                            opcionSub = 0;
                            break;

                        default:
                            break;
                    }
                } while (opcionSub != 0);
                getch();

                break;
            }
            case 3:
            transferencia(banco, posicionBanco, numeroCuentaOrigen, numeroCuentaDestino, contador);
            break;
            case 4:
            cancelarCuenta(banco, posicionBanco, numeroCuenta, contador);
            break;
            case 5:
                opcionPrincipal = 5;
                break;

            default:
                break;
        }
    } while (opcionPrincipal != 3);
    getch();
}


int main()
{
	// Arreglo de CLIENTE para almacenar múltiples clientes
    CLIENTE banco[100]; 
    int contador=0; //contar los clientes del sistema, para que el vector banco se ubique donde colocar el ingreso cliente
    int contadorTipoCuentas = 0;
    int contadorCuentas = 0;
    int contadorProductos = 0;
    int posicionBanco;
    int posicionCuenta;
    int opcion = -9; //se inicializa en 9 para que el programa entre al bucle
  do {
        system("cls");
        cout << "\n==========================================" << endl;
        cout << "Menu" << endl;
        cout << "Banco de la casita roja" << endl;
        cout << "==========================================" << endl;
        cout << endl;
        cout << "1. Crear un tipo de cuenta." << endl;
        cout << "2. Crear persona (datos basicos)." << endl;
        cout << "3. Crear cuenta." << endl;
        cout << "4. Producto" << endl;
        cout << "5. Consultar Saldo" << endl;
        cout << "6. Consultar Disponible" << endl;
        cout << "7. Transacciones" << endl;
        cout << "8. Actualizar" << endl;
        cout << "9. Estadisticas" << endl;
        cout << "10. Salir" << endl;
        cout << endl;
        cout << "Digite la opcion del menu: ";
        cin >> opcion;

        switch (opcion) 
        {
            case 1:
                crearTipoCuenta(banco, contadorTipoCuentas);
                break;
            case 2:
                crearPersona(banco, contador);
                break;
            case 3:
                crearCuenta(banco, contadorCuentas);
                break;
            case 4:
                crearProducto(banco, posicionBanco, contadorProductos);
                break;
            case 5:
                consultarSaldo(banco, posicionBanco, posicionCuenta ,contador);
                break;
            case 6:
                consultarDisponible(banco, posicionBanco, posicionCuenta ,contador);
                break;
            case 7:
                menuTransacciones();
                break;
            case 8:
                break;

            case 9:
                break;    
            case 10:
                opcion = 0;
                break;
            default:
                break;
        }
    } while (opcion != 0);

    getch();
    return 0;
}

