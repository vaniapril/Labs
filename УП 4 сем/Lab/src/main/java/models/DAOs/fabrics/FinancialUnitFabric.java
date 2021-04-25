package models.DAOs.fabrics;

import models.units.FinancialUnit;
import org.json.simple.JSONObject;
import org.w3c.dom.Element;

import java.util.List;

@Deprecated
public interface FinancialUnitFabric {
    public abstract FinancialUnit fromJson(JSONObject jsonObject) throws Exception;
    public abstract FinancialUnit fromXml(Element element) throws Exception;
    public abstract FinancialUnit fromCsv(List<String> source) throws Exception;
}
