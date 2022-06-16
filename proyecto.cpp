#include<iostream>
#include<fstream>
#include<sstream>
using namespace::std;
#include<bits/stdc++.h>
#include<windows.h>

//declaracion de prototipos de metodos
void crear_usuario();
void listado_general();
void menu(const string);
void menu_usuario(const string);
void buscar_x_num_id();
void buscar_x_ciudad();
void buscar_x_ciudad_estado();
int getFrecuencia(string);
void modificar();
void eliminar();
void listado_general_web();
void crear_nota(const string);
void listado_nota_web();
void modificarNota(const string, int);
void eliminarNota(const string, int);
void modificarNotaAdm(const string, int);


//implementacion de metodos
void crear_usuario(){
    ofstream archivo("usuario.csv", ios::app);
    if(!archivo){
        cout<<"Error al crear el archivo 'usuario.csv'"<<endl;
    }else{
        long num_id;
        string ape, nom, ciudad, correo;
        int estado = 0;
        cout<<"Ingrese el numero de ID: ";
        cin>>num_id;
        if(getFrecuencia(to_string(num_id)) == 0){
            fflush(stdin);//limpiar el buffer de lectura
            cout<<"Ingrese el apellido: ";
            getline(cin, ape);
            cout<<"Ingrese el nombre: ";
            getline(cin, nom);
            cout<<"Ingrese la ciudad de residencia: ";
            getline(cin, ciudad);
            cout<<"Ingrese el correo electronico: ";
            getline(cin, correo);

            archivo<<num_id<<";"<<ape<<";"<<nom<<";"<<ciudad<<";"<<correo<<";"<<estado<<endl;
            archivo.close();

            cout<<"Se ingreso con exito el usuario"<<endl<<endl;
        }else cout<<"El cliente con numero de ID "<<num_id<<" ya existe en el archivo"<<endl<<endl;
    }
}

int getFrecuencia(string num_id_buscar){
    int cont = 0;
    ifstream archivo("usuario.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'usuario.csv'"<<endl<<endl;
    }else{
        string registro;
        string num_id, ape, nom, ciudad, correo, estado;

        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline(token, num_id, ';');
            getline(token, ape, ';');
            getline(token, nom, ';');
            getline(token, ciudad, ';');
            getline(token, correo, ';');
            getline(token, estado, ';');

            if(num_id_buscar.compare(num_id) == 0) cont++;
        }//fin del while
        archivo.close();
    }
    return cont;
}

void listado_general(){
    ifstream archivo("usuario.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'usuario.csv'"<<endl<<endl;
    }else{
        string registro;
        string num_id, ape, nom, ciudad, correo, estado;
        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline(token, num_id, ';');
            getline(token, ape, ';');
            getline(token, nom, ';');
            getline(token, ciudad, ';');
            getline(token, correo, ';');
            getline(token, estado, ';');

            cout<<"id:"<<num_id<<endl;
            cout<<"Nombre:"<<ape<<" "<<nom<<endl;
            cout<<"ciudad:"<<ciudad<<"   correo:"<<correo<<endl;
            cout<<"ADM:"<<estado<<endl<<endl;
        }
        archivo.close();
    }
}

void listado_general_web(){
    ifstream archivo("usuario.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'usuario.csv'"<<endl<<endl;
    }else{
        ofstream web("listado_general_web.html");
        web<<"<html><head><title>Listado general del usuario</title><link rel=\"stylesheet\" href=\"mi_estilo.css\"></head><body>"<<endl;
        web<<"<div align=center>"<<endl;
        web<<"<h2>Listado general del usuario</h2><br>"<<endl;
        web<<"<table>"<<endl;
        web<<"<tr>"<<endl;
        web<<"<th>Numero de ID</th>"<<endl;
        web<<"<th>Apellido</th>"<<endl;
        web<<"<th>Nombre</th>"<<endl;
        web<<"<th>Ciudad</th>"<<endl;
        web<<"<th>Correo</th>"<<endl;
        web<<"<th>Estado</th>"<<endl;
        web<<"</tr>"<<endl;

        string registro;
        string num_id, ape, nom, ciudad, correo, estado;
        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline(token, num_id, ';');
            getline(token, ape, ';');
            getline(token, nom, ';');
            getline(token, ciudad, ';');
            getline(token, correo, ';');
            getline(token, estado, ';');

            if(estado.compare("1") == 0) web<<"<tr class=adm>"<<endl;
            else web<<"<tr class=no_adm>"<<endl;

            web<<"<td>"<<num_id<<"</td>"<<endl;
            web<<"<td>"<<ape<<"</td>"<<endl;
            web<<"<td>"<<nom<<"</td>"<<endl;
            web<<"<td>"<<ciudad<<"</td>"<<endl;
            web<<"<td>"<<correo<<"</td>"<<endl;
            if(estado.compare("1") == 0) web<<"<td>adm</td>"<<endl;
            else web<<"<td>No adm</td>"<<endl;
            web<<"</tr>"<<endl;
        }
        archivo.close();
        web<<"</table></body></div></html>"<<endl;
        web.close();
        cout<<"Se creo con exito la pagina web"<<endl;
        cout<<"Desea visualizar la pagina web? [1 -> Si o 0 -> No]: ";
        int resp;
        cin>>resp;
        if(resp == 1)
            ShellExecute(GetDesktopWindow(),//ventana donde se muestra el documento
                  "open", //operacion
                  "listado_general_web.html", //ruta y nombre del documento
                  NULL, //se abrira un documento
                  NULL, //directorio actual
                  SW_SHOWNORMAL); //activa y muestra una ventana
    }
}

void buscar_x_num_id(){
    ifstream archivo("usuario.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'usuario.csv'"<<endl<<endl;
    }else{
        string registro;
        string num_id, ape, nom, ciudad, correo, estado;
        string numid_buscar;
        cout<<"Ingrese el numero de ID a buscar: ";
        cin>>numid_buscar;
        bool existe = false;

        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline(token, num_id, ';');
            getline(token, ape, ';');
            getline(token, nom, ';');
            getline(token, ciudad, ';');
            getline(token, correo, ';');
            getline(token, estado, ';');

            if(numid_buscar.compare(num_id) == 0){
                existe = true;
                cout<<num_id<<endl;
                cout<<ape<<" "<<nom<<endl;
                cout<<ciudad<<" "<<correo<<endl;
                cout<<estado<<endl<<endl;
            }
        }//fin del while
        archivo.close();
        if(!existe){//if(existe == false)
            cout<<"El cliente con numero de ID "<<numid_buscar<<" no existe en el archivo"<<endl<<endl;
        }
    }
}

void modificar(){
    ifstream archivo("usuario.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'usuario.csv'"<<endl<<endl;
    }else{
        vector<string> all_registros;
        string registro;
        string num_id, ape, nom, ciudad, correo, estado;
        string numid_buscar;
        cout<<"Ingrese el numero de ID a buscar: ";
        cin>>numid_buscar;
        bool existe = false, modifico = false;
        int opc = 0;

        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline(token, num_id, ';');
            getline(token, ape, ';');
            getline(token, nom, ';');
            getline(token, ciudad, ';');
            getline(token, correo, ';');
            getline(token, estado, ';');

            if(numid_buscar.compare(num_id) == 0){
                existe = true;
                cout<<"Datos actuales del cliente"<<endl;
                cout<<"Numero de ID = "<<num_id<<endl;
                cout<<"1. Apellido = "<<ape<<endl;
                cout<<"2. Nombre = "<<nom<<endl;
                cout<<"3. Ciudad = "<<ciudad<<endl;
                cout<<"4. Correo = "<<correo<<endl;
                cout<<"5. estado = "<<estado<<endl;
                cout<<"0. Ninguno"<<endl;
                do{
                    cout<<"Seleccione el campo a modificar: ";
                    cin>>opc;
                }while(opc < 0 || opc > 5);

                fflush(stdin);

                switch(opc){
                    case 1: modifico = true;
                            cout<<"Ingrese el nuevo apellido: ";
                            getline(cin, ape);
                            break;
                    case 2: modifico = true;
                            cout<<"Ingrese el nuevo nombre: ";
                            getline(cin, nom);
                            break;
                    case 3: modifico = true;
                            cout<<"Ingrese la nueva ciudad: ";
                            getline(cin, ciudad);
                            break;
                    case 4: modifico = true;
                            cout<<"Ingrese el nuevo correo: ";
                            getline(cin, correo);
                    case 5: modifico = true;
                            cout<<"Ingrese el nuevo estado: ";
                            getline(cin, estado);
                            break;
                    
                }
                all_registros.push_back(num_id + ";" + ape + ";" + nom + ";" + ciudad + ";" + correo + ";" + estado);
            }else all_registros.push_back(registro);
        }//fin del while

        archivo.close();

        if(existe){//if(existe == true)
            if(modifico){
                ofstream nuevo("usuario.csv");
                for(int i = 0; i < int(all_registros.size()); i++){
                    nuevo<<all_registros[i]<<endl;
                }
                nuevo.close();
                cout<<"Se modifico el cliente"<<endl<<endl;
            }
        }else{
            cout<<"El cliente con numero de ID "<<numid_buscar<<" no existe en el archivo"<<endl<<endl;
        }
    }
}

void eliminar(){
    ifstream archivo("usuario.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'usuario.csv'"<<endl<<endl;
    }else{
        vector<string> registros_no_eliminar;
        string registro;
        string num_id, ape, nom, ciudad, correo, estado;
        string numid_buscar;
        cout<<"Ingrese el numero de ID a eliminar: ";
        cin>>numid_buscar;
        bool existe = false;

        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline(token, num_id, ';');
            getline(token, ape, ';');
            getline(token, nom, ';');
            getline(token, ciudad, ';');
            getline(token, correo, ';');
            getline(token, estado, ';');

            if(numid_buscar.compare(num_id) == 0) existe = true;
            else registros_no_eliminar.push_back(registro);
        }//fin del while

        archivo.close();

        if(existe){//if(existe == true)
            ofstream nuevo("usuario.csv");
            for(int i = 0; i < int(registros_no_eliminar.size()); i++){
                nuevo<<registros_no_eliminar[i]<<endl;
            }
            nuevo.close();
            cout<<"Se elimino el cliente"<<endl<<endl;
        }else{
            cout<<"El cliente con numero de ID "<<numid_buscar<<" no existe en el archivo"<<endl<<endl;
        }
    }
}

void buscar_x_correo(){
    ifstream archivo("usuario.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'usuario.csv'"<<endl<<endl;
    }else{
        string registro;
        string num_id, ape, nom, ciudad, correo, estado;
        string buscar_correo;
        fflush(stdin);
        cout<<"Ingrese su correo: ";
        getline(cin, buscar_correo);
        bool existe = false;

        transform(buscar_correo.begin(), buscar_correo.end(),buscar_correo.begin(), ::toupper);//convertir buscar_correo a mayusculas. tolower

        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline(token, num_id, ';');
            getline(token, ape, ';');
            getline(token, nom, ';');
            getline(token, ciudad, ';');
            getline(token, correo, ';');
            getline(token, estado, ';');

            transform(correo.begin(), correo.end(),correo.begin(), ::toupper);

            if(buscar_correo.compare(correo) == 0){
                existe = true;
                if(estado.compare("1") == 0){
                    menu(buscar_correo);
                }else{
                    menu_usuario(buscar_correo);
                }
            }
        }//fin del while
        archivo.close();
        if(!existe){//if(existe == false)
            cout<<"No existe el usuario con ese correo "<<buscar_correo<<" en el archivo"<<endl<<endl;
        }
    }
}

void buscar_x_ciudad_estado(){
    ifstream archivo("usuario.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'usuario.csv'"<<endl<<endl;
    }else{
        string registro;
        string num_id, ape, nom, ciudad, correo, estado;
        string ciudad_buscar, estado_buscar;
        fflush(stdin);
        cout<<"Ingrese la ciudad a buscar: ";
        getline(cin, ciudad_buscar);
        cout<<"Ingrese el estado a buscar [1 = adm, 0 = No adm]: ";
        cin>>estado_buscar;
        bool existe = false;

        transform(ciudad_buscar.begin(), ciudad_buscar.end(),
                ciudad_buscar.begin(), ::toupper);//convertir ciudad_buscar a mayusculas. tolower

        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline(token, num_id, ';');
            getline(token, ape, ';');
            getline(token, nom, ';');
            getline(token, ciudad, ';');
            getline(token, correo, ';');
            getline(token, estado, ';');

            transform(ciudad.begin(), ciudad.end(),ciudad.begin(), ::toupper);

            if(ciudad_buscar.compare(ciudad) == 0 &&
                estado_buscar.compare(estado) == 0){
                existe = true;
                cout<<num_id<<endl;
                cout<<ape<<" "<<nom<<endl;
                cout<<ciudad<<" "<<correo<<endl;
                cout<<estado<<endl<<endl;
            }
        }//fin del while
        archivo.close();
        if(!existe){//if(existe == false)
            cout<<"No existen usuario con ciudad de residencia "<<ciudad_buscar<<
                "y estado "<<estado_buscar <<" en el archivo"<<endl<<endl;
        }
    }
}

void menu(const string correo){
    
    int estatus = 1;
    int opc;
    do{
        cout<<"Menu de opciones"<<endl;
        cout<<"1. Crear usuario"<<endl;
        cout<<"2. Listado general de usuario"<<endl;
        cout<<"3. Consultar x numero de ID"<<endl;
        cout<<"4. Consultar x ciudad de residencia"<<endl;
        cout<<"5. Consultar x ciudad de residencia y estado"<<endl;
        cout<<"6. Modificar usuario x numero de ID"<<endl;
        cout<<"7. Eliminar usuario x numero de ID"<<endl;
        cout<<"8. Listado general de usuario (Web)"<<endl;
        cout<<"9. crear nota"<<endl;
        cout<<"10. listar notas"<<endl;
        cout<<"11. modificar nota"<<endl;
        cout<<"12. eliminar nota"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Seleccione una opcion: ";
        cin>>opc;
        switch(opc){
            case 1: crear_usuario(); break;
            case 2: listado_general(); break;
            case 3: buscar_x_num_id(); break;
            case 4: buscar_x_ciudad(); break;
            case 5: buscar_x_ciudad_estado(); break;
            case 6: modificar(); break;
            case 7: eliminar(); break;
            case 8: listado_general_web(); break;
            case 9: crear_nota(correo); break;
            case 10: listado_nota_web(); break;
            case 11: modificarNotaAdm(correo,estatus); break;
            case 12: eliminarNota(correo,estatus); break;
            case 0: break;
            default: cout<<"Opcion incorrecta"<<endl<<endl;
        }
    }while(opc != 0);
}

void menu_usuario(const string correo){
    int estado = 0;
    int opc;
    do{
        cout<<"Menu de opciones"<<endl;
        cout<<"1. crear nota"<<endl;
        cout<<"2. listar notas"<<endl;
        cout<<"3. modificar nota"<<endl;
        cout<<"4. eliminar nota"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Seleccione una opcion: ";
        cin>>opc;
        switch(opc){
            case 1: crear_nota(correo); break;
            case 2: listado_nota_web(); break;
            case 3: modificarNota(correo,estado); break;
            case 4: eliminarNota(correo,estado); break;
            case 0: break;
            default: cout<<"Opcion incorrecta"<<endl<<endl;
        }
    }while(opc != 0);
}

int main(){
    int opc;
    do{
        cout<<"Menu de opciones"<<endl;
        cout<<"1. registrarse "<<endl;
        cout<<"2. iniciar sesion"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Seleccione una opcion: ";
        cin>>opc;
        switch(opc){
            case 1: crear_usuario(); break;
            case 2: buscar_x_correo(); break;
            case 0: break;
            default: cout<<"Opcion incorrecta"<<endl<<endl;
        }
    }while(opc != 0);
    return 0;
}

void crear_nota(const string correo){

    ofstream archivo("notas.csv", ios::app);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'notas.csv'"<<endl<<endl;
    }else{
        long nota_id;
        string nota, fecha, autor, titulo ;
        int aprovacion = 0;
        fflush(stdin);
        cout<<"Ingrese el titulo: ";
        getline(cin, titulo);
        cout<<"Ingrese la nota: ";
        getline(cin, nota);
        cout<<"Ingrese la fecha: ";
        getline(cin, fecha);
        autor = correo;
        cout<<"Ingrese el id: ";
        cin>>nota_id;
        archivo<<titulo<<";"<<nota<<";"<<fecha<<";"<<autor<<";"<<nota_id<<";"<<aprovacion <<endl;
        archivo.close();
    }
}
void listado_nota_web(){
    ifstream archivo("notas.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'usuario.csv'"<<endl<<endl;
    }else{
        ofstream web("listado_notas_web.html");
        web<<"<html><head><title>Listado general de las notas </title><link rel=\"stylesheet\" href=\"mi_estilo.css\"></head><body >"<<endl;
        web<<"<div align=center>"<<endl;
        web<<"<h2 class=titulo>Listado general de las notas </h2><br>"<<endl;
        web<<"</div>"<<endl;

        string registro;
        string nota_id,nota, fecha, autor, titulo,aprovacion ;
        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);
            getline (token, titulo, ';');
            getline (token, nota, ';');
            getline (token, fecha, ';');
            getline (token, autor, ';');
            getline (token, nota_id, ';');
            getline (token, aprovacion, ';');


            if(aprovacion.compare("1") == 0){ web<<"<div class=notas>"<<endl;
            //else web<<"<tr class=no_adm>"<<endl;
            web<<"<div class=titulo><h2>"<<titulo<<"</h2></div>"<<endl;
            web<<"<div class=autor><h4>"<<autor<<", fecha de publicacion"<<endl;
            web<<fecha<<"</h4></div>"<<endl;
            web<<"<div class=nota><h3>"<<nota<<"<h3></div>"<<endl;
            
            web<<"</div>"<<endl;
            }
        }
        archivo.close();
        web<<"</body></html>"<<endl;
        web.close();
        cout<<"Se creo con exito la pagina web"<<endl;
        cout<<"Desea visualizar la pagina web? [1 -> Si o 0 -> No]: ";
        int resp;
        cin>>resp;
        if(resp == 1)
            ShellExecute(GetDesktopWindow(),//ventana donde se muestra el documento
                  "open", //operacion
                  "listado_notas_web.html", //ruta y nombre del documento
                  NULL, //se abrira un documento
                  NULL, //directorio actual
                  SW_SHOWNORMAL); //activa y muestra una ventana
    }
}


void eliminarNota(const string correo, int estado){
    ifstream archivo("notas.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'notas.csv'"<<endl<<endl;
    }else{
        vector<string> registros_no_eliminar;
        string registro;
        string titulo, nota,fecha,autor,nota_id,aprovacion;
        string numid_buscar;
        cout<<"Ingrese el numero de ID a eliminar: ";
        cin>>numid_buscar;
        bool existe = false;

        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline (token, titulo, ';');
            getline (token, nota, ';');
            getline (token, fecha, ';');
            getline (token, autor, ';');
            getline (token, nota_id, ';');
            getline (token, aprovacion, ';');
            transform(autor.begin(), autor.end(),autor.begin(), ::toupper);
                if(numid_buscar.compare(nota_id) && autor.compare(correo) == 0 || estado == 1  ){
                        existe = true;
                }
                else registros_no_eliminar.push_back(registro);
            }//fin del while

        archivo.close();

        if(existe == true){//if(existe == true)
            ofstream nuevo("notas.csv");
            for(int i = 0; i < int(registros_no_eliminar.size()); i++){
                nuevo<<registros_no_eliminar[i]<<endl;
            }
            nuevo.close();
            cout<<"Se elimino el cliente"<<endl<<endl;
        }else{
            cout<<"El cliente con numero de ID "<<numid_buscar<<" no existe en el archivo o no es su nota"<<endl<<endl;
        }
    }
}   

void modificarNota(const string correo, int estado){
    
    ifstream archivo("notas.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'notas.csv'"<<endl<<endl;
    }else{
        vector<string> all_registros;
        string registro;
        string titulo, nota,fecha,autor,nota_id,aprovacion;
        string numid_buscar;
        cout<<"Ingrese el numero de ID a buscar: ";
        cin>>numid_buscar;
        bool existe = false, modifico = false;
        int opc = 0;

        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline (token, titulo, ';');
            getline (token, nota, ';');
            getline (token, fecha, ';');
            getline (token, autor, ';');
            getline (token, nota_id, ';');
            getline (token, aprovacion, ';');
            transform(autor.begin(), autor.end(),autor.begin(), ::toupper);
            if(numid_buscar.compare(nota_id) == 0){
                    if(estado == 1 || correo.compare(autor) == 0){
                    existe = true;
                    cout<<"Datos actuales del cliente"<<endl;
                    cout<<"Numero de ID = "<<nota_id<<endl;
                    cout<<"1. titulo = "<<titulo<<endl;
                    cout<<"2. nota = "<<nota<<endl;
                    cout<<"3. fecha = "<<fecha<<endl;
                    cout<<"4. autor = "<<autor<<endl;
                    cout<<"0. Ninguno"<<endl;
                    do{
                        cout<<"Seleccione el campo a modificar: ";
                        cin>>opc;
                    }while(opc < 0 || opc > 5);

                    fflush(stdin);

                    switch(opc){
                        case 1: modifico = true;
                                cout<<"Ingrese el nuevo titulo: ";
                                getline(cin, titulo);
                                break;
                        case 2: modifico = true;
                                cout<<"Ingrese la nueva nota: ";
                                getline(cin, nota);
                                break;
                        case 3: modifico = true;
                                cout<<"Ingrese la nueva fecha: ";
                                getline(cin, fecha);
                                break;
                        case 4: modifico = true;
                                cout<<"Ingrese el nuevo autor: ";
                                getline(cin, autor);
                                break;
                        
                    }
                    all_registros.push_back(titulo + ";" + nota + ";" + fecha + ";" + autor + ";" + nota_id + ";" + aprovacion);
                }}else all_registros.push_back(registro);
        }//fin del while

        archivo.close();

        if(existe){//if(existe == true)
            if(modifico){
                ofstream nuevo("notas.csv");
                for(int i = 0; i < int(all_registros.size()); i++){
                    nuevo<<all_registros[i]<<endl;
                }
                nuevo.close();
                cout<<"Se modifico el cliente"<<endl<<endl;
            }
        }else{
            cout<<"El cliente con numero de ID "<<numid_buscar<<" no existe en el archivo  o no es su nota"<<endl<<endl;
        }
    }
}
void buscar_x_ciudad(){
    ifstream archivo("usuario.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'usuario.csv'"<<endl<<endl;
    }else{
        string registro;
        string num_id, ape, nom, ciudad, correo, estado;
        string ciudad_buscar;
        fflush(stdin);
        cout<<"Ingrese la ciudad a buscar: ";
        getline(cin, ciudad_buscar);
        bool existe = false;

        transform(ciudad_buscar.begin(), ciudad_buscar.end(),
                ciudad_buscar.begin(), ::toupper);//convertir ciudad_buscar a mayusculas. tolower

        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline(token, num_id, ';');
            getline(token, ape, ';');
            getline(token, nom, ';');
            getline(token, ciudad, ';');
            getline(token, correo, ';');
            getline(token, estado, ';');

            transform(ciudad.begin(), ciudad.end(),
                ciudad.begin(), ::toupper);

            if(ciudad_buscar.compare(ciudad) == 0){
                existe = true;
                cout<<num_id<<endl;
                cout<<ape<<" "<<nom<<endl;
                cout<<ciudad<<" "<<correo<<endl;
                cout<<estado<<endl<<endl;
            }
        }//fin del while
        archivo.close();
        if(!existe){//if(existe == false)
            cout<<"No existen usuario con ciudad de residencia "<<ciudad_buscar<<" en el archivo"<<endl<<endl;
        }
    }
}

void modificarNotaAdm(const string correo, int estado){
    
    ifstream archivo("notas.csv", ios::in);
    if(!archivo){
        cout<<"Error en tratar de abrir el archivo 'notas.csv'"<<endl<<endl;
    }else{
        vector<string> all_registros;
        string registro;
        string titulo, nota,fecha,autor,nota_id,aprovacion;
        string numid_buscar;
        cout<<"Ingrese el numero de ID a buscar: ";
        cin>>numid_buscar;
        bool existe = false, modifico = false;
        int opc = 0;

        while(getline(archivo, registro)){
            //cout<<registro<<endl;
            stringstream token(registro);

            getline (token, titulo, ';');
            getline (token, nota, ';');
            getline (token, fecha, ';');
            getline (token, autor, ';');
            getline (token, nota_id, ';');
            getline (token, aprovacion, ';');
            transform(autor.begin(), autor.end(),autor.begin(), ::toupper);
            if(numid_buscar.compare(nota_id) == 0){
                    if(estado == 1 || correo.compare(autor) == 0){
                    existe = true;
                    cout<<"Datos actuales del cliente"<<endl;
                    cout<<"Numero de ID = "<<nota_id<<endl;
                    cout<<"1. titulo = "<<titulo<<endl;
                    cout<<"2. nota = "<<nota<<endl;
                    cout<<"3. fecha = "<<fecha<<endl;
                    cout<<"4. autor = "<<autor<<endl;
                    cout<<"5. aprobacion = "<<aprovacion<<endl;
                    cout<<"0. Ninguno"<<endl;
                    do{
                        cout<<"Seleccione el campo a modificar: ";
                        cin>>opc;
                    }while(opc < 0 || opc > 5);

                    fflush(stdin);

                    switch(opc){
                        case 1: modifico = true;
                                cout<<"Ingrese el nuevo titulo: ";
                                getline(cin, titulo);
                                break;
                        case 2: modifico = true;
                                cout<<"Ingrese la nueva nota: ";
                                getline(cin, nota);
                                break;
                        case 3: modifico = true;
                                cout<<"Ingrese la nueva fecha: ";
                                getline(cin, fecha);
                                break;
                        case 4: modifico = true;
                                cout<<"Ingrese el nuevo autor: ";
                                getline(cin, autor);
                                break;
                        case 5 : modifico = true;
                                cout<<"Ingrese la nueva aprobacion:  1= aprovado, 0= no aprovado";
                                getline(cin, aprovacion);
                        
                    }
                    all_registros.push_back(titulo + ";" + nota + ";" + fecha + ";" + autor + ";" + nota_id + ";" + aprovacion);
                }}else all_registros.push_back(registro);
        }//fin del while

        archivo.close();

        if(existe){//if(existe == true)
            if(modifico){
                ofstream nuevo("notas.csv");
                for(int i = 0; i < int(all_registros.size()); i++){
                    nuevo<<all_registros[i]<<endl;
                }
                nuevo.close();
                cout<<"Se modifico el cliente"<<endl<<endl;
            }
        }else{
            cout<<"El cliente con numero de ID "<<numid_buscar<<" no existe en el archivo  o no es su nota"<<endl<<endl;
        }
    }
}