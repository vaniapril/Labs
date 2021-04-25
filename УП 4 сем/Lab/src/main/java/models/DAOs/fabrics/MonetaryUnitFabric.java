package models.DAOs.fabrics;

import models.units.FinancialUnit;
import models.units.MonetaryUnit;
import org.json.simple.JSONObject;
import org.w3c.dom.Element;

import java.util.List;

@Deprecated
public class MonetaryUnitFabric implements FinancialUnitFabric{
    @Override
    public FinancialUnit fromJson(JSONObject jsonObject) throws Exception {
        String name = (String) jsonObject.get("name");
        double high52week = (Double) jsonObject.get("high52week");
        double low52week = (Double)jsonObject.get("low52week");
        double current = (Double)jsonObject.get("current");
        String code = (String) jsonObject.get("code");
        String country = (String) jsonObject.get("country");
        return new MonetaryUnit(name, high52week, low52week, current, code, country);
    }

    @Override
    public FinancialUnit fromXml(Element element) throws Exception {
        String name = element.getElementsByTagName("name").item(0).getTextContent();
        double high52week = Double.parseDouble(element.getElementsByTagName("high52week").item(0).getTextContent());
        double low52week = Double.parseDouble(element.getElementsByTagName("low52week").item(0).getTextContent());
        double current = Double.parseDouble(element.getElementsByTagName("current").item(0).getTextContent());
        String code = element.getElementsByTagName("code").item(0).getTextContent();
        String country = element.getElementsByTagName("country").item(0).getTextContent();
        return new MonetaryUnit(name, high52week, low52week, current, code, country);
    }

    @Override
    public FinancialUnit fromCsv(List<String> source) throws Exception {
        String name = source.get(0);
        double high52week = Double.parseDouble(source.get(1));
        double low52week = Double.parseDouble(source.get(2));
        double current = Double.parseDouble(source.get(3));
        String code = source.get(4);
        String country = source.get(5);
        return new MonetaryUnit(name, high52week, low52week, current, code, country);
    }
}
