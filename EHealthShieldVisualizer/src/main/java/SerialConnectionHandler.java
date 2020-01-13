import gnu.io.*;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;

public class SerialConnectionHandler{
    //COM POrt Variables
    CommPortIdentifier serialPortId;
    Enumeration portEnumeration;
    //Serial
    SerialPort serialPort;
    public  char[] c;
    //Connection Variablers
    private InputStream input;
    private OutputStream output;
    private static final int TIME_OUT = 2000;
    private static final int DATA_RATE = 9600;
    private DataHandler dataHandler;


    public SerialConnectionHandler(DataHandler dataHandler) {
        this.dataHandler = dataHandler;
        this.portEnumeration = CommPortIdentifier.getPortIdentifiers();
    }
    public void setSerialPortByID(int id){
        int i = 0;
        while(portEnumeration.hasMoreElements()){
            if (i == id) {
                this.serialPortId = (CommPortIdentifier) portEnumeration.nextElement();
                break;
            }
            else{
                portEnumeration.nextElement();
                i++;
            }
        }
    }
    public Enumeration getComPorts() {
        return CommPortIdentifier.getPortIdentifiers();
    }
    public void startListening() throws Exception{
            serialPort = (SerialPort) this.serialPortId.open(this.getClass().getName(),
                    TIME_OUT);
            // set port parameters
            if( serialPort instanceof SerialPort ) {
                SerialPort sserialPort = ( SerialPort )serialPort;
                serialPort.setSerialPortParams( DATA_RATE,
                        SerialPort.DATABITS_8,
                        SerialPort.STOPBITS_1,
                        SerialPort.PARITY_NONE );

                InputStream in = sserialPort.getInputStream();

                ( new Thread( new SerialReader(in, this.dataHandler) ) ).start();

            } else {
                System.out.println( "Error: Only serial ports are handled by this example." );
            }
    }

}


