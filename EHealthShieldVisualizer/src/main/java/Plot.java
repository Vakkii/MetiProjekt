import javax.swing.JFrame;
import javax.swing.JPanel;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.DefaultOHLCDataset;
import org.jfree.data.xy.DefaultXYDataset;

import java.awt.*;

public class Plot extends JPanel{
    private JFreeChart chart;
    public Plot(String name, DefaultXYDataset defDs, int width) {
        this.setLayout(new GridLayout());
        chart =
                ChartFactory.createXYLineChart(name,
                        "", " ", defDs, PlotOrientation.VERTICAL, false, false,
                        false);

        this.add(new ChartPanel(chart, width, (int)(width*2), -100, -100, 1000, 2000,
                false, true, true, true, false, true));
    }
    public void update(DefaultXYDataset dataset){
        this.chart.getXYPlot().setDataset(dataset);
    }
}
