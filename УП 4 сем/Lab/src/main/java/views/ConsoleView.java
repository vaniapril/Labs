package views;

import models.units.FinancialUnit;

import java.util.List;
import java.util.Scanner;
import java.util.function.Consumer;

public class ConsoleView {
    Scanner scanner;

    public ConsoleView(){
        scanner = new Scanner(System.in);
    }

    public void wrongFileNameAlert(String fileName){
        System.out.println("Неверное расширение файла: " + fileName);
    }

    public void validationErrorAlert(){
        System.out.println("Ошибка валидации!");
    }

    public void fineNotExistAlert(String fileName){
        System.out.println("Файл не существует: " + fileName);
    }

    public void wrongOperationAlert(){
        System.out.println("Недопустимая операция.");
    }

    public void cannotReadFileAlert(String fileName){
        System.out.println("Не удалось прочитать файл: " + fileName);
    }

    public int operationTypeDialog(){
        System.out.println("Выберете операцию:");
        System.out.println("1. Данные в порядке убывания максимальной процентной разницы курса за год");
        System.out.println("2. Данные в порядке убывания цены за еденицу");
        try {
            return scanner.nextInt();
        } catch (Exception e){
            return 0;
        }
    }

    public String fileNameDialog(){
        System.out.println("Введите название файла:");
        return "in/monetaryunit.csv";/*
        try {
            return scanner.nextLine();
        } catch (Exception e){
            return "";
        }*/
    }

    public void showData(List<FinancialUnit> list){
        list.forEach(new Consumer<FinancialUnit>() {
            @Override
            public void accept(FinancialUnit financialUnit) {
                System.out.println(financialUnit);
            }
        });
    }
}
