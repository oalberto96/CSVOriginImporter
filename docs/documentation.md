# Documentacion tecnica
# CSVOriginImporter

CSVOriginImporter es un programa que se encarga de importar un archivo csv generado con datos (*Figura 1*),
y tomar el renglon que el usuario desee, creando una nuevo espacio de trabajo con el la muestra y aplicando 
algunas operaciones a la columna generada (*Figura 2*).

![Figura1]()
*Figura 1*

![Figura2]()
*Figura 2*

# Clases
![DiagramaClases]()

## CSVImporter
**Descripcion:**
Esta clase se encarga de invocar los demas metodos
**Funciones:**


## CSVParser
**Descripcion:**
Su funcion principal es darle formato al archivo CSV para poder importarlo como archivo ASCII

**Funciones:**
```c
string createCopy(string str_path);
```
Crea una copia temporal del archivo CSV para poder modificiarlo

```c
string loadTextFile(string str_path);
```
Carga el archivo de texto temporal

```c
string replaceComas(string str_path_temp);
```
Cambia las comas por espacios para darle el formato necesario para importarlo

## MathColumns
**Descripcion:**
Esta clase se encarga de realizar asignar las operaciones matematicas en columnas y ejecutarlas

**Funciones:**
```c
columnDivide(Column result_col);
```
Divide cada dato de la columna entre el primer numero
```c
columnLn(Column col);
```
Calcula el logaritmo natural de la columna asignada

## WorksheetConversor
**Descripcion:**
Se encarga de la manipulacion de *Worksheets* 

**Funciones:**
```c
void RowtoColumn(Worksheet* wks,Column col,int rowIndex);
```
Recibe una hoja de trabajo y regresa como columna el renglon asignado por `rowIndex`

```c
void generateTimeColumn(Column col);
```
Genera una columna de tiempo para el eje X
