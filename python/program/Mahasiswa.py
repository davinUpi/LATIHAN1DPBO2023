
class Mahasiswa:
    '''
    Kelas untuk menampung data2 Mahasiswa
    terdiri dari Nama, Nim, Prodi, dan Fakultas
    Masing2 dapat diset menggunakan setter
    Masing2 dapat diambil menggunakan getter
    '''
    
    def __init__(self, id, nama, nim, prodi, fakultas):
        self.id = id
        self.nama = nama
        self.nim = nim
        self.prodi = prodi
        self.fakultas = fakultas
    
    #Setter
    def setId(self, id):
        self.id = id
    
    def setName(self, name):
        self.nama = name
    
    def setNim(self, nim):
        self.nim = nim
    
    def setProdi(self, prodi):
        self.prodi = prodi
        
    def setFac(self, fakultas):
        self.fakultas = fakultas
    
    #getter
    def getId(self):
        return self.id
    
    def getName(self):
        return self.nama
    
    def getNim(self):
        return self.nim
    
    def getProdi(self):
        return self.prodi
    
    def getFac(self):
        return self.fakultas