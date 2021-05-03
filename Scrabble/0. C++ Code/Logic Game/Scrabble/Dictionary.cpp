//
//  Dictionary.cpp


#include "Dictionary.h"

#include <fstream>
#include <string>

using namespace std;

void Dictionary::setLanguage(Language language)
{
	ifstream fitxer;
	string fileName;
	int n_lines = 0;
	string line;
	string word;

	m_currentLanguage=language;
	
	switch (m_currentLanguage)
	{
	case 0:
		fileName = "Catalan.dic";
		break;
	case 1:
		fileName = "Spanish.dic";
		break;
	case 2:
		fileName = "English.dic";
		break;
	case 3:
		fileName = " ";
		break;
	default:
		break;
	}

	fitxer.open(fileName);
	//Contar lineas del txt
	while (getline(fitxer, line))
		n_lines++;

	m_words.resize(n_lines);

	for (int i = 1; i < n_lines; i++)
	{
		fitxer >> word;
		m_words.push_back(word);
	}
}

Dictionary::Dictionary(){
	m_words.push_back(0);
	m_languagesPath[0]="$(ProjectDir)\..\..\1. Resources\data\Dictionaries\Catalan.dic";
	m_languagesPath[1]="$(ProjectDir)\..\..\1. Resources\data\Dictionaries\Spanish.dic";
	m_languagesPath[2]="$(ProjectDir)\..\..\1. Resources\data\Dictionaries\English.dic";
	m_languagesPath[3]= NO_LANGUAGE;
	m_currentLanguage = NO_LANGUAGE;
}
bool Dictionary::check(const string& word){
	int i = 0;
	bool trobat = false;
	while (i < m_words.size() && trobat != true){
		if(m_words[i] == word)
			trobat = true;
		i++;
	}
	return trobat;
}