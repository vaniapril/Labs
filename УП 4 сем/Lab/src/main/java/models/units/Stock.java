package models.units;

//Акции

public class Stock extends FinancialUnit{
    public Stock(){
        super();
    }

    public Stock(String name, double high52week, double low52week, double current, String code){
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
