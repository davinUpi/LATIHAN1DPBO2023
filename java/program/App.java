import java.util.LinkedList;
import java.util.Scanner;
import java.io.File;
import java.io.FileWriter;
import java.io.FileNotFoundException;
import java.io.IOException;

enum ATTRIBUTETYPE{
    /*
     * enum untuk jenis2 atribut.
     * Digunakan untuk pencarian
     */
    NAME,
    NIM,
    PRODI,
    FAKULTAS,
}

public class App {
    /*
     * Kelas untuk kondisi program
     * start:
     *  Ketika program mulai, load data2 dari file ke dalam list
     * 
     * run:
     *  Ketika program berjalan, menerima query pengguna.
     * 
     * exit:
     *  Ketika program selesai. Memasukan data2 dalam list
     * ke sebuah file.
     */
    private LinkedList<Mahasiswa> listMhs;
    /// List yang digunakan untuk menampung objek mahasiswa

    private int numMhs;
    /// List yang digunakan sebagai ID

    private String filePath;
    /// Alamat file penyimpanan

    App()
    {
        this.filePath = "mahasiswa.dat";
        this.listMhs = new LinkedList<Mahasiswa>();
        this.numMhs = 0;
    }
    
    public void start(){
        //
        ///metoda akan di eksekusi jika program baru di mulai
        //
        File file = new File("mahasiswa.dat");
        
        if (file.isFile()){
            //
            ///jika file tidak null maka data di mahasiswa.dat akan dimasukan pada listMhs
            //
            try {
                Scanner fileReader = new Scanner(file);
                while (fileReader.hasNextLine()){
                    String data = fileReader.nextLine();
                    int state = 0;

                    String name = "";
                    String nim = "";
                    String prodi = "";
                    String fakultas = "";

                    for (String val : data.split(" ")){
                        //
                        /// Mengambil data2 dari file
                        //
                        switch (state) {
                            case 0:
                                name = val;
                                state = 1;
                                break;
                            
                            case 1:
                                nim = val;
                                state = 2;
                                break;

                            case 2:
                                prodi = val;
                                state = 3;
                                break;

                            case 3:
                                fakultas = val;
                                state = 4;
                                break;

                            case 5:
                                break;
                        }
                    }

                    if (state == 4){
                        //
                        /// Bila semua data yang diperlukan sudah terambil, isntansiasi dan masukkan
                        /// objek Mahasiswa ke dalam list
                        //
                        this.numMhs++;
                        Mahasiswa newMhs = new Mahasiswa(this.numMhs, name, nim, prodi, fakultas);
                        listMhs.add(newMhs);
                    }
                }

                fileReader.close();
            }
            catch (FileNotFoundException e){
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
        }
    }
    
    public void run(){
        //
        ///metoda akan di eksekusi selama program berjalan
        //
        Scanner inputReader = new Scanner(System.in);
        Boolean shouldRun = true;
        while (shouldRun){

            String input = inputReader.nextLine();
            String query[] = input.split(" ");
            
            if (query[0].equalsIgnoreCase("exit")){
                //
                ///jika input exit maka loop akan berhenti
                //
                shouldRun = false;
            }
            
            else if (query[0].equalsIgnoreCase("add")){
                //
                ///jika input add maka akan tambahkan mahasiswa baru
                //
                if (query.length == 5)
                {
                    String name = "", nim = "", prodi = "", fakultas = "";

                    for(int i = 1; i < 5; i++)
                    {
                        switch(i)
                        {
                            case 1:
                            name = query[i];
                            break;
                            case 2:
                            nim = query[i];
                            break;
                            case 3:
                            prodi = query[i];
                            break;
                            case 4:
                            fakultas = query[i];
                            break;
                        }
                    }

                    numMhs++;
                    listMhs.add(new Mahasiswa(numMhs, name, nim, prodi, fakultas));
                }
            }
            
            else if (query[0].equalsIgnoreCase("change")){
                //
                ///jika input change maka akan mengubah nilai sautu atribut
                /// dari mahasiswa tujuan
                //

                if(query.length == 6)
                {
                    ATTRIBUTETYPE searchType = null, changeType = null;
                    /// Variabel untuk mencari atribut yang dituju

                    String searchVal = "", changeVal = "";
                    /// nilai sebuah atribut

                    int i = 1;
                    String err = "";
                    while((i < 6) && (err == ""))
                    {
                        //
                        /// Memecah dan megecek input apakah sesuai dengan query
                        //
                        switch(i)
                        {
                            case 1:
                            if(query[i].equalsIgnoreCase("nama")) changeType = ATTRIBUTETYPE.NAME;
                            else if (query[i].equalsIgnoreCase("nim")) changeType = ATTRIBUTETYPE.NIM;
                            else if (query[i].equalsIgnoreCase("prodi")) changeType = ATTRIBUTETYPE.PRODI;
                            else if (query[i].equalsIgnoreCase("fakultas")) changeType = ATTRIBUTETYPE.FAKULTAS;
                            else err = "Attribut type not found!";
                            break;
                            
                            case 2:
                            changeVal = query[i];
                            break;

                            case 3:
                            if(!query[i].equalsIgnoreCase("where")) err = "Syntax error!";
                            break;
                            
                            case 4:
                            if(query[i].equalsIgnoreCase("nama")) searchType = ATTRIBUTETYPE.NAME;
                            else if (query[i].equalsIgnoreCase("nim")) searchType = ATTRIBUTETYPE.NIM;
                            else if (query[i].equalsIgnoreCase("prodi")) searchType = ATTRIBUTETYPE.PRODI;
                            else if (query[i].equalsIgnoreCase("fakultas")) searchType = ATTRIBUTETYPE.FAKULTAS;
                            else err = "Attribut type not found!";
                            break;

                            case 5:
                            searchVal = query[i];
                            break;
                        }

                        i++;
                    }
                    if (err == "")
                    //
                    /// Jika tidak ada error dalam query, cari mahasiswa yang dituju lalu
                    /// ubah nilai atribut yang ditujunya bila ketemu.
                    //
                    {
                        Mahasiswa changeMhs = null;
                        for(Mahasiswa mhs : listMhs){

                            if (searchType == ATTRIBUTETYPE.NAME){
                                if(mhs.getName().equalsIgnoreCase(searchVal)) changeMhs = mhs;
                            }
                            else if (searchType == ATTRIBUTETYPE.NIM){
                                if(mhs.getNim().equalsIgnoreCase(searchVal)) changeMhs = mhs;
                            }
                            else if (searchType == ATTRIBUTETYPE.PRODI){
                                if (mhs.getProdi().equalsIgnoreCase(searchVal)) changeMhs = mhs;

                            }
                            else if (searchType == ATTRIBUTETYPE.FAKULTAS){
                                if (mhs.getFakultas().equalsIgnoreCase(searchVal)) changeMhs = mhs;
                            }
                        }

                        if(changeMhs != null)
                        {
                            if (changeType == ATTRIBUTETYPE.NAME) changeMhs.setName(changeVal);
                            else if(changeType == ATTRIBUTETYPE.NIM) changeMhs.setNim(changeVal);
                            else if(changeType == ATTRIBUTETYPE.PRODI) changeMhs.setProdi(changeVal);
                            else if(changeType == ATTRIBUTETYPE.FAKULTAS) changeMhs.setFakultas(changeVal);
                        }
                    }
                    else{
                        System.out.println(err);
                    }
                }
                else{
                    System.out.println("Syntax error!");
                }
            }
            
            else if (query[0].equalsIgnoreCase("delete")){
                //
                ///jika input delete maka akan menghapus Mahasiswa yang dimaksud
                //
                if(query.length == 3)
                {
                    ATTRIBUTETYPE searchType = null;
                    String searchVal = "";

                    int i = 1;
                    String err = "";
                    while((i < 3) && (err == ""))
                    {
                        switch(i)
                        {
                            case 1:
                            if(query[i].equalsIgnoreCase("nama")) searchType = ATTRIBUTETYPE.NAME;
                            else if (query[i].equalsIgnoreCase("nim")) searchType = ATTRIBUTETYPE.NIM;
                            else if (query[i].equalsIgnoreCase("prodi")) searchType = ATTRIBUTETYPE.PRODI;
                            else if (query[i].equalsIgnoreCase("fakultas")) searchType = ATTRIBUTETYPE.FAKULTAS;
                            else err = "Attribut type not found!";
                            break;
                            
                            case 2:
                            searchVal = query[i];
                            break;

                        }

                        i++;
                    }

                    if (err == "")
                    {
                        Mahasiswa delMhs = null;
                        for(Mahasiswa mhs : listMhs){

                            if (searchType == ATTRIBUTETYPE.NAME){
                                if(mhs.getName().equalsIgnoreCase(searchVal)) delMhs = mhs;
                            }
                            else if (searchType == ATTRIBUTETYPE.NIM){
                                if(mhs.getNim().equalsIgnoreCase(searchVal)) delMhs = mhs;
                            }
                            else if (searchType == ATTRIBUTETYPE.PRODI){
                                if (mhs.getProdi().equalsIgnoreCase(searchVal)) delMhs = mhs;

                            }
                            else if (searchType == ATTRIBUTETYPE.FAKULTAS){
                                if (mhs.getFakultas().equalsIgnoreCase(searchVal)) delMhs = mhs;
                            }
                        }

                        if(delMhs != null)
                        {
                            listMhs.removeFirstOccurrence(delMhs);
                        }
                    }
                    else{
                        System.out.println(err);
                    }
                }

                else if(query[0].equalsIgnoreCase("print")){
                    for (Mahasiswa i : this.listMhs){
                        System.out.println(i.getName());
                        System.out.println(i.getNim());
                        System.out.println(i.getProdi());
                        System.out.println(i.getFakultas());
                    }
                }
                else{
                    System.out.println("Syntax error!");
                }
                
            }
        }
        inputReader.close();
    }
    
    public void exit() {
        //
        /// metode akan dieksekusi jika program keluar.
        /// Menyimpan data2 dalam list ke sebuah file
        //
        try {
            File file = new File("mahasiswa.dat");
            if(!file.exists()){
                file.createNewFile();
            }

            try {
                FileWriter fileWriter = new FileWriter(file);
                for(Mahasiswa i : this.listMhs){
                    try {
                        fileWriter.write
                        (
                            i.getName() + " " +
                            i.getNim() + " " +
                            i.getProdi() + " " +
                            i.getFakultas() + "\n"
                            );
                    } catch (IOException e){
                        e.printStackTrace();
                    }
                }
                fileWriter.close();
            } catch (IOException e){
                e.printStackTrace();
            }

        }catch (IOException e){
            System.out.println("Error");
            e.printStackTrace();
        }
    }

    // path setter and getter

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }

    public String getFilePath() {
        return filePath;
    }

}
