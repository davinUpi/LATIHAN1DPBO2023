#pragma once

#include <iostream>
#include <string>

class Mahasiswa
{

private:
    int id;
    std::string name;
    std::string nim;
    std::string prodi;
    std::string fakultas;

public:
    Mahasiswa(
        int id,
        std::string newName = "", 
        std::string newNim = "",
        std::string newProdi = "",
        std::string newFac = "")
        {
            this->id = id;
            this->name = newName;
            this->nim = newNim;
            this->prodi = newProdi;
            this->fakultas = newFac;
        }

    ~Mahasiswa(){}

    //Setter
    void setId(int newId)
    {
        this->id = newId;
    }
    
    void setName(std::string newName)
    {
        this->name = newName;
    }

    void setNim(std::string newNim)
    {
        this->nim = newNim;
    }
    void setProdi(std::string newProdi)
    {
        this->prodi = newProdi;
    }
    void setFac(std::string newFac)
    {
        this->fakultas = newFac;
    }

    //getter
    int getId()
    {
        return this->id;
    }
    std::string getName()
    {
        return this->name;
    }

    std::string getNim()
    {
        return this->nim;
    }
    std::string getProdi()
    {
        return this->prodi;
    }
    std::string getFac()
    {
        return this->fakultas;
    }

private:

    bool isEmpty(std::string string)
    {
        bool value;
        (string == "")? (value = true) : (value = false);
        return value;
    }

};