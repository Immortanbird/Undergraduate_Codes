import java.util.Scanner;

public class Main extends Test{
    @SuppressWarnings("InfiniteLoopStatement")
    public static void main(String[] args) {
        Control control = new Control();

        int[] servedFloors0 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        int[] servedFloors1 = {0, 4, 5, 6, 7, 8, 9, 10, 11};
        int[] servedFloors2 = {10, 11, 12, 13, 14, 15, 16, 17, 18};
        int[] servedFloors3 = {12, 13, 14, 15, 16, 17, 18, 19, 20};
        initElevator(control, 0, servedFloors0, 10, 1000, 800, 1200, 0);
        initElevator(control, 1, servedFloors1, 10, 1000, 800, 1200, 0);
        initElevator(control, 2, servedFloors2, 10, 1000, 800, 1200, 10);
        initElevator(control, 3, servedFloors3, 10, 1000, 800, 1200, 12);

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