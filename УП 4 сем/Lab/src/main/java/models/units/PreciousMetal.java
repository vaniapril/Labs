package models.units;

//Драгоценный металл

public class PreciousMetal extends FinancialUnit{

    public PreciousMetal(){
        super();
    }

    public PreciousMetal(String name, double high52week, double low52week, double current, String code){
        super(name, high52week, low52week, current, code);
    }

    @Override
    public String toString() {
        return "{" + name + ", " +
                high52week + ", " +
                low52week + ", " +
                current + ", " +
                code + "}";
    }
}
