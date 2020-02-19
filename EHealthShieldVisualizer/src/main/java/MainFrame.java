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
    private static int graphSize = 400;
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
    DefaultXYDataset dsECG;
    DefaultXYDataset dsAirflow;

    private double [] arraysXAxis;
    private int arrayCount;
    private Plot plotECG;
    private Plot plotAirflow;
    public MainFrame(SerialConnectionHandler connectionHandler, DataHandler dataHandler)  {
        this.dataHandler = dataHandler;
        this.panelSensors.setBorder(BorderFactory.createTitledBorder("Sensor"));
        this.panelValues.setBorder(BorderFactory.createTitledBorder("Value"));
        this.panelUnits.setBorder(BorderFactory.createTitledBorder("Unit"));
        this.panelAnalysis.setBorder(BorderFactory.createTitledBorder("Analysis"));
        this.arraysXAxis = new double[100];
        for(int i = 0; i < 100; i++){
            arraysXAxis[i] = i + 1;
        }
        //Borders
        this.panelECG.setBorder(BorderFactory.createTitledBorder("ECG"));
        this.panelAirflow.setBorder(BorderFactory.createTitledBorder("Airflow"));
        //create Datasets
        this.dsECG = new DefaultXYDataset();
        double[][] dataECG = {this.arraysXAxis , this.dataHandler.getEcg()};
        this.dsECG.addSeries("Electrocardiogram", dataECG);
        this.dsAirflow = new DefaultXYDataset();
        double[][] dataAirflow = {this.arraysXAxis , this.dataHandler.getAirflow()};
        this.dsAirflow.addSeries("Airflow", dataAirflow);
        //create Plot classes
        this.plotECG = new Plot("Electrocardiogram", dsECG, this.mainPanel.getPreferredSize().width/2);
        this.panelECG.add(plotECG, BorderLayout.CENTER);
        this.plotAirflow = new Plot("Airflow", dsAirflow, this.mainPanel.getPreferredSize().width/2);
        this.panelAirflow.add(this.plotAirflow, BorderLayout.CENTER);
        //stuff
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
                //Update Plots
                DefaultXYDataset dsECG = new DefaultXYDataset();
                double[][] dataECG = {this.arraysXAxis , this.dataHandler.getEcg()};
                dsECG.addSeries("Electrocardiogram", dataECG);
                this.plotECG.update(dsECG);
                this.arrayCount++;
            }
            if(this.dataHandler.isAirflowIsEnabled()) {
                this.dsAirflow = new DefaultXYDataset();
                double[][] dataAirflow = {this.arraysXAxis , this.dataHandler.getAirflow()};
                this.dsAirflow.addSeries("Airflow", dataAirflow);
            }

            try {
                Thread.sleep(0);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

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
            try{
                this.cBoxComPorts.setSelectedIndex(0);
            }catch(IllegalArgumentException e){
                JOptionPane.showMessageDialog(mainPanel, "No COM-Port Connection found, connect device and restart.");
                System.out.println(e);
            }
        }catch(IndexOutOfBoundsException e ){
            System.out.println("No ComPort Connected, restart Application when Arduino is connected");
        }
    }

    public JPanel getMainPanel() {
        return mainPanel;
    }
}
