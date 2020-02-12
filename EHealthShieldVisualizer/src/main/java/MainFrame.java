import gnu.io.CommPortIdentifier;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.DefaultXYDataset;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Enumeration;

public class MainFrame implements Runnable{
    private JComboBox cBoxComPorts;
    private JButton butSelCom;
    private JLabel valuePulse;
    private JLabel valueOxi;
    private JPanel mainPanel;
    private JLabel valueTemperature;
    private JLabel labelPulse;
    private JLabel labelOxi;
    private JLabel labelTemperature;
    private JLabel labelPosition;
    private JLabel labelConductance;
    private JLabel labelBloodPressureSyst;
    private JLabel labelBloodPressureDias;
    private JLabel valuePosition;
    private JLabel valueConductance;
    private JLabel valueBloodPressureSys;
    private JLabel valueBloodPressureDias;
    private JLabel unitPulse;
    private JLabel unitOxi;
    private JLabel unitTemperature;
    private JLabel unitPosition;
    private JLabel unitConductance;
    private JLabel unitBloodPressureSys;
    private JLabel unitBloodPressureDias;
    private JPanel panelECG;
    private JPanel panelSensors;
    private JPanel panelValues;
    private JPanel panelUnits;
    private JPanel panelAnalysis;
    private JLabel analysisPulse;
    private JLabel analysisOxi;
    private JLabel analysisTemperature;
    private JLabel analysisPosition;
    private JLabel analysisConductance;
    private JLabel analysisBloodPressureSys;
    private JLabel analysisBloodPressureDias;
    private JPanel panelAirflow;
    private SerialConnectionHandler serialConnectionHandler;
    private DataHandler dataHandler;
    private double [] ecgArray;
    private double [] airflowArray;
    private double [] arraysXAxis;
    private int arrayCount;
    private ChartPanel cpECG;
    public MainFrame(SerialConnectionHandler connectionHandler, DataHandler dataHandler)  {
        this.panelSensors.setBorder(BorderFactory.createTitledBorder("Sensor"));
        this.panelValues.setBorder(BorderFactory.createTitledBorder("Value"));
        this.panelUnits.setBorder(BorderFactory.createTitledBorder("Unit"));
        this.panelAnalysis.setBorder(BorderFactory.createTitledBorder("Analysis"));
        this.ecgArray = new double[100];
        this.airflowArray = new double[100];
        this.arraysXAxis = new double[100];
        for(int i = 0; i < 100; i++){
            ecgArray[i] = 0.0;
            airflowArray[i] = 0.0;
            arraysXAxis[i] = i + 1;
        }
        this.panelECG.setBorder(BorderFactory.createTitledBorder("ECG"));
        this.panelAirflow.setBorder(BorderFactory.createTitledBorder("Airflow"));
        DefaultXYDataset dsECG = new DefaultXYDataset();
        double[][] dataECG = {this.arraysXAxis , this.arraysXAxis};
        dsECG.addSeries("Electrocardiogram", dataECG);
        JFreeChart chartECG =
                ChartFactory.createXYLineChart("Electrocardiogram",
                        "", " ", dsECG, PlotOrientation.VERTICAL, false, false,
                        false);
        this.cpECG = new ChartPanel(chartECG);
        this.cpECG.setSize((int)this.getMainPanel().getBounds().getWidth(), -1);
        this.panelECG.add(this.cpECG, BorderLayout.CENTER);
        this.panelAirflow.add(this.cpECG, BorderLayout.CENTER);
        //arrayCount = 0;
        this.dataHandler = dataHandler;
        this.serialConnectionHandler = connectionHandler;
        this.setComboBox();
        butSelCom.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
               serialConnectionHandler.setSerialPortByName(cBoxComPorts.getSelectedItem().toString());
                try {
                    serialConnectionHandler.startListening();
                }
                catch(Exception ex){
                    ex.printStackTrace();
                }
            }
        });
    }
    public void run(){
        System.out.println("Start thread: MainFrame");
        while(true) {
            //System.out.println("mainframe");
            if(this.dataHandler.isOxyIsEnabled()){
                this.valueOxi.setText(Integer.toString(this.dataHandler.getOxy()));
            }
            if(this.dataHandler.isPulseIsEnabled()) {
                this.valuePulse.setText(Integer.toString(this.dataHandler.getPulse()));
            }
            if(this.dataHandler.isTemperatureIsEnabled()) {
                this.valueTemperature.setText(Double.toString(this.dataHandler.getTemperature()));
            }
            if(this.dataHandler.isPositionIsEnabled()) {
                this.valuePosition.setText(this.dataHandler.getPosition());
            }
            if(this.dataHandler.isConductanceIsEnabled()){
                this.valueConductance.setText(Double.toString(this.dataHandler.getConductance()));
            }
            if(this.dataHandler.isBloodPressureSysIsEnabled()) {
                this.valueBloodPressureSys.setText(Integer.toString(this.dataHandler.getBloodPressureSys()));
            }
            if(this.dataHandler.isBloodPressureDiasIsEnabled()) {
                this.valueBloodPressureDias.setText(Integer.toString(this.dataHandler.getBloodPressureDias()));
            }
            if(this.dataHandler.isEcgIsEnabled()) {
                this.ecgArray[this.arrayCount] = this.dataHandler.getEcg();
                this.arrayCount++;
            }
            if(this.dataHandler.isAirflowIsEnabled()) {
                this.airflowArray[this.arrayCount] = this.dataHandler.getAirflow();
            }
            if(this.arrayCount == 100){
                this.arrayCount = 0;
            }
            //Create Plots
            this.cpECG.getChart().getXYPlot().setDataset(this.cpECG.getChart().getXYPlot().getDataset());

            /*try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }*/
        }

    }

    public JComboBox getcBoxComPorts() {
        return cBoxComPorts;
    }
    public void setPulseValue(int value){
        this.valuePulse.setText(Integer.toString(value));
    }
    public void setOxiValue(int value){
        this.valueOxi.setText(Integer.toString(value));
    }
    public void setComboBox(){
        int i = 0;
        String[] comports = this.serialConnectionHandler.getComPorts();
        for(i = 0; i < comports.length; i++){
            this.cBoxComPorts.insertItemAt(comports[i], i);
        }
        try {
            this.cBoxComPorts.setSelectedIndex(0);
        }catch(IndexOutOfBoundsException e ){
            System.out.println("No ComPort Connected, restart Application when Arduino is connected");
        }
    }

    public JPanel getMainPanel() {
        return mainPanel;
    }
}
