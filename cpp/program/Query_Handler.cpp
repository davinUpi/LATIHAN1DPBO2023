#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include "Mahasiswa.cpp"

enum class ATTRIBUTETYPE{
    ///  
    /// kelas untuk menentukan jenis attribut
    ///
    ID = 0,
    NAME,
    NIM,
    PRODI,
    FAKULTAS
};

class Query_Handler{
    ///
    /// Kelas ini berfungsi untuk memproses query2
    ///
public:
    Query_Handler(){};
    ~Query_Handler(){};
    
    static std::string lowercase(std::string query)
    ///
    /// ubah query menjadi lowercase
    ///
    {
        std::string temp = query;
        for(auto& i:temp)
            i = tolower(i);
        return temp;
    }
    
    static void delFirstWord(std::string* string)
    ///
    /// delete kata pertama dari string, digunakan untuk pembersihan query
    ///
    {
        std::string::size_type n = 0;
        n = (*string).find_first_not_of(" \t", n);
        n = (*string).find_first_of(" \t", n);
        (*string).erase(0, (*string).find_first_not_of(" \t", n));

    }

    static void errorHandler(std::string errorMsg)
    // Metode untuk ngeprint error
    {
        std::cout << "ERROR:\n" << errorMsg << std::endl;
    }

    static void addMahasiswa
    ///
    /// Metode pembantu untuk memudahkan penambahan objek Mahasiswa
    ///
    (
        std::string input,
        std::string* iName,
        std::string* iNim,
        std::string* iProdi,
        std::string* iFakultas
        )
    {
        unsigned int state = 0;

        std::string name;
        std::string nim;
        std::string prodi;
        std::string fakultas;
        ///
        /// Variabel2 penampung sementara nilai2 atribut Mahasiswa
        ///

        std::istringstream string_stream(input);
        while(string_stream)
        ///
        /// Pengulangan untuk mendapatkan nilai setiap atribut Mahasiswa dari input
        ///
        {
            std::string word;
            string_stream >> word;
            switch(state)
            {
                case 0:
                    name = word;
                    state = 1;
                    break;
                case 1:
                    nim = word;
                    state = 2;
                    break;
                case 2:
                    prodi = word;
                    state = 3;
                    break;
                case 3:
                    fakultas = word;
                    state = 4;
                    break;
            }
        }
        if(state == 4)
        ///
        /// Bila semua nilai yang dibutuhkan didapatkan.
        ///
            {
                *iName = name;
                *iNim = nim;
                *iProdi = prodi;
                *iFakultas = fakultas;
            }
        else
            {
            std::string errorMsg = "Not enough arguments!";
            errorHandler(errorMsg);
        }
    }
    
    static void changeMahasiswa(std::string input, std::list<Mahasiswa*> listMhs)
    ///
    /// mengubah attribut mahasiswa yang dituju mahasiswa
    ///
    {
        ATTRIBUTETYPE changeType;
        std::string changeVal;
        /// Kedua variabel ini digunakan untuk mengubah nilai suatu atribut Mahasiswa

        ATTRIBUTETYPE serachType;
        std::string searchVal;
        // Kedua variabel ini digunakan untuk mencari Mahasiswa dengan nilai atribut tertentu
        
        std::string errorMsg = "";
        unsigned int state = 0;
        std::istringstream string_stream(input);
        ///
        /// Pengulangan untuk mengolah input. Input yang berhubungan dengan
        /// Pencarian dijadikan huruf kecil
        ///
        do{
            std::string curWord;
            string_stream >> curWord;
            switch(state)
            {
                case 0:
                ///
                /// Menentukan atribut apa yang ingin diubah nilainya
                ///
                    if (lowercase(curWord) == "id"){
                        changeType = ATTRIBUTETYPE::ID;
                        state = 1;
                    }
                    else if (lowercase(curWord) == "nama"){
                        changeType = ATTRIBUTETYPE::NAME;
                        state = 1;
                    }
                    else if (lowercase(curWord) == "nim"){
                        changeType = ATTRIBUTETYPE::NIM;
                        state = 1;
                    }
                    else if ((lowercase(curWord) == "prodi") || ((lowercase(curWord) == "program_studi"))){
                        changeType = ATTRIBUTETYPE::PRODI;
                        state = 1;
                    }
                    else if (lowercase(curWord) == "fakultas"){
                        changeType = ATTRIBUTETYPE::FAKULTAS;
                        state = 1;
                    }
                    else
                    {
                        state = 6;
                        errorMsg = "No Attribut named : ";
                        errorMsg = errorMsg + curWord;
                    }

                break;
                
                case 1:
                ///
                /// Nilai baru atribut yang diubah
                ///
                    changeVal = curWord;
                    state = 2;
                break;
                
                case 2:
                    if (lowercase(curWord) == "where")
                    {
                        state = 3;
                    }
                    else
                    {
                        state = 6;
                        errorMsg = "Incorrect query";
                    }
                break;

                case 3:
                ///
                /// Menentukan atribut apa yang dijadikan patokan pencarian
                ///
                    if (lowercase(curWord) == "id"){
                        serachType = ATTRIBUTETYPE::ID;
                        state = 4;
                    }
                    else if (lowercase(curWord) == "nama"){
                        serachType = ATTRIBUTETYPE::ID;
                        state = 4;
                    }
                    else if (lowercase(curWord) == "nim"){
                        serachType = ATTRIBUTETYPE::NIM;
                        state = 4;
                    }
                    else if ((lowercase(curWord) == "prodi") || ((lowercase(curWord) == "program_studi"))){
                        serachType = ATTRIBUTETYPE::ID;
                        state = 4;
                    }
                    else if (lowercase(curWord) == "fakultas"){
                        serachType = ATTRIBUTETYPE::FAKULTAS;
                        state = 4;
                    }
                    else
                    {
                        state = 6;
                        errorMsg = "No Attribut named : " + curWord;
                    }
                break;

                case 4:
                ///
                /// Nilai atribut yang dicari
                ///
                    searchVal = curWord;
                    state = 5;
                break;

            }
        }while(string_stream);

        if(state == 5)
        ///
        /// Bila semua data yang dibutuhkan didapatkan, baru melakukan perubahan nilai atribut
        /// Mahasiswa yang dituju
        ///
        {
            Mahasiswa* changeMhs = searchMahasiswa(serachType, listMhs, searchVal);
            if (changeMhs != NULL)
            ///
            /// Bila Mahasiswa yang dicari ada, baru mengubah attributnya
            ///
            {
                if (changeType == ATTRIBUTETYPE::ID)
                {
                    Mahasiswa* checkMhs = searchMahasiswa(changeType, listMhs, changeVal);
                    //
                    /// Khusus Id, harus unik
                    //
                    if (checkMhs == NULL)
                    {
                        changeMhs->setId(std::stoi(changeVal));
                    }
                    else
                    {
                        errorMsg = "Id must be unique!";
                    }
                }
                else if (changeType == ATTRIBUTETYPE::NAME) changeMhs->setName(changeVal);
                else if (changeType == ATTRIBUTETYPE::NIM) changeMhs->setNim(changeVal);
                else if (changeType == ATTRIBUTETYPE::PRODI) changeMhs->setProdi(changeVal);
                else if (changeType == ATTRIBUTETYPE::FAKULTAS) changeMhs->setFac(changeVal);

            }
            else
            {
                errorMsg = "Mahasiswa not found";
            }
        }
        else
        {
            errorMsg = "Query incorrect!";
        }
        
        if (errorMsg != "")
        {
            errorHandler(errorMsg);
        }

    }
    
    static void deleteMahasiswa(std::string input, std::list<Mahasiswa*> &listMhs)
    //
    /// menghapus mahasiswa tertentu
    //
    {
        std::string deleteVal;
        ATTRIBUTETYPE deleteType;
        /// variabel yang digunakan untuk mencari Mahasiswa yang akan dihapus

        std::string errorMsg = "";
        unsigned int state = 0;
        std::istringstream string_stream(input);
        //
        /// Pengulangan untuk mengolah input
        //
        do{
            std::string curWord;
            string_stream >> curWord;
            switch(state)
            {
                case 0:
                    if (lowercase(curWord) == "id")
                    {
                        deleteType = ATTRIBUTETYPE::ID;
                        state = 1;
                    }
                    else if (lowercase(curWord) == "nama")
                    {
                        deleteType = ATTRIBUTETYPE::NAME;
                        state = 1;
                    }
                    else if (lowercase(curWord) == "nim") 
                    {
                        deleteType = ATTRIBUTETYPE::NIM;
                        state = 1;
                    }
                    else if ((lowercase(curWord) == "prodi") || (lowercase(curWord) == "program_studi"))
                    {
                        deleteType = ATTRIBUTETYPE::PRODI;
                        state = 1;
                    }
                    else if (lowercase(curWord) == "fakultas")
                    {
                        deleteType = ATTRIBUTETYPE::FAKULTAS;
                        state = 1;
                    }
                    else{
                        errorMsg = "No attribute named : " + curWord;
                        state = 3;
                    }

                break;

                case 1:
                    deleteVal = curWord;
                    state = 2;
                break;
            }

        }while(string_stream);


        if (state == 2)
        //
        /// Bila input sesuai, mencari Mahasiswa yang akan dihapus lalu menghapusnya.
        //
        {
            Mahasiswa* delMhs = searchMahasiswa(deleteType, listMhs, deleteVal);
            if(delMhs != NULL)
            {
                listMhs.remove(delMhs);
                free(delMhs);
            }
            else
            {
                errorMsg = "Mahasiswa not found!";
            }
        }
        else
            errorMsg = "Query incomplete!";
        
        if(errorMsg != "")
            errorHandler(errorMsg);

    }
    
    static Mahasiswa* searchMahasiswa (ATTRIBUTETYPE searchType, std::list<Mahasiswa*> listMhs, std::string string)
    //
    /// mencari mahasiswa. Akan mengembalikan null bila tidak ketemu
    //
    {
        Mahasiswa* value = NULL;
        bool found = false;
        string = lowercase(string);
        for (auto const& i : listMhs)
        //
        /// Melakukan pencarian di dalam list
        //
        {
            if( searchType == ATTRIBUTETYPE::ID)
            {
                int findId = stoi(string);
                if(findId == i->getId()) found = true;
            }
            else if (searchType == ATTRIBUTETYPE::NAME)
            {
                if(string == lowercase(i->getName())) found = true;
            }
            else if (searchType == ATTRIBUTETYPE::NIM)
            {
                if (string == i->getNim()) found = true;
            }    
            else if (searchType == ATTRIBUTETYPE::PRODI)
            {
                if (string == lowercase(i->getProdi())) found = true;
            }
            else if (searchType == ATTRIBUTETYPE::FAKULTAS)
            {
                if (string == lowercase(i->getFac())) found = true;
            }

            if (found == true)
            {
                value = i;
                break;
            }
        }

        return value;
    }

};
