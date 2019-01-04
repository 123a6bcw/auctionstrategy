package ru.asgui;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.control.Tooltip;
import javafx.scene.input.MouseEvent;
import javafx.scene.control.Label;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import javafx.util.Pair;

import java.io.*;

public class CycleController {
    @FXML public Label numberOfSellersLabel;
    @FXML public Label numberOfBuyersLabel;
    @FXML public Label numberOfStepsLabel;
    @FXML public Label numberOfMovesLabel;
    @FXML public Label numberOfPlayersDyingLabel;
    @FXML public Label numberOfSellerPairingLabel;
    @FXML public Label numberOfBuyerPairingLabel;
    @FXML public Label nameOfLogFileLabel;
    @FXML private Button getBack;
    @FXML private Button runCycle;
    @FXML private TextField numberOfSellers;
    @FXML private TextField numberOfBuyers;
    @FXML private TextField totalSteps;
    @FXML private TextField movesInGame;
    @FXML private TextField howMuchToKill;
    @FXML private TextField pairSellers;
    @FXML private TextField pairBuyers;
    @FXML private TextField logFile;
    @FXML private Label errorLog;
    @FXML private GridPane gridPane;
    @FXML private Button basicSettings;
    @FXML private Button largeSettings;
    @FXML private Button runLogView;
    @FXML private Label header;
    private SimpleDateFormat sdf;
    private int currentCycle;

    @FXML
    protected void getOnWelcomeScreen(ActionEvent event) throws Exception {
        getBack.getScene().setRoot(FXMLLoader.load(getClass().getResource("Welcome.fxml")));
    }

    @FXML
    public void initialize() {
        currentCycle = 1;
        sdf = new SimpleDateFormat("-MM.dd-HH:mm:ss");
        gridPane.getColumnConstraints().add(new ColumnConstraints(300));
        gridPane.getColumnConstraints().add(new ColumnConstraints(200));
        gridPane.getColumnConstraints().add(new ColumnConstraints(200));
        gridPane.getRowConstraints().add(new RowConstraints(100));
        for (int i = 1; i <= 18; i += 2) {
            gridPane.getRowConstraints().add(new RowConstraints(20));
            gridPane.getRowConstraints().add(new RowConstraints(10));
        }
        gridPane.getRowConstraints().add(new RowConstraints(5));
        gridPane.getRowConstraints().add(new RowConstraints(5));
        gridPane.getRowConstraints().add(new RowConstraints());
        header.setText("Please specify parameters of the cycle\nMove Mouse on label to see the tooltip");
        basicSettings.fire();

        numberOfSellersLabel.setTooltip(new Tooltip("How many sellers exists on each step of cycle\nDon't forget, that program works in (number of players) * (number of cycle steps) * (number of moves in game)"));
        numberOfBuyersLabel.setTooltip(new Tooltip("How many buyers exists on each step of cycle"));
        numberOfStepsLabel.setTooltip(new Tooltip("Each step is game between each players and genetic transformation"));
        numberOfMovesLabel.setTooltip(new Tooltip("Number of moves in every game between two players"));
        numberOfPlayersDyingLabel.setTooltip(new Tooltip("On each step of cycle worst players are dying"));
        numberOfSellerPairingLabel.setTooltip(new Tooltip("Don't change. Only single Pairing function implemented"));
        numberOfBuyerPairingLabel.setTooltip(new Tooltip("Don't change. Only single Pairing function implemented"));
        nameOfLogFileLabel.setTooltip(new Tooltip("Don't be scared of conflicting names - current time will be append to the name"));
    }

    private void setSettings(Integer numberOfSellers, Integer numberOfBuyers, Integer totalSteps, Integer movesInGame, Integer howMuchToKill, Integer pairSellers, Integer pairBuyers, String logFile) {
        this.numberOfSellers.setText(numberOfSellers.toString());
        this.numberOfBuyers.setText(numberOfBuyers.toString());
        this.totalSteps.setText(totalSteps.toString());
        this.movesInGame.setText(movesInGame.toString());
        this.howMuchToKill.setText(howMuchToKill.toString());
        this.pairSellers.setText(pairSellers.toString());
        this.pairBuyers.setText(pairBuyers.toString());
        this.logFile.setText(logFile);
    }

    @FXML
    protected void setBasicSettings(ActionEvent event) {
        setSettings(10,10,10,10,2,1,1,"basicLog.txt");
    }

    @FXML
    protected void setLargeSettings(ActionEvent event) {
        setSettings(50,50,50,50,5,1,1,"largeLog.txt");
    }

    @FXML
    protected void setExtraLargeSettings(ActionEvent event) {
        setSettings(100,100,100,100,10,1,1,"extraLargeLog.txt");
    }

    private Pair<String, String> getExtension(String s) {
        int i;
        for (i = s.length() - 1; i >= 0; i--) {
            if (s.charAt(i) == '.') {
                break;
            }
        }

        if (i < 0) {
            return new Pair<>(s, "");
        }

        return new Pair<>(s.substring(0, i), s.substring(i));
    }

    private String getOutput(BufferedReader buffer) throws Exception {
        String line;
        StringBuilder sb = new StringBuilder();
        while ((line = buffer.readLine()) != null) {
            sb.append(line).append("\n");
        }

        return sb.toString();
    }

    @FXML
    protected void runCycle(ActionEvent event) throws Exception {
        long startTime = System.currentTimeMillis();

        errorLog.setText("");

        Pair<String, String> extension = getExtension(logFile.getText());
        String logFileExtended = extension.getKey() + sdf.format(Calendar.getInstance().getTime()) + extension.getValue();
        String command = GuiMain.findFile("build/auctionGame");
        ProcessBuilder builder = new ProcessBuilder(command, numberOfSellers.getText(), numberOfBuyers.getText(), totalSteps.getText(),
                movesInGame.getText(), howMuchToKill.getText(), pairSellers.getText(), pairBuyers.getText(), logFileExtended);
        Process process = builder.start();
        process.waitFor();

        if (process.exitValue() != 0) {
            BufferedReader errorBuffer =
                    new BufferedReader(new InputStreamReader(process.getErrorStream()));
            String result = getOutput(errorBuffer);

            errorLog.setText("Cycle " + currentCycle +  " finished with error:\n" + result);
        } else {
            BufferedReader outputBuffer =
                    new BufferedReader(new InputStreamReader(process.getInputStream()));
            String result = getOutput(outputBuffer);

            long stopTime = System.currentTimeMillis();
            double elapsedTime = stopTime - startTime;
            elapsedTime /= 1000;
            errorLog.setText("Cycle " + currentCycle + " successfully ended.\n\nYour results has been put into\nlogs/" + logFileExtended + "\n\nExecution time: " + elapsedTime + " seconds");
        }

        currentCycle++;

        header.setText("Cycle " + (currentCycle-1) + " finished\n" + "Please specify parameters of the " + currentCycle + " cycle");
    }

    @FXML
    protected void showNumberOfSellersInfo(MouseEvent event) {

    }

    @FXML
    protected void showNumberOfBuyersInfo(MouseEvent event) {

    }

    @FXML
    protected void showTotalStepsInfo(MouseEvent event) {

    }

    @FXML
    protected void MovesInGame(MouseEvent event) {

    }

    @FXML
    protected void showHowMuchToKillInfo(MouseEvent event) {

    }

    @FXML
    protected void showPairSellersInfo(MouseEvent event) {

    }

    @FXML
    protected void showPairBuyersInfo(MouseEvent event) {

    }

    @FXML
    protected void showLogFileInfo(MouseEvent event) {

    }

    @FXML
    protected void viewLogFile(ActionEvent event) throws Exception {
        runLogView.getScene().setRoot(FXMLLoader.load(getClass().getResource("Statistic.fxml")));
    }
}
