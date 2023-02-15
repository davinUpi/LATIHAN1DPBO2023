
public class Mahasiswa {
    
    /*
     * Kelas yang berisi data2 mahasiswa.
     * Terdiri ddari atribut name, nim, prodi, fakultas
     * Masing2 atribut dapat diset dan diambil menggunakan methode
     */
    private int id;
    private String name;
    private String nim;
    private String prodi;
    private String fakultas;

    public Mahasiswa(int id, String name, String nim, String prodi, String fakultas) {
        this.id = id;
        this.name = name;
        this.nim = nim;
        this.prodi = prodi;
        this.fakultas = fakultas;
    }

    // Setter
    public void setId(int id)
    {
        this.id = id;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public void setNim(String nim)
    {
        this.nim = nim;
    }

    public void setProdi(String prodi) {
        this.prodi = prodi;
    }

    public void setFakultas(String fakultas) {
        this.fakultas = fakultas;
    }

    // Getter
    public int GetId()
    {
        return this.id;
    }

    public String getName()
    {
        return this.name;
    }

    public String getNim()
    {
        return this.nim;
    }

    public String getProdi()
    {
        return this.prodi;
    }

    public String getFakultas() {
        return this.fakultas;
    }
}
