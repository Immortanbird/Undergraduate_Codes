import java.util.Scanner;

public class Main extends Test{
    @SuppressWarnings("InfiniteLoopStatement")
    public static void main(String[] args) {
        Control control = new Control();

        int[] servedFloors0 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        int[] servedFloors1 = {0, 1, 2, 3, 4, 5};
        int[] servedFloors2 = {9, 10, 11, 12, 13, 14, 15};
        int[] servedFloors3 = {0, 1, 2, 3, 4, 5, 16, 17, 18, 19, 20};

        configure(control, 0, servedFloors0,8, 800, 1500, 2000, 1);
        configure(control, 1, servedFloors1,10, 1000, 1500, 2000, 4);
        configure(control, 2, servedFloors2,6, 600, 1500, 2000, 9);
        configure(control, 3, servedFloors3,15, 1500, 1500, 2000, 20);

        control.start(0);
        control.start(1);
        control.start(2);
        control.start(3);

        int floor, dest, weight;
        while (true) {
            Scanner scanner = new Scanner(System.in);
            floor = scanner.nextInt();
            dest = scanner.nextInt();
            weight = scanner.nextInt();
            addWaiting(control, floor, weight, dest);
        }
    }
}
