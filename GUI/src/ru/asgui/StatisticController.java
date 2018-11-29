package ru.asgui;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.stage.FileChooser;

import java.io.*;
import java.lang.*;
import java.util.Scanner;

import javafx.scene.control.*;
import javafx.util.Pair;

public class StatisticController {
    @FXML private MenuItem numberOfAcceptedDeals;
    @FXML private Button getBack;
    @FXML private Button runCycle;
    @FXML private Button basicStatisticShow;
    @FXML private Label statisticLabel;
    private File f;

    @FXML
    protected void getOnWelcomeScreen(ActionEvent event) throws Exception {
        getBack.getScene().setRoot(FXMLLoader.load(getClass().getResource("Welcome.fxml")));
    }

    @FXML
    protected void startCycle(ActionEvent event) throws Exception {
        runCycle.getScene().setRoot(FXMLLoader.load(getClass().getResource("Cycle.fxml")));
    }

    public void getFile() {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Open log file");
        fileChooser.setInitialDirectory(new File(GuiMain.findFile("logs")));
        f = fileChooser.showOpenDialog(getBack.getScene().getWindow());
    }


    @FXML
    public void getNumberOfAcceptedDeals(ActionEvent actionEvent) throws IOException {
        getFile();
        BufferedReader reader = new BufferedReader(new FileReader(f));
        String line;
        String result = "";
        int acceptedDeals = 0;
        int currentCycle = 0;
        while ((line = reader.readLine()) != null) {
            Pair <String, String> code = getCode(line);
            Scanner s = new Scanner(code.getValue());
            if (code.getKey().length() > 0) {
                if (isAcceptedDeals(code.getKey())) {
                    acceptedDeals += s.nextInt();
                } else
                    if (isNewCycle(code.getKey())) {
                        if (currentCycle > 0)
                            result += Integer.toString(acceptedDeals) + " deals was accepted on " + Integer.toString(currentCycle - 1) + " cycle" + "\n";
                        acceptedDeals = 0;
                        currentCycle++;
                }
            }
        }

        statisticLabel.setText(result);
    }

    private Pair<String,String> getCode(String line) {
        int i = 0;
        while (i < line.length() && line.charAt(i) != ' ') {
            i++;
        }

        String result = line.substring(0, i);
        line = line.substring(i+1);
        return new Pair<>(result, line);
    }

    private boolean isNewCycle(String code) {
        return code.equals("CS");
    }

    private boolean isAcceptedDeals(String code) {
        return code.equals("ACD");
    }
}
