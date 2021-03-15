package controllers;

import models.DAOs.AbstractDao;
import models.DAOs.proxy.ProxyFabric;
import models.Validator;
import models.units.*;
import views.ConsoleView;

import java.io.File;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class MainController {
    private static final String[] fileNames = {
            "monetaryunit",
            "cryptocurrency",
            "preciousmetal",
            "stock"
    };
    private static final String[] types = {
            "json",
            "xml",
            "csv"
    };
    private static final String inPrefix = "src\\main\\resources\\in\\";
    private static final String outPrefix = "src\\main\\resources\\out\\";

    private static MainController shared;
    public static MainController sharedInstance(){
        if (null == shared){
            shared = new MainController();
        }
        return shared;
    }
    private MainController(){
        view = new ConsoleView();
    }
    static List<FinancialUnit> list;
    ConsoleView view;

    public void start(){
        for (String fileName : fileNames){
            for (String type : types){
                String path = inPrefix + fileName + "." + type;
                File file = new File(path);
                if(!file.exists()){
                    view.fineNotExistAlert(fileName);
                    return;
                }

                try {
                    AbstractDao dao = getDao(path);
                    list = dao.read();
                    /*
                    int id = view.operationTypeDialog();
                    List<FinancialUnit> sortedList;
                    if (id == 1){
                        sortedList = operation1();
                    } else if(id == 2){
                        sortedList = operation2();
                    } else {
                        view.wrongOperationAlert();
                        return;
                    }
                    view.showData(sortedList);
                    */
                    for (int i = 0; i < list.size(); i ++){
                        if(!Validator.sharedInstance().validate(list.get(i), getClass(fileName))){
                            view.validationErrorAlert();
                        }
                    }
                    for (String writeTypes : types){
                        dao = getDao(outPrefix + type + "\\" + fileName + "." + writeTypes);
                        dao.write(list);
                    }
                } catch (Exception exception){
                    view.cannotReadFileAlert(fileName);
                }
            }
        }
    }

    Class getClass(String name){
        switch (name){
            case "cryptocurrency":
                return Cryptocurrency.class;
            case "monetaryunit":
                return MonetaryUnit.class;
            case "preciousmetal":
                return PreciousMetal.class;
            case "stock":
                return Stock.class;
        }
        return Object.class;
    }

    private AbstractDao getDao(String path) throws Exception {
        String fileName = path.substring(path.lastIndexOf("\\") + 1, path.lastIndexOf("."));
        File file = new File(path);
        switch (path.substring(path.lastIndexOf(".") + 1)){
            case "xml":
                switch (fileName){
                    case "cryptocurrency":
                        return new ProxyFabric<Cryptocurrency>().getXmlDaoProxy(file, Cryptocurrency.class);
                    case "monetaryunit":
                        return new ProxyFabric<MonetaryUnit>().getXmlDaoProxy(file, MonetaryUnit.class);
                    case "preciousmetal":
                        return new ProxyFabric<PreciousMetal>().getXmlDaoProxy(file, PreciousMetal.class);
                    case "stock":
                        return new ProxyFabric<Stock>().getXmlDaoProxy(file, Stock.class);
                }
                break;
            case "json":
                switch (fileName){
                    case "cryptocurrency":
                        return new ProxyFabric<Cryptocurrency>().getJsonDaoProxy(file, Cryptocurrency.class);
                    case "monetaryunit":
                        return new ProxyFabric<MonetaryUnit>().getJsonDaoProxy(file, MonetaryUnit.class);
                    case "preciousmetal":
                        return new ProxyFabric<PreciousMetal>().getJsonDaoProxy(file, PreciousMetal.class);
                    case "stock":
                        return new ProxyFabric<Stock>().getJsonDaoProxy(file, Stock.class);
                }
                break;
            case "csv":
                switch (fileName){
                    case "cryptocurrency":
                        return new ProxyFabric<Cryptocurrency>().getCsvDaoProxy(file, Cryptocurrency.class);
                    case "monetaryunit":
                        return new ProxyFabric<MonetaryUnit>().getCsvDaoProxy(file, MonetaryUnit.class);
                    case "preciousmetal":
                        return new ProxyFabric<PreciousMetal>().getCsvDaoProxy(file, PreciousMetal.class);
                    case "stock":
                        return new ProxyFabric<Stock>().getCsvDaoProxy(file, Stock.class);
                }
                break;
        }
        throw new Exception();
    }

    private List<FinancialUnit> operation1(){//в порядке убывания максимальной разницы курса за год
        return list.stream().sorted(new Comparator<FinancialUnit>() {
            @Override
            public int compare(FinancialUnit o1, FinancialUnit o2) {
                double value1 = (o1.high52week - o1.low52week )/ o1.low52week;
                double value2 = (o2.high52week - o2.low52week )/ o2.low52week;
                return Double.compare(value2, value1);
            }
        }).collect(Collectors.toList());
    }

    private List<FinancialUnit> operation2(){//в порядке убывания цены за еденицу
        return list.stream().sorted(new Comparator<FinancialUnit>() {
            @Override
            public int compare(FinancialUnit o1, FinancialUnit o2) {
                return Double.compare(o2.current, o1.current);
            }
        }).collect(Collectors.toList());
    }
}
