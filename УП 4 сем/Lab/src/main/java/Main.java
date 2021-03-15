import controllers.MainController;

import java.io.FileWriter;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        MainController.sharedInstance().start();
    }
}
