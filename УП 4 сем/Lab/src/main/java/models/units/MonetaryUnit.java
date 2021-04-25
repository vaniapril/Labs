package models.units;

//Денежная еденица
public class MonetaryUnit extends FinancialUnit{
    public String country;

    public MonetaryUnit(){
        super();
    }

    public MonetaryUnit(String name, double high52week, double low52week, double current, String code, String country){
        super(name, high52week, low52week, current, code);
        this.country = country;
    }

    @Override
    public String toString() {
        return "{" + name + ", " +
                high52week + ", " +
                low52week + ", " +
                current + ", " +
                code + ", " +
                country + "}";
    }
}
