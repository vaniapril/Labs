package models.units;

import com.fasterxml.jackson.annotation.JsonSubTypes;
import com.fasterxml.jackson.annotation.JsonSubTypes.Type;
import com.fasterxml.jackson.annotation.JsonTypeInfo;

@JsonTypeInfo(
        use = JsonTypeInfo.Id.NAME,
        include = JsonTypeInfo.As.PROPERTY,
        property = "type",
        visible = true)
@JsonSubTypes({
        @Type(value = Cryptocurrency.class, name = "cryptocurrency"),
        @Type(value = MonetaryUnit.class, name = "monetaryunit"),
        @Type(value = PreciousMetal.class, name = "preciousmetal"),
        @Type(value = Stock.class, name = "stock")
})
abstract public class FinancialUnit {
    public String type;
    public String name;
    public double high52week;
    public double low52week;
    public double current;
    public String code;

    public FinancialUnit(){}

    FinancialUnit(String name, double high52week, double low52week, double current, String code){
        this.name = name;
        this.high52week = high52week;
        this.low52week = low52week;
        this.current = current;
        this.code = code;
    }
}
