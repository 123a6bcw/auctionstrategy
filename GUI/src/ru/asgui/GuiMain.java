package ru.asgui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.File;
import java.io.FilenameFilter;

public class GuiMain extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("Welcome.fxml"));
        primaryStage.setTitle("Auction Strategy");
        primaryStage.setScene(new Scene(root, 800, 800));
        primaryStage.show();
    }

    static String findFile(String fileName) {
        String pathname = "../";
        FilenameFilter filter = new FilenameFilter() {
            @Override
            public boolean accept(File dir, String name) {
                return name.startsWith(fileName);
            }
        };

        while (true) {
            if ((new File(pathname)).listFiles(filter) != null) {
                pathname += fileName;
                break;
            } else {
                pathname = pathname + "../";
            }
        }

        return pathname;
    }


    public static void main(String[] args) {
        launch(args);
    }
}
