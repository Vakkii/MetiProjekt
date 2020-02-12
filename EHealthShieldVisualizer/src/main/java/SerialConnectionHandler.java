import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortList;
public class SerialConnectionHandler{
    //COM POrt Variables
    String[] portNames;
    //Serial
    SerialPort serialPort;
    //datahandler
    private DataHandler dataHandler;



    public SerialConnectionHandler(DataHandler dataHandler) {
        this.dataHandler = dataHandler;
        portNames = SerialPortList.getPortNames();
    }
    public void setSerialPortByName(String portName){
            this.serialPort = new SerialPort(portName);
    }
    public String[] getComPorts()
    {
        return this.portNames;
    }
    public void startListening() throws Exception{
        // set port parameters
        try {
            this.serialPort.openPort();
            this.serialPort.setParams(9600, 8, 1, 0);
            (new Thread(new SerialReader(this.serialPort, this.dataHandler))).start();
        }catch (SerialPortException e) {
            e.printStackTrace();
        }



    }

}


