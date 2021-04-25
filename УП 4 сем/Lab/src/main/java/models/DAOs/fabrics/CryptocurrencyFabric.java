package models.DAOs.fabrics;

import models.units.Cryptocurrency;
import models.units.FinancialUnit;
import org.json.simple.JSONObject;
import org.w3c.dom.Element;

import java.util.List;

@Deprecated
public class CryptocurrencyFabric implements FinancialUnitFabric{
    @Override
    public FinancialUnit fromJson(JSONObject jsonObject) throws Exception {
        String name = (String) jsonObject.get("name");
        double high52week = (Double) jsonObject.get("high52week");
        double low52week = (Double)jsonObject.get("low52week");
        double current = (Double)jsonObject.get("current");
        String code = (String) jsonObject.get("code");
        return new Cryptocurrency(name, high52week, low52week, current, code);
    }

    @Override
    public FinancialUnit fromXml(Element element) throws Exception {
        String name = element.getElementsByTagName("name").item(0).getTextContent();
        double high52week = Double.parseDouble(element.getElementsByTagName("high52week").item(0).getTextContent());
        double low52week = Double.parseDouble(element.getElementsByTagName("low52week").item(0).getTextContent());
        double current = Double.parseDouble(element.getElementsByTagName("current").item(0).getTextContent());
        String code = element.getElementsByTagName("code").item(0).getTextContent();
        return new Cryptocurrency(name, high52week, low52week, current, code);
    }

    @Override
    public FinancialUnit fromCsv(List<String> source) throws Exception {
        String name = source.get(0);
        double high52week = Double.parseDouble(source.get(1));
        double low52week = Double.parseDouble(source.get(2));
        double current = Double.parseDouble(source.get(3));
        String code = source.get(4);
        return new Cryptocurrency(name, high52week, low52week, current, code);
    }
}
