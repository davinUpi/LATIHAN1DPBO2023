#pragma once

#include <list>
#include <fstream>
#include <sstream>
#include "Mahasiswa.cpp"
#include "Query_Handler.cpp"

class Program{

private:
    int numMhs;
    /// Untuk menampung jumlah mahasiswa. Digunakan sebagai ID

    std::list<Mahasiswa*> listMhs;
    /// Untuk menampung objek2 mahasiswa.

public:

    Program()
    {
        this->numMhs = 0;

    };
    ~Program(){};
    
    void start()
    ///
    /// Metode yang dieksekusi pada saat program di mulai
    ///
    {
        std::ifstream fileData;
        fileData.open("mahasiswa.dat", std::ios::out|std::ios::app);
        if(fileData.is_open())
        ///
        ///jika data mahasiswa.dat bukan null maka data-data yang berada di mahasiswa.dat masuk pada class Mahasiswa
        ///

        {
            std::string dataString;
            while(std::getline(fileData, dataString))
            {
                std::string name = "";
                std::string nim = "";
                std::string prodi = "";
                std::string fakultas = "";
                Query_Handler::addMahasiswa(dataString, &name, &nim, &prodi, &fakultas);
                ///
                ///  Fungsi untuk mengambil data2 Mahasiswa dari string input
                ///
                if ((name != "") && (nim != "") && (prodi != "") && (fakultas != ""))
                ///
                /// Jika semua data yang dibutuhkan didapatkan, Membuat dan memasukkan objek Mahasiswa
                ///
                {
                    numMhs++;
                    Mahasiswa* newMhs = new Mahasiswa(numMhs, name, nim, prodi, fakultas);
                    listMhs.push_back(newMhs);

                }
            }
        }
        
        fileData.close();
    }
    
    void run()
    ///
    /// Metode yang dieksekusi selama program berjalan
    ///
    {
        std::string input;
        bool run = true;
        while (run)
        ///
        ///program akan run sampai user input exit
        ///
        {
            int error = 0;
            std::getline (std::cin, input);
            std::istringstream curWord(input);
            std::string word;
            curWord >> word;
            if(Query_Handler::lowercase(word) == "exit")
            ///
            ///jika input exit maka program akan berhenti run
            ///
            {
                run = false;
            }
            
            else if ((Query_Handler::lowercase(word) == "help") || (Query_Handler::lowercase(word) == "?"))
            ///
            ///jika input help atau ? maka akan menunjukan cara kerja
            ///
            {
                std::cout << "Queries and how to use them:" << std::endl;
                std::cout << "Add: add {name} {nim} {prodi} {fakultas}" << std::endl;
                std::cout << "Change: change {change attribute} {change value} where {search attribute} {search value}" << std::endl;
                std::cout << "Delete: delete {search attribute} {search value}" << std::endl;
                std::cout << "Print: print" << std::endl;
            }
            
            else if (Query_Handler::lowercase(word) == "add")
            ///
            ///jika input add maka akan tambah data mahasiswa ke list
            ///
            {
                Query_Handler::delFirstWord(&input);
                ///Membersihkan input agar dapat menggunakan addMahasiswa()

                std::string name = "";
                std::string nim = "";
                std::string prodi = "";
                std::string fakultas = "";

                Query_Handler::addMahasiswa(input, &name, &nim, &prodi, &fakultas);
                if ((name != "") && (nim != "") && (prodi != "") && (fakultas != ""))
                {
                    numMhs++;
                    Mahasiswa newMhs(numMhs, name, nim, prodi, fakultas);
                    listMhs.push_back(&newMhs);
                }
            }
            
            else if (Query_Handler::lowercase(word) == "change")
            ///
            ///jika input change maka akan mengubah data di list menjadi data baru
            ///
            {
                Query_Handler::delFirstWord(&input);
                Query_Handler::changeMahasiswa(input, listMhs);
                /// Metode untuk mengubah nilai attribut Mahasiswa
                
            }
            
            else if (Query_Handler::lowercase(word) == "delete")
            ///
            ///jika input delete maka akan menghapus data di list yang diinputkan oleh user
            ///
            {
                Query_Handler::delFirstWord(&input);
                Query_Handler::deleteMahasiswa(input, listMhs);
                /// Metode untuk menghapus Mahasiswa
                
            }
            
            else if(Query_Handler::lowercase(word) == "print")
            ///
            ///jika input print maka akan print data yang ada di list
            ///
            {
                for(auto i : listMhs)
                {
                    std::cout << "O" << std::endl;
                    std::cout << "> MAHASISWA ID : " << i->getId() << std::endl;
                    std::cout << "> NAMA         : " << i->getName() << std::endl;
                    std::cout << "> NIM          : " << i->getNim() << std::endl;
                    std::cout << "> PROGRAM STUDI: " << i->getProdi() << std::endl;
                    std::cout << "> FAKULTAS     : " << i->getFac() << std::endl;
                    std::cout << "O" << std::endl;
                }
            }
            else
                Query_Handler::errorHandler("Query not recognizeable!");
        }
    }
    
    void close ()
    ///
    ///fungsi akan di eksekusi pada saat program berjalan
    ///
    {
        /*
        std::ofstream file;
        file.open("mahasiswa.dat", std::ios::out|std::ios::app);
        if(file.is_open())
        {
            for(auto const i : listMhs)
            {
                file << i->getName() << '\n';
            }
            listMhs.clear();
            
        }
        file.close();
        */
       listMhs.clear();
    }

};
