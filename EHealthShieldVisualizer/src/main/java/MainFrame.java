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
        ecgArray = new double[100];
        airflowArray = new double[100];
        arraysXAxis = new double[100];
        for(int i = 0; i < 100; i++){
            ecgArray[i] = 0.0;
            airflowArray[i] = 0.0;
            arraysXAxis[i] = i + 1;
        }
        this.panelECG.setBorder(BorderFactory.createTitledBorder("ECG"));
        DefaultXYDataset dsECG = new DefaultXYDataset();
        double[][] dataECG = {this.arraysXAxis , this.ecgArray};
        dsECG.addSeries("Electrocardiogram", dataECG);
        JFreeChart chartECG =
                ChartFactory.createXYLineChart("Electrocardiogram",
                        "Time", " ", dsECG, PlotOrientation.VERTICAL, false, false,
                        false);
        this.cpECG = new ChartPanel(chartECG);
        this.cpECG.setSize((int)this.getMainPanel().getBounds().getWidth(), -1);
        this.panelECG.add(this.cpECG, BorderLayout.CENTER);
        arrayCount = 0;
        this.dataHandler = dataHandler;
        this.serialConnectionHandler = connectionHandler;
        this.setComboBox();
        butSelCom.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
               serialConnectionHandler.setSerialPortByID(cBoxComPorts.getSelectedIndex());
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
        while(true) {
            //System.out.println("mainframe");
            this.valueOxi.setText(Integer.toString(this.dataHandler.getOxy()));
            //System.out.println(this.dataHandler.getOxy());
            this.valuePulse.setText(Integer.toString(this.dataHandler.getPulse()));
            //System.out.println(this.dataHandler.getPulse());
            this.valueTemperature.setText(Double.toString(this.dataHandler.getTemperature()));
            this.valuePosition.setText(this.dataHandler.getPosition());
            this.valueConductance.setText(Double.toString(this.dataHandler.getConductance()));
            this.valueBloodPressureSys.setText(Integer.toString(this.dataHandler.getBloodPressureSys()));
            this.valueBloodPressureDias.setText(Integer.toString(this.dataHandler.getBloodPressureDias()));
            this.ecgArray[this.arrayCount] = this.dataHandler.getEcg();
            this.airflowArray[this.arrayCount] = this.dataHandler.getAirflow();
            if(this.arrayCount == 99){
                this.arrayCount = 0;
            }
            this.arrayCount++;
            //Create Plots
            this.cpECG.getChart().getXYPlot().setDataset(this.cpECG.getChart().getXYPlot().getDataset());

            try {
                Thread.sleep(10);
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
        Enumeration comports = this.serialConnectionHandler.getComPorts();
        CommPortIdentifier serialPortId;
        while(comports.hasMoreElements()){
            serialPortId = (CommPortIdentifier)comports.nextElement();
            this.cBoxComPorts.insertItemAt(serialPortId.getName(), i++);
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
