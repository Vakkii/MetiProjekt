import javax.swing.*;
public class Main {

    public static void main(String[] args){
        //SerialConnection Handling class
        DataHandler dh = new DataHandler();
        SerialConnectionHandler sc = new SerialConnectionHandler(dh);
        //GUI Handling
        JFrame frame = new JFrame("EHealthShieldVisualizer");

        
        MainFrame mainFrame = new MainFrame(sc, dh);
        frame.setContentPane(mainFrame.getMainPanel());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
        new Thread(mainFrame).start();


    }

}
