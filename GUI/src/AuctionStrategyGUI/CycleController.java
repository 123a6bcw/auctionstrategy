package AuctionStrategyGUI;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.scene.control.Label;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;

import java.io.*;

public class CycleController {
    @FXML
    private Button getBack;

    @FXML
    private Button runCycle;

    @FXML
    private TextField numberOfSellers;

    @FXML
    private TextField numberOfBuyers;

    @FXML
    private TextField totalSteps;

    @FXML
    private TextField movesInGame;

    @FXML
    private TextField howMuchToKill;

    @FXML
    private TextField pairSellers;

    @FXML
    private TextField pairBuyers;

    @FXML
    private TextField logFile;

    @FXML
    private Label errorLog;

    @FXML
    private GridPane gridPane;

    @FXML
    protected void getOnWelcomeScreen(ActionEvent event) throws Exception {
        getBack.getScene().setRoot(FXMLLoader.load(getClass().getResource("Welcome.fxml")));
    }

    @FXML
    public void initialize() {
        gridPane.getColumnConstraints().add(new ColumnConstraints(300));
        gridPane.getColumnConstraints().add(new ColumnConstraints(200));
        gridPane.getRowConstraints().add(new RowConstraints(100));
        for (int i = 1; i <= 16; i += 2) {
            gridPane.getRowConstraints().add(new RowConstraints(20));
            gridPane.getRowConstraints().add(new RowConstraints(10));
        }
        gridPane.getRowConstraints().add(new RowConstraints(5));
        gridPane.getRowConstraints().add(new RowConstraints(100));

        numberOfSellers.setText("10");
        numberOfBuyers.setText("10");
        totalSteps.setText("10");
        movesInGame.setText("10");
        howMuchToKill.setText("2");
        pairSellers.setText("1");
        pairBuyers.setText("1");
        logFile.setText("basicLog.txt");
    }

    @FXML
    protected void runCycle(MouseEvent event) throws Exception {
        errorLog.setText("");
        String command = "../build/auctionGame";
        command += " " + numberOfSellers.getText();
        command += " " + numberOfBuyers.getText();
        command += " " + totalSteps.getText();
        command += " " + movesInGame.getText();
        command += " " + howMuchToKill.getText();
        command += " " + pairSellers.getText();
        command += " " + pairBuyers.getText();
        command += " " + logFile.getText();

        Process p = Runtime.getRuntime().exec(command);

        BufferedReader reader =
                new BufferedReader(new InputStreamReader(p.getErrorStream()));

        String sb = "";
        String line = "";
        while ((line = reader.readLine())!= null) {
            sb += line + "\n";
        }

        if (!sb.equals("")) {
            errorLog.setText(sb);
        } else {
            errorLog.setText("Cycle successfully ended.\nYour results has been put into\nlog/" + logFile.getText());
        }
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
}
