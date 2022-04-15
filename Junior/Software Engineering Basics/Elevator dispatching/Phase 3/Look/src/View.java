import javax.swing.*;
import javax.swing.border.MatteBorder;
import java.awt.*;
import java.util.Set;

public class View{
    private final Control control;

    private final JFrame frame;
    private final JPanel floorStatusPanel;
    private final JPanel[] elevatorPanel;

    private final JLabel[][] floorNo;
    private final JLabel[][] elevatorStatus;
    private final JLabel[] floorStatus;

    View(Control control) {
        this.control = control;

        frame = new JFrame();

        floorStatusPanel = new JPanel();
        elevatorPanel = new JPanel[4];

        floorNo        = new JLabel[4][22];
        elevatorStatus = new JLabel[4][22];
        floorStatus    = new JLabel[21];

        init();
    }

    private void init() {
        frame.setTitle("Elevator Dispatcher");
        frame.setSize(1280, 720);
        frame.setResizable(false);
        frame.setLocationRelativeTo(null);
        frame.setLayout(new GridLayout(1, 5));

        initElevators();
        initFloorStatus();

        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private void initElevators() {
        for (int i=0; i<4; i++) {
            elevatorPanel[i] = new JPanel();

            elevatorPanel[i].setLayout((new GridLayout(22, 2)));
            elevatorPanel[i].setBorder(new MatteBorder(1, 1, 1, 0, Color.orange));

            floorNo[i][21] = new JLabel("Elevator" + ' ' + (i + 1), SwingConstants.CENTER);
            elevatorStatus[i][21] = new JLabel("", SwingConstants.CENTER);
            elevatorPanel[i].add(floorNo[i][21]);
            elevatorPanel[i].add(elevatorStatus[i][21]);

            for (int j=20; j>=0; j--) {
                if (j == 0)
                    floorNo[i][j] = new JLabel(String.valueOf(-1), SwingConstants.CENTER);
                else
                    floorNo[i][j] = new JLabel(String.valueOf(j), SwingConstants.CENTER);

                floorNo[i][j].setBorder(new MatteBorder(1, 0, 0, 0, Color.orange));
                elevatorPanel[i].add(floorNo[i][j]);

                elevatorStatus[i][j] = new JLabel();
                elevatorStatus[i][j].setBorder(new MatteBorder(1, 1, 0, 0, Color.orange));
                elevatorStatus[i][j].setOpaque(true);
                elevatorStatus[i][j].setBackground(Color.BLACK);
                elevatorPanel[i].add(elevatorStatus[i][j]);
            }
            frame.add(elevatorPanel[i]);
        }
    }

    private void initFloorStatus() {
        floorStatusPanel.setLayout(new GridLayout(22, 1));
        floorStatusPanel.setBorder(new MatteBorder(1, 1, 1, 0, Color.orange));
        floorStatusPanel.add(new JLabel("Floor status", SwingConstants.CENTER));

        for (int i=20; i>=0; i--) {
            floorStatus[i] = new JLabel("", SwingConstants.CENTER);
            floorStatus[i].setBorder(new MatteBorder(1, 0, 0, 0, Color.orange));
            floorStatusPanel.add(floorStatus[i]);
        }

        frame.add(floorStatusPanel);
    }

    public void displayServedFloors(int elevator, Set<Integer> servedFloors) {
        for (int i=0; i<21; i++) {
            if (servedFloors.contains(i))
                elevatorStatus[elevator][i].setBackground(Color.GRAY);
            else
                elevatorStatus[elevator][i].setBackground(Color.BLACK);
        }
    }

    public void displayFloorStatus(int floor, int upWaiting, int downWaiting) {
        floorStatus[floor].setText("Up: " + upWaiting + ' ' + "Down: " + downWaiting);
    }

    public void displayElevator(int elevator, int floor, Color color) {
        elevatorStatus[elevator][floor].setBackground(color);
    }
}
