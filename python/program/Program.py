import os.path
from Mahasiswa import Mahasiswa


class Program:
    '''
    Kelas untuk menampung status program
    
    start:
        Di saat program baru dijalankan. Akan mengambil
        data2 mahasiswa yang tersimpan di dalam file
        
    run:
        Di saat program berjalan. Akan menerima masukan
        berupa Query. Tidak akan berhenti hingga disuruh
        berhenti dengan query tertentu (exit)
    
    exit:
        Ketika program disuruh berhenti. Akan menyimpan
        Mahasiswa2 yang tersimpan dalam list(?) ke sebuah
        file
    '''
    
    def __init__(self):
        self.listMhs = []
        # Untuk menampung Mahasiswa
        
        self.numMhs = 0
        # bertindak sebagai id (sementara ini)
        
        self.path = 'mahasiswa.dat'
        # alamat file yang digunakan untuk penyimpanan
    
    def start(self):
        '''
        Di saat program baru dijalankan. Akan mengambil
        data2 mahasiswa yang tersimpan di dalam file
        '''
        if os.path.exists(self.path) is True:
            file = open(self.path, 'r')
            content = file.readlines()
            for line in content:
                self.numMhs += 1
                name, nim, prodi, fakultas = line.split()
                newMhs = Mahasiswa(self.numMhs, name, nim, prodi, fakultas)
                self.listMhs.append(newMhs)
            file.close()
    
    def run(self):
        '''
        Di saat program berjalan. Akan menerima masukan
        berupa Query. Tidak akan berhenti hingga disuruh
        berhenti dengan query tertentu (exit)
        '''
        run = True
        while run :
            query = input().split()
            
            if query[0].lower() == 'exit':
                run = False
            elif query[0].lower() == 'add':
                '''
                Query penambahan mahasiswa
                '''
                if len(query) == 5:
                    name, nim, prodi, fakultas = query[1:5]
                    self.numMhs += 1
                    newMhs = Mahasiswa(self.numMhs, name, nim, prodi, fakultas)
                    self.listMhs.append(newMhs)
                else:
                    print('Query is incomplete or excessive!')
                    
            elif query[0].lower() == 'print':
                for mahasiswa in self.listMhs:
                    print(mahasiswa.getId())
                    print(mahasiswa.getName())
                    print(mahasiswa.getNim())
                    print(mahasiswa.getProdi())
                    print(mahasiswa.getFac())
                    
            elif query[0].lower() == 'change':
                '''
                Query pengubahan nilai suatu atribut Mahasiswa tujuan.
                Akan dilakukan pencarian Mahasiswa yang dituju, baru mengubah
                atribut yang dituju
                '''
                if len(query) == 6:
                    if query[3].lower() == 'where':
                        changeType, changeVal = query[1:3]
                        searchType, searchVal = query[4:6]
                        index = -1
                        
                        for mahasiswa in self.listMhs:
                            '''
                            Mencari Mahasiswa di dalam list
                            '''
                            if searchVal.lower() == 'id':
                                if mahasiswa.getId() == int(searchVal):
                                    index = self.listMhs.index(mahasiswa)
                                    break
                            
                            elif searchType.lower() == 'nama':
                                if mahasiswa.getName().lower() == searchVal:
                                    index = self.listMhs.index(mahasiswa)
                                    break
                            
                            elif searchType.lower() == 'nim':
                                if mahasiswa.getNim() == searchVal:
                                    index = self.listMhs.index(mahasiswa)
                                    break
                                
                            elif searchType.lower() == 'prodi':
                                if mahasiswa.getProdi().lower() == searchVal:
                                    index = self.listMhs.index(mahasiswa)
                                    break
                            
                            elif searchType.lower() == 'fakultas':
                                if mahasiswa.getFac().lower() == searchVal:
                                    index = self.listMhs.index(mahasiswa)
                                    break
                        
                        if index != -1:
                            '''
                            Bila ketemu, ubahlah nila atribut yang dituju
                            '''
                            if changeType.lower() == 'id':
                                dupe = False
                                for i in self.listMhs:
                                    if i.getId() == int(changeVal):
                                        dupe = True
                                
                                if dupe != True:
                                    self.listMhs[index].setId(int(changeVal))
                                else:
                                    print("Id can't be duplicates!")
                            
                            elif changeType.lower() == 'nama':
                                self.listMhs[index].setName(changeVal)
                            
                            elif changeType.lower() == 'nim':
                                self.listMhs[index].setNim(changeVal)
                            
                            elif changeType.lower() == 'prodi':
                                self.listMhs[index].setProdi(changeVal)
                            
                            elif changeType.lower() == 'fakultas':
                                self.listMhs[index].setFac(changeVal)
                            
                        else:
                            print('mahasiswa not found!')
                            
                    else:
                        print('Incomplete query')
                        
            elif query[0].lower() == 'delete':
                '''
                Query menghapus mahasiswa yang inngin dihapus.
                Akan dilakukan pencarian di dalam list
                '''
                if len(query) == 3:
                    searchType, searchVal = query[1:3]
                    index = -1
                    
                    for mahasiswa in self.listMhs:
                            if searchVal.lower() == 'id':
                                if mahasiswa.getId() == int(searchVal):
                                    index = self.listMhs.index(mahasiswa)
                                    break
                            
                            elif searchType.lower() == 'nama':
                                if mahasiswa.getName().lower() == searchVal:
                                    index = self.listMhs.index(mahasiswa)
                                    break
                            
                            elif searchType.lower() == 'nim':
                                if mahasiswa.getNim() == searchVal:
                                    index = self.listMhs.index(mahasiswa)
                                    break
                                
                            elif searchType.lower() == 'prodi':
                                if mahasiswa.getProdi().lower() == searchVal:
                                    index = self.listMhs.index(mahasiswa)
                                    break
                            
                            elif searchType.lower() == 'fakultas':
                                if mahasiswa.getFac().lower() == searchVal:
                                    index = self.listMhs.index(mahasiswa)
                                    break
                    
                    if index != -1:
                        self.listMhs.pop(index)
                    else:
                        print('mahasiswa not found!')
                
    def exit(self):
        file = open(self.path, 'w')
        for mahasiswa in self.listMhs:
            file.write(mahasiswa.getName() + ' ' + mahasiswa.getNim() + ' ' + mahasiswa.getProdi() + ' ' + mahasiswa.getFac() + '\n')
        
        file.close()