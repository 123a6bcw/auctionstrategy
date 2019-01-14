package ru.asgui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.File;
import java.io.FilenameFilter;

/*
Main class that simply runs application and has some general function.
 */
public class GuiMain extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("Welcome.fxml"));
        primaryStage.setTitle("Auction Strategy");
        primaryStage.setScene(new Scene(root, 1200, 900));
        primaryStage.show();
    }

    /*
    GUI executable supposed to be somewhere inside project directory, but not in it's root. This function finds filepath from position of this executable to some other file
    by given filepath from project's root by simply lifting up until finding given fileName. Name's conflicts gives undefined behaviour. If given file does not exist, throws exception.

    Required for portability.
     */
    static String findFile(String fileName) throws Exception {
        String pathname = "../";
        FilenameFilter filter = (dir, name) -> name.startsWith(fileName);

        for (int i = 1; i <= 10; i++) {
            if ((new File(pathname)).listFiles(filter) != null) {
                pathname += fileName;
                break;
            } else {
                pathname = pathname + "../";
            }

            if (i == 10) {
                throw (new Exception("Can't find file " + fileName));
            }
        }

        return pathname;
    }


    public static void main(String[] args) {
        launch(args);
    }
}
