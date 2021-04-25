package models;

import controllers.MainController;
import models.units.*;
import views.ConsoleView;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Validator {
    private static Validator shared;
    public static Validator sharedInstance(){
        if (null == shared){
            shared = new Validator();
        }
        return shared;
    }
    private Validator(){}

    private boolean validateCryptocurrency(Cryptocurrency cryptocurrency){
        return validateFinancialUnit(cryptocurrency);
    }
    private boolean validateMonetaryUnit(MonetaryUnit monetaryUnit){
        return validateFinancialUnit(monetaryUnit) && validateCountry(monetaryUnit.country);
    }
    private boolean validatePreciousUnit(PreciousMetal preciousMetal){
        return validateFinancialUnit(preciousMetal);
    }
    private boolean validateStock(Stock stock){
        return validateFinancialUnit(stock);
    }

    private boolean validateFinancialUnit(FinancialUnit financialUnit){
        return validateCode(financialUnit.code) && validateName(financialUnit.name);
    }

    public boolean validate(FinancialUnit financialUnit, Class clazz){
        if (Cryptocurrency.class.equals(clazz)) {
            return validateCryptocurrency((Cryptocurrency) financialUnit);
        } else if (MonetaryUnit.class.equals(clazz)) {
            return validateMonetaryUnit((MonetaryUnit) financialUnit);
        } else if (PreciousMetal.class.equals(clazz)) {
            return validatePreciousUnit((PreciousMetal) financialUnit);
        } else if (Stock.class.equals(clazz)) {
            return validateStock((Stock) financialUnit);
        } else {
            return false;
        }
    }

    private boolean validateCode(String code){
        Pattern pattern = Pattern.compile("[A-Z]{2,4}");
        Matcher matcher = pattern.matcher(code);
        return matcher.matches();
    }

    private boolean validateName(String name){
        //USDollar
        //Belarusian Ruble
        Pattern pattern = Pattern.compile("[A-Z]{1,}[a-z]{1,}( [A-Z]{0,1}[a-z]{1,})*");
        Matcher matcher = pattern.matcher(name);
        return matcher.matches();
    }

    private boolean validateCountry(String country){
        //Belarus
        //United States
        Pattern pattern = Pattern.compile("([A-Z]{1}[a-z]{1,} {0,1}){1,}");
        Matcher matcher = pattern.matcher(country);
        return matcher.matches();
    }
}
