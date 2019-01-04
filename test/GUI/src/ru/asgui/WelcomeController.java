package ru.asgui;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

public class WelcomeController {
    @FXML private Button runCycle;
    @FXML private Button runLogView;
    @FXML private Label mainLabel;

    @FXML
    public void initialize() {
        mainLabel.setText("Hello! \n\n" +
                "Welcome to genetic algorithm on auction game problem.\n\n" +
                "Please use the toolbar above.\n" +
                "First option let's you run new genetic cycle with custom parameters. It will create log file which you could later see using second option in this menu");
    }

    @FXML
    protected void startCycle(ActionEvent event) throws Exception {
        runCycle.getScene().setRoot(FXMLLoader.load(getClass().getResource("Cycle.fxml")));
    }

    @FXML
    protected void viewLogFile(ActionEvent event) throws Exception {
        runCycle.getScene().setRoot(FXMLLoader.load(getClass().getResource("Statistic.fxml")));
    }
}
