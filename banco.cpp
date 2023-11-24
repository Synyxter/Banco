#include <iostream>
#include <cstdlib>
#include <string> //tener mejor control sobre el string y más opciones
#include <sstream>
#include <time.h>
#include <fstream>
#include <conio.h>
#include <vector>
/*define un tipo llamado stringstream que nos 
permite tratar un string como un stream, eso nos 
permite la inserción y la extracción 
desde y a strings de la misma manera que 
podríamos hacer con cin y cout.
*/
// comentario prueba commit para ver si funciona clave ssh
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
    DATOS_BASICOS(): cedula("") {}
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
    vector<TIPO_DE_CUENTA> tipoCuentas;
    vector<CUENTA> cuentas;
    vector<PRODUCTO> productos;
};

CLIENTE cliente;
CUENTA cuenta;
TIPO_DE_CUENTA tipo_de_cuenta;
PRODUCTO producto;

void guardarPersonas(vector<CLIENTE>& banco){
    ofstream archivo("personas.txt", ios::app);

    if (archivo.is_open()) {
        // El archivo se abrió correctamente
        // Realiza operaciones de escritura en el archivo
        for(CLIENTE cliente : banco){
            archivo << cliente.datosBasicos.nombre;
            archivo << ";";
            archivo << cliente.datosBasicos.apellido;
            archivo << ";";
            archivo << cliente.datosBasicos.cedula;
            archivo << ";";
            archivo << cliente.datosBasicos.fechaNacimiento.dia;
            archivo << ";";
            archivo << cliente.datosBasicos.fechaNacimiento.mes;
            archivo << ";";
            archivo << cliente.datosBasicos.fechaNacimiento.anio;
            archivo << ";";
            archivo << cliente.datosBasicos.edad;
            archivo << ";";
            archivo << cliente.datosBasicos.correoElectronico;
            archivo << ";";
            archivo << cliente.datosBasicos.sexo;
            archivo << ";";
            archivo << cliente.datosBasicos.estatura;
            archivo << ";";
            archivo << cliente.datosBasicos.telefono<<endl;
        }
        archivo.close(); // Cierra el archivo cuando hayas terminado
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }

}

void guardarCuentas(vector<CLIENTE>& banco){
    ofstream archivoCuentas("cuentas.txt", ios::app);

    if (archivoCuentas.is_open()) {
        //for que recorre los clientes
        for(CLIENTE cliente : banco){
            // for que recorre las cuentas del cliente
            for(CUENTA cuenta : cliente.cuentas)
            {
                archivoCuentas << cuenta.codCuenta;
                archivoCuentas << ";";
                archivoCuentas << cuenta.numeroCuenta;
                archivoCuentas << ";";
                archivoCuentas << cuenta.cupo;
                archivoCuentas << ";";
                archivoCuentas << cuenta.saldo;
                archivoCuentas << ";";
                archivoCuentas << cuenta.disponible;
                archivoCuentas << ";";
                archivoCuentas << cuenta.estado.cod;
                archivoCuentas << ";";
                archivoCuentas << cuenta.estado.descripcion;
                archivoCuentas << ";";
                archivoCuentas << cuenta.plazo.dia_plazo;
                archivoCuentas << ";";
                archivoCuentas << cuenta.plazo.mes_plazo;
                archivoCuentas << ";";
                archivoCuentas << cuenta.plazo.anio_plazo;
                archivoCuentas << ";";
                archivoCuentas << cuenta.fechaCreacion.dia_creacion_cuenta;
                archivoCuentas << ";";
                archivoCuentas << cuenta.fechaCreacion.mes_creacion_cuenta;
                archivoCuentas << ";";
                archivoCuentas << cuenta.fechaCreacion.anio_creacion_cuenta<<endl;
            }
        }
        archivoCuentas.close(); // Cierra el archivo cuando hayas terminado
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }

}

void guardarProductos(vector<CLIENTE>& banco){
    ofstream archivoProductos("productos.txt", ios::app);

    if (archivoProductos.is_open()) {
        //for que recorre los clientes
        for(CLIENTE cliente : banco){
            // for que recorre los productos del cliente
            for(PRODUCTO producto : cliente.productos)
            {
                archivoProductos << producto.cedula;
                archivoProductos << ";";
                archivoProductos << producto.numeroCuenta<<endl;
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

void guardarDatos(vector<CLIENTE>& banco){
    guardarPersonas(banco);
    guardarCuentas(banco);
    guardarProductos(banco);
}


//Verifica si un cliente tiene un tipo de cuenta en especifico
bool verificarTipoCuentaCliente(vector<TIPO_DE_CUENTA> tipoCuentas, string codigoCuenta){
   for(TIPO_DE_CUENTA tipoCuenta : tipoCuentas){
        if(tipoCuenta.codigo == codigoCuenta){
            return true;
        }
    }
    return false;

}

//Busca a un cliente por cedula o por numero de cuenta
CLIENTE& obtenerCliente(vector<CLIENTE>& banco, string cedula="", string numeroCuenta=""){
    CLIENTE clienteNulo;
    for(CLIENTE& cliente: banco)
    {   if(cedula != "")
        {
            if(cliente.datosBasicos.cedula == cedula){
                return cliente;
            }
        }else {
            for(CUENTA cuenta : cliente.cuentas)
            {   
                if(cuenta.numeroCuenta == numeroCuenta){
                    return cliente;
                }
            }
        }
    }
    return clienteNulo;
}

//Busca la cuenta de un cliente por numero de cuenta
CUENTA& obtenerCuenta(vector<CUENTA>& cuentas, string numeroCuenta){
    CUENTA cuentaNula;
    for(CUENTA& cuenta : cuentas){
        if(cuenta.numeroCuenta == numeroCuenta){
            return cuenta;
        }
    }

    return cuentaNula;
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

//TIPO DE CUENTA
// Función para crear un tipo de cuenta
void crearTipoCuenta(vector<CLIENTE>& banco){
   system("cls");  // Limpia la pantalla 
    int codigo;
    string cedulaPersona;
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

    CLIENTE& cliente = obtenerCliente(banco, cedulaPersona);
    if(cliente.datosBasicos.cedula == ""){
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
        //inserta un tipo de cuenta para el cliente
        cliente.tipoCuentas.push_back(tipo_de_cuenta);
    }
    getch();

}

//PERSONA
// Función para crear datos básicos de una persona e ingresar
void crearPersona(vector<CLIENTE>& banco){
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
    cin >> cliente.datosBasicos.fechaNacimiento.dia;
    cin >> cliente.datosBasicos.fechaNacimiento.mes;
    cin >> cliente.datosBasicos.fechaNacimiento.anio;
    cout << "Su fecha ha sido registrada como: " <<cliente.datosBasicos.fechaNacimiento.dia << "/" << cliente.datosBasicos.fechaNacimiento.mes << "/" << cliente.datosBasicos.fechaNacimiento.anio <<endl;
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
    //inserta el cliente
    banco.push_back(cliente);
    getch();
}

void actualizarDatosPersona(vector<CLIENTE>& banco)
{
    system("cls");
    string cedulaPersona;
    CLIENTE& cliente = obtenerCliente(banco, cedulaPersona);
    cout << "Digite la cedula de la cuenta que desea actualizar: " << endl;
    cin>>cedulaPersona;
    if(cliente.datosBasicos.cedula == ""){
        cout << "La persona no se encuentra registrada."<<endl;
        getch();
    }else
    {
        cout << "\n==========================================" << endl;
        cout <<"Persona (datos basicos)"<<endl;
        cout << "==========================================" << endl;
        cout << "Actualizar el nombre: ";
        cin >> cliente.datosBasicos.nombre;
        cout << "Actualizar el apellido: ";
        cin >> cliente.datosBasicos.apellido;
        cout << "Actualizar la cedula: ";
        cin >> cliente.datosBasicos.cedula;
        cout << "Actualizar la fecha de nacimiento (DD MM AAAA): " <<endl;
        cin >> cliente.datosBasicos.fechaNacimiento.dia;
        cin >> cliente.datosBasicos.fechaNacimiento.mes;
        cin >> cliente.datosBasicos.fechaNacimiento.anio;
        cout << "Su fecha ha sido registrada como: " <<cliente.datosBasicos.fechaNacimiento.dia << "/" << cliente.datosBasicos.fechaNacimiento.mes << "/" << cliente.datosBasicos.fechaNacimiento.anio <<endl;
        cout << "Actualizar la edad: ";
        cin >> cliente.datosBasicos.edad;
        cout << "Actualizar el correo electronico: ";
        cin >> cliente.datosBasicos.correoElectronico;
        cout << "Actualizar el sexo (M para masculino, F para femenino): ";
        cin >> cliente.datosBasicos.sexo;
        cout << "Actualizar la estatura (Metros): ";
        cin >> cliente.datosBasicos.estatura;
        cout << "Actualizar el telefono: ";
        cin >> cliente.datosBasicos.telefono;
        //inserta el cliente
        banco.push_back(cliente);
        getch();   
    }
}

//Obtiene la fecha actual
FECHACREACION obtenerFechaActual()
{ 
    // Obtener la fecha actual
    time_t now = time(0);
    tm *ltm = localtime(&now);
    FECHACREACION fechaCreacion;
    // Asignar la fecha actual a la estructura FECHACREACION
    fechaCreacion.dia_creacion_cuenta = ltm->tm_mday;
    fechaCreacion.mes_creacion_cuenta = 1 + ltm->tm_mon;
    fechaCreacion.anio_creacion_cuenta = 1900 + ltm->tm_year;

    return fechaCreacion;

} 

//C   U   E   N   T   A
// Funcion para crear una cuenta
void crearCuenta(vector<CLIENTE>& banco){
    string cedulaPersona;
    bool existeCuenta;
    system("cls");  
    cout << "\n==========================================" << endl;
    cout << "Creando cuenta"<<endl;
    cout << "==========================================" << endl;
    cout << "Digite la cedula de la persona para crear la cuenta: ";
    cin >> cedulaPersona;
    cout <<endl;
    CLIENTE& cliente = obtenerCliente(banco, cedulaPersona);
    if(cliente.datosBasicos.cedula == ""){
        cout << "La persona no se encuentra registrada."<<endl;
        getch();
    } else {
        cout << "Digite el codigo de tipo de codigo cuenta: ";
        cin >> cuenta.codCuenta;
        existeCuenta = verificarTipoCuentaCliente(cliente.tipoCuentas, cuenta.codCuenta);
        if(!existeCuenta){
            cout << "La persona no tiene registrado ese tipo de cuenta"<<endl;
            getch();
        }else {

            cout <<endl;
            
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
            cuenta.fechaCreacion = obtenerFechaActual();
            cout << "La fecha de creacion fue exitosamente registrada como: " << cuenta.fechaCreacion.dia_creacion_cuenta << "/" << cuenta.fechaCreacion.mes_creacion_cuenta << "/" << cuenta.fechaCreacion.anio_creacion_cuenta<<endl;

            stringstream numeroCuentaStream;
            srand(time(NULL)); // Inicializar la semilla para obtener números realmente aleatorios
            int codigoTipoCuenta = stoi(cuenta.codCuenta); // Convertir el código de tipo de cuenta a entero
            long long  numeroAleatorio = rand() % 9000000 + 1000000; // Generar un número aleatorio de 10 dígitos
            string numeroCuentaStr = to_string(codigoTipoCuenta) + to_string(numeroAleatorio); // Concatenar el código de tipo de cuenta y el número aleatorio
            cuenta.numeroCuenta = numeroCuentaStr;

            cout << "\n El numero de cuenta generado es: " << cuenta.numeroCuenta << endl;
            cliente.cuentas.push_back(cuenta);
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

// funcion para hacer la asociacion de cedula con numero de cuenta
void crearProducto(vector<CLIENTE>& banco)
{
    string cedulaPersona;
    string numeroCuenta;
    system("cls");
     cout << "\n==========================================" << endl;
    cout << "Asociando producto"<<endl;
    cout << "==========================================" << endl;
    cout << "Digite la cedula de la persona: ";
    cin >> cedulaPersona;
    CLIENTE& cliente = obtenerCliente(banco, cedulaPersona);
    if(cliente.datosBasicos.cedula == ""){
        cout << "La persona no se encuentra registrada."<<endl;
        getch();
    } else 
    {
        cout << "Digite el numero de la cuenta: ";
        cin >> numeroCuenta;
        CUENTA& cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
        if(cuenta.numeroCuenta == ""){
            cout << "El numero de la cuenta no existe.";
            getch();
        }else 
        {
            cuenta.estado.cod = 'A';
            cuenta.estado.descripcion = "Activa";
            producto.cedula = cedulaPersona;
            producto.numeroCuenta = numeroCuenta;
            cliente.productos.push_back(producto);
            cout << "Para la cedula "<< cedulaPersona <<" esta asignado el producto "<< numeroCuenta <<endl;
            getch();
        }
    
    }
}

// Funcion para consultar saldo
void consultarSaldo(vector<CLIENTE> banco)
{
    system("cls");
    string numeroCuenta;
    cout << "\n==========================================" << endl;
    cout << "Consultar Saldo" << endl;
    cout << "==========================================" << endl; 
    cout << "Digite el número de cuenta: ";
    cin >> numeroCuenta;
    CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);
    if(cliente.datosBasicos.cedula == ""){
        cout << "El numero de cuenta no existe."<<endl;
        getch();
    }else {
        CUENTA cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
            // Mostrar saldo según el tipo de cuenta
        if (cuenta.codCuenta == "102") {
            // Cuenta corriente
            if (cuenta.saldo < 0) {
                cout << "No tiene saldo." << endl;
            } else {
                cout << "saldo: $" << cuenta.saldo + cuenta.cupo << endl;
            }
        } else if (cuenta.codCuenta == "103") {
            // Tarjeta de crédito
            cout << "saldo: $" << cuenta.cupo - cuenta.saldo << endl;
        } else if (cuenta.codCuenta == "101" || 
                    cuenta.codCuenta == "105" || 
                    cuenta.codCuenta == "106") {
            // Cuenta de Ahorros, Nequi, Fiducuenta
            cout << "saldo: $" << cuenta.disponible; // saldo es lo mismo que disponible
        }
        getch();   
    }
}        

// Funcion para consultar disponible
void consultarDisponible(vector<CLIENTE> banco) 
{
    string numeroCuenta;
    system("cls");
    cout << "\n==========================================" << endl;
    cout << "Consultar Disponible" << endl;
    cout << "==========================================" << endl;
    cout << "Digite el número de cuenta: ";
    cin >> numeroCuenta;

    CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);
    if(cliente.datosBasicos.cedula == ""){
        cout << "El numero de cuenta no existe."<<endl;
        getch();
    } else {
        CUENTA cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
        // Mostrar disponible según el tipo de cuenta
        if (cuenta.codCuenta == "101" || 
            cuenta.codCuenta == "105" || 
            cuenta.codCuenta == "106"){
            cout << "disponible: $" << cuenta.saldo; //disponible es lo mismo que saldo

            }
        if (cuenta.codCuenta == "102") {
            // Cuenta corriente
            if (cuenta.saldo < 0) {
                cout << "No tiene disponible." << endl;
            } else {
                cout << "Disponible: $" << cuenta.saldo + cuenta.cupo << endl;
            }
        } else if (cuenta.codCuenta == "103") {
            // Tarjeta de crédito
            cout << "Disponible: $" << cuenta.cupo - cuenta.saldo << endl;
        }
        getch();
    }

 }

//BLOQUE DE FUNCIONES ENCARGADAS DE CONSIGNAR 
//funcion que controla las consignaciones de cuenta corriente

// Funcion para consignar en cuenta de ahorros

void consignarCuentaTipoAhorro(vector<CLIENTE>& banco)
{
    system ("cls");
    float montoAbono;
    string numeroCuenta;
    
    cout << "Ingrese el numero de la cuenta: " << endl;
    cin >> numeroCuenta;

    CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);

    if(cliente.datosBasicos.cedula == "")
    {
        cout << "El numero de cuenta no existe." << endl;
        getch();
    } 
    else 
    {
        CUENTA& cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
        int saldoAnterior = cuenta.saldo;
        cout << "Ingrese el monto a abonar: ";
        cin >> montoAbono;

        if (cuenta.estado.descripcion == "Activa" || 
            cuenta.estado.descripcion == "Inactiva" || 
            cuenta.estado.descripcion == "Embargada")
        {
            if (cuenta.codCuenta == "101" || 
                cuenta.codCuenta == "105 "|| 
            cuenta.codCuenta == "106")
            {
                // Cuenta de Ahorro
                if (montoAbono > 0)
                {
                    // Aumenta el saldo con el monto abonado
                    cuenta.saldo += montoAbono;
                    cuenta.disponible= cuenta.saldo;

                    cout << "Abono exitoso. Nuevo saldo: $" << cuenta.saldo << endl;
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
        else if (cuenta.estado.descripcion == "Bloqueada" ||
                cuenta.estado.descripcion == "Eliminada") 
        {
            cout << "No puede abonar a una cuenta bloqueada o eliminada" << endl;
        }
        system("cls");
                    cout << "Abono exitoso."<< endl;
                    cout << "Usuario: " << cliente.datosBasicos.nombre << " " << cliente.datosBasicos.apellido<<endl;
                    cout << "Cedula: " << cliente.datosBasicos.cedula <<endl;
                    cout << "Numero de producto: " << cuenta.numeroCuenta<<endl;
                    cout << "Valor abonado: $" << montoAbono <<endl;
                    cout << "Saldo Anterior: $" << saldoAnterior <<endl;
                    cout << "Saldo actualizado: $" << cuenta.saldo <<endl;
                    cout << "Disponible: $" <<cuenta.disponible << endl;
        getch();
    }
}


void consignarCuentaCorriente(vector<CLIENTE> &banco) 
{
    float montoAbono;
    string cedula;
    string numeroCuenta;
    system("cls");
    cout << "Ingrese el numero de la cuenta: " <<endl;
    cin >> numeroCuenta;
    CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);
    if(cliente.datosBasicos.cedula == ""){
        cout << "El numero de cuenta no existe."<<endl;
        getch();
    } else {

        CUENTA& cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
        cout << "Ingrese el monto a abonar: ";
        cin >> montoAbono;
        int saldoAnterior = cuenta.saldo;
        if (cuenta.estado.descripcion == "Activa" ||
            cuenta.estado.descripcion == "Inactiva" ||
            cuenta.estado.descripcion == "Embargada") 
        {
            if (cuenta.codCuenta == "102")
            {
                // Cuenta Corriente
                if (montoAbono > 0) 
                {
                    if (cuenta.saldo >= 0) 
                    {
                        // Caso 1: Saldo positivo
                        cuenta.disponible += montoAbono;
                    } 
                    else 
                    {
                        // Caso 2: Saldo negativo
                        if (montoAbono >= abs(cuenta.saldo))
                        {
                            // Actualizar saldo y disponible
                           cuenta.saldo += montoAbono;
                            cuenta.disponible += montoAbono;
                        } 
                        else 
                        {
                            // Actualizar solo el saldo
                           cuenta.saldo += montoAbono;
                        }
                    }
                    system("cls");
                    cout << "Abono exitoso."<< endl;
                    cout << "Usuario: " << cliente.datosBasicos.nombre << " " << cliente.datosBasicos.apellido<<endl;
                    cout << "Cedula: " << cliente.datosBasicos.cedula <<endl;
                    cout << "Numero de producto: " << cuenta.numeroCuenta<<endl;
                    cout << "Valor abonado: $" << montoAbono <<endl;
                    cout << "Saldo Anterior: $" << saldoAnterior <<endl;
                    cout << "Saldo actualizado: $" << cuenta.saldo <<endl;
                    cout << "Disponible: $" <<cuenta.disponible << endl;
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
        else if (cuenta.estado.descripcion == "Bloqueada" ||
                cuenta.estado.descripcion == "Eliminada") 
        {
            cout << "No puede abonar a una cuenta bloqueada o eliminada" << endl;
        }
        getch();
    }
}


// funcion que controla la consignacion en tarjetas de credito
void consignarTarjetaDeCredito(vector<CLIENTE>& banco)
{   
    float montoAbono;
    string numeroCuenta;
    cout << "Ingrese el numero de la cuenta: " <<endl;
    cin >> numeroCuenta;
    CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);
    if(cliente.datosBasicos.cedula == ""){
        cout << "El numero de cuenta no existe."<<endl;
        getch();
    } else
     {
        CUENTA& cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
        int saldoAnterior = cuenta.saldo;
        cout << "Ingrese el monto a abonar: ";
        cin >> montoAbono;

        // Verificar si la cuenta está bloqueada
        if (cuenta.estado.descripcion == "Bloqueada") 
        {
            cout << "No puede abonar a una cuenta bloqueada." << endl;
        } 
        else 
        {
            if (cuenta.estado.descripcion == "Activa" ||
                cuenta.estado.descripcion == "Inactiva" ||
                cuenta.estado.descripcion == "Embargada") 
            {
                // Verificar el tipo de cuenta 
                if (cuenta.codCuenta == "103")
                {
                    // El saldo se actualiza restando al saldo actual el valor consignado
                    // y se aumenta el disponible más no el cupo. 
                    cuenta.saldo -= montoAbono;
                    cuenta.disponible += montoAbono;
                    system("cls");
                    cout << "Abono exitoso."<< endl;
                    cout << "Usuario: " << cliente.datosBasicos.nombre << " " << cliente.datosBasicos.apellido<<endl;
                    cout << "Cedula: " << cliente.datosBasicos.cedula <<endl;
                    cout << "Numero de producto: " << cuenta.numeroCuenta<<endl;
                    cout << "Valor abonado: $" << montoAbono <<endl;
                    cout << "Saldo Anterior: $" << saldoAnterior <<endl;
                    cout << "Saldo actualizado: $" << cuenta.saldo <<endl;
                    cout << "Disponible: $" <<cuenta.disponible << endl;
                } 
                else 
                {
                    cout << "No se puede realizar la consignación. Tipo de cuenta no válido." << endl;
                }
            }
        }

        getch();
    }
}
//funcion para consignar prestamo
void consignarPrestamo(vector<CLIENTE>& banco)
{
    float montoAbono;
    string numeroCuenta;
    cout << "Ingrese el numero de la cuenta: " <<endl;
    cin >> numeroCuenta;
    CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);
    if(cliente.datosBasicos.cedula == ""){
        cout << "El numero de cuenta no existe."<<endl;
        getch();
    } else {
        CUENTA& cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
        int saldoAnterior = cuenta.saldo;
        cout << "Ingrese el monto a abonar: ";
        cin >> montoAbono;
        if (cuenta.estado.cod == 'A' ||
         cuenta.estado.cod == 'I' ||
         cuenta.estado.cod == 'E') 
        {
            if (cuenta.codCuenta == "104")
            {
                cuenta.saldo -= montoAbono;
                cout << "Consignación realizada con éxito." << endl;
                cout << "Saldo del prestamo actual: " << cuenta.saldo << endl;
            }
        
        }
        system("cls");
                    cout << "Abono exitoso."<< endl;
                    cout << "Usuario: " << cliente.datosBasicos.nombre << " " << cliente.datosBasicos.apellido<<endl;
                    cout << "Cedula: " << cliente.datosBasicos.cedula <<endl;
                    cout << "Numero de producto: " << cuenta.numeroCuenta<<endl;
                    cout << "Valor abonado: $" << montoAbono <<endl;
                    cout << "Saldo Anterior: $" << saldoAnterior <<endl;
                    cout << "Saldo actualizado: $" << cuenta.saldo <<endl;
                    cout << "Disponible: $" <<cuenta.disponible << endl;
        getch();
    }
}

void consignarCdt(vector<CLIENTE>& banco) 
{
    // string numeroCuenta;
    // int montoAbono;
    // cout << "Ingrese su numero de cuenta: ";
    // cin >> numeroCuenta;
    // CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);
    // if(cliente.datosBasicos.cedula == ""){
    //     cout << "El numero de cuenta no existe."<<endl;
    //     getch();
    // } else {
    //     CUENTA cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
    //     cout << "Ingrese el valor a consignar :" << endl;
    //     cin >> montoAbono;

    // if (cuenta.estado.descripcion == "Activa" || 
    //     cuenta.estado.descripcion == "Inactiva" || 
    //     cuenta.estado.descripcion == "Embargada")
    //     {
    //         // CDT
    //         if (cuenta.plazo.dia_plazo > 0 && 
    //         cuenta.plazo.mes_plazo > 0 && 
    //         cuenta.plazo.anio_plazo > 0)
    //         {
    //             if (obtenerFechaActual())
    //             {
    //                 if (montoAbono > 0)
    //                 {
    //                     // Calcula los intereses según el plazo
    //                     float intereses = 0.0;
    //                     if (cuenta.plazo.dia_plazo == 30) 
    //                     {
    //                         intereses = montoAbono * 0.03;
    //                     } 
    //                     else if (cuenta.plazo.dia_plazo == 60) 
    //                     {
    //                         intereses = montoAbono * 0.05;
    //                     } 
    //                     else if (cuenta.plazo.dia_plazo == 90)
    //                     {
    //                         intereses = montoAbono * 0.07;
    //                     } 
    //                     else if (cuenta.plazo.dia_plazo == 180) 
    //                     {
    //                         intereses = montoAbono * 0.09;
    //                     } 
    //                     else if (cuenta.plazo.dia_plazo == 365) 
    //                     {
    //                         intereses = montoAbono * 0.15;
    //                     }

    //                     // Actualiza el saldo con los intereses
    //                    cuenta.saldo += montoAbono + intereses;
    //                     cout << "Abono exitoso. Nuevo saldo: $" << cuenta.saldo << endl;
    //                 }
    //                 else
    //                 {
    //                     cout << "El monto a abonar debe ser mayor que cero." << endl;
    //                 }
    //             }
    //             else
    //             {
    //                 cout << "No puede abonar a una cuenta con fecha de creación futura" << endl;
    //             }
    //         }
    //         else
    //         {
    //             cout << "El plazo debe ser mayor que cero." << endl;
    //         }
    //     } 
    //     else if (cuenta.estado.descripcion == "Bloqueada" ||
    //     cuenta.estado.descripcion == "Eliminada") 
    //     {
    //         cout << "No puede abonar a una cuenta bloqueada o eliminada" << endl;
    //     }
    //     getch();
    // }
}

//BLOQUE DE FUNCIONES DE RETIROS
void retiroCuentasTipoAhorro(vector<CLIENTE>& banco) 
{   
    string numeroCuenta;
    int valorRetiro;
    cout << "Ingrese su numero de cuenta: ";
    cin >> numeroCuenta;
    CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);
    if(cliente.datosBasicos.cedula == ""){
        cout << "El numero de cuenta no existe."<<endl;
        getch();
    }else {

        CUENTA cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
        int saldoAnterior= cuenta.saldo;
        cout << "Ingrese el valor  a retirar :" << endl;
        cin >> valorRetiro;
        if ((cuenta.codCuenta == "101" || 
            cuenta.codCuenta== "106" || 
            cuenta.codCuenta== "105")) 
        {
            // Verificar que el valor a retirar no sea mayor que el saldo o disponible
            if (valorRetiro <= cuenta.saldo || valorRetiro <= cuenta.disponible) 
            {
                // Realizar el retiro
                cuenta.saldo -= valorRetiro;
                cuenta.disponible -= valorRetiro;

                cout << "Retiro exitoso. Nuevo saldo: " << cuenta.saldo << endl;
            } else 
            {
            cout << "Error: El monto a retirar es mayor que el saldo o disponible." << endl;
            }
        }
        system("cls");
                    cout << "Abono exitoso."<< endl;
                    cout << "Usuario: " << cliente.datosBasicos.nombre << " " << cliente.datosBasicos.apellido<<endl;
                    cout << "Cedula: " << cliente.datosBasicos.cedula <<endl;
                    cout << "Numero de producto: " << cuenta.numeroCuenta<<endl;
                    cout << "Valor Retirado: $" << valorRetiro <<endl;
                    cout << "Saldo Anterior: $" << saldoAnterior <<endl;
                    cout << "Saldo actualizado: $" << cuenta.saldo <<endl;
                    cout << "Disponible: $" <<cuenta.disponible << endl;
        getch();    
    }
    
}

// Función para realizar retiro en cuenta corriente
void realizarRetiroCuentaCorriente(vector<CLIENTE>& banco) 
{
    string numeroCuenta;
    int valorRetiro;
    cout << "Ingrese su numero de cuenta: ";
    cin >> numeroCuenta;
    CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);
    if(cliente.datosBasicos.cedula == ""){
        cout << "El numero de cuenta no existe."<<endl;
        getch();
    } else {
        CUENTA cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
        int saldoAnterior= cuenta.saldo;
        cout << "Ingrese el valor a retirar: " << endl;
        cin >> valorRetiro;
        // 1. Si tiene saldo cero (0)
        if (cuenta.saldo == 0) 
        {
            cuenta.saldo -= valorRetiro;
            cuenta.disponible = cuenta.cupo - valorRetiro;
            cout << "Retiro exitoso. Nuevo saldo: " << cuenta.saldo << ", Nuevo disponible: " << cuenta.disponible << endl;
        } 
        // 2. Si tiene saldo > 0
        else if (cuenta.saldo > 0) 
        {
            // Caso 2.1: El valor a retirar es mayor que el saldo actual
            if (valorRetiro > cuenta.saldo) 
            {
                cuenta.saldo -= valorRetiro;
                cuenta.disponible = cuenta.cupo - valorRetiro;
                cout << "Retiro exitoso. Nuevo saldo: " << cuenta.saldo << ", Nuevo disponible: " << cuenta.disponible << endl;
            } 
            // Caso 2.2: El valor a retirar es menor que el saldo actual
            else 
            {
                cuenta.saldo -= valorRetiro;
                cout << "Retiro exitoso. Nuevo saldo: " << cuenta.saldo << ", Nuevo disponible: " << cuenta.disponible << endl;
            }
        } 
        // 3. Si tiene saldo < 0 (saldo negativo)
        else
        {
            cuenta.saldo -= valorRetiro;
            if (cuenta.saldo < -cuenta.cupo) 
            {
                cout << "Error: Saldo negativo excede el límite del cupo." << endl;
                // Revertir el cambio en el saldo
                cuenta.saldo += valorRetiro;
            } else 
            {
                cuenta.disponible = cuenta.cupo + cuenta.saldo;
                cout << "Retiro exitoso. Nuevo saldo: " << cuenta.saldo << ", Nuevo disponible: " << cuenta.disponible << endl;
            }

            system("cls");
            cout << "Abono exitoso."<< endl;
            cout << "Usuario: " << cliente.datosBasicos.nombre << " " << cliente.datosBasicos.apellido << endl;
            cout << "Cedula: " << cliente.datosBasicos.cedula << endl;
            cout << "Numero de producto: " << cuenta.numeroCuenta << endl;
            cout << "Valor Retirado: $" << valorRetiro << endl;
            cout << "Saldo Anterior: $" << saldoAnterior << endl;

            if (cuenta.saldo < 0) {
                cout << "Saldo actualizado: $" << cuenta.saldo << " (Saldo en rojo)" << endl;
                cout << "Disponible: $" << cuenta.disponible;

                // Mostrar información de sobregiro
                if (cuenta.saldo < -cuenta.cupo) {
                    cout << " (Sobregiro excede el límite del cupo)" << endl;
                } else {
                    cout << " (Sobregiro dentro del límite del cupo)" << endl;
                }
            } else {
                cout << "Saldo actualizado: $" << cuenta.saldo << endl;
                cout << "Disponible: $" << cuenta.disponible << endl;
            }
        }
        getch();
    }
}


//Funcion para hacer retiro de tarjeta de credito
void retiroTarjetaDeCredito(vector<CLIENTE>& banco) 
{
    string numeroCuenta;
    int valorRetiro;
    cout << "Ingrese su numero de cuenta: ";
    cin >> numeroCuenta;
    CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);
    if(cliente.datosBasicos.cedula == ""){
        cout << "El numero de cuenta no existe."<<endl;
        getch();
    } else {
        CUENTA cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
        int saldoAnterior= cuenta.saldo;
        cout << "Ingrese el valor  a retirar :" << endl;
        cin >> valorRetiro;

        // Verificar que el monto de retiro no sea mayor al disponible
        if (valorRetiro > cuenta.disponible) {
            cout << "Error: El monto de retiro supera el disponible de la cuenta." << endl;
        }

        // Actualizar el saldo y el disponible
        cuenta.saldo += valorRetiro;
        cuenta.disponible -= valorRetiro;

        // SALIDA
        system("cls");
                    cout << "Abono exitoso."<< endl;
                    cout << "Usuario: " << cliente.datosBasicos.nombre << " " << cliente.datosBasicos.apellido<<endl;
                    cout << "Cedula: " << cliente.datosBasicos.cedula <<endl;
                    cout << "Numero de producto: " << cuenta.numeroCuenta<<endl;
                    cout << "Valor Retirado: $" << valorRetiro <<endl;
                    cout << "Saldo Anterior: $" << saldoAnterior <<endl;
                    cout << "Saldo actualizado: $" << cuenta.saldo <<endl;
                    cout << "Disponible: $" <<cuenta.disponible << endl;
        getch();
    }
}


// Función para realizar transferencias entre cuentas
void transferencia(vector<CLIENTE>& banco) 
{   
    system("cls");
    int montoTransferencia;
    string numeroCuentaOrigen;
    string numeroCuentaDestino;

    cout << "Digite el numero de la cuenta: ";
    cin >> numeroCuentaOrigen;
    CLIENTE& clienteOrigen = obtenerCliente(banco, "", numeroCuentaOrigen);
    if(clienteOrigen.datosBasicos.cedula == ""){
        cout << "El numero de cuenta no existe."<<endl;
        getch();
    }else {
        cout << "Digite el numero de la cuenta a transferir: ";
        cin >> numeroCuentaDestino;
        CLIENTE clienteDestino = obtenerCliente(banco, "", numeroCuentaDestino);
        if(clienteDestino.datosBasicos.cedula == ""){
            cout << "El numero de cuenta no existe."<<endl;
            getch();
        } else {
            CUENTA cuentaOrigen = obtenerCuenta(clienteOrigen.cuentas, numeroCuentaOrigen);
            CUENTA cuentaDestino = obtenerCuenta(clienteDestino.cuentas, numeroCuentaOrigen);
            // Solicitar el monto a transferir
            cout << "Ingrese el monto a transferir: ";
            cin >> montoTransferencia;

            // Verificar si la cuenta de origen es un préstamo o CDT
            if (cuentaOrigen.codCuenta == "104" || cuentaOrigen.codCuenta == "107") {
                cout << "Error: No se puede transferir desde un préstamo ni de un CDT." << endl;
                return;
            }

            // Verificar si la cuenta de destino es un préstamo o CDT
            if (cuentaDestino.codCuenta == "104" || cuentaDestino.codCuenta == "107") {
                cout << "Error: No se puede transferir a un préstamo ni a un CDT." << endl;
                return;
            }

            // Realizar la transferencia
            // Verificar que el monto de transferencia no sea mayor que el saldo o disponible de la cuenta de origen
            if (montoTransferencia > cuentaOrigen.saldo ||
                montoTransferencia > cuentaOrigen.disponible) {
                cout << "Error: El monto a transferir es mayor que el saldo o disponible de la cuenta de origen." << endl;
                getch();
            } else {
                // Realizar la transferencia
               cuentaOrigen.saldo -= montoTransferencia;
               cuentaDestino.saldo  += montoTransferencia;
         
            system("cls");
            cout << "Transferencia exitosa." << endl;
            cout << "Cuenta de origen:" << endl;
            cout << "Usuario: " << cliente.datosBasicos.nombre << " " << cliente.datosBasicos.apellido << endl;
            cout << "Cedula: " << clienteOrigen.datosBasicos.cedula << endl;
            cout << "Numero de producto: " << cuentaOrigen.numeroCuenta << endl;
            cout << "Saldo actualizado de la cuenta de origen: $" << cuentaOrigen.saldo << endl;

            cout << "Cuenta de destino:" << endl;
            cout << "Usuario: " << cliente.datosBasicos.nombre << " " << cliente.datosBasicos.apellido << endl;
            cout << "Cedula: " << clienteDestino.datosBasicos.cedula << endl;
            cout << "Numero de producto: " << cuentaDestino.numeroCuenta << endl;
            cout << "Saldo actualizado de la cuenta de destino: $" << cuentaDestino.saldo << endl;

            cout << "Valor transferido: $" << montoTransferencia << endl;
            getch();
            }
        }

    }

}

//BLOQUE DE FUNCIONES PARA CANCELAR CUENTA
// Función para realizar un retiro de una cuenta
void realizarRetiro(CUENTA &cuenta) {
        system("cls");
        // Verificar que la cuenta es de tipo Ahorros, CDT, Fiducuenta o Nequi
        if (cuenta.codCuenta == "101" || cuenta.codCuenta == "106" || cuenta.codCuenta == "107" || cuenta.codCuenta == "105") {
            int saldo = cuenta.saldo;
           cuenta.saldo = 0;  // Retirar el saldo
            cout << "Se realizó un retiro de $" << saldo << " por la cancelación de la cuenta." << endl;
        } else {
            cout << "La operación de retiro solo es válida para cuentas de tipo Ahorros, CDT, Fiducuenta o Nequi." << endl;
        }
}
// Función para realizar una consignación en una cuenta
void realizarConsignacion(CUENTA &cuenta) 
{       system("cls");
        int saldo = cuenta.saldo;
        cuenta.saldo = 0;  // Dejar el saldo en cero
        cout << "Se realizó una consignación de $" << saldo << " por la cancelación de la cuenta corriente." << endl;
        getch();
}

// Función para pagar el saldo y cancelar productos asociados a la cuenta
void pagarSaldoYCancelarProductos(CUENTA &cuenta, CLIENTE &cliente) 
{   
    system("cls");
    int saldo = cuenta.saldo;

    // Pagar (consignar) el saldo
    cuenta.saldo = 0;
    cout << "Se realizó el pago (consignación) de $" << saldo << " por la cancelación de la cuenta." << endl;

    // Cancelar productos asociados a la cuenta
    for (PRODUCTO producto : cliente.productos)
     {
        if (producto.numeroCuenta == cuenta.numeroCuenta)
        {
            producto = PRODUCTO();  // Limpiar el producto
        }
    }

    cout << "Los productos asociados a la cuenta han sido cancelados." << endl;
    getch();
}

// Función para emitir un paz y salvo al cliente
void emitirPazYSalvo(CLIENTE &cliente) 
{
    system("cls");  

    cout << "\n==============================" << endl;
    cout << "       Paz y Salvo" << endl;
    cout << "==============================" << endl;

    cout << "Cliente: " << cliente.datosBasicos.nombre << " " << cliente.datosBasicos.apellido << endl;
    cout << "Cedula: " << cliente.datosBasicos.cedula << endl;

    cout << "\nEstado de cuentas:" << endl;
    for (CUENTA cuenta : cliente.cuentas) {
        if (cuenta.estado.cod != 'I') 
        {
            cout << "Cuenta: " << cuenta.numeroCuenta << " - Estado: " << cuenta.estado.descripcion << endl;
        }
    }

    cout << "\nProductos cancelados:" << endl;
    for (PRODUCTO producto : cliente.productos) {
        if (producto.cedula != "-1") {
            cout << "Producto: " << producto.numeroCuenta << " - Cancelado" << endl;
        }
    }

    cout << "\n==============================" << endl;

    cout << "\nSe ha emitido un paz y salvo al cliente." << endl;
    getch(); 
}

// Función para cancelar una cuenta
void cancelarCuenta(vector<CLIENTE>& banco) 
{   system("cls");
    string numeroCuenta;
    cout << "Ingrese el numero de la cuenta: ";
    cin >> numeroCuenta;
     CLIENTE& cliente = obtenerCliente(banco, "", numeroCuenta);
    if(cliente.datosBasicos.cedula == ""){
        cout << "El numero de cuenta no existe."<<endl;
        getch();
    } else {
        CUENTA cuenta = obtenerCuenta(cliente.cuentas, numeroCuenta);
        // Verificamos el saldo
        if(cuenta.saldo != 0){
             // Verificar el tipo de cuenta
            if (cuenta.codCuenta == "103" || cuenta.codCuenta == "104") 
            {
                pagarSaldoYCancelarProductos(cuenta, cliente);
    
            } else if (cuenta.codCuenta == "102") 
            {
                 if (cuenta.saldo > 0) 
                {
                    realizarRetiro(cuenta);
                } else if (cuenta.saldo < 0) 
                {
                    realizarConsignacion(cuenta);
                }
            }

        }else {

            cuenta.estado.cod = 'C';
            cuenta.estado.descripcion = "Cancelada";

            cout << "La cuenta ha sido cancelada." << endl;

            // Emitir un paz y salvo
            emitirPazYSalvo(cliente);
        }

        // Cambiar el estado a 'C' (Cancelado)
    }
    getch();
}

//MENU DE FUNCIONES DE CONSIGNACION/RETIRO/TRANSFERENCIA/CANCELAR
void menuTransacciones(vector<CLIENTE>& banco) 
{
    int opcionPrincipal = -3;

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
                            consignarCuentaTipoAhorro(banco);
                            break;

                        case 102:
                            consignarCuentaCorriente(banco);
                            break;

                        case 103:
                            consignarTarjetaDeCredito(banco);
                            break;

                        case 104:
                            consignarPrestamo(banco);
                            break;

                        case 105:
                            consignarCuentaTipoAhorro(banco);
                            break;

                        case 106:
                            consignarCuentaTipoAhorro(banco);
                            break;

                        case 107:
                            cout << "que mas pues mijo";
                            getch();
                            // consignarCdt(banco);
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
                            retiroCuentasTipoAhorro(banco);
                            break;

                        case 102:
                             realizarRetiroCuentaCorriente(banco);
                            break;

                        case 103:
                             retiroTarjetaDeCredito(banco);
                            break;

                        case 104:
                           retiroCuentasTipoAhorro(banco);
                            break;

                        case 105:
                            retiroCuentasTipoAhorro(banco);
                            break;

                        case 106:
                            retiroCuentasTipoAhorro(banco);
                            break;

                        case 107:
                            retiroCuentasTipoAhorro(banco);
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
            transferencia(banco);
            break;
            case 4:
            cancelarCuenta(banco);
            break;
            case 5:
                opcionPrincipal = 0;
                break;

            default:
                break;
        }
    } while (opcionPrincipal != 0);
    getch();
}


//banco y cedula
//pedir datos
//se pone mismas variables



int main()
{
	// Arreglo de CLIENTE para almacenar múltiples clientes
    vector<CLIENTE> banco; 
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
                crearTipoCuenta(banco);
                break;
            case 2:
                crearPersona(banco);
                break;
            case 3:
                crearCuenta(banco);
                break;
            case 4:
                crearProducto(banco);
                break;
            case 5:
                consultarSaldo(banco);
                break;
            case 6:
                consultarDisponible(banco);
                break;
            case 7:
                menuTransacciones(banco);
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
    guardarDatos(banco);
    return 0;
}

