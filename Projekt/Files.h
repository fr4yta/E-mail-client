#pragma once
#include <iostream>
#include <fstream>

using namespace std;

/** Klasa obslugujaca strumienie plikow
* 
* W tej klasie mozemy sprawdzic czy istnieje plik o danej nazwie metoda (`ifFileExists()`) oraz mozemy wkonac zapis do pliku metoda (`reWriteContentFile()`).
*/

class Files {
public:
	/// Nazwa pliku
	string fileName;

	/** Konstruktor dla klasy `Files`
	*
	* @param fileName - Nazwa pliku podawana do konstuktora
	*/
	Files(string fileName);

	/** Metoda `ifFileExists()` sprawdza czy istnieje plik o danej nazwie, ktory zostal wyslany wczesniej do konstruktora 
	*
	* @result - Funkcja zwraca `1` jesli plik juz istnieje, `0` jesli plik nie istnieje.
	*/
	bool ifFileExists();

	/** Metoda `reWriteContentFile()` zapisuje do pliku o danej nazwie kontent, ktory przyjmuje jako argument
	* 
	* @param content - Kontent ktory bedzie zapisywany do pliku
	*/
	void reWriteContentFile(const string& content);
};