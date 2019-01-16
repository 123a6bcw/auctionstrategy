package ru.asgui;

import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.*;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import javafx.util.Pair;
import javafx.application.Platform;

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
    @FXML public Label scenarioNumberLabel;
    @FXML public Button stopCycle;
    @FXML protected Button getBack;
    @FXML protected Button runCycle;
    @FXML protected TextField numberOfSellers;
    @FXML protected TextField numberOfBuyers;
    @FXML protected TextField totalSteps;
    @FXML protected TextField movesInGame;
    @FXML protected TextField howMuchToKill;
    @FXML protected TextField pairSellers;
    @FXML protected TextField pairBuyers;
    @FXML protected TextField scenarioNumber;
    @FXML protected TextField logFile;
    @FXML protected Label errorLog;
    @FXML protected GridPane gridPane;
    @FXML protected Button basicSettings;
    @FXML protected Button largeSettings;
    @FXML protected Button runLogView;
    @FXML protected Label header;
    private SimpleDateFormat sdf;
    private int currentCycle;

    @FXML
    protected void getOnWelcomeScreen(ActionEvent event) throws Exception {
        getBack.getScene().setRoot(FXMLLoader.load(getClass().getResource("Welcome.fxml")));
    }

    @FXML
    public void initialize() {
        currentCycle = 1; // Number of past cycles show on the top so the user won't be confused whether current cycle has ended or not. Wanted to add progress bar but too hard
        sdf = new SimpleDateFormat("-MM.dd-HH:mm:ss");  // Current date and time is added to log file's name so there will be no name's conflicts
        gridPane.getColumnConstraints().add(new ColumnConstraints(300));
        gridPane.getColumnConstraints().add(new ColumnConstraints(300));
        gridPane.getColumnConstraints().add(new ColumnConstraints(300));
        gridPane.getRowConstraints().add(new RowConstraints(100));
        for (int i = 1; i <= 20; i += 2) {
            gridPane.getRowConstraints().add(new RowConstraints(20));
            gridPane.getRowConstraints().add(new RowConstraints(10));
        }
        gridPane.getRowConstraints().add(new RowConstraints(5));
        gridPane.getRowConstraints().add(new RowConstraints(5));
        gridPane.getRowConstraints().add(new RowConstraints());
        header.setText("Please specify parameters of the cycle\nMove Mouse on label to see the tooltip");
        basicSettings.fire(); //initialise basic settings to the text fields

        numberOfSellersLabel.setTooltip(new Tooltip("How many sellers exists on each step of cycle\nDon't forget, that program works in (number of players) * (number of cycle steps) * (number of moves in game)"));
        numberOfBuyersLabel.setTooltip(new Tooltip("How many buyers exists on each step of cycle"));
        numberOfStepsLabel.setTooltip(new Tooltip("Each step is game between each players and genetic transformation"));
        numberOfMovesLabel.setTooltip(new Tooltip("Number of moves in every game between two players"));
        numberOfPlayersDyingLabel.setTooltip(new Tooltip("On each step of cycle worst players are dying"));
        numberOfSellerPairingLabel.setTooltip(new Tooltip("Don't change. Only single Pairing function implemented"));
        numberOfBuyerPairingLabel.setTooltip(new Tooltip("Don't change. Only single Pairing function implemented"));
        nameOfLogFileLabel.setTooltip(new Tooltip("Don't be scared of conflicting names - current time will be append to the name"));
        scenarioNumberLabel.setTooltip(new Tooltip("1: default scenario without anything special"));
        //progressIndicator.setProgress(5);
        stopCycle.setDisable(true); //pressing this button before cycleThread is started causing error
    }

    /*
    Set setting of the cycle to the corresponding text fields. Helps to set common settings by pressing corresponding button.
     */
    private void setSettings(Integer numberOfSellers, Integer numberOfBuyers, Integer totalSteps, Integer movesInGame, Integer howMuchToKill, Integer pairSellers, Integer pairBuyers, String logFile, Integer scenarioNumber) {
        this.numberOfSellers.setText(numberOfSellers.toString());
        this.numberOfBuyers.setText(numberOfBuyers.toString());
        this.totalSteps.setText(totalSteps.toString());
        this.movesInGame.setText(movesInGame.toString());
        this.howMuchToKill.setText(howMuchToKill.toString());
        this.pairSellers.setText(pairSellers.toString());
        this.pairBuyers.setText(pairBuyers.toString());
        this.logFile.setText(logFile);
        this.scenarioNumber.setText(scenarioNumber.toString());
    }

    @FXML
    protected void setBasicSettings(ActionEvent event) {
        setSettings(10,10,10,10,2,1,1,"basicLog.txt", 1);
    }

    @FXML
    protected void setLargeSettings(ActionEvent event) {
        setSettings(50,50,50,50,5,1,1,"largeLog.txt", 1);
    }

    @FXML
    protected void setExtraLargeSettings(ActionEvent event) {
        setSettings(100,100,100,100,10,1,1,"extraLargeLog.txt", 1);
    }

    /*
    Get last extension from the file's name.
    "someFileName.txt" -> ("someFileName", ".txt")
    "justFileName" (without extension) -> ("justFileName", "")
     */
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

    /*
    Gets all content of some BufferedReader
     */
    private String getOutput(BufferedReader buffer) throws Exception {
        String line;
        StringBuilder sb = new StringBuilder();
        while ((line = buffer.readLine()) != null) {
            sb.append(line).append("\n");
        }

        return sb.toString();
    }

    private Thread cycleThread; //saving this so we could safely close this thread pressing another button
    private volatile boolean exitCycle = false; // when true thread with cycle should stop

    /*
    runs cycle after filling all text fields with settings
     */
    @FXML
    protected void runCycle(ActionEvent event) throws Exception {
        /*
         Use of thread is necessity to update the progress of the process online
          */
        cycleThread = new Thread(new CycleTask());
        cycleThread.start();
    }

    /*
    Go to page with viewing log file
     */
    @FXML
    protected void viewLogFile(ActionEvent event) throws Exception {
        runLogView.getScene().setRoot(FXMLLoader.load(getClass().getResource("Statistic.fxml")));
    }

    @FXML
    public void stopCycle(ActionEvent actionEvent) throws Exception {
        exitCycle = true;
        while (cycleThread.isAlive()) {
        }
        runCycle.setDisable(false);
        stopCycle.setDisable(true);
        exitCycle = false;
    }

    /*
       Thread of running process with cycle
     */
    class CycleTask extends Task<Void> {
        private void afterStop(Process process, String logFile) {
            process.destroy();
            Platform.runLater(() -> errorLog.setText(errorLog.getText() + "\nExecution interrupted\nbeware of unfinished logs/" + logFile));
        }

        @Override
        protected Void call() throws Exception {
            long startTime = System.currentTimeMillis();
            Platform.runLater(() -> runCycle.setDisable(true));
            Platform.runLater(() -> stopCycle.setDisable(false));

            Platform.runLater(() -> errorLog.setText(""));

            // "filename" + ".extension" -> "filename" + "current time" + ".extension"
            Pair<String, String> extension = getExtension(logFile.getText());
            String logFileExtended = extension.getKey() + sdf.format(Calendar.getInstance().getTime()) + extension.getValue();

            //path to the earlier built C++ project
            String command = GuiMain.findFile("build/auctionGame");
            //bash command to run project. Windows not supported.
            ProcessBuilder builder = new ProcessBuilder(command, numberOfSellers.getText(), numberOfBuyers.getText(), totalSteps.getText(),
                    movesInGame.getText(), howMuchToKill.getText(), pairSellers.getText(),
                    pairBuyers.getText(), scenarioNumber.getText(), logFileExtended);

            Process process = builder.start();

            /*
            updating progress of process. After finishing cycle step, process prints current step to output. This cycle reads it
            and updates log label accordingly
             */
            String line = "";
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            int numberOfSteps = Integer.parseInt(totalSteps.getText());
            int currentStep = 0;
            while (currentStep < numberOfSteps) {
                if (exitCycle) {
                    //someone called this thread to stop
                    afterStop(process, logFileExtended);
                    return null;
                }

                while ((line = reader.readLine()) != null) {
                    if (exitCycle) {
                        //someone called this cycle to stop
                        afterStop(process, logFileExtended);
                        return null;
                    }

                    if (line.equals("Error")) {
                        //execution of cycle caused error. Breaking from cycle so error log would be printed
                        currentStep = numberOfSteps; //cause external while to break
                        break;
                    }

                    final String currentRes = "Finished " + line + " steps out of " + numberOfSteps;
                    Platform.runLater(() -> errorLog.setText(currentRes));
                    currentStep = Integer.parseInt(line);

                }
                //Thread.sleep(200);
            }

            process.waitFor();
            if (process.exitValue() != 0) {
                //project execution ended with error.
                BufferedReader errorBuffer =
                        new BufferedReader(new InputStreamReader(process.getErrorStream()));
                String result = getOutput(errorBuffer);

                Platform.runLater(() -> errorLog.setText("Cycle " + currentCycle +  " finished with error:\n" + result));
            } else {
            /*
            following code is unused.

            BufferedReader outputBuffer =
                    new BufferedReader(new InputStreamReader(process.getInputStream()));
            String result = getOutput(outputBuffer);
            */

                long stopTime = System.currentTimeMillis();
                final double elapsedTime = ((double)(stopTime - startTime)) / 1000;

                Platform.runLater(() -> errorLog.setText("Cycle " + currentCycle +
                         " successfully ended.\n\nYour results has been put into\nlogs/" + logFileExtended + "\n\nExecution time: " + elapsedTime + " seconds"));
            }

            Platform.runLater(() -> currentCycle++);
            Platform.runLater(() -> header.setText("Cycle " + (currentCycle-1) + " finished\n" + "Please specify parameters of the " + currentCycle + " cycle"));
            Platform.runLater(() -> runCycle.setDisable(false));
            Platform.runLater(() -> stopCycle.setDisable(true));
            return null;
        }
    }
}