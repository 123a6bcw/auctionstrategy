package ru.asgui;

import com.sun.xml.internal.ws.policy.privateutil.PolicyUtils;
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

import javax.jnlp.FileContents;
import javax.jnlp.FileSaveService;

/*
class for converting coded statistic inside logfile to some readable information.
TODO more statistic items? graphics?
 */

public class StatisticController {
    // @FXML private MenuItem numberOfAcceptedDeals; //unused
    @FXML private Button getBack;
    @FXML private Button runCycle;
    //@FXML private Button basicStatisticShow; //unused
    @FXML private Label statisticLabel;
    private File logFile;

    /*
    change page to welcome page
     */
    @FXML
    protected void getOnWelcomeScreen(ActionEvent event) throws Exception {
        getBack.getScene().setRoot(FXMLLoader.load(getClass().getResource("Welcome.fxml")));
    }

    /*
    change page to cycle page
     */

    @FXML
    protected void startCycle(ActionEvent event) throws Exception {
        runCycle.getScene().setRoot(FXMLLoader.load(getClass().getResource("Cycle.fxml")));
    }

    /*
    create dialog screen to choose logFile one wants to use
     */
    private void getFile() throws Exception {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Open log file");
        fileChooser.setInitialDirectory(new File(GuiMain.findFile("logs")));
        logFile = fileChooser.showOpenDialog(getBack.getScene().getWindow());
    }

    /*

     */
    @FXML
    private void saveFile() throws Exception {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Save log file");
        fileChooser.setInitialDirectory(new File(GuiMain.findFile("logs/transformed")));
        File saveFile = fileChooser.showSaveDialog(getBack.getScene().getWindow());
        if (saveFile != null) {
            FileWriter fileWriter = new FileWriter(saveFile);
            fileWriter.write(statisticLabel.getText());
            fileWriter.close();
        }
    }

    @FXML
    public void getNumberOfAcceptedDeals(ActionEvent actionEvent) throws Exception, IOException {
        getFile();
        BufferedReader reader = new BufferedReader(new FileReader(logFile));
        String line;
        StringBuilder result = new StringBuilder();
        int currentCycle = 0;
        while ((line = reader.readLine()) != null) {
            Pair <String, String> code = getCode(line);
            if (code.getKey().length() > 0) {
                if (isAcceptedDeals(code.getKey())) {
                    result.append(code.getValue()).append(" deals was accepted on ").append(currentCycle - 1).append(" cycle").append("\n");
                } else
                if (isNewCycle(code.getKey())) {
                    currentCycle++;
                }
            }
        }

        statisticLabel.setText(result.toString());
    }

    @FXML
    public void getStrategiesInfo(ActionEvent actionEvent) throws Exception, IOException {
        getFile();
        BufferedReader reader = new BufferedReader(new FileReader(logFile));
        String line;
        StringBuilder result = new StringBuilder();
        int currentCycle = 0;
        while ((line = reader.readLine()) != null) {
            Pair <String, String> code = getCode(line);
            if (code.getKey().length() > 0) {
                if (isStrategiesOverall(code.getKey())) {
                    result.append("Overall usage of ");
                    if (isSeller(code.getKey())) {
                        result.append("sellers ");
                    } else {
                        result.append("buyers ");
                    }
                    result.append("strategies in moves played:\n");
                    result.append(code.getValue()).append("\n");
                } else
                if (isStrategyPlayers(code.getKey())) {
                    result.append("Players number of ");
                    if (isSeller(code.getKey())) {
                        result.append("sellers ");
                    } else {
                        result.append("buyers ");
                    }
                    result.append("strategies:\n");
                    result.append(code.getValue()).append("\n");
                } else
                if (isNewCycle(code.getKey())) {
                    currentCycle++;
                    if (currentCycle != 1) {
                        result.append("\n");
                    }
                    result.append(currentCycle).append(" cycle:\n");
                }
            }
        }

        statisticLabel.setText(result.toString());
    }

    @FXML
    public void getGainInfo(ActionEvent actionEvent) throws Exception, IOException {
        getFile();
        BufferedReader reader = new BufferedReader(new FileReader(logFile));
        String line;
        StringBuilder result = new StringBuilder();
        int currentCycle = 0;
        while ((line = reader.readLine()) != null) {
            Pair <String, String> code = getCode(line);
            if (code.getKey().length() > 0) {
                if (isOverallGain(code.getKey())) {
                    result.append("Overall ");
                } else
                if (isAverageGain(code.getKey())) {
                    result.append("Average ");
                } else
                if (isAverageGainPerGame(code.getKey())) {
                    result.append("Average per game ");
                }

                if (isOverallGain(code.getKey()) || isAverageGain(code.getKey()) || isAverageGainPerGame(code.getKey())) {
                    if (isSeller(code.getKey())) {
                        result.append("sellers ");
                    } else {
                        result.append("buyers ");
                    }
                    result.append("gain: ");
                    result.append(code.getValue()).append(" ");
                    for (int i = code.getValue().length(); i < 12; i++) {
                        result.append(" ");
                    }
                }

                if (isAverageGainPerGame(code.getKey())) {
                    result.append("\n");
                    if (!isSeller(code.getKey())) {
                        result.append("\n");
                    }
                }

                if (isNewCycle(code.getKey())) {
                    currentCycle++;
                    result.append(currentCycle).append(" cycle:\n");
                }
            }
        }

        statisticLabel.setText(result.toString());
    }

    /*
     each line in logfile starts with several symbols that codes what type of information is in this line.
     functions chops this code from string
     */
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
    private boolean isSeller(String code) { return (code.charAt(0) == 'S');}
    private boolean isAcceptedDeals(String code) {
        return code.equals("WS");
    }
    private boolean isStrategiesOverall(String code) {
        return code.equals("SSO") || code.equals("BSO");
    }
    private boolean isStrategyPlayers(String code) {
        return code.equals("SSP") || code.equals("BSP");
    }
    private boolean isOverallGain(String code) {
        return code.equals("SOG") || code.equals("BOG");
    }
    private boolean isAverageGain(String code) {
        return code.equals("SAG") || code.equals("BAG");
    }
    private boolean isAverageGainPerGame(String code) {
        return code.equals("SAGPG") || code.equals("BAGPG");
    }
}
