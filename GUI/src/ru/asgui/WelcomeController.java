package ru.asgui;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

/*
Welcome screen.
 */

public class WelcomeController {
    // @FXML private Button runCycle; // unused
    // @FXML private Button runLogView; // unused
    @FXML private Label mainLabel;

    /*
    Set welcome text
     */
    @FXML
    public void initialize() {
        mainLabel.setText("Hello! \n\n" +
                "Welcome to genetic algorithm on auction game problem.\n\n" +
                "Please use the toolbar above.\n" +
                "First option let's you run new genetic cycle with custom parameters. It will create log file which you could later see using second option in this menu");
    }

    /*
    Change to page for running new cycles after pressing button runCycle
     */
    @FXML
    protected void startCycle(ActionEvent event) throws Exception {
        mainLabel.getScene().setRoot(FXMLLoader.load(getClass().getResource("Cycle.fxml")));
    }

    /*
    Change to page for getting statistic after pressing button runLogView
     */
    @FXML
    protected void viewLogFile(ActionEvent event) throws Exception {
        mainLabel.getScene().setRoot(FXMLLoader.load(getClass().getResource("Statistic.fxml")));
    }
}
